//
//  mDNS_IPExtract.h
//  NEL_VirtualControlSurface-macOS
//  Bonjour browser and IP resolver
//  Created by Cristian Andres Vogel on 17/07/2020.
//
#pragma once

#ifndef mDNS_IPExtract_h
#define mDNS_IPExtract_h

#include <dns_sd.h>
#include <arpa/inet.h>


static int addr_rslv_lock = 0;
static std::string extractedIP{""};
static std::string hostName{"localhost"};
/**
* Represents a "lock" held by 'resolve_callback' for as long as it takes
* 'addrinfo_callback' to report that all IP Addresses associated to a hostname
* have been processed.
* '0' means "lock not held"
* '1' means "lock held"
*/


class mDNS {

  /**
   * Handles replies to queries initiated by 'DNSServiceGetAddrInfo'.
   * IP Addresses are extracted from the replies and inserted into the zresource
   * they belong to.
   */
  static void
  addrinfo_callback(DNSServiceRef sdRef,
                    DNSServiceFlags flags,
                    uint32_t interfaceIndex,
                    DNSServiceErrorType errorCode,
                    const char *hostname,
                    const struct sockaddr *address,
                    uint32_t ttl,
                    void *context);


  /**
   * Handles replies to queries initiated by 'DNSServiceResolve'.
   * Hostnames and TXT Records are extracted from the replies and inserted into
   * the zresource they belong to. A query for IP Addresses associated with the
   * resolved hostname is also initiated.
   */
  static void
  resolve_callback(DNSServiceRef resolveRef,
                   DNSServiceFlags flags,
                   uint32_t interface,
                   DNSServiceErrorType errorCode,
                   const char *fullname,
                   const char *hosttarget,
                   uint16_t port,
                   uint16_t txtLen,
                   const unsigned char *txtRecord,
                   void *context);


  /**
   * Handles replies to queries initiated by 'DNSServiceBrowse'.
   * A zresource is created for each service discovered. Services are then
   * resolved. As part of the resolution process, the zresource is updated with
   * service name, hostname, TXT record, and IP address information.
   */
  static void
  browse_callback(DNSServiceRef browseRef,
                  DNSServiceFlags flags,
                  uint32_t interfaceIndex,
                  DNSServiceErrorType errorCode,
                  const char *name,
                  const char *type,
                  const char *domain,
                  void *context);

  /**
   * Initiates browsing for mDNS services.
   * this function should serve as the main loop for
   * a thread dedicated to mDNS operations.
   */
  void mdns_thread_func();
  
  
public:

  void init();
  std::string addressToString();
  std::string hostNameToString();
};

#endif /* mDNS_IPExtract_h */
