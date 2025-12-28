#include "ModelBase2D.h"

FLOAT ModelBase2D::getAction(Lattice2D<FLOAT> &latticeToCheck) {

    FLOAT accum = 0.0;

    #pragma omp parallel for reduction(+:accum)
    for (uint x = 0; x < latticeToCheck.getSizeX(); x ++){
        
        FLOAT accum_thread = 0.0;

        for (uint y = 0; y < latticeToCheck.getSizeY(); y ++){

            if (x == 0) {
                if (periodicBC) {
                    accum_thread += getAction(latticeToCheck.getSite(x, 0), latticeToCheck.getSite(x, latticeToCheck.getSizeY() -1));
                }
            }
            else {
                accum_thread += getAction(latticeToCheck.getSite(x, y), latticeToCheck.getSite(x - 1, y));
            }
            if (y == 0) {
                if (periodicBC) {
                    accum_thread += getAction(latticeToCheck.getSite(0, y), latticeToCheck.getSite(latticeToCheck.getSizeX() -1, y));
                }
            }
            else {
                accum_thread += getAction(latticeToCheck.getSite(x, y), latticeToCheck.getSite(x, y - 1));
            }
            if (x == latticeToCheck.getSizeX() -1) {
                if (periodicBC) {
                    accum_thread += getAction(latticeToCheck.getSite(x, latticeToCheck.getSizeY() -1), latticeToCheck.getSite(x, 0));
                }
            }
            else {
                accum_thread += getAction(latticeToCheck.getSite(x, y), latticeToCheck.getSite(x + 1, y));
            }
            if (y == latticeToCheck.getSizeY() -1) {
                accum_thread += getAction(latticeToCheck.getSite(latticeToCheck.getSizeX() -1, y), latticeToCheck.getSite(0, y));
            }
            else {
                accum_thread += getAction(latticeToCheck.getSite(x, y), latticeToCheck.getSite(x, y + 1));
            }
        }

        accum += accum_thread;
    }

    return accum;
}
