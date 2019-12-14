#include "CairoExtra.h"
#include "resource.h"
#include <unordered_map>

cairo_surface_t *
cairo_image_surface_create_from_png_data(const unsigned char *data, unsigned length)
{
	struct PngReaderData
	{
		const unsigned char *dataPtr;
		unsigned sizeLeft;
	};

	auto readSomePngData = [](void *closure,
							  unsigned char *data,
							  unsigned int length) noexcept -> cairo_status_t
						   {
							   PngReaderData &readerData = *reinterpret_cast<PngReaderData *>(closure);
							   if (readerData.sizeLeft < length)
								   return CAIRO_STATUS_READ_ERROR;

							   memcpy(data, readerData.dataPtr, length);
							   readerData.dataPtr += length;
							   readerData.sizeLeft -= length;
							   return CAIRO_STATUS_SUCCESS;
						   };

	PngReaderData readerData;
	readerData.dataPtr = data;
	readerData.sizeLeft = length;
	return cairo_image_surface_create_from_png_stream(+readSomePngData, &readerData);
}

cairo_surface_t *
cairo_image_surface_create_from_png_resource(unsigned int id)
{
	const Resource *res = GetResource(id);

	if (!res || res->type != 'png ')
		return nullptr;

	return cairo_image_surface_create_from_png_data(res->data, res->size);
}
