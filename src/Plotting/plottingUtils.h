#pragma once

#include <vector>
#include "matplotlibcpp.h"
#include "Lattice.h"
#include "dtypes.h"

namespace plt = matplotlibcpp;

/// @brief Make a 1D histogram from a set of data points
/// @param data The data points to be binned
/// @param[out] binCentres The cenral values of the bins
/// @param[out] counts The counts for each bin
/// @param min The minimum x value of the histogram
/// @param max The maximum x value of the histogram
/// @param nBins The number of bins
/// @param overflow Whether to include overflow / underflow events in the last / first bin
inline void binData(
    const std::vector<FLOAT> &data, 
    std::vector<FLOAT> &binCentres, 
    std::vector<int> &counts, 
    FLOAT min, 
    FLOAT max, 
    int nBins, 
    bool overflow = false
)
{
    binCentres.resize(nBins);
    counts.resize(nBins);
    FLOAT binWidth = (max - min) / (FLOAT)nBins;

    // set the bin centre vector
    for (uint iBin = 0; iBin < nBins; iBin++){
        binCentres[iBin] = min + ((FLOAT) iBin + 0.5) * binWidth;
    }

    for(const FLOAT &point: data){
        if(point <= min) {
            if( overflow )
                counts[0] ++;
        }
        else if(point >= max) {
            if( overflow )
                counts[nBins -1] ++;
        }
        else{        
            int index = (int)std::floor((point - min) / binWidth);
            counts[index] ++;
        }
    }
}

/// @brief Plot the first dimension of sites in a 2D lattice
/// @param lattice The lattice to plot
inline void plotLattice2D(const Lattice2D<FLOAT> &lattice) 
{

    // get the min and max values in the lattice
    FLOAT min, max;

    min = lattice.getSite(0, 0)[0];
    max = lattice.getSite(0, 0)[0];

    for (int x = 0; x < lattice.getSizeX(); x++) {
        for (int y = 0; y < lattice.getSizeY(); y++) {
    
            min = std::min(min, lattice.getSite(x, y)[0]);
            max = std::max(min, lattice.getSite(x, y)[0]);

        }
    }

    // u and v are respectively the x and y components of the arrows we're plotting
    std::vector<float> zVals;
    for (int x = 0; x < lattice.getSizeX(); x++) {
        for (int y = 0; y < lattice.getSizeY(); y++) {

            auto &siteVals = lattice.getSite(x, y);
            float z = (siteVals[0] - min) / (max - min);
            zVals.push_back(z);
        }
    }

    const float* zptr = &(zVals[0]);

    plt::imshow(zptr, lattice.getSizeX(), lattice.getSizeY(), /*colors=*/1);
    plt::show();
}


/// @brief Plot the first dimension of sites in a 2D lattice
/// @param lattice The lattice to plot
inline void plotLattice2DSurface(const Lattice2D<FLOAT> &lattice) 
{

    // get the min and max values in the lattice
    FLOAT min, max;

    min = lattice.getSite(0, 0)[0];
    max = lattice.getSite(0, 0)[0];

    for (int x = 0; x < lattice.getSizeX(); x++) {
        for (int y = 0; y < lattice.getSizeY(); y++) {
    
            min = std::min(min, lattice.getSite(x, y)[0]);
            max = std::max(min, lattice.getSite(x, y)[0]);

        }
    }

    int xLow = - std::floor((float)lattice.getSizeX() / 2);
    int xHigh = std::ceil((float)lattice.getSizeX() / 2);
    int yLow = - std::floor((float)lattice.getSizeY() / 2);
    int yHigh = std::ceil((float)lattice.getSizeY() / 2);

    std::vector<std::vector<double>> xVals, yVals, zVals;
    // u and v are respectively the x and y components of the arrows we're plotting
    for (int x = xLow; x < xHigh; x++) {
        std::vector<double> xRow, yRow, zRow;
        for (int y = yLow; y < yHigh; y++) {

            auto &siteVals = lattice.getSite(x - xLow, y - yLow);
            float z = (siteVals[0] - min) / (max - min);

            xRow.push_back(x);
            yRow.push_back(y);
            zRow.push_back(z);
        }

        xVals.push_back(xRow);
        yVals.push_back(yRow);
        zVals.push_back(zRow);
    }

    plt::plot_surface(xVals, yVals, zVals);
    plt::show();
}

/// @brief Plot the first 2 dimensions of sites in a 2D lattice
/// @param lattice The lattice to plot
inline void plotLattice2DArrows(const Lattice2D<FLOAT> &lattice) 
{
    int xLow = - std::floor((float)lattice.getSizeX() / 2);
    int xHigh = std::ceil((float)lattice.getSizeX() / 2);
    int yLow = - std::floor((float)lattice.getSizeY() / 2);
    int yHigh = std::ceil((float)lattice.getSizeY() / 2);

    std::vector<int> xVals, yVals;
    // u and v are respectively the x and y components of the arrows we're plotting
    std::vector<float> uVals, vVals;
    for (int x = xLow; x < xHigh; x++) {
        for (int y = yLow; y < yHigh; y++) {

            xVals.push_back(x);
            yVals.push_back(y);

            auto &siteVals = lattice.getSite(x - xLow, y - yLow);
            uVals.push_back(siteVals[0]);
            vVals.push_back(siteVals[1]);
        }
    }

    plt::quiver<int, int, float, float>(xVals, yVals, uVals, vVals);
    plt::show();
}