#include "MagneticSpinModel.h"

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

FLOAT MagneticSpinModel::getAction(const std::vector<FLOAT> &s1, const std::vector<FLOAT> &s2) {
    assert(s1.size() == s2.size());
    FLOAT accum = 0.0;

    for(uint d = 0; d < s1.size(); d++){
        accum += s1[d] * s2[d];
    }

    return magneticCoupling * accum;
}
