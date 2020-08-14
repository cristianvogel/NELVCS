//
//  NEL_GlyphButton.cpp
//  NEL_VirtualControlSurface-macOS
//
//  Created by Cristian Andres Vogel on 04/08/2020.
//

#include "NEL_GlyphButton.hpp"
#include "NEL_VCS_Enums.hpp"

NEL_GlyphButton::NEL_GlyphButton(const IRECT& bounds, IActionFunction aF, const char* offText, const char* onText, const IText& text, const char * kToolTip, const IColor& bgColor)
: ITextControl(bounds, offText, text, bgColor)
, mOnText(onText)
, mOffText(offText)
{
  SetActionFunction(aF);
  mDblAsSingleClick = true;
  mIgnoreMouse = false;
  SetTooltip( kToolTip );
}

void NEL_GlyphButton::OnInit(){

  simulateOnMouseDown();
}

void NEL_GlyphButton::OnMouseOver(float x, float y, const IMouseMod& mod)
{
  mText = GLYPH.WithFGColor(COLOR_WHITE);
  ITextControl::OnMouseOver(x, y, mod);
  SetDirty(false);
}

void NEL_GlyphButton::OnMouseOut()
{
  mText = GLYPH;
  SetDirty(false);
}

void NEL_GlyphButton::OnMouseDown(float x, float y, const IMouseMod& mod)
{
  if (GetValue() < 0.5) {
    SetValue(1.);
    SetBlend(BLEND_25);
    
  }
  else {
    SetValue(0.);
    SetBlend(EBlend::Default);
  }
  
  SetDirty(true);
}

void NEL_GlyphButton::simulateOnMouseDown() {
  if (GetValue() < 0.5) {
    SetValue(1.);
    SetBlend(BLEND_25);
  }
  else {
    SetValue(0.);
    SetBlend(EBlend::Default);
  }
  
  SetDirty(true);
}

void NEL_GlyphButton::SetDirty(bool push, int valIdx)
{
  if(GetValue() > 0.5)
    SetStr(mOnText.Get());
  else
    SetStr(mOffText.Get());
  
  IControl::SetDirty(push);
}

NEL_GlyphButton* NEL_GlyphButton::SetOnText( const char*  glyph ) {
  mOnText.Set(glyph);
  return this;
}
NEL_GlyphButton* NEL_GlyphButton::SetOffText( const char* glyph ) {
  mOffText.Set(glyph);
  return this;
}
