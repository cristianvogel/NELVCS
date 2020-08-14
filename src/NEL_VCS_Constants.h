//
//  NEL_VCS_Constants.h
//  NEL_VirtualControlSurface-macOS
//
//  Created by Cristian Andres Vogel on 07/07/2020.
//
#pragma once
#include <map>
#include "IPlug_include_in_plug_hdr.h"

using namespace iplug::igraphics;


#pragma mark NEL_Colours
const IColor NEL_TUNGSTEN(255, 27, 27, 30);
const IColor NEL_TUNGSTEN_FGBlend( 255, 230,  87,  74  );
const IColor NEL_MEMARIANI_stop1(255, 78, 141, 153);
const IColor NEL_MEMARIANI_stop2(255, 107, 107, 131);
const IColor NEL_MEMARIANI_stop3(255, 170, 75, 107);
const IColor NEL_LUNADA_stop1(255, 84, 51, 255);
const IColor NEL_LUNADA_stop2(255, 32, 189, 255);
const IColor NEL_LUNADA_stop3(255, 165, 254, 203);

enum Swatches {
  Memariani = 0,
  Lunada,
  Tungsten,
  Swatches_size
};

static IColor getSwatch(int gradient, int stop)
{
  switch (gradient) {
    case Memariani:
    switch (stop) {
      case 0: return NEL_MEMARIANI_stop1;
      case 1: return NEL_MEMARIANI_stop2;
      case 2: return NEL_MEMARIANI_stop3;
      default:
        assert(0);
        return NEL_MEMARIANI_stop1;
      }
      case Lunada:
         switch (stop) {
           case 0: return NEL_LUNADA_stop1;
           case 1: return NEL_LUNADA_stop2;
           case 2: return NEL_LUNADA_stop3;
           default:
             assert(0);
             return NEL_LUNADA_stop1;
           }
  default:
         //assert(0);
         return NEL_MEMARIANI_stop1;
  }
}

static IVStyle rescanButtonStyle() {
  const IVStyle rescanButtonStyle
  {
    true, // Show label
    false, // Show value
    {
      COLOR_TRANSLUCENT, // Background
      COLOR_TRANSLUCENT, // Foreground
      COLOR_LIGHT_GRAY, // Pressed
      COLOR_TRANSPARENT, // Frame
      DEFAULT_HLCOLOR, // Highlight
      DEFAULT_SHCOLOR, // Shadow
      COLOR_BLACK, // Extra 1
      DEFAULT_X2COLOR, // Extra 2
      DEFAULT_X3COLOR  // Extra 3
    }, // Colors
    IText(
          12.f,
          COLOR_LIGHT_GRAY,
          "Menlo",
          EAlign::Center,
          EVAlign::Middle,
          0.f,
          DEFAULT_TEXTENTRY_BGCOLOR,
          DEFAULT_TEXTENTRY_FGCOLOR
          ) // Label text
  };
  return rescanButtonStyle;
}

static IVStyle prefsButtonStyle() {
  const IVStyle prefsButtonStyle
  {
    true, // Show label
    false, // Show value
    {
      COLOR_TRANSPARENT, // Background
      COLOR_TRANSLUCENT, // Foreground
      COLOR_LIGHT_GRAY, // Pressed
      COLOR_LIGHT_GRAY, // Frame
      DEFAULT_HLCOLOR, // Highlight
      DEFAULT_SHCOLOR, // Shadow
      COLOR_BLACK, // Extra 1
      DEFAULT_X2COLOR, // Extra 2
      DEFAULT_X3COLOR  // Extra 3
    }, // Colors
    IText(
          12.f,
          COLOR_LIGHT_GRAY,
          "Menlo",
          EAlign::Center,
          EVAlign::Middle,
          0.f,
          COLOR_TRANSPARENT,
          COLOR_TRANSPARENT
          ) // Label text
  };
  return prefsButtonStyle;
}

const IText GLYPH
      {16.f, NEL_TUNGSTEN_FGBlend, "ForkAwesome"};

const IText DEFAULT_CONSOLE_TEXT
      { 11.f, NEL_TUNGSTEN_FGBlend, "Menlo" };

