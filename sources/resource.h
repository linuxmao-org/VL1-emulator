#pragma once

struct Resource
{
	unsigned int id;
	unsigned int type;
	const unsigned char *data;
	unsigned int size;
};

const Resource *GetResource(unsigned int id);
