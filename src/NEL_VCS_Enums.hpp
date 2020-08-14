//
//  NEL_VCS_Enums.hpp
//  NEL_VirtualControlSurface-macOS
//
//  Created by Cristian Andres Vogel on 28/07/2020.
//

#pragma once
#ifndef NEL_VCS_Enums_hpp
#define NEL_VCS_Enums_hpp

#include "NEL_VCS_Constants.h"

enum EParams
{
  kNetstatus = 0,
  kReScan,
  kSendPort = 9090,
  kListenPort = 8080,
  kDualDialInner = 4,
  kDualDialOuter = kDualDialInner + NBR_DUALDIALS,
  kDualDialPulse = kDualDialInner + NBR_DUALDIALS + 1,
  kNumParams = kDualDialPulse + NBR_DUALDIALS
};

enum EControlTags
{
  kCtrlNetStatus = 100,
  kCtrlReScan,
  kCtrlFluxDial,
  kNumCtrlTags = kCtrlFluxDial + NBR_DUALDIALS
};

enum EControlReadOutTags
{
  kCtrlReadInnerRing = 150,
  kCtrlReadOuterRing = kCtrlReadInnerRing + NBR_DUALDIALS
};

enum EControlDialTags
{
  kCtrlFluxDialInner = 200,
  kCtrlFluxDialOuter = kCtrlFluxDialInner + NBR_DUALDIALS,
  kNumCtrlFluxDials = kCtrlFluxDialOuter + NBR_DUALDIALS
};

enum EControlTextInputTags
{
  kCtrlTextInput = 300,
  kNumCtrlTextInputs = kCtrlTextInput + NBR_DUALDIALS
};

enum EStatusMisc
{
  kMsgScanning = 400,
  kMsgConnected,
  kNumStatusMisc
};

enum EDisplays
{
  kCtrlTagDisplay = 500,
  kCtrlPlot,
  kTargetPort,
  kTargetHost,
  kNumDisplays
};

enum EWidgets 
{
  kNoWidgets = 600,
  kAddressWidget,
  kPortWidget,
  kPresetsWidget,
  kNumWidgets = kNoWidgets + NBR_WIDGETS
};

static std::map<int, const char * > toolTips = {
  { kAddressWidget, "Message Config"},
  { kPortWidget, "Net Config"},
  { kPresetsWidget, "Presets" }
};




#endif /* NEL_VCS_Enums_hpp */
