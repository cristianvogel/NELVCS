//
//  packetListener.cpp
//  NEL_VirtualControlSurface-macOS
//
//  Created by Cristian Andres Vogel on 22/07/2020.
//

#include "NEL_PacketListener.hpp"
#include <vector>
#include <sstream>

#define LOCALHOST "127.0.0.1"


NEL_PacketListener::NEL_PacketListener(  int port , PacketListener& listener) : m_listenerPort(port) {
 
  openListenerSocket( listener ) ;
  
};

NEL_PacketListener::~NEL_PacketListener() {
  //m_receiveSocket->Break();
  m_receiveSocket.release();
}

void NEL_PacketListener::openListenerSocket ( PacketListener& listener ) {
  try {
          m_receiveSocket = std::make_unique<UdpListeningReceiveSocket>(
                 IpEndpointName( IpEndpointName::ANY_ADDRESS, m_listenerPort ),
                 &listener );

    
     } catch (std::runtime_error e) {

       setMostRecentMessage( u8"\u26A0 listener port "+ std::to_string(m_listenerPort)+" is occupied");
       m_receiveSocket = nullptr;
     }
}

void NEL_PacketListener::changeListenPort ( int newPort ) {
  m_listenerPort = newPort;
  if (m_receiveSocket != nullptr) {
      // m_receiveSocket->Break();
      //openListenerSocket( &listener );
  }
}

void NEL_PacketListener::ProcessMessage(const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint)  {
 
  
    const char * addr = m.AddressPattern();
 
    try{
        // example of parsing single messages. osc::OsckPacketListener
        // handles the bundle traversal.
        
       
        log.addMessageData( addr, m.ArgumentCount() );
        
        if( std::strcmp( addr, "/osc/response_from" ) == 0 ){
            // kyma protocol handshake, go bidi
            osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
            osc::int32 a1;
            args >> a1 >> osc::EndMessage;
            
            setMostRecentMessage( u8"\u25B6Paca(rana) connected" );
            hardwareConnected = true;
            
        } else {
            // example #2 -- argument iterator interface, supports
            // reflection for overloaded messages (eg you can call
            // (*arg)->IsBool() to check if a bool was passed etc).
          
            osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
            if( arg == m.ArgumentsEnd() )
                         throw osc::MissingArgumentException();
                        
          std::vector<float> floatArgs;
          std::basic_stringstream<char> msgAndArgs;
          
          while ( arg != m.ArgumentsEnd() ) {
          if ( arg->IsFloat() ) { floatArgs.push_back( (arg++) -> AsFloat() ); }
          }
          
          setMostRecentFloatArgs( floatArgs );
          
          msgAndArgs << addr;
          for ( float f: floatArgs) {
           msgAndArgs << " " << f;
          }
          setMostRecentMessage(msgAndArgs.str());
        }
    } catch ( osc::Exception& e ) {
            // any parsing errors such as unexpected argument types, or
            // missing arguments get thrown as exceptions.
            std::cout << "error while parsing message: " << m.AddressPattern() << ": " << e.what() << "\n";
            messageReceived = false;
            setMostRecentMessage( u8"\u26A0 message error" );
    }
}

#pragma mark getters

void NEL_PacketListener::setMostRecentMessage( const std::string& msg ) {
  
  msgMutex.lock();
    mostRecentMessage = msg;
    messageReceived = true;
  msgMutex.unlock();
}

void NEL_PacketListener::setMostRecentFloatArgs(const std::vector<float>& floatArgs)
{
  msgMutex.lock();
  m_floatArgs.clear();
    std::copy(floatArgs.begin(), floatArgs.end(), std::back_inserter(m_floatArgs));
  msgMutex.unlock();
}

#pragma mark setters
const std::string NEL_PacketListener::getMostRecentMessage() {
  msgMutex.lock();
    std::string msg{ "" };
    msg = mostRecentMessage;
  msgMutex.unlock();
  return msg;
}

const std::string NEL_PacketListener::getMostRecentAddress() {
  msgMutex.lock();
    std::string addr{ "" };
    addr = mostRecentAddr;
  msgMutex.unlock();
  return addr;
}

//todo: figure out how to mutex lock this
const std::vector<float> NEL_PacketListener::getMostRecentFloatArgs() {
  std::vector<float> args;
  msgMutex.lock();
    std::copy(m_floatArgs.begin(), m_floatArgs.end(), std::back_inserter(args));
  msgMutex.unlock();
  return args;
}
