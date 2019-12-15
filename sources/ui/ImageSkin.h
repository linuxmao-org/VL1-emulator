#pragma once
#include "utility/CairoExtra.h"

class ImageSkin
{
public:
	enum Orientation {
		kOrientationAuto,
		kOrientationHorizontal,
		kOrientationVertical,
	};

	ImageSkin(cairo_surface_t *surface, unsigned imageCount, Orientation ori = kOrientationAuto);
	ImageSkin(const ImageSkin &other);
	ImageSkin &operator=(const ImageSkin &other);

	cairo_surface_t *getImageForRatio(double ratio) const;

	unsigned getWidth() const;
	unsigned getHeight() const;

	Orientation getOrientation() const;
	void setOrientation(Orientation ori);

	Orientation getEffectiveOrientation() const;

private:
	void makeDecoupage() const;

private:
	cairo_surface_u fSurface;
	unsigned fImageCount = 0;
	Orientation fOrientation = kOrientationAuto;
	mutable std::unique_ptr<cairo_surface_u[]> fSubSurface;
};