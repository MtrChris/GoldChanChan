#include "ExceptionClasses.h"
using namespace std;

LoadFailure::LoadFailure() : filename(string("unknown file")), filetype(string("unknown type"))
{
	error_content = "Error while loading: \nFilename: \"" + filename +
		"\", Filetype: " + filetype + "\n";
}

LoadFailure::LoadFailure(string& fname, string& ftype) : filename(fname), filetype(ftype)
{
	error_content = "Error while loading: \nFilename: \"" + filename +
		"\", Filetype: " + filetype + "\n";
}

LoadFailure::LoadFailure(const char* fname, const char* ftype)
{
	filename = string(fname);
	filetype = string(ftype);
	error_content = "Error while loading: \nFilename: \"" + filename +
		"\", Filetype: " + filetype + "\n";
}

const char* LoadFailure::what() const
{
	return error_content.c_str();
}

LoadFailure::~LoadFailure()
{
	exception::~exception();
}