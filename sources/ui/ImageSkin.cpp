/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

#include "ImageSkin.h"
#include <stdexcept>
#include <cassert>

ImageSkin::ImageSkin(cairo_surface_t *surface, unsigned imageCount, Orientation ori)
{
	assert(surface);
	assert(imageCount > 0);

	fSurface.reset(cairo_surface_reference(surface));
	fImageCount = imageCount;
	fOrientation = ori;

	cairo_format_t fmt = cairo_image_surface_get_format(surface);
	if (fmt != CAIRO_FORMAT_ARGB32 && fmt != CAIRO_FORMAT_RGB24)
		throw std::runtime_error("unsupported skin image format");
}

ImageSkin::ImageSkin(const ImageSkin &other)
{
	fSurface.reset(cairo_surface_reference(other.fSurface.get()));
	fImageCount = other.fImageCount;
	fOrientation = other.fOrientation;
}

ImageSkin &ImageSkin::operator=(const ImageSkin &other)
{
	fSurface.reset(cairo_surface_reference(other.fSurface.get()));
	fImageCount = other.fImageCount;
	fOrientation = other.fOrientation;
	fSubSurface.reset();
	return *this;
}

unsigned ImageSkin::getImageCount() const
{
	return fImageCount;
}

cairo_surface_t *ImageSkin::getImageForRatio(double ratio) const
{
	if (!fSubSurface)
		makeDecoupage();

	unsigned imageCount = fImageCount;
	int index = (int)(0.5 + ratio * (imageCount - 1));
	index = (index < 0) ? 0 : index;
	index = ((unsigned)index < imageCount) ? index : (imageCount - 1);
	return fSubSurface[index].get();
}

unsigned ImageSkin::getWidth() const
{
	cairo_surface_t *surface = fSurface.get();
	unsigned imageCount = fImageCount;

	unsigned w = cairo_image_surface_get_width(surface);
	return (getEffectiveOrientation() == kOrientationHorizontal) ?
		(w / imageCount) : w;
}

unsigned ImageSkin::getHeight() const
{
	cairo_surface_t *surface = fSurface.get();
	unsigned imageCount = fImageCount;

	unsigned h = cairo_image_surface_get_height(surface);
	return (getEffectiveOrientation() == kOrientationVertical) ?
		(h / imageCount) : h;
}

ImageSkin::Orientation ImageSkin::getOrientation() const
{
	return fOrientation;
}

void ImageSkin::setOrientation(Orientation ori)
{
	fOrientation = ori;
	fSubSurface.reset();
}

ImageSkin::Orientation ImageSkin::getEffectiveOrientation() const
{
	Orientation ori = fOrientation;
	if (ori == kOrientationAuto)
	{
		cairo_surface_t *surface = fSurface.get();
		unsigned w = cairo_image_surface_get_width(surface);
		unsigned h = cairo_image_surface_get_height(surface);
		return (w > h) ? kOrientationHorizontal : kOrientationVertical;
	}
	return ori;
}

void ImageSkin::makeDecoupage() const
{
	cairo_surface_t *surface = fSurface.get();
	unsigned imageCount = fImageCount;

	cairo_surface_u *subSurface = new cairo_surface_u[imageCount];
	fSubSurface.reset(subSurface);

	cairo_format_t fmt = cairo_image_surface_get_format(surface);
	unsigned char *d = cairo_image_surface_get_data(surface);

	unsigned wf = cairo_image_surface_get_width(surface);
	unsigned hf = cairo_image_surface_get_height(surface);
	unsigned s = cairo_image_surface_get_stride(surface);

	bool vertical = getEffectiveOrientation() == kOrientationVertical;

	unsigned w = vertical ? wf : (wf / imageCount);
	unsigned h = vertical ? (hf / imageCount) : hf;

	unsigned bpp;
	switch (fmt) {
		case CAIRO_FORMAT_ARGB32:
			bpp = 4;
			break;
		case CAIRO_FORMAT_RGB24:
			bpp = 3;
			break;
		default:
			throw std::runtime_error("unsupported skin image format");
	}

	for (unsigned i = 0; i < imageCount; ++i)
	{
		cairo_surface_t *sub;
		if (vertical)
			sub = cairo_image_surface_create_for_data(d + i * (h * s), fmt, w, h, s);
		else
			sub = cairo_image_surface_create_for_data(d + i * (bpp * w), fmt, w, h, s);
		if (!surface)
			throw std::runtime_error("cannot extract skin image region");
		subSurface[i].reset(sub);
	}
}
