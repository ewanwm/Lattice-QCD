#pragma once

#include "dtypes.h"
#include "Lattice.h"
#include "SampleWriterBase.h"
#include <random>

/// @brief Defines the interface of all models
class ModelBase {

public:

    /// @brief Constructor
    /// @param sizeX size in X direction
    /// @param sizeY size in Y direction
    /// @param sizeZ size in Z direction 
    /// @param sizeT size in time 
    ModelBase(uint nDims, uint sizeX, uint sizeY, uint sizeZ, uint sizeT);

    /// @brief Get the action for the current lattice configuration
    /// @return The action
    inline FLOAT getCurrentAction()  { return getAction(m_lattice); }
    
    /// @brief Get the action for the proposed lattice configuration
    /// @return The action
    inline FLOAT getProposedAction() { return getAction(m_proposedLattice); }

    /// @brief Propose a new configuration for the lattice
    /// \todo add ability to set the type of proposal using some kinda other object ("Proposer", "PropGenerator"... something like that)
    virtual void proposeLattice(FLOAT stepSize);

    /// @brief should add any observables to be saved out when sampling
    virtual void writeObservables(SampleWriterBase &writer) {};
    /// @todo make observables their own class and have some addObservable(observableBase) that can be called flexibly
    /// depending on user configuration

    /// @defgroup Getters
    /// @{
    inline const Lattice<FLOAT> &getCurrentLattice() { return m_lattice; }
    inline const Lattice<FLOAT> &getProposedLattice() { return m_proposedLattice; }
    /// @}

    /// @brief set the current lattice values to the proposed ones
    inline void acceptProposedLattice() { m_lattice.set(m_proposedLattice); }

    /// @brief Set whether or not to use periodic boundary conditions in each dimension
    /// @param X Value for x
    /// @param Y Value for y
    /// @param Z Value for z
    /// @param T Value for t
    inline void setPeriodicBC(bool X, bool Y, bool Z, bool T) { 
        m_periodicBCx = X;
        m_periodicBCy = Y;
        m_periodicBCz = Z;
        m_periodicBCt = T; 
    }

    /// @brief Set whether or not to use periodic boundary conditions in all dimension
    /// @param newVal The new value for all dimensions
    inline void setPeriodicBC(bool newVal = true) { 
        setPeriodicBC(/*X=*/newVal, /*Y=*/newVal, /*Z=*/newVal, /*T=*/newVal);
    }

protected:

    /// @brief Get the action for any two (neighbouring) sites on the lattice
    /// @param s1 The vector of values at the first site
    /// @param s2 The vector of values at the second site
    /// @return The action for the connection of the two sites
    virtual FLOAT getAction(const std::vector<FLOAT> &s1, const std::vector<FLOAT> &s2) = 0;

    /// @brief Get the self action for a site on the lattice
    /// @param s1 The vector of values at the first site
    /// @return The self action for the site
    virtual FLOAT getAction(const std::vector<FLOAT> &s1) = 0;

    /// @brief Get the action for a particular lattice configuration
    /// @param latticeToCheck The lattice to get the action for 
    /// @return The action
    FLOAT getAction(Lattice<FLOAT> &latticeToCheck);

    bool m_periodicBCx = false; /// <! whether to use periodic boundary conditions in X
    bool m_periodicBCy = false; /// <! whether to use periodic boundary conditions in Y
    bool m_periodicBCz = false; /// <! whether to use periodic boundary conditions in Z
    bool m_periodicBCt = false; /// <! whether to use periodic boundary conditions in T
    /// \todo make boundary condition options some kind of enum or something

    Lattice<FLOAT> m_lattice; /// !< The current lattice for this model
    Lattice<FLOAT> m_proposedLattice; /// !< The lattice currently being proposed by this model

    std::default_random_engine m_randomGenerator; /// !< The RNG to use to draw from the distribution 
    std::normal_distribution<FLOAT> m_distribution; /// !< The distribution to be used when proposing new lattice configurations
}; 