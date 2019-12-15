#include "json.hpp"
#include <unordered_map>
#include <memory>
#include <cstdio>

struct FILE_deleter { void operator()(FILE *x) const noexcept { fclose(x); } };
typedef std::unique_ptr<FILE, FILE_deleter> FILE_u;

static bool load_json(const std::string &path, nlohmann::json &json)
{
	FILE_u file(fopen(path.c_str(), "rb"));
	if (!file)
		return false;

	if (fseek(file.get(), 0, SEEK_END) != 0)
		return false;

	off_t size = ftell(file.get());

	if (fseek(file.get(), 0, SEEK_SET) != 0)
		return false;

	std::unique_ptr<char[]> data(new char[size]);
	if (fread(data.get(), size, 1, file.get()) != 1)
		return false;

	file.reset();

	json = nlohmann::json::parse(&data[0], &data[size]);

	return true;
}

static bool is_path_separator(char c)
{
	if (c == '/')
		return true;
#ifdef _WIN32
	if (c == '\\')
		return true;
#endif
	return false;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Please indicate the path of Res.json.\n");
		return 1;
	}

	FILE *res_out = stdout;

	std::string res_dict_filename = argv[1];
	nlohmann::json res_dict;

	if (!load_json(res_dict_filename, res_dict))
	{
		fprintf(stderr, "Cannot load the resource dictionary as JSON.\n");
		return 1;
	}

	std::string res_dict_dirname = res_dict_filename;
	while (!res_dict_dirname.empty() && !is_path_separator(res_dict_dirname.back()))
		res_dict_dirname.pop_back();
	if (res_dict_dirname.empty())
		res_dict_dirname = "./";

	std::unordered_map<unsigned, unsigned> res_lengths;

	for (const auto &item : res_dict.items())
	{
		unsigned res_id = std::stoi(item.key());
		std::string res_file = item.value()["file"];
		std::string res_path = res_dict_dirname + res_file;

		fprintf(res_out, "static const unsigned char res_%u[] = {", res_id);
		unsigned res_length = 0;
		FILE_u res_in(fopen(res_path.c_str(), "rb"));
		if (!res_in)
		{
			fprintf(stderr, "Cannot open the resource file: %s.\n", res_path.c_str());
			return 1;
		}

		char buf[8192];
		for (size_t count; (count = fread(buf, 1, sizeof(buf), res_in.get())) > 0;)
		{
			res_length += count;
			for (size_t i = 0; i < count; ++i)
				fprintf(res_out, "%d,", (unsigned char)buf[i]);
		}

		if (ferror(res_in.get()))
		{
			fprintf(stderr, "Cannot read the resource file: %s.\n", res_path.c_str());
			return 1;
		}
		res_in.reset();

		fprintf(res_out, "};\n");
		res_lengths[res_id] = res_length;
	}

	fprintf(
		res_out, "struct Resource\n{\n"
		"\t" "unsigned int id;" "\n"
		"\t" "unsigned int type;" "\n"
		"\t" "const unsigned char *data;" "\n"
		"\t" "unsigned int size;" "\n"
		"};\n");

	fprintf(res_out, "extern const Resource RES[] =\n{\n");
	for (const auto &item : res_dict.items())
	{
		unsigned res_id = std::stoi(item.key());
		std::string res_type = item.value()["type"];
		std::string res_file = item.value()["file"];
		unsigned res_length = res_lengths.at(res_id);

		while (res_type.size() < 4)
			res_type += ' ';
		if (res_type.size() != 4)
		{
			fprintf(stderr, "The resource type is invalid: %s\n", res_type.c_str());
			return 1;
		}

		fprintf(
			res_out, "\t" "{%u, '%s', res_%u, %u}, /* %s */\n",
			res_id, res_type.c_str(), res_id, res_length, res_file.c_str());
	}

	fprintf(res_out, "};\n");
	fprintf(res_out, "extern const unsigned int NRES = %lu;\n", res_dict.size());

	return 0;
}
