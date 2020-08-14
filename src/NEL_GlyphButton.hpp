//
//  NEL_GlyphButton.hpp
//  NEL_VirtualControlSurface-macOS
//
//  Created by Cristian Andres Vogel on 04/08/2020.
//

#pragma once

#ifndef NEL_GlyphButton_hpp
#define NEL_GlyphButton_hpp

#include <stdio.h>
#include "IControl.h"
#include "NEL_VCS_Constants.h"
#include "NEL_VCS_Enums.hpp"


using namespace iplug::igraphics;

class NEL_GlyphButton : public ITextControl
{
public:
 
  NEL_GlyphButton(const IRECT& bounds, IActionFunction aF = nullptr, const char* offText = "OFF", const char* onText = "ON", const IText& text = GLYPH, const char * = "config", const IColor& BGColor = COLOR_TRANSPARENT);

  void OnMouseDown(float x, float y, const IMouseMod& mod) override;
  void simulateOnMouseDown();
  void SetDirty(bool push, int valIdx = 0) override;
  void OnMouseOver(float x, float y, const IMouseMod& mod) override;
  void OnMouseOut() override;
  void OnInit() override;

  NEL_GlyphButton* SetOnText( const char* onText  );
  NEL_GlyphButton* SetOffText( const char* offText );
  
protected:
  WDL_String mOffText;
  WDL_String mOnText;
  IColor colourStop1;
  IColor colourStop2;
  IColor colourStop3;

};








#endif /* NEL_GlyphButton_hpp */
