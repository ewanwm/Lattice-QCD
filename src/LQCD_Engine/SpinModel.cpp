#include "SpinModel.h"

MagneticSpinModel::MagneticSpinModel(int nDims, int sizeX, int sizeY, FLOAT magneticCoupling)
    :
        magneticCoupling(magneticCoupling)
    {

    lattice = Lattice2D<FLOAT>(nDims, sizeX, sizeY);
    lattice.randomise();

    distribution = std::normal_distribution<FLOAT>(0.0, 1.0);

    proposedLattice = Lattice2D<FLOAT>(nDims, sizeX, sizeY);

}

void MagneticSpinModel::proposeLattice(FLOAT stepSize){
    for(int x = 0; x < proposedLattice.getSizeX(); x++){
        for (int y= 0; y < proposedLattice.getSizeY(); y++){

            float norm = 0.0;
            // propose some random variations of the spin vectors
            for (int d=0; d < proposedLattice.getNDims(); d++){
                FLOAT val = proposedLattice.getSite(x,y)[d] + distribution(randomGenerator) *stepSize;
                proposedLattice.setSite(x, y, d, val);

                norm += val *val;
            }

            // normalise the spin vectors
            norm = std::sqrt(norm);
            for (int d=0; d < proposedLattice.getNDims(); d++){
                FLOAT val = proposedLattice.getSite(x,y)[d] / norm;
                proposedLattice.setSite(x, y, d, val);
            }
        }
    }
}

FLOAT MagneticSpinModel::getMagneticAction(std::vector<FLOAT> s1, std::vector<FLOAT> s2) {
    assert(s1.size() == s2.size());
    FLOAT accum = 0.0;

    for(int d = 0; d < s1.size(); d++){
        accum -= s1[d] * s2[d];
    }

    return accum;
}

FLOAT MagneticSpinModel::getMagneticAction(Lattice2D<FLOAT> &latticeToCheck) {
    FLOAT accum = 0.0;

    // #### First the sites at the edges of the lattice ######
    for (int x = 0; x < latticeToCheck.getSizeX(); x ++){
        if (periodicBC){
            accum += 2.0 *getMagneticAction(latticeToCheck.getSite(x, 0), latticeToCheck.getSite(x, latticeToCheck.getSizeY() -1));
        }
        accum += getMagneticAction(latticeToCheck.getSite(x, 0), latticeToCheck.getSite(x, 1));
        accum += getMagneticAction(latticeToCheck.getSite(x, latticeToCheck.getSizeY() -1 ), latticeToCheck.getSite(x, latticeToCheck.getSizeY() -2));
    }
    for (int y = 0; y < latticeToCheck.getSizeY(); y ++){
        if (periodicBC){
            accum += 2.0 *getMagneticAction(latticeToCheck.getSite(0, y), latticeToCheck.getSite(latticeToCheck.getSizeX() -1, y));
        }
        accum += getMagneticAction(latticeToCheck.getSite(0, y), latticeToCheck.getSite(1, y));
        accum += getMagneticAction(latticeToCheck.getSite(latticeToCheck.getSizeX() - 1, y), latticeToCheck.getSite(latticeToCheck.getSizeX() -2, y));
    }

    // Now do the bulk
    for (int x = 1; x < latticeToCheck.getSizeX() - 1; x ++){
        for (int y = 1; y < latticeToCheck.getSizeY() - 1; y ++){
            accum += getMagneticAction(latticeToCheck.getSite(x, y), latticeToCheck.getSite(x, y - 1));
            accum += getMagneticAction(latticeToCheck.getSite(x, y), latticeToCheck.getSite(x, y + 1));
            accum += getMagneticAction(latticeToCheck.getSite(x, y), latticeToCheck.getSite(x - 1, y));
            accum += getMagneticAction(latticeToCheck.getSite(x, y), latticeToCheck.getSite(x + 1, y));
        }
    }

    return accum;
}