#include "LQCD.h"

namespace plt = matplotlibcpp;
FLOAT beta = 0.01;


void binData(const std::vector<FLOAT> &data, std::vector<FLOAT> &binCentres, std::vector<int> &counts, FLOAT min, FLOAT max, int nBins, bool overflow = false){
    binCentres.resize(nBins);
    counts.resize(nBins);
    FLOAT binWidth = (max - min) / (FLOAT)nBins;

    // set the bin centre vector
    for (int i = 0; i < nBins; i++){
        binCentres[i] = min + ((FLOAT)i + 0.5) * (max - min) / (FLOAT)nBins;
    }

    for(int i = 0; i < data.size(); i++){
        if(data[i] <= min) {
            if( overflow )
                counts[0] ++;
        }
        else if(data[i] >= max) {
            if( overflow )
                counts[nBins -1] ++;
        }
        else{        
            int index = (int)std::floor(data[i] / binWidth);
            counts[index] ++;
        }
    }
}


int main()
{
    std::vector<FLOAT> stepIndices;
    std::vector<FLOAT> energies;

    MagneticSpinModel model(4, 20, 10);
    model.proposeLattice(0.05);
    model.setPeriodicBC(true);

    const Lattice2D<FLOAT> &lattice = model.getCurrentLattice();
    const Lattice2D<FLOAT> &propLattice = model.getProposedLattice();

    for(int it=0; it < 150000; it++){
        model.proposeLattice(0.15);

        FLOAT propAction = model.getProposedAction();
        FLOAT currentAction = model.getCurrentAction();

        FLOAT accProb = (FLOAT)std::min((FLOAT)1.0, (FLOAT)std::exp(-beta *(propAction - currentAction)));
    
        //std::cout << std::endl;
        //std::cout << "Current Action:  " << currentAction << std::endl;
        //std::cout << "Proposed Action: " << propAction << std::endl;
        //std::cout << "Acceptance Prob: " << accProb << std::endl;

        //std::cout << "(" << propLattice.getSite(10, 5)[0] << ", " << propLattice.getSite(10, 5)[1] << ")" << std::endl;

        FLOAT energyToSave = -9999.9;

        // if proposed action > current, accept the other step
        if( accProb == 1.0 ){
            model.acceptProposedLattice();
            energyToSave = (FLOAT)std::exp(-beta *(propAction));
        }
        // otherwise accept with probability given by ratio 
        else{
            FLOAT rand = (FLOAT)std::rand() / (FLOAT)RAND_MAX;
            if ( rand < accProb ){
                model.acceptProposedLattice();
                energyToSave = (FLOAT)std::exp(-beta *(propAction));
            }
            else{
                energyToSave = (FLOAT)std::exp(-beta *(currentAction));
            }
        }

        stepIndices.push_back((float)it);
        energies.push_back(energyToSave);
    }

    plt::plot(energies);
    plt::show();

    // u and v are respectively the x and y components of the arrows we're plotting
    std::vector<int> x, y;
    std::vector<float> u, v;
    for (int i = -10; i <= 9; i++) {
        for (int j = -5; j <= 4; j++) {
            //std::cout << propLattice.getSite(i + 5, j + 5)[0] << ", " << propLattice.getSite(i + 5, j + 5)[1] << ", " << lattice.getSite(i + 5, j + 5)[2] << std::endl;
            x.push_back(i);
            u.push_back(propLattice.getSite(i + 10, j + 5)[0]);
            y.push_back(j);
            v.push_back(propLattice.getSite(i + 10, j + 5)[1]);
        }
    }

    plt::quiver<int, int, float, float>(x, y, u, v);
    plt::show();

    std::vector<FLOAT> centres;
    std::vector<int> counts;
    binData(energies, centres, counts, 0.0, 10.0, 100);
    plt::plot(centres, counts);
    plt::show();
}