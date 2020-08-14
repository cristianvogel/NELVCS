/*
  oscpack -- Open Sound Control (OSC) packet manipulation library
    http://www.rossbencina.com/code/oscpack

    Copyright (c) 2004-2013 Ross Bencina <rossb@audiomulch.com>

  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files
  (the "Software"), to deal in the Software without restriction,
  including without limitation the rights to use, copy, modify, merge,
  publish, distribute, sublicense, and/or sell copies of the Software,
  and to permit persons to whom the Software is furnished to do so,
  subject to the following conditions:

  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
  ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/*
  The text above constitutes the entire oscpack license; however,
  the oscpack developer(s) also make the following non-binding requests:

  Any person wishing to distribute modifications to the Software is
  requested to send the modifications to the original developer so that
  they can be incorporated into the canonical version. It is also
  requested that these non-binding requests be included whenever the
  above license is reproduced.
*/

#pragma once

#include <cstdlib>
#include <cstring>
#include <iostream>

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"
#include "ip/IpEndpointName.h"

#define OUTPUT_BUFFER_SIZE 1536
#define KYMA_RCV_PORT 8000

namespace osc {



  class NEL_PacketSender
  {
  public:
    NEL_PacketSender(  const char * host, int port) :
      transmitSocket( IpEndpointName( host, port ) )
    , m_targetPort( port )
    , m_hostname ( host )
    { }
    
    ~NEL_PacketSender() { }
  
    friend class NEL_OSC;
    
    UdpTransmitSocket transmitSocket;
    
    void sendOSC(const std::string& msg , const float& arg);
    void sendOSC(const std::string& msg , const std::vector<float>& args);
    
    void changeTargetHost( const char * hostname );
    void changeTargetPort( int newPort );
    void setTargetPortForKyma();
    void setTargetPort(int newPort) { m_targetPort = newPort; }
    

    
  protected:
    int m_targetPort;
    const char * m_hostname;
    
  };

}
