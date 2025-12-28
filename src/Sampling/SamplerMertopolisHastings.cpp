#include "SamplerMetropolisHastings.h"

void SamplerMetropolisHastings::doStep() {

    m_model->proposeLattice(0.025);

    m_proposedAction = m_model->getProposedAction();

    m_acceptanceProb = (FLOAT) std::min((FLOAT) 1.0, (FLOAT) std::exp(m_proposedAction - m_currentAction));

    // if proposed action > current, accept the other step
    if( m_acceptanceProb == 1.0 ){
        acceptProposed();
    }
    // otherwise accept with probability given by ratio 
    else{
        FLOAT rand = (FLOAT)std::rand() / (FLOAT)RAND_MAX;
        if ( rand < m_acceptanceProb ){
            acceptProposed();
        }
        else{
            rejectProposed();
        }
    }
}
