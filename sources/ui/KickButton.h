#pragma once
#include "Widget.hpp"
#include "ImageSkin.h"
#include <functional>

class KickButton : public Widget
{
public:
	KickButton(ImageSkin skin, Widget *group);

	bool hasInvertedAppearance() const { return fHasInvertedAppearance; }
	void setHasInvertedAppearance(bool inv);

	bool onMouse(const MouseEvent &event) override;
	void onDisplay() override;

	std::function<void()> TriggerCallback;

private:
	bool fValue = false;
	bool fIsPressed = false;
	bool fHasInvertedAppearance = false;
	ImageSkin fSkin;
};
