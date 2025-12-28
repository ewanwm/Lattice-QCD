#pragma once 

class SampleWriterBase {

public:

    /// @brief Constructor
    /// @param outputName The name of the output file *without* any extension
    SampleWriterBase(std::string outputName)
    :
        m_stepsWritten(0),
        m_outputName(outputName)
    {
    }

    /// @defgroup Add data to the current step
    /// @{
    virtual void addFloat(std::string name, FLOAT &value) = 0;
    virtual void addInt(std::string name, uint &value) = 0;
    virtual void addInt(std::string name, int &value) = 0;
    virtual void addBool(std::string name, bool &value) = 0;
    /// @}

    /// @brief Write a step to the output file
    virtual void writeStep() = 0;

protected:

    uint m_stepsWritten;
    std::string m_outputName;

};

