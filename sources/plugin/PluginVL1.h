#ifndef PLUGIN_VL1_H
#define PLUGIN_VL1_H

#include "DistrhoPlugin.hpp"
#include "SharedVL1.h"
#include "Filters.h"
#include "SharedData.h"
#include <functional>
#include <memory>
#include <atomic>
#include <mutex>

// -----------------------------------------------------------------------

class PluginVL1 : public Plugin
{
public:
	PluginVL1();
	~PluginVL1();

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

	void initAudioPort(bool input, uint32_t index, AudioPort& port) override;
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
	void deactivate() override;

	void run(const float **, float **outputs, uint32_t frames, const MidiEvent *midiEvents,
	         uint32_t midiEventCount) override;

	// -------------------------------------------------------------------

public:
	CSharedData *GetSharedData() { return &m_sharedData; }
	const CSharedData *GetSharedData() const { return &m_sharedData; }

	int GetModeI() { return m_modeI; }
	bool IsPlayingDemoSong() const { return m_bDemoSong; }

	CSequencer *GetSequencer() const { return m_sequencer.get(); }

	void HandleKey(int key, float value);
	void SendKey(int noteOnOff, int note, int velocity);

	void Reset();
	void OnMode(int mode);
	void OnReset();
	void OnDel();
	void OnRhythm(float value);
	void OnMusic();
	void OnAutoPlay();
	void OnOneKeyPlayDotDot(float value);
	void OnOneKeyPlayDot(float value);

	void Calculator(int key);
	void AutoPlay();
	void OneKeyPlay();
	void ResetSound();

	void MemorizeAdsrPresetFromCalculator();
	const tVL1Preset &GetAdsrPreset() const { return m_adsr; }
	bool IsEditingAdsr() const { return m_editingAdsr; }
	void SetEditingAdsr(bool edit) { m_editingAdsr = edit; }

	const tLcdScreenData &GetLcdScreenData() const { return *m_lcdScreenData; }
	float GetTempoUpDown(bool bUp) const;

	typedef std::function<void()> tSynchronousCallback;
	void PerformEditSynchronous(const tSynchronousCallback &fn);

private:
	CSharedData m_sharedData;

	std::unique_ptr<CCalculator> m_calculator;
	std::unique_ptr<CLcdBuffer> m_lcdBuffer;
	std::unique_ptr<tLcdScreenData> m_lcdScreenData;
	std::unique_ptr<CWaveSet> m_waves;
	std::unique_ptr<CSequencer> m_sequencer;
	std::unique_ptr<CRhythm> m_rhythm;
	std::unique_ptr<CEventManager> m_eventManager;
	std::unique_ptr<CVoiceManager> m_voices1;
	std::unique_ptr<CClock> m_clock;

	float m_octave = 0;
	float m_balance = 0;
	float m_volume = 0;
	float m_tempo = 0;
	float m_tune = 0;

	tVL1Preset m_adsr {};
	bool m_editingAdsr = false;

	int m_modeI = kVL1Off;
	bool m_bDemoSong = false;
	bool m_bOneKeyPlay = false;
	bool m_bIgnoreNextEvent = false;

	CIIR1 m_lp1;
	CIIR1 m_lp2;

	std::unique_ptr<tParameterRange[]> m_parameterRanges;
	std::unique_ptr<uint32_t[]> m_parameterHints;

	bool fIsActive = false;
	std::mutex fRunMutex;

	std::atomic<const tSynchronousCallback *> fSynchronousCallback{};
	std::atomic<bool> fSynchronousCompletion{};

	DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginVL1)
};

// -----------------------------------------------------------------------

#endif // #ifndef PLUGIN_VL1_H
