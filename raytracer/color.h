//
// Created by robert on 03.04.24.
//

#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

#include "math.h"
#include "geometry.h"
#include <iostream>
using color = Vector;

void write color(std:ostream &out, color pixel_color){
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
    out << static_cast<int>(255.999 * pixel_color.y()) << ' '
    out << static_cast<int>(255.999 * pixel_color.z()) << ' '
}

#endif //RAYTRACER_COLOR_H
