#include "ModelBase.h"

FLOAT ModelBase::getAction(Lattice<FLOAT> &latticeToCheck) {

    FLOAT accum = 0.0;

    const uint &sizeX = latticeToCheck.getSizeX();
    const uint &sizeY = latticeToCheck.getSizeY();
    const uint &sizeZ = latticeToCheck.getSizeZ();
    const uint &sizeT = latticeToCheck.getSizeT();

    #pragma omp parallel for reduction(+:accum)
    for (uint x = 0; x < sizeX; x ++){
        
        FLOAT accum_thread = 0.0;

        for (uint y = 0; y < sizeY; y++){

            for (uint z = 0; z < sizeZ; z++){

                for (uint t = 0; t < sizeT; t++) {

                    const auto &centralSite = latticeToCheck.getSite(x, y, z, t);

                    accum_thread += getAction(centralSite);

                    if (x == sizeX -1) {
                        if (m_periodicBCx) {
                            accum_thread += 2.0 * getAction(centralSite, latticeToCheck.getSite(0, y, z, t));
                        }
                    }
                    else {
                        accum_thread += 2.0 * getAction(centralSite, latticeToCheck.getSite(x + 1, y, z, t));
                    }
                    if (y == sizeY -1) {
                        if (m_periodicBCy) {
                            accum_thread += 2.0 * getAction(centralSite, latticeToCheck.getSite(x, 0, z, t));
                        }
                    }
                    else {
                        accum_thread += 2.0 * getAction(centralSite, latticeToCheck.getSite(x, y + 1, z, t));
                    }
                    if (z == sizeZ -1) {
                        if (m_periodicBCz) {
                            accum_thread += 2.0 * getAction(centralSite, latticeToCheck.getSite(x, y, 0, t));
                        }
                    }
                    else {
                        accum_thread += 2.0 * getAction(centralSite, latticeToCheck.getSite(x, y, z + 1, t));
                    }
                    if (t == sizeT - 1) {
                        if (m_periodicBCt) {
                            accum_thread += 2.0 * getAction(centralSite, latticeToCheck.getSite(x, y, z, 0));
                        }
                    }
                    else {
                        accum_thread += 2.0 * getAction(centralSite, latticeToCheck.getSite(x, y, z, t + 1));                    
                    }
                }
            }
        }

        accum += accum_thread;
    }

    return accum;
}
