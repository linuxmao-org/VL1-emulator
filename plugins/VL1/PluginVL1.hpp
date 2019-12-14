#ifndef PLUGIN_VL1_H
#define PLUGIN_VL1_H

#include "DistrhoPlugin.hpp"
#include "SharedVL1.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

class PluginVL1 : public Plugin
{
public:
	PluginVL1();

protected:
	// -------------------------------------------------------------------
	// Information

	const char *getLabel() const noexcept override;
	const char *getDescription() const override;
	const char *getMaker() const noexcept override;
	const char *getHomePage() const override;
	const char *getLicense() const noexcept override;
	uint32_t getVersion() const noexcept override;
	int64_t getUniqueId() const noexcept override;

	// -------------------------------------------------------------------
	// Init

	void initParameter(uint32_t index, Parameter &parameter) override;
	void initProgramName(uint32_t index, String &programName) override;

	// -------------------------------------------------------------------
	// Internal data

	float getParameterValue(uint32_t index) const override;
	void setParameterValue(uint32_t index, float value) override;
	void loadProgram(uint32_t index) override;

	// -------------------------------------------------------------------
	// Optional

	// Optional callback to inform the plugin about a sample rate change.
	void sampleRateChanged(double newSampleRate) override;

	// -------------------------------------------------------------------
	// Process

	void activate() override;

	void run(const float **, float **outputs, uint32_t frames, const MidiEvent *midiEvents,
	         uint32_t midiEventCount) override;

	// -------------------------------------------------------------------

private:
	DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginVL1)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // #ifndef PLUGIN_VL1_H
