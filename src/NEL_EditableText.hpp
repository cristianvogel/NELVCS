//
//  NEL_EditableText.hpp
//  NEL_VirtualControlSurface-macOS
//
//  Created by Cristian Andres Vogel on 06/08/2020.
//

#ifndef NEL_EditableText_hpp
#define NEL_EditableText_hpp

#include <stdio.h>
#include <stdio.h>
#include "IControl.h"
#include "NEL_VCS_Constants.h"
#include "NEL_VCS_Enums.hpp"


using namespace iplug::igraphics;

class NEL_TextField : public IEditableTextControl
{
public:
 
  NEL_TextField(
                const IRECT& bounds,
                IActionFunction aF = nullptr,
                const char * entry = "",
                const IText& text = DEFAULT_CONSOLE_TEXT,
                const char * toolTip = "",
                const bool isEditable = true,
                const IColor& bgColor = COLOR_TRANSPARENT
                );

  void OnInit() override;
  void OnMouseOver(float x, float y, const IMouseMod& mod) override;
  void OnMouseOut() override;
  void OnMouseDown(float x, float y, const IMouseMod& mod) override;
  void OnTextEntryCompletion(const char* str, int valIdx) override;

protected:
  bool m_isEditable;
};


#endif /* NEL_EditableText_hpp */


