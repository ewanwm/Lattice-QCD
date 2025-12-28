#pragma once

#include "dtypes.h"

/// @brief Defines the interface of all models
class ModelBase {

public:

    /// @brief Get the action for the current lattice configuration
    /// @return The action
    virtual FLOAT getCurrentAction() = 0;

    /// @brief Get the action for the proposed lattice configuration
    /// @return The action
    virtual FLOAT getProposedAction() = 0;

    /// @brief Propose a new configuration for the lattice
    /// \todo add ability to set the type of proposal using some kinda other object ("Proposer", "PropGenerator"... something like that)
    virtual void proposeLattice(FLOAT stepSize) = 0;

    virtual void acceptProposedLattice() = 0;

    /// @brief Set whether or not to use periodic boundary conditions
    /// @param newVal The new value
    inline void setPeriodicBC(bool newVal = true) { periodicBC = newVal; }

protected:

    bool periodicBC = false; /// <! whether to use periodic boundary conditions
    /// \todo make boundary condition options some kind of enum or something

}; 