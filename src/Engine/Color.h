#ifndef ALOGDAT_LABYRINTH_COLORMAP_H
#define ALOGDAT_LABYRINTH_COLORMAP_H

enum color_type {
    color_white = 0, color_gray = 1, color_black = 2
};

struct Color {
    static color_type white() { return color_white; }
    static color_type gray() { return color_gray; }
    static color_type black() { return color_black; }
};

#endif //ALOGDAT_LABYRINTH_COLORMAP_H
