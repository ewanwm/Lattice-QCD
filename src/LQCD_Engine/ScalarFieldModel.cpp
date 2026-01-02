#include "ScalarFieldModel.h"

ScalarFieldModel::ScalarFieldModel(int sizeX, int sizeY, int sizeZ, int sizeT, FLOAT mass)
    :
        m_mass(mass)
    {

    m_lattice = Lattice<FLOAT>(1, sizeX, sizeY, sizeZ, sizeT);
    m_lattice.randomise();

    m_distribution = std::normal_distribution<FLOAT>(0.0, 1.0);

    m_proposedLattice = Lattice<FLOAT>(1, sizeX, sizeY, sizeZ, sizeT);

}

void ScalarFieldModel::proposeLattice(FLOAT stepSize){

    m_proposedLattice.set(getCurrentLattice());
    
    for(uint x = 0; x < m_proposedLattice.getSizeX(); x++){
        for (uint y = 0; y < m_proposedLattice.getSizeY(); y++){
            for (uint z = 0; z < m_proposedLattice.getSizeZ(); z++){
                for (uint t = 0; t < m_proposedLattice.getSizeT(); t++) {

                    // propose some random variations of the spin vectors
                    FLOAT val = m_proposedLattice.getSite(x,y,z,t)[0] + m_distribution(m_randomGenerator) * stepSize;
                    m_proposedLattice.setSite(x, y, z, t, 0, val);
                    
                }
            }
        }
    }
}

FLOAT ScalarFieldModel::getAction(const std::vector<FLOAT> &s1) {

    return 0.5 * ( 8.0 - m_mass * m_mass ) * s1[0] * s1[0];
}

FLOAT ScalarFieldModel::getAction(const std::vector<FLOAT> &s1, const std::vector<FLOAT> &s2) {
    assert(s1.size() == s2.size());
    assert(s1.size() == 1);

    return - 0.5 * s1[0] * s2[0];
}
