//
// Created by robert on 03.04.24.
//

#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

#include "math.h"
#include "geometry.h"
#include <iostream>


void write_color(std::ostream &out, Vector3df pixel_color) {
    out << static_cast<int>(255.999 * pixel_color[0]) << ' '
        << static_cast<int>(255.999 * pixel_color[1]) << ' '
        << static_cast<int>(255.999 * pixel_color[2]) << '\n';
}

#endif //RAYTRACER_COLOR_H
