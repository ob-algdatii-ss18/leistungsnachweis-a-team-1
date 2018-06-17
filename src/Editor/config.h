#ifndef ALOGDAT_LABYRINTH_CONFIG_H
#define ALOGDAT_LABYRINTH_CONFIG_H

struct Config {
    static constexpr int WindowHeight = 400;
    static constexpr int WindowWidth = 640;
    static constexpr int NumCellsX = 5;
    static constexpr int NumCellsY = 5;
    static constexpr int NodeRadius = 8;
    static constexpr float WaterCost = 1.5;
    static constexpr float HillCost = 2.0;
    static constexpr float PlanarCost = 1.0;
};

#endif //ALOGDAT_LABYRINTH_CONFIG_H
