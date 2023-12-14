#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

using color = vec3;

void write_color(std::ostream& out, color rgb) {
  out << static_cast<int>(255.9999 * rgb.x()) << " "
      << static_cast<int>(255.9999 * rgb.y()) << " "
      << static_cast<int>(255.9999 * rgb.z()) << "\n";
}


#endif 