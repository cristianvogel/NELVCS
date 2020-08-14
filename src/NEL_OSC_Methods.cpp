//
//  NEL_OSC.cpp
//  NEL_OSC-macOS
//
//  Created by Cristian Andres Vogel on 12/07/2020.
//


#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include "NEL_VCS_Constants.h"
#include "NEL_OSC_Methods.hpp"


NEL_OSC::NEL_OSC( const char * host  , int port  ) :
   udpListener (8080, udpListener) //default listener
  
 {
   m_targetHost = host ;
   m_listenerPort = DEFAULT_LISTENER_PORT;
   m_targetPort = DEFAULT_TARGET_PORT;
   messageLog = std::make_unique<std::vector<std::string>>(2);
   initOSCSender("localhost", m_targetPort); //default sender
   
   for (int i = 0; i<= NBR_DUALDIALS; i++) {
     dialSendAddress.push_back( DEFAULT_DIAL_ADDRESS + std::to_string( i ) );
   }
 };
 NEL_OSC::~NEL_OSC() {  }; // to-do: close ports

#pragma mark setup

/**
* mDNS discovery thread
*/
void NEL_OSC::launchNetworkingThread(){
  std::thread slimeThread( [this] () { zeroConf.init(); } );
  std::thread listener ( [this] () { runOSCListener(  m_listenerPort  ); } );
  slimeThread.detach();
  listener.detach();
}

void NEL_OSC::runOSCListener ( int port ) {

  udpListener.m_receiveSocket->Run();

}

// prob not very good idea to detach another networking thread
// todo: learn how to break a currently active zeroconf networking thread
bool NEL_OSC::tryToOpenListener() {
  udpListener.openListenerSocket( udpListener );
 // if (udpListener.m_receiveSocket != nullptr) { launchNetworkingThread(); }
  return (udpListener.m_receiveSocket != nullptr);
}

void NEL_OSC::initOSCSender( const char* IP, int port = KYMA_RCV_PORT ) {

if (udpSender == nullptr) {
  udpSender = std::make_unique<osc::NEL_PacketSender>(IP, port);
  }

}

void NEL_OSC::initKyma() {
  if (udpSender != nullptr ) {
  udpSender->setTargetPortForKyma();
  udpSender->changeTargetHost( getBeSlimeName().c_str() );
  udpSender->transmitSocket.SetEnableBroadcast(true);
  udpSender->sendOSC("/osc/respond_to", m_listenerPort); //hardware handshake should receive /osc/response_from
  }
}

 
#pragma mark getters

std::string NEL_OSC::remoteAddressToString( const char * remoteAddress ) {
  char *addy = nullptr;
  udpSender->transmitSocket.LocalEndpointFor(remoteAddress).AddressAsString(addy);
  return static_cast<std::string>(addy);
}


std::string NEL_OSC::getLatestMessage() {
  
  if ( udpListener.messageReceived && !(udpListener.getMostRecentMessage().empty()) )  return udpListener.getMostRecentMessage();
  else return "";
}

const std::vector<float> NEL_OSC::getLatestFloatArgs() {
  
  return udpListener.getMostRecentFloatArgs();
}

std::string NEL_OSC::getBeSlimeIP() {
  mtx.lock();
  std::string IP = zeroConf.addressToString();
  if (IP == "0.0.0.0") IP = "127.0.0.1" ;
  mtx.unlock();
  return IP;
}

std::string NEL_OSC::getBeSlimeName() {
  mtx.lock();
  std::string n {""};
  n = zeroConf.hostNameToString();
  mtx.unlock();
  return n;
}

void NEL_OSC::disconnectHardware() {
  udpListener.hardwareConnected = false;
}

bool NEL_OSC::getHardwareStatus() {
  return udpListener.hardwareConnected;
}


