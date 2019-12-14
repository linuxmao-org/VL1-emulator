#ifndef PLUGIN_VL1_H
#define PLUGIN_VL1_H

#include "DistrhoPlugin.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

class PluginVL1 : public Plugin
{
public:
	enum Parameters
	{
		paramVolumeLeft = 0,
		paramVolumeRight,
		paramCount
	};

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
	float fParams[paramCount];
	double fSampleRate;

	DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginVL1)
};

struct Preset
{
	const char *name;
	float params[PluginVL1::paramCount];
};

const Preset factoryPresets[] = {
    {"Default", {0.2f, 0.2f}}
    //,{
    //    "Another preset",  // preset name
    //    {0.5f, ...}        // array of presetCount float param values
    //}
};

const uint presetCount = sizeof(factoryPresets) / sizeof(Preset);

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // #ifndef PLUGIN_VL1_H
