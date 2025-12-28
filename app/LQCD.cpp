#include "LQCD.h"
#include "plottingUtils.h"

namespace plt = matplotlibcpp;
FLOAT beta = -1.0;

int main()
{
    std::vector<FLOAT> stepIndices;
    std::vector<FLOAT> energies;

    MagneticSpinModel model(2, 32, 32);
    model.proposeLattice(0.005);
    model.setPeriodicBC(true);

    const Lattice2D<FLOAT> &lattice = model.getCurrentLattice();

    const uint nIterations = 1500000;

    for(uint it = 0; it < nIterations; it++){

        model.proposeLattice(0.025);

        FLOAT propAction = model.getProposedAction();
        FLOAT currentAction = model.getCurrentAction();

        FLOAT accProb = (FLOAT)std::min((FLOAT)1.0, (FLOAT)std::exp(-beta * (propAction - currentAction)));
    
        if ((it > 10) & (it % (uint) std::floor( nIterations / 10 ) == 0)) 
        {
            std::cout << std::endl;

            std::cout << " ============ " << "Iteration " << it << " ============ " << std::endl;
            std::cout << "Current Action:  " << currentAction << std::endl;
            std::cout << "Proposed Action: " << propAction << std::endl;
            std::cout << "Acceptance Prob: " << accProb << std::endl;
        }

        FLOAT energyToSave = -9999.9;

        // if proposed action > current, accept the other step
        if( accProb == 1.0 ){
            model.acceptProposedLattice();
            energyToSave = propAction;
        }
        // otherwise accept with probability given by ratio 
        else{
            FLOAT rand = (FLOAT)std::rand() / (FLOAT)RAND_MAX;
            if ( rand < accProb ){
                model.acceptProposedLattice();
                energyToSave = propAction;
            }
            else{
                energyToSave = currentAction;
            }
        }

        stepIndices.push_back((float)it);
        energies.push_back(energyToSave);
    }

    plt::plot(energies);
    plt::show();

    plotLattice2D(lattice);

    std::vector<FLOAT> centres;
    std::vector<int> counts;
    binData(energies, centres, counts, 3000.0, 4000.0, 100);
    plt::plot(centres, counts);
    plt::show();
}