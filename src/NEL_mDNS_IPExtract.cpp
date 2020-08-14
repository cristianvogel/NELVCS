//
//  mDNS_IPExtract.cpp
//  NEL_VirtualControlSurface-macOS
//  Bonjour browser and IP resolver
//  Created by Cristian Andres Vogel on 17/07/2020.
//

// * mDNS IP extract based on
// * dnssd-mdns.c
// *
// * Created on: Apr 26, 2017
// *     Author: hkr
// *
// * Provides mDNS service discovery and resolution for systems using DNS-SD. The
// * functionality is equivalent to what 'avahi-mdns.c' provides for systems using
// * Avahi.
// *
// * The goal is to provide functionality for macOS systems, while following
// * the "thread model" used in 'avahi-mdns.c' and avoiding libdispatch features
// * to make it easier to port to non-macOS systems using DNS-SD.
// */

#include <stdio.h>
#include <iostream>
#include <string.h>
#include "NEL_mDNS_IPExtract.h"


/**
 * Handles replies to queries initiated by 'DNSServiceGetAddrInfo'.
 * IP Addresses are extracted from the replies and inserted into the zresource
 * they belong to.
 */

void mDNS::init() {
  mdns_thread_func();
}

std::string mDNS::addressToString() {
  return extractedIP;
}

std::string mDNS::hostNameToString() {
  return hostName;
}

void mDNS::addrinfo_callback(DNSServiceRef sdRef,
                  DNSServiceFlags flags,
                  uint32_t interfaceIndex,
                  DNSServiceErrorType errorCode,
                  const char *inHostname,
                  const struct sockaddr *address,
                  uint32_t ttl,
                  void *context)
{
    if (errorCode != kDNSServiceErr_NoError) {
        fprintf(stderr, "(Browser) %d\n", errorCode);
        addr_rslv_lock = 0;
    } else {
         if (flags & kDNSServiceFlagsAdd) {
          //std::cout << "hostname: " << hostname << std::endl;
           hostName = inHostname;
           
           // Extract IPv4 address
           //https://stackoverflow.com/questions/1276294/getting-ipv4-address-from-a-sockaddr-structure
          struct sockaddr_in *addr_in = (struct sockaddr_in *) address;
          char *s = inet_ntoa(addr_in->sin_addr);
          extractedIP = s;
          printf("IP address: %s\n", s);
          //addr_rslv_lock = strcmp(s,"0.0.0.0") == 0 ? 1 : 0;
        }
      if (!(flags & kDNSServiceFlagsAdd)) {
        //service removed
        extractedIP = "127.0.0.1";
        hostName = "localhost";
      }
      
      
      
    }
  // If there are no more callbacks expected, release 'addr_rslv_lock'.
         //addr_rslv_lock = flags & kDNSServiceFlagsMoreComing;
}

/**
 * Handles replies to queries initiated by 'DNSServiceResolve'.
 * Hostnames and TXT Records are extracted from the replies and inserted into
 * the zresource they belong to. A query for IP Addresses associated with the
 * resolved hostname is also initiated.
 */
void mDNS::resolve_callback(DNSServiceRef resolveRef,
                 DNSServiceFlags flags,
                 uint32_t interface,
                 DNSServiceErrorType errorCode,
                 const char *fullname,
                 const char *hosttarget,
                 uint16_t port,
                 uint16_t txtLen,
                 const unsigned char *txtRecord,
                 void *context)
{
    
    if (errorCode != kDNSServiceErr_NoError) {
        fprintf(stderr, "(Browser) %d\n", errorCode);
    } else {
        // Query for IP Address.
        DNSServiceErrorType error;
        DNSServiceRef  addressRef;
        error = DNSServiceGetAddrInfo(&addressRef,
                                      0,                    // no flags
                                      0,                    // all network interfaces
                                      kDNSServiceProtocol_IPv4 | kDNSServiceProtocol_IPv6,
                                      hosttarget,           // hostname
                                      addrinfo_callback,    // callback function
                                      NULL);             // zresource as context
      
      
      
        if (error == kDNSServiceErr_NoError) {
            addr_rslv_lock = 1;
            // 'DNSServiceProcessResult' blocks until the DNS-SD daemon has
            // data available for reading. The thread will wait here until
            // the daemon has received a response to the query asking for the
            // IP Addresses belonging to the hostname. When the daemon has
            // received this information, 'addrinfo_callback' will be called.
            // 'addrinfo_callback' clears 'addr_rslv_lock' when all IP address
            // have been processed, breaking out of the 'while' and allowing the
            // thread to continue running.

           while (addr_rslv_lock && DNSServiceProcessResult(addressRef) == kDNSServiceErr_NoError) { continue; }
            
            DNSServiceRefDeallocate(addressRef);
        } else {
            fprintf(stderr, "Failed to resolve IP address for service '%s': %d\n", fullname, error);
        }
    }
}

/**
 * Handles replies to queries initiated by 'DNSServiceBrowse'.
 * A zresource is created for each service discovered. Services are then
 * resolved. As part of the resolution process, the zresource is updated with
 * service name, hostname, TXT record, and IP address information.
 */
void mDNS::browse_callback(DNSServiceRef browseRef,
                DNSServiceFlags flags,
                uint32_t interfaceIndex,
                DNSServiceErrorType errorCode,
                const char *name,
                const char *type,
                const char *domain,
                void *context)
{
  
    if (errorCode != kDNSServiceErr_NoError) {
        fprintf(stderr, "(Browser) %d\n", errorCode);
    } else {
        if (flags & kDNSServiceFlagsAdd) {
             // Resolve Service.
            DNSServiceErrorType error;
            DNSServiceRef  resolveRef;
            
            error = DNSServiceResolve(&resolveRef,
                                      0,                // no flags
                                      0,                // all network interfaces
                                      name,             // service name
                                      type,             // service type
                                      domain,           // domain
                                      resolve_callback, // callback function
                                      NULL);
            
            if (error == kDNSServiceErr_NoError) {
                // 'DNSServiceProcessResult' blocks until the DNS-SD daemon has
                // data available for reading. The thread will wait here until
                // the daemon has resolved the Service Name. When the daemon has
                // resolved the name, 'resolve_callback' will be called.
                DNSServiceProcessResult(resolveRef);
                
                DNSServiceRefDeallocate(resolveRef);
            } else {
                fprintf(stderr, "Failed to resolve service '%s': %d\n", name, error);
            }
        }
    }
}

/**
 * Initiates browsing for mDNS services.
 * this function should serve as the main loop for
 * a thread dedicated to mDNS operations.
 */
void mDNS::mdns_thread_func() {
    DNSServiceRef browseRef;
    size_t ret = 1;
    
    DNSServiceErrorType error = DNSServiceBrowse(&browseRef,
                                                 0,                // no flags
                                                 0,                // all network interfaces
                                                 "_ssh._tcp",     // service type for BeSlime
                                                 "local.",         // default domains , was "local.",
                                                 browse_callback,  // callback function
                                                 NULL);            // no context
    
    if (error == kDNSServiceErr_NoError) {
        // 'DNSServiceProcessResult' blocks until the DNS-SD daemon has data
        // available for reading. Since reference_client creates a thread for
        // this function, it is safe to wait at this call. When a Service Event
        // is received by the daemon, 'browse_callback' will be called.
        while (DNSServiceProcessResult(browseRef) == kDNSServiceErr_NoError) { continue; }
        
        DNSServiceRefDeallocate(browseRef);
        ret = 0;
    }
}

