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
#include "NEL_PacketSender.hpp"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"
#include "ip/IpEndpointName.h"

#define IP_MTU_SIZE 1536

void osc::NEL_PacketSender::sendOSC(const std::string& msg , const float& arg)
{
  char buffer[OUTPUT_BUFFER_SIZE];
  osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
  p << osc::BeginBundleImmediate << osc::BeginMessage( msg.c_str() ) << arg << osc::EndMessage << osc::EndBundle;
  transmitSocket.Send( p.Data(), p.Size() );
  
}

void osc::NEL_PacketSender::sendOSC(const std::string& msg , const std::vector<float>& args)
{
  char buffer[OUTPUT_BUFFER_SIZE];
  osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
  p << osc::BeginBundleImmediate << osc::BeginMessage( msg.c_str() );
  
  for (float f : args) {
    p << f;
  }
  p << osc::EndMessage << osc::EndBundle;
  transmitSocket.Send( p.Data(), p.Size() );
  
}

void osc::NEL_PacketSender::changeTargetHost( const char * hostname ) {
  
  if ( hostname != nullptr) {
    m_hostname = hostname;
    transmitSocket.Connect ( IpEndpointName ( m_hostname , m_targetPort ) );
  }
}


void osc::NEL_PacketSender::changeTargetPort( int newPort ) {
  m_targetPort = newPort;
  transmitSocket.Connect( IpEndpointName ( m_hostname , m_targetPort ) );
}

void osc::NEL_PacketSender::setTargetPortForKyma() {
  m_targetPort = KYMA_RCV_PORT;
}



