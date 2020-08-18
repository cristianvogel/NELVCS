//
//  NELDoubleDial.hpp
//  APP
//
//  Created by Cristian Andres Vogel on 02/07/2020.
//

#pragma once

#include <stdio.h>
#include "IControl.h"
#include "IPlugTimer.h"
#include "NEL_VCS_Constants.h"
#include <atomic>


//using namespace iplug;
using namespace iplug::igraphics;

class NEL_DualDial : public IKnobControlBase
{
public:
  NEL_DualDial(
                const IRECT& bounds
                , const std::initializer_list< int >& params
                , const IColor& stop1 = getSwatch( Lunada, 0)
                , const IColor& stop2 = getSwatch( Lunada, 1)
                , const IColor& stop3 = getSwatch( Lunada, 2)
                , int flashRate = 0
                , float a1 = -135.f, float a2 = 135.f, float aAnchor = -135.f
                );
  
  ~NEL_DualDial();
   
  std::atomic<int> atomicTimerMillis;
  std::atomic<int> atomicPulseTimerScalar{ 1000 }; // todo: use this for host BPM sync
  
  const int scalePulseRate(const float scale, bool set = true );
  const int& setPulseRate(const int);
  void setPulseRate(const float);
  const int& getPulseRate( );
  
  iplug::Timer* doubleDialPulseTimer;
  std::function<void( iplug::Timer & )> pulseTimerFunc = nullptr;
  const bool& togglePulse( bool );
  
  bool pulse [2] = { std::atomic<bool>{false}, std::atomic<bool>{false} };
  
  void Draw(IGraphics& p) override;
  void OnMouseDrag(float x, float y, float dX, float dY, const IMouseMod& mod) override;
  void OnMouseWheel(float x, float y, const IMouseMod& mod, float d) override;
  
  std::vector<ISVG> buttonStates;
  NEL_DualDial* setupButtonStateSVG( const ISVG& on , const ISVG& off);

  int tickMarks {10};

  
  IRECT* getDialBounds();
  
private:
  
  const int getTimerMillis();
  const float getTimerMillisF();
  
  double mMouseDragValue = 0;
  float mTrackToHandleDistance = 4.f;
  float mInnerPointerFrac = 0.1f;
  float mOuterPointerFrac = 1.f;
  float mPointerThickness = 2.5f;
  float mAngle1, mAngle2;
  float mTrackSize = static_cast<float> ( fmax( 4, 20 - NBR_DUALDIALS) );
  float mAnchorAngle; // for bipolar arc
  
  IColor colourStop1;
  IColor colourStop2;
  IColor colourStop3;
  int m_pulseRate = 0;
  
};

