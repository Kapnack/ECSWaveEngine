#include "FileReader.h"

#include <iostream>

#include <filesystem>
#include <sstream>
#include <fstream>

namespace WaveEngine
{
	FileReader::FileReader() : Service()
	{
	}

	FileReader::~FileReader()
	{
	}

	string FileReader::FileImporter(const string_view& filePath, const bool& binary)
	{
		ifstream inStream;

		stringstream buffer;

		try
		{
			inStream.open(filePath, ios::in);

			if (!inStream.is_open())
				throw runtime_error("FilePath; " + string(filePath) + " wasn't found.\n");

			buffer << inStream.rdbuf();

		}
		catch (const runtime_error& e)
		{
			cerr << e.what() << "\n";
		}
		catch (...)
		{
			cerr << "Unknow error detected while trying to read file.\n";
		}

		if (inStream.is_open())
			inStream.close();

		return buffer.str();
	}

	string FileReader::ReadFile(const string_view filePath)
	{
		return FileImporter(filePath, false);
	}

	string FileReader::ReadFileBinary(const string_view filePath)
	{
		return FileImporter(filePath, true);
	}
}