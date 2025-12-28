#include "plottingUtils.h"
#include "Lattice.h"
#include "MagneticSpinModel.h"
#include "SamplerMetropolisHastings.h"

namespace plt = matplotlibcpp;

int main()
{
    std::vector<FLOAT> stepIndices;
    std::vector<FLOAT> energies;

    // create the lattice config model
    auto model = std::make_shared<MagneticSpinModel>(2, 32, 32);
    model->setPeriodicBC(true);

    // create the lattice config sampler
    SamplerMetropolisHastings sampler(0.025);
    sampler.SetModel(model);
    sampler.initialise();

    const Lattice2D<FLOAT> &lattice = model->getCurrentLattice();

    const uint nIterations = 1500000;
    
    for(uint iteration = 0; iteration < nIterations; iteration++){
        
        sampler.step();

        if ((iteration > 10) & (iteration % (uint) std::floor( nIterations / 10 ) == 0)) 
        {
            std::cout << std::endl;
            std::cout << " ============ " << "Iteration " << iteration << " ============ " << std::endl;

            sampler.printCurrentStep();

            std::cout 
                << "Accepted steps:  " 
                << sampler.getAcceptedSteps() << " / " << iteration 
                << " (" << sampler.getAcceptanceRate() * 100.0 << "%) " << std::endl;
        }
    
        energies.push_back(sampler.getStepAction());
        stepIndices.push_back((float)iteration);
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