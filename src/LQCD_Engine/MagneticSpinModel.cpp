#include "MagneticSpinModel.h"

MagneticSpinModel::MagneticSpinModel(int nDims, int sizeX, int sizeY, FLOAT magneticCoupling)
    :
        magneticCoupling(magneticCoupling)
    {

    m_lattice = Lattice<FLOAT>(nDims, sizeX, sizeY, 0, 0);
    m_lattice.randomise();

    m_distribution = std::normal_distribution<FLOAT>(0.0, 1.0);

    m_proposedLattice = Lattice<FLOAT>(nDims, sizeX, sizeY, 0, 0);

}

void MagneticSpinModel::proposeLattice(FLOAT stepSize){

    m_proposedLattice.set(getCurrentLattice());
    
    for(int x = 0; x < m_proposedLattice.getSizeX(); x++){
        for (int y= 0; y < m_proposedLattice.getSizeY(); y++){

            float norm = 0.0;
            // propose some random variations of the spin vectors
            for (int d=0; d < m_proposedLattice.getNDims(); d++){
                FLOAT val = m_proposedLattice.getSite(x,y, 0, 0)[d] + m_distribution(m_randomGenerator) * stepSize;
                m_proposedLattice.setSite(x, y, 0, 0, d, val);

                norm += val * val;
            }

            // normalise the spin vectors
            norm = std::sqrt(norm);
            for (int d=0; d < m_proposedLattice.getNDims(); d++){
                FLOAT val = m_proposedLattice.getSite(x,y, 0, 0)[d] / norm;
                m_proposedLattice.setSite(x, y, 0, 0, d, val);
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

    return - magneticCoupling * accum;
}
