//
//  NEL_EditableText.cpp
//  NEL_VirtualControlSurface-macOS
//
//  Created by Cristian Andres Vogel on 06/08/2020.
//

#include "IControl.h"
#include "NEL_EditableText.hpp"
#include "NEL_VCS_Enums.hpp"

using namespace iplug::igraphics;

NEL_TextField::NEL_TextField(
                             const IRECT& bounds,
                             IActionFunction aF,
                             const char * entry,
                             const IText& text,
                             const char * kToolTip,
                             const bool isEditable,
                             const IColor& bgColor
                             )
: IEditableTextControl(bounds, entry, text)
{
  SetTooltip(kToolTip);
  SetActionFunction(aF);
  m_isEditable = isEditable;
}

void NEL_TextField::OnInit() { SetBoundsBasedOnStr(); }

void NEL_TextField::OnMouseOver( float x, float y, const IMouseMod& mod)
{
  SetText( DEFAULT_CONSOLE_TEXT.WithFGColor(COLOR_WHITE));
}

void NEL_TextField::OnMouseOut()
{
   SetText( DEFAULT_CONSOLE_TEXT );
}

void NEL_TextField::OnMouseDown(float x, float y, const IMouseMod& mod) {
  
  if (m_isEditable) {
    IText t = DEFAULT_CONSOLE_TEXT.WithTEColors(COLOR_TRANSPARENT, COLOR_WHITE);
    GetUI()->CreateTextEntry(*this, t, mRECT, GetStr());
  }
}

void NEL_TextField::OnTextEntryCompletion(const char * str, int valIdx){
  {
    SetStr(str);
    SetDirty(true);
  }
}
