/**
 * @file HSLAPixel.h
 *
 * @author University of Illinois CS 225 Course Staff
 * @version 2018r1-lab1 - Updated for CS 400
 */

#pragma once

#include <iostream>
#include <sstream>

namespace uiuc {

  // Put your HSLAPixel class definition here.
  // (Remember to end it with a semicolon!)
  class HSLAPixel {
        public:
            double h; // stores the hue of the pixel between 0 - 360 degrees
            double s; // stores the saturation of the pixel between 0.0 - 1.0
            double l; // stores the luminance of the pixel between 0.0 - 1.0
            double a; // stores alpha channel (blending opacity) as a decimal value between 0.0 and 1.0     
    };

}