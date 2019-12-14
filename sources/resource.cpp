#include "resource.h"
#include <algorithm>

extern const Resource RES[];
extern const unsigned int NRES;

static bool operator<(const Resource &a, const Resource &b)
{
	return a.id < b.id;
}

const Resource *GetResource(unsigned int id)
{
	/* binary search into a sorted array */
	Resource ref;
	ref.id = id;
	const Resource *begin = RES;
	const Resource *end = begin + NRES;
	const Resource *res = std::lower_bound(begin, end, ref);
	return (res != end && res->id == id) ? res : nullptr;
}
