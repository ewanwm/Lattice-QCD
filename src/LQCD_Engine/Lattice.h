#pragma once

#include <memory>
#include <vector>
#include <assert.h>
#include <iostream>

#include "dtypes.h"


template < typename T = FLOAT >
class Lattice2D{

public:
    
    Lattice2D(){

    }

    /// @brief Constructor
    /// @param siteDims Number of dimensions of field at each site
    /// @param nSitesX Number of sites in X direction
    /// @param nSitesY Number of sites in Y direction
    Lattice2D(int siteDims, int nSitesX, int nSitesY)
    : 
        sizeX(nSitesX),
        sizeY(nSitesY),
        nDims(siteDims)
    {
        // set the size of the array 
        siteArray.resize(nSitesX);
        for (int x = 0; x < nSitesX; x ++){
            siteArray[x].resize(nSitesY);

            for (int y = 0; y < nSitesY; y++){
                siteArray[x][y].resize(siteDims);
            }
        }
    }

    /// @brief Get array of values at a particular site
    /// @param x X coord of site
    /// @param y Y coord of site
    /// @return the site values 
    inline const std::vector<T> &getSite(int x, int y) const { return siteArray[x][y]; }

    /// @brief Set the values of this lattice to the ones contained in the other lattice
    /// @param otherLattice The lattice object to take the values from
    inline void set(const Lattice2D<T> &otherLattice){
        assert(otherLattice.getNDims() == nDims);
        assert(otherLattice.getSizeX() == sizeX);
        assert(otherLattice.getSizeY() == sizeY);

        for(int x = 0; x < sizeX; x++){
            for(int y = 0; y < sizeY; y++){
                setSite(x, y, otherLattice.getSite(x, y));
            }
        }
    }

    /// @brief Set the values at a particular site
    /// @param x X coord of the site
    /// @param y Y coord of the site
    /// @param values The values to set
    inline void setSite(int x, int y, const std::vector<T> &values){ 
        assert( values.size() == nDims);
        for (int idx = 0; idx < nDims; idx++)
            siteArray[x][y][idx] = values[idx]; 
    }

    /// @brief Set the values at a particular site for a particular dimension
    /// @param x X coord of the site
    /// @param y Y coord of the site
    /// @param d Dimension
    /// @param value The value to set
    inline void setSite(int x, int y, int d, T value){ 
        siteArray[x][y][d] = value; 
    }

    /// @brief Randomise the values at a specific point in the lattice
    /// @param x X coord of site
    /// @param y Y coord of site
    inline void randomise(int x, int y){
        for (int d = 0; d < nDims; d++){
            /// \todo will need to change this depending on the type T, e.g. will not work if type is complex or matrix valued
            siteArray[x][y][d] = 1.0 - 2.0 * (T)std::rand() / (T)RAND_MAX; 
        }
    }

    /// @brief Randomise the values at every point in the lattice
    inline void randomise(){
        for (int x = 0; x < sizeX; x++){
            for (int y = 0; y < sizeY; y++){
                randomise(x,y);
            }
        }
    }

    /// @brief Print a small summary of this object
    void print(){
        std::cout << "####### 2D Lattice #######" << std::endl;
        std::cout << "  NDims: " << nDims << std::endl;
        std::cout << "  sizeX: " << sizeX << std::endl;
        std::cout << "  sizeY: " << sizeY << std::endl;
    }

    /// @defgroup Getters
    /// @{
    inline const int getNDims() const { return nDims; }
    inline const int getSizeX() const { return sizeX; }
    inline const int getSizeY() const { return sizeY; }
    /// @}

private:
    std::vector< std::vector< std::vector<T> > > siteArray;
    int nDims;
    int sizeX;
    int sizeY;
};