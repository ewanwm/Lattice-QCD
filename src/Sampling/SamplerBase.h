#pragma once

class SamplerBase {

public:

    /// @brief Constructor
    SamplerBase()
    :
        m_currentStep(0)
    {
    }

    /// @brief Do any initialisation required for the sampler. e.g. setting intial 
    ///        values or lattice configurations
    virtual void initialise() {}

    /// @defgroup Setters
    /// @{
    void SetModel(const std::shared_ptr<ModelBase> newModel) { m_model = newModel; }
    void SetWriter(const std::shared_ptr<SampleWriterBase> newWriter) { m_writer = newWriter; }
    /// @}

    /// @brief perform a single sampler step - calls the user implemented doStep() function and
    ///        increments step counter
    void step() {
        doStep();
        m_currentStep++;
    }

    /// @brief Print info about the current state of the sampler
    virtual void printCurrentStep() const {}

protected:

    /// @brief Perform a single sampler step. Should propose new config, decide whether to move there
    ///        and then do that
    virtual void doStep() = 0;

    /// @brief The Lattice model
    std::shared_ptr<ModelBase> m_model;
    /// @brief The sample writer
    std::shared_ptr<SampleWriterBase> m_writer;
    /// @brief The current step
    uint m_currentStep;

};

