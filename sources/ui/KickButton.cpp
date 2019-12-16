#include "KickButton.h"
#include "Cairo.hpp"
#include "ImageSkin.h"
#include "Window.hpp"

KickButton::KickButton(ImageSkin skin, Widget *group)
	: CControl(group), fSkin(skin)
{
	setSize(skin.getWidth(), skin.getHeight());
}

void KickButton::setHasInvertedAppearance(bool inv)
{
	if (fHasInvertedAppearance == inv)
		return;

	fHasInvertedAppearance = inv;
	repaint();
}

bool KickButton::onMouse(const MouseEvent &event)
{
	DGL::Size<uint> wsize = getSize();
	DGL::Point<int> mpos = event.pos;

	bool inside = mpos.getX() >= 0 && mpos.getY() >= 0 && (unsigned)mpos.getX() < wsize.getWidth() &&
	              (unsigned)mpos.getY() < wsize.getHeight();

	if (event.press && event.button == 1 && inside)
	{
		fIsPressed = true;
		setValue(1);
		return true;
	}
	else if (!event.press && event.button == 1 && fIsPressed)
	{
		fIsPressed = false;
		setValue(0);
		return true;
	}

	return false;
}

void KickButton::onDisplay()
{
	const ImageSkin &skin = fSkin;
	cairo_t *cr = getParentWindow().getGraphicsContext().cairo;

	int w = getWidth();
	int h = getHeight();

	bool checked = fValue ^ fIsPressed;
	if (fHasInvertedAppearance)
		checked = !checked;

	cairo_surface_t *image = skin.getImageForRatio(checked ? 1.0 : 0.0);
	cairo_rectangle(cr, 0, 0, w, h);
	cairo_set_source_surface(cr, image, 0, 0);
	cairo_fill(cr);
}
