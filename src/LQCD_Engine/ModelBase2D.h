#pragma once

#include <random>

#include "omp.h"
#include "dtypes.h"
#include "Lattice.h"

/// @brief Base class for various 2D spin models
class ModelBase2D{
public:

    /// @brief Get the action for the current state of the model
    /// @return The action
    inline FLOAT getCurrentAction()  { return getAction(lattice); }
    
    /// @brief Get the action for the proposed state of the model
    /// @return The action
    inline FLOAT getProposedAction() { return getAction(proposedLattice); }

    /// @brief Propose a new configuration for the lattice
    /// \todo add ability to set the type of proposal using some kinda other object ("Proposer", "PropGenerator"... something like that)
    virtual void proposeLattice(FLOAT stepSize) = 0;

    /// @defgroup Getters
    /// @{
    inline const Lattice2D<FLOAT> &getCurrentLattice() { return lattice; }
    inline const Lattice2D<FLOAT> &getProposedLattice() { return proposedLattice; }
    /// @}

    /// @brief Set whether or not to use periodic boundary conditions
    /// @param newVal The new value
    inline void setPeriodicBC(bool newVal = true) { periodicBC = newVal; }

    /// @brief set the current lattice values to the proposed ones
    inline void acceptProposedLattice() { lattice.set(proposedLattice); }

protected:
    Lattice2D<FLOAT> lattice; /// !< The current lattice for this model
    Lattice2D<FLOAT> proposedLattice; /// !< The lattice currently being proposed by this model
    
    std::default_random_engine randomGenerator; /// !< The RNG to use to draw from the distribution 
    std::normal_distribution<FLOAT> distribution; /// !< The distribution to be used when proposing new lattice configurations

    /// @brief Get the action for any two (neighbouring) sites on the lattice
    /// @param s1 The vector of values at the first site
    /// @param s2 The vector of values at the second site
    /// @return The action for the connection of the two sites
    virtual FLOAT getAction(std::vector<FLOAT> s1, std::vector<FLOAT> s2) = 0;

    /// @brief Get the action for a particular lattice configuration
    /// @param latticeToCheck The lattice to get the action for 
    /// @return The action
    FLOAT getAction(Lattice2D<FLOAT> &latticeToCheck);

    bool periodicBC = false; /// <! whether to use periodic boundary conditions
    /// \todo make boundary condition options some kind of enum or something
};
