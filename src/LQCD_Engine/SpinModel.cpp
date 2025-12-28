#include "SpinModel.h"
#include "omp.h"

FLOAT SpinModelBase2D::getAction(Lattice2D<FLOAT> &latticeToCheck) {

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

    proposedLattice.set(getCurrentLattice());
    
    for(int x = 0; x < proposedLattice.getSizeX(); x++){
        for (int y= 0; y < proposedLattice.getSizeY(); y++){

            float norm = 0.0;
            // propose some random variations of the spin vectors
            for (int d=0; d < proposedLattice.getNDims(); d++){
                FLOAT val = proposedLattice.getSite(x,y)[d] + distribution(randomGenerator) * stepSize;
                proposedLattice.setSite(x, y, d, val);

                norm += val * val;
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

FLOAT MagneticSpinModel::getAction(std::vector<FLOAT> s1, std::vector<FLOAT> s2) {
    assert(s1.size() == s2.size());
    FLOAT accum = 0.0;

    for(uint d = 0; d < s1.size(); d++){
        accum += s1[d] * s2[d];
    }

    return magneticCoupling * accum;
}
