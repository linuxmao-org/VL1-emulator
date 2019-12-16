#pragma once
#include "Control.h"
#include "ImageSkin.h"

class KickButton : public CControl
{
public:
	KickButton(ImageSkin skin, Widget *group);

	bool hasInvertedAppearance() const { return fHasInvertedAppearance; }
	void setHasInvertedAppearance(bool inv);

	bool onMouse(const MouseEvent &event) override;
	void onDisplay() override;

private:
	bool fValue = false;
	bool fIsPressed = false;
	bool fHasInvertedAppearance = false;
	ImageSkin fSkin;
};
