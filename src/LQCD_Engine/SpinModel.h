#pragma once
#include <random>
#include "Lattice.h"

/// @brief Base class for various 2D spin models
class SpinModelBase2D{
public:

    /// @brief Get the action for the current state of the model
    /// @return The action
    virtual FLOAT getCurrentAction() = 0;
    
    /// @brief Get the action for the proposed state of the model
    /// @return The action
    virtual FLOAT getProposedAction() = 0;

    /// @brief Propose a new configuration for the lattice
    /// \todo add ability to set the type of proposal using some kinda other object ("Proposer", "PropGenerator"... something like that)
    virtual void proposeLattice(FLOAT stepSize) = 0;

    /// @defgroup Getters
    /// @{
    inline const Lattice2D<FLOAT> &getCurrentLattice() { return lattice; }
    inline const Lattice2D<FLOAT> &getProposedLattice() { return proposedLattice; }
    /// @}


protected:
    Lattice2D<FLOAT> lattice; /// !< The current lattice for this model
    Lattice2D<FLOAT> proposedLattice; /// !< The lattice currently being proposed by this model
    
    std::default_random_engine randomGenerator; /// !< The RNG to use to draw from the distribution 
    std::normal_distribution<FLOAT> distribution; /// !< The distribution to be used when proposing new lattice configurations

};


class MagneticSpinModel: public SpinModelBase2D{
public:

    /// @brief Constructor
    /// @param nDims Number of lattice dimensions
    /// @param sizeX Size of lattice in X
    /// @param sizeY Size of lattice in Y
    MagneticSpinModel(int nDims, int sizeX, int sizeY, FLOAT magneticCoupling=1.0);

    void proposeLattice(FLOAT stepSize);

    inline FLOAT getCurrentAction() { return getMagneticAction(lattice); }
    inline FLOAT getProposedAction() { return getMagneticAction(proposedLattice); }

    /// @brief Set whether or not to use periodic boundary conditions
    /// @param newVal The new value
    inline void setPeriodicBC(bool newVal = true) { periodicBC = newVal; }

    /// @brief set the current lattice values to the proposed ones
    inline void acceptProposedLattice() { lattice.set(proposedLattice); }

private:
    FLOAT getMagneticAction(Lattice2D<FLOAT> &latticeToCheck);
    FLOAT getMagneticAction(std::vector<FLOAT> s1, std::vector<FLOAT> s2);
    FLOAT magneticCoupling; /// <! The strength of the magnetic coupling between neighbouring lattice sites

    bool periodicBC = false; /// <! whether to use periodic boundary conditions
    /// \todo make boundary condition options some kind of enum or something
};