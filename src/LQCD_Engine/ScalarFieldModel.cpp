#include "ScalarFieldModel.h"

ScalarFieldModel::ScalarFieldModel(int sizeX, int sizeY, FLOAT mass)
    :
        m_mass(mass)
    {

    lattice = Lattice2D<FLOAT>(1, sizeX, sizeY);
    lattice.randomise();

    distribution = std::normal_distribution<FLOAT>(0.0, 1.0);

    proposedLattice = Lattice2D<FLOAT>(1, sizeX, sizeY);

}

void ScalarFieldModel::proposeLattice(FLOAT stepSize){

    proposedLattice.set(getCurrentLattice());
    
    for(int x = 0; x < proposedLattice.getSizeX(); x++){
        for (int y= 0; y < proposedLattice.getSizeY(); y++){

            // propose some random variations of the spin vectors
            FLOAT val = proposedLattice.getSite(x,y)[0] + distribution(randomGenerator) * stepSize;
            proposedLattice.setSite(x, y, 0, val);

        }
    }
}

FLOAT ScalarFieldModel::getAction(const std::vector<FLOAT> &s1) {

    return 0.5 * ( 8.0 - m_mass * m_mass ) * s1[0] * s1[0];
}

FLOAT ScalarFieldModel::getAction(const std::vector<FLOAT> &s1, const std::vector<FLOAT> &s2) {
    assert(s1.size() == s2.size());
    assert(s1.size() == 1);

    return - s1[0] * s2[0];
}
