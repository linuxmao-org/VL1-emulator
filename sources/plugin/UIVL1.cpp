#include "UIVL1.h"
#include "Window.hpp"
#include "VL1Program.h"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------
// Init / Deinit

UIVL1::UIVL1() : UI(600, 400)
{
}

UIVL1::~UIVL1()
{
}

// -----------------------------------------------------------------------
// DSP/Plugin callbacks

/**
  A parameter has changed on the plugin side.
  This is called by the host to inform the UI about parameter changes.
*/
void UIVL1::parameterChanged(uint32_t index, float value)
{
	switch (index)
	{
#pragma message("TODO implement me")
		default:
			(void)value;
	}
}

/**
  A program has been loaded on the plugin side.
  This is called by the host to inform the UI about program changes.
*/
void UIVL1::programLoaded(uint32_t index)
{
	DISTRHO_SAFE_ASSERT_RETURN(index < kNumPrograms, );

	const CVL1Program &program = GetFactoryPresets()[index];

	for (uint32_t i = 0; i < kNumParams; i++)
	{
		// set values for each parameter and update their widgets
		parameterChanged(i, program.GetParameter(i));
	}
}

/**
  Optional callback to inform the UI about a sample rate change on the plugin side.
*/
void UIVL1::sampleRateChanged(double newSampleRate)
{
	(void)newSampleRate;
}

// -----------------------------------------------------------------------
// Optional UI callbacks

/**
  Idle callback.
  This function is called at regular intervals.
*/
void UIVL1::uiIdle()
{
}

/**
  Window reshape function, called when the parent window is resized.
*/
void UIVL1::uiReshape(uint width, uint height)
{
	(void)width;
	(void)height;
}

// -----------------------------------------------------------------------
// Widget callbacks

/**
  A function called to draw the view contents.
*/
void UIVL1::onDisplay()
{

	cairo_t *cr = getParentWindow().getGraphicsContext().cairo;

	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_paint(cr);
}

// -----------------------------------------------------------------------
// Optional widget callbacks; return true to stop event propagation, false otherwise.

/**
  A function called when a key is pressed or released.
*/
bool UIVL1::onKeyboard(const KeyboardEvent &ev)
{
	return false;
	(void)ev;
}

/**
  A function called when a special key is pressed or released.
*/
bool UIVL1::onSpecial(const SpecialEvent &ev)
{
	return false;
	(void)ev;
}

/**
  A function called when a mouse button is pressed or released.
*/
bool UIVL1::onMouse(const MouseEvent &ev)
{
	return false;
	(void)ev;
}

/**
  A function called when the mouse pointer moves.
*/
bool UIVL1::onMotion(const MotionEvent &ev)
{
	return false;
	(void)ev;
}

/**
  A function called on scrolling (e.g. mouse wheel or track pad).
*/
bool UIVL1::onScroll(const ScrollEvent &ev)
{
	return false;
	(void)ev;
}

// -----------------------------------------------------------------------

UI *createUI()
{
	return new UIVL1();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
