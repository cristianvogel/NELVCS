#pragma once


#include "IPlug_include_in_plug_hdr.h"
#include "NEL_VCS_Constants.h"
#include "IconsForkAwesome.h"
#include "NEL_OSC_Methods.hpp"
#include "GlobSeqHelpers.h"
#include "NEL_VCS_Enums.hpp"
#include "NEL_DualDial.h"
#include "NEL_GlyphButton.hpp"
#include "NEL_EditableText.hpp"
#include <atomic>

const int kNumPresets = 1;

#pragma mark NEL_enumerators


class NELVirtualControlSurface final : public iplug::Plugin
{
  
public:
  NELVirtualControlSurface(const iplug::InstanceInfo& info);
  ~NELVirtualControlSurface();
  
  void OnIdle() override;
  
  NEL_OSC nelosc;
  
  std::string prevMsg = "";
  std::string beSlimeName = "";
 
  std::string consoleText = "NEL VCS v1.0";
  
  std::string beSlimeIP = "";
  std::atomic_bool beSlimeConnected {false};
  
  typedef std::string DialAddr;
  
  bool hideReadouts { true } ;
  bool hover {false};
  
  
  IText numericDisplayTextDef;
  IText ledOn;
  IText ledOff;
   
  IAnimationFunction unGhostText =
    [this] (IControl* pCaller) {
     pCaller->SetDisabled(false);
     auto progress = pCaller->GetAnimationProgress();
      if(progress>1.0f) {
        pCaller->SetDisabled(true);
        pCaller->SetMouseOverWhenDisabled(true);
        pCaller->OnEndAnimation(); return;
      }
    };
  
  IAnimationFunction ghostText =
    [this] (IControl* pCaller) {
     pCaller->SetDisabled(true);
     auto progress = pCaller->GetAnimationProgress();
      if(progress>1.0f) {
        pCaller->SetDisabled(false);
        pCaller->OnEndAnimation(); return;
      }
    };
  
  void defaultConsoleText();
  void updatesFromIncomingOSC();
  void updateNumericDisplays();
  void hideNumericDisplays( const bool );
  std::unique_ptr<GlobSeqHelpers> gsh = std::make_unique<GlobSeqHelpers>();

  
  
  private:
  bool m_noNetwork = false;
  
  
#if IPLUG_DSP // http://bit.ly/2S64BDd
  void ProcessBlock(iplug::sample** inputs, iplug::sample** outputs, int nFrames) override;
#endif
};

