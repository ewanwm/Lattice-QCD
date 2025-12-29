#include "ModelBase2D.h"

FLOAT ModelBase2D::getAction(Lattice2D<FLOAT> &latticeToCheck) {

    FLOAT accum = 0.0;

    const uint &sizeX = latticeToCheck.getSizeX();
    const uint &sizeY = latticeToCheck.getSizeY();

    #pragma omp parallel for reduction(+:accum)
    for (uint x = 0; x < sizeX; x ++){
        
        FLOAT accum_thread = 0.0;

        for (uint y = 0; y < sizeY; y ++){

            const auto &centralSite = latticeToCheck.getSite(x, y);

            accum_thread += getAction(centralSite);

            if (x == latticeToCheck.getSizeX() -1) {
                if (periodicBC) {
                    accum_thread += 2.0 * getAction(centralSite, latticeToCheck.getSite(0, y));
                }
            }
            else {
                accum_thread += 2.0 * getAction(centralSite, latticeToCheck.getSite(x + 1, y));
            }
            if (y == latticeToCheck.getSizeY() -1) {
                accum_thread += 2.0 * getAction(centralSite, latticeToCheck.getSite(x, 0));
            }
            else {
                accum_thread += 2.0 * getAction(centralSite, latticeToCheck.getSite(x, y + 1));
            }
        }

        accum += accum_thread;
    }

    return accum;
}
