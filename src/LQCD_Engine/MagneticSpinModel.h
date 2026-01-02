#pragma once
#include <random>
#include "ModelBase.h"
#include "dtypes.h"

class MagneticSpinModel: public ModelBase{
public:

    /// @brief Constructor
    /// @param nDims Number of lattice dimensions
    /// @param sizeX Size of lattice in X
    /// @param sizeY Size of lattice in Y
    MagneticSpinModel(int nDims, int sizeX, int sizeY, FLOAT magneticCoupling=1.0);

    void proposeLattice(FLOAT stepSize);

private:
    FLOAT getAction(const std::vector<FLOAT> &s1, const std::vector<FLOAT> &s2);
    
    inline FLOAT getAction(const std::vector<FLOAT> &s1) { return 0.0; };

    FLOAT magneticCoupling; /// <! The strength of the magnetic coupling between neighbouring lattice sites
};