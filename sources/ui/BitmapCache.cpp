#include "BitmapCache.h"
#include <unordered_map>
#include <mutex>
#include <assert.h>

typedef std::unordered_map<unsigned, cairo_surface_u> tBitmapCache;
static std::mutex bitmapCacheMutex;
static tBitmapCache bitmapCache;

cairo_surface_t *BitmapCache::load(unsigned id)
{
	std::lock_guard<std::mutex> lock(bitmapCacheMutex);

	tBitmapCache::iterator it = bitmapCache.find(id);
	if (it != bitmapCache.end())
		return it->second.get();

	cairo_surface_u image{cairo_image_surface_create_from_png_resource(id)};
	assert(image);

	cairo_surface_t *ret = image.get();
	bitmapCache[id] = std::move(image);
	return ret;
}

void BitmapCache::clear()
{
	std::lock_guard<std::mutex> lock(bitmapCacheMutex);

	bitmapCache.clear();
}
