#include <fstream>
#include <ostream>
#include <nlohmann/json.hpp>

#include "dtypes.h"
#include "SampleWriterBase.h"

using json = nlohmann::json;

class SampleWriterJSON : public SampleWriterBase {

public:

    SampleWriterJSON(const std::string outputName)
    :
        SampleWriterBase(outputName),
        m_outFile(nullptr) 
    {

        // open the output file for writing
        m_outFile = std::ofstream((m_outputName + ".json").c_str());

    }

    ~SampleWriterJSON() {
        m_outFile.close();
    }

    inline void addFloat(std::string name, FLOAT &value) {
        stepData[name] = value;
    }

    inline void addInt(std::string name, uint &value) {
        stepData[name] = value;
    }

    inline void addInt(std::string name, int &value) {
        stepData[name] = value;
    }

    inline void addBool(std::string name, bool &value) {
        stepData[name] = value;
    }

    inline void writeStep() {

        m_outFile << std::setw(4) << stepData << std::endl;

    }

private:

    json stepData;

    std::ofstream m_outFile;

};