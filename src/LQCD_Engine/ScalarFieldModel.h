#pragma once

#include "ModelBase.h"
#include "dtypes.h"

class ScalarFieldModel: public ModelBase{
public:

    /// @brief Constructor
    /// @param sizeX Size of lattice in X
    /// @param sizeY Size of lattice in Y
    /// @param sizeZ Size of lattice in Z
    /// @param sizeT Size of lattice in time
    ScalarFieldModel(int sizeX, int sizeY, int sizeZ, int sizeT, FLOAT mass);

    void proposeLattice(FLOAT stepSize);

private:

    FLOAT getAction(const std::vector<FLOAT> &s1, const std::vector<FLOAT> &s2);
    
    inline FLOAT getAction(const std::vector<FLOAT> &s1);

    FLOAT m_mass; /// <! The mass of the field
};