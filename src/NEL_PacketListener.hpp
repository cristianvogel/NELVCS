//
//  packetListener.hpp
//  NEL_VirtualControlSurface-macOS
//
//  Created by Cristian Andres Vogel on 22/07/2020.
//

#pragma once

#include <iostream>
#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "ip/UdpSocket.h"
#include <vector>
#include <tuple>

class NEL_PacketListener : public osc::OscPacketListener {
  
public:
  
  NEL_PacketListener(  int , PacketListener& );
  ~NEL_PacketListener();
  
  
  const char * m_destinationHost;
  int m_listenerPort;
  std::unique_ptr<UdpListeningReceiveSocket> m_receiveSocket;
  
  std::atomic_bool messageReceived{false};
  std::atomic_bool hardwareConnected{false};
  
  const std::string getMostRecentMessage( );
  const std::string getMostRecentAddress( );
  const std::vector<float> getMostRecentFloatArgs( );
  
  void setMostRecentMessage( const std::string& );
  void setMostRecentAddress( const std::string& );
  void setMostRecentFloatArgs( const std::vector<float>& );
  
  void changeListenPort( int );
  
  std::mutex msgMutex;
  
  /*
      Messages recevied log, for debugging purposes or whatever.
      Only collects messages with address stems we haven't seen before
  */
  
  struct MessageLog {
    
    std::vector< std::pair < std::string ,  int  > >  m_log;
    MessageLog() { };
    ~MessageLog() { clear(); };
    
    
    // retrieve the number assoc with a message or return -1
    int getNumberFor( std::string msg) {
      for (std::pair< std::string ,  int > keyValue : m_log) {
        if (keyValue.first == msg) { return keyValue.second; }
      }
      return -1;
    }

    // add  data to the log don't let grow too big
    void addMessageData( std::string msg, int nbr ) {
      if (m_log.size() > 256) m_log.clear();
      if ( !contains(msg) ) m_log.push_back( {msg, nbr } )   ;
    }
    
    // returns false if the message has never been received
    bool contains( std::string msg ) {
      for (std::pair< std::string ,  int > keyValue : m_log) {
        if (keyValue.first == msg) return true;
      }
    return false;
    }
    
    //clear log
    void clear() {
      m_log.clear();
    }
    
  };

protected:
  void ProcessMessage( const osc::ReceivedMessage& m,
                                const IpEndpointName& remoteEndpoint ) ;
  
  void openListenerSocket ( PacketListener& listener );
  friend class NEL_OSC;
  std::vector<float> m_floatArgs;
  std::string mostRecentMessage{""};
  std::string mostRecentAddr{""};
  MessageLog log;
};




