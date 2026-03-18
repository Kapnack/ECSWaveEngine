#pragma once

#include <string>
#include <fstream>
#include <iostream>

#include "ServiceProvider/Service.h"
#include "Export.h"

class BaseGame;
class ServiceProvider;

using namespace std;

namespace WaveEngine
{
	WAVEEXPORT class FileReader : public Service
	{
	private:

		FileReader();
		~FileReader();

		string FileImporter(const string_view& filePath, const bool& binary);

		template<typename T>
		void WriteIntoFile(ofstream& outStream, T& data)
		{
			outStream.write(reinterpret_cast<char*>(&data), sizeof(data));
		}

		template<typename T>
		void LoadFromFile(ifstream& inStream, T& data)
		{
			inStream.read(reinterpret_cast<char*>(&data), sizeof(data));
		}

		friend class BaseGame;
		friend class ServiceProvider;

	public:

		WAVEEXPORT string ReadFile(const string_view filePath);

		WAVEEXPORT string ReadFileBinary(const string_view filePath);

		template<typename... T>
		void SaveData(const string_view filePath, T&... data)
		{
			ofstream outStream;

			try
			{
				outStream.open(filePath, ios::out | ios::binary);

				if (!outStream.is_open())
					throw runtime_error("FilePath; " + string(filePath) + " wasn't found.\n");

				(WriteIntoFile(outStream, data), ...);

			}
			catch (const runtime_error& e)
			{
				cerr << e.what() << "\n";
			}
			catch (...)
			{
				cerr << "Unknow error detected while trying to read file.\n";
			}

			if (outStream.is_open())
				outStream.close();
		}

		template<typename... T>
		void SaveData(const string_view filePath, int& amount, T&... data)
		{
			ofstream outStream;

			try
			{
				outStream.open(filePath, ios::out | ios::binary);

				if (!outStream.is_open())
					throw runtime_error("FilePath; " + string(filePath) + " wasn't found.\n");

				WriteIntoFile(outStream, amount);
				(WriteIntoFile(outStream, data), ...);

			}
			catch (const runtime_error& e)
			{
				cerr << e.what() << "\n";
			}
			catch (...)
			{
				cerr << "Unknow error detected while trying to read file.\n";
			}

			if (outStream.is_open())
				outStream.close();
		}

		template<typename... T>
		void LoadData(const string_view filePath, T&... data)
		{
			ifstream inStream;

			try
			{
				inStream.open(filePath, ios::out | ios::binary);

				if (!inStream.is_open())
					throw runtime_error("FilePath; " + string(filePath) + " wasn't found.\n");

				(LoadFromFile(inStream, data), ...);

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
		}
	};
}