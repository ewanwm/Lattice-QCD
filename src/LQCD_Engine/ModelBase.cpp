#include "ModelBase.h"

ModelBase::ModelBase(uint nDims, uint sizeX, uint sizeY, uint sizeZ, uint sizeT)
{
    m_lattice = Lattice<FLOAT>(nDims, sizeX, sizeY, sizeZ, sizeT);
    m_lattice.randomise();

    m_distribution = std::normal_distribution<FLOAT>(0.0, 1.0);

    m_proposedLattice = Lattice<FLOAT>(nDims, sizeX, sizeY, sizeZ, sizeT);
    m_proposedLattice.set(getCurrentLattice());
}

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
                    
                    FLOAT siteAction = 0.0;

                    siteAction += getAction(centralSite);

                    if (x == sizeX -1) {
                        if (m_periodicBCx) {
                            siteAction += 2.0 * getAction(centralSite, latticeToCheck.getSite(0, y, z, t));
                        }
                    }
                    else {
                        siteAction += 2.0 * getAction(centralSite, latticeToCheck.getSite(x + 1, y, z, t));
                    }
                    if (y == sizeY -1) {
                        if (m_periodicBCy) {
                            siteAction += 2.0 * getAction(centralSite, latticeToCheck.getSite(x, 0, z, t));
                        }
                    }
                    else {
                        siteAction += 2.0 * getAction(centralSite, latticeToCheck.getSite(x, y + 1, z, t));
                    }
                    if (z == sizeZ -1) {
                        if (m_periodicBCz) {
                            siteAction += 2.0 * getAction(centralSite, latticeToCheck.getSite(x, y, 0, t));
                        }
                    }
                    else {
                        siteAction += 2.0 * getAction(centralSite, latticeToCheck.getSite(x, y, z + 1, t));
                    }
                    if (t == sizeT - 1) {
                        if (m_periodicBCt) {
                            siteAction += 2.0 * getAction(centralSite, latticeToCheck.getSite(x, y, z, 0));
                        }
                    }
                    else {
                        siteAction += 2.0 * getAction(centralSite, latticeToCheck.getSite(x, y, z, t + 1));                    
                    }

                    accum_thread += siteAction;
                }
            }
        }

        accum += accum_thread;
    }

    return accum;
}


void ModelBase::proposeLattice(FLOAT stepSize){

    for(uint x = 0; x < m_lattice.getSizeX(); x++){
        for (uint y = 0; y < m_lattice.getSizeY(); y++){
            for (uint z = 0; z < m_lattice.getSizeZ(); z++){
                for (uint t = 0; t < m_lattice.getSizeT(); t++) {
                    for(uint d = 0; d < m_lattice.getNDims(); d++) {

                        // propose some random variations of the current field
                        FLOAT val = m_lattice.getSite(x,y,z,t)[d] + m_distribution(m_randomGenerator) * stepSize;
                        m_proposedLattice.setSite(x, y, z, t, d, val);
                    
                    }
                }
            }
        }
    }
}