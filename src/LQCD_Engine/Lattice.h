#pragma once

#include <memory>
#include <vector>
#include <assert.h>
#include <iostream>

#include "dtypes.h"


template < typename T = FLOAT >
class Lattice{

public:
    
    Lattice(){

    }

    /// @brief Constructor
    /// @param siteDims Number of dimensions of field at each site
    /// @param sizeX Number of sites in X direction
    /// @param sizeY Number of sites in Y direction
    /// @param sizeZ Number of sites in Z direction
    /// @param sizeT Number of sites in time dimension
    Lattice(int siteDims, int sizeX, int sizeY, int sizeZ, int sizeT)
    : 
        m_sizeX(sizeX),
        m_sizeY(sizeY),
        m_sizeZ(sizeZ),
        m_sizeT(sizeT),
        nDims(siteDims)
    {
        // set the size of the array 
        siteArray.resize(m_sizeX);
        for (int x = 0; x < m_sizeX; x ++){
            siteArray[x].resize(m_sizeY);

            for (int y = 0; y < m_sizeY; y++){
                siteArray[x][y].resize(m_sizeZ);

                for (int z = 0; z < m_sizeZ; z++){
                    siteArray[x][y][z].resize(m_sizeT);
                        
                    for (int t = 0; t < m_sizeT; t++){

                        siteArray[x][y][z][t].resize(siteDims);
                    }
                }
            }
        }
    }

    /// @brief Get array of values at a particular site
    /// @param x X coord of site
    /// @param y Y coord of site
    /// @param z Z coord of site
    /// @param t T coord of site
    /// @return the site values 
    inline const std::vector<T> &getSite(uint x, uint y, uint z, uint t) const { return siteArray[x][y][z][t]; }

    /// @brief Set the values of this lattice to the ones contained in the other lattice
    /// @param otherLattice The lattice object to take the values from
    inline void set(const Lattice<T> &otherLattice){
        assert(otherLattice.getNDims() == nDims);
        assert(otherLattice.getSizeX() == m_sizeX);
        assert(otherLattice.getSizeY() == m_sizeY);
        assert(otherLattice.getSizeZ() == m_sizeZ);
        assert(otherLattice.getSizeT() == m_sizeT);

        for(uint x = 0; x < m_sizeX; x++){
            for(uint y = 0; y < m_sizeY; y++){
                for(uint z = 0; z < m_sizeZ; z++){
                    for(uint t = 0; t < m_sizeT; t++){
                        setSite(x, y, z, t, otherLattice.getSite(x, y, z, t));
                    }
                }
            }
        }
    }

    /// @brief Set the values at a particular site
    /// @param x X coord of the site
    /// @param y Y coord of the site
    /// @param z z coord of the site
    /// @param t T coord of the site
    /// @param values The values to set
    inline void setSite(uint x, uint y, uint z, uint t, const std::vector<T> &values){ 
        assert( values.size() == nDims);
        for (int idx = 0; idx < nDims; idx++)
            siteArray[x][y][z][t][idx] = values[idx]; 
    }

    /// @brief Set the values at a particular site for a particular dimension
    /// @param x X coord of the site
    /// @param y Y coord of the site
    /// @param z Z coord of the site
    /// @param t T coord of the site
    /// @param d Dimension
    /// @param value The value to set
    inline void setSite(uint x, uint y, uint z, uint t, uint d, T value){ 
        siteArray[x][y][z][t][d] = value; 
    }

    /// @brief Randomise the values at a specific point in the lattice
    /// @param x X coord of site
    /// @param y Y coord of site
    /// @param z Z coord of site
    /// @param t T coord of site
    inline void randomise(uint x, uint y, uint z, uint t){
        for (int d = 0; d < nDims; d++){
            /// \todo will need to change this depending on the type T, e.g. will not work if type is complex or matrix valued
            siteArray[x][y][z][t][d] = 1.0 - 2.0 * (T)std::rand() / (T)RAND_MAX; 
        }
    }

    /// @brief Randomise the values at every point in the lattice
    inline void randomise(){
        for (int x = 0; x < m_sizeX; x++){
            for (int y = 0; y < m_sizeY; y++){
                for (int z = 0; z < m_sizeZ; z++){
                    for (int t = 0; t < m_sizeT; t++){
                        randomise(x,y,z,t);
                    }
                }
            }
        }
    }

    /// @brief Print a small summary of this object
    void print(){
        std::cout << "####### 2D Lattice #######" << std::endl;
        std::cout << "  NDims: " << nDims << std::endl;
        std::cout << "  sizeX: " << m_sizeX << std::endl;
        std::cout << "  sizeY: " << m_sizeY << std::endl;
        std::cout << "  sizeZ: " << m_sizeY << std::endl;
        std::cout << "  sizeT: " << m_sizeT << std::endl;
    }

    /// @defgroup Getters
    /// @{
    inline const uint getNDims() const { return nDims; }
    inline const uint getSizeX() const { return m_sizeX; }
    inline const uint getSizeY() const { return m_sizeY; }
    inline const uint getSizeZ() const { return m_sizeZ; }
    inline const uint getSizeT() const { return m_sizeT; }
    /// @}

    /// @brief Get total number of sites in the underlying lattice
    /// @return N sites
    virtual uint getNsites() { return getSizeX() * getSizeY() * getSizeZ() * getSizeT(); };

private:
    std::vector< std::vector< std::vector < std::vector < std::vector<T> > > > > siteArray;
    uint nDims;
    uint m_sizeX;
    uint m_sizeY;
    uint m_sizeZ;
    uint m_sizeT;
};