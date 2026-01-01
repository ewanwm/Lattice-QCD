#pragma once

#include "ModelBase2D.h"
#include "dtypes.h"

class ScalarFieldModel: public ModelBase2D{
public:

    /// @brief Constructor
    /// @param sizeX Size of lattice in X
    /// @param sizeY Size of lattice in Y
    ScalarFieldModel(int sizeX, int sizeY, FLOAT mass);

    void proposeLattice(FLOAT stepSize);

private:

    FLOAT getAction(const std::vector<FLOAT> &s1, const std::vector<FLOAT> &s2);
    
    inline FLOAT getAction(const std::vector<FLOAT> &s1);

    FLOAT m_mass; /// <! The mass of the field
};