#pragma once

#include <random>
#include <memory>
#include <iostream>

#include "dtypes.h"
#include "ModelBase.h"
#include "SampleWriterBase.h"
#include "SamplerBase.h"

class SamplerMetropolisHastings : public SamplerBase {

public:

    /// @brief Constructor
    /// @param stepSize The step size to use when proposing new lattice configurations
    SamplerMetropolisHastings(FLOAT stepSize) 
    :
        m_proposedAction(-999.9),
        m_currentAction(-999.9),
        m_acceptanceProb(-999.9),
        m_acceptedSteps(0),
        m_stepAccepted(false),
        m_stepSize(stepSize)
    {
    }

    /// @brief Initialise the sampler - sets the current action to the action of the current lattice config
    /// @warning Should be called *after* SetModel()
    inline void initialise() {
        m_currentAction = m_model->getCurrentAction();
    }

    /// @brief Proposes a new lattice configuration, evaluates new action, throws random acceptance 
    ///        and moves to new config if applicable
    void doStep();

    /// @brief Print current and proposed action, and acceptance prob
    inline void printCurrentStep() const {

        std::cout << "Current Action:  " << m_currentAction << std::endl;
        std::cout << "Proposed Action: " << m_proposedAction << std::endl;
        std::cout << "Acceptance Prob: " << m_acceptanceProb << std::endl;
    }

    /// @defgroup Getters
    /// @{
    FLOAT getStepAction() { return m_currentAction; }
    FLOAT getStepAcceptanceProb() { return m_acceptanceProb; }
    FLOAT getAcceptanceRate() { return (FLOAT) m_acceptedSteps / (FLOAT) m_currentStep; }
    uint getAcceptedSteps() { return m_acceptedSteps; }
    bool getStepAccepted() { return m_stepAccepted; }
    /// @}

protected:

    /// @brief Accept the proposed step
    ///        
    /// Moves the model to the proposed configuration and sets the current action tot he proposed one.
    inline void acceptProposed() {
        m_model->acceptProposedLattice();
        m_currentAction = m_proposedAction;
        
        m_stepAccepted = true;
        m_acceptedSteps++;
    }

    /// @brief Reject the proposed step
    inline void rejectProposed() {
        m_stepAccepted = false;
    }

    /// The action of the proposed lattice configuration
    FLOAT m_proposedAction;
    /// The action of the current lattice configuration
    FLOAT m_currentAction;
    /// The acceptance probability of the proposed lattice configuration
    FLOAT m_acceptanceProb;
    /// The number of steps that have been accepted
    uint m_acceptedSteps;
    /// Whether the most recent step was accepted
    bool m_stepAccepted;
    /// The step size to use when proposing new lattice configurations
    /// @todo move this to LatticeProposer (when written)
    FLOAT m_stepSize;
};
