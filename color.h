#ifndef COLOUR_H
#define COLOUR_H
#include "vec3.h"
#include <iostream>
#include <fstream>

using colour = Vec3;
// a function to change to colour values

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}


void writeRgb(std::ofstream& image, const colour& pixelColor) {
  int ir = static_cast<int>(256 * clamp(pixelColor.x(), 0.0, 0.999));
  int ig = static_cast<int>(256 * clamp(pixelColor.y(), 0.0, 0.999));
  int ib = static_cast<int>(256 * clamp(pixelColor.z(), 0.0, 0.999));
  image << ir << ' ' << ig << ' ' << ib << '\n';
}

#endif