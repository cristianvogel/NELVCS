//
//  NEL_OSC_Methods.hpp
//  NEL_VirtualControlSurface-macOS
//
//  Created by Cristian Andres Vogel on 12/07/2020.
//
#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "NEL_mDNS_IPExtract.h"
#include "NEL_PacketListener.hpp"
#include "NEL_PacketSender.hpp"
#include <iostream>
#include <cstring>

#include <mutex>

class NEL_OSC
{
public:
  NEL_OSC( const char * host , int port );
  ~NEL_OSC();
    
  const char * m_targetHost;
  int m_listenerPort;
  int m_targetPort;
  std::unique_ptr<std::vector<std::string>> messageLog;
  
  NEL_PacketListener udpListener;
  std::unique_ptr<osc::NEL_PacketSender> udpSender;
  
  void launchNetworkingThread();
  void initOSCSender( const char* IP ,  int port );
  void runOSCListener ( int port);
  void initKyma(); 
  bool oscSendActive {true}; //todo: make UI button to disable OSC activity
  
  std::mutex mtx; // mutex for critical section in network thread
  
  std::string getLatestMessage();
  const std::vector<float> getLatestFloatArgs();
  bool getHardwareStatus();
  void disconnectHardware();
  std::string getBeSlimeIP();
  std::string getBeSlimeName();
  
  std::vector <std::string> dialSendAddress;
  
  bool tryToOpenListener();
  
  std::string remoteAddressToString( const char *  );
  
  
private:
  mDNS zeroConf;

};





