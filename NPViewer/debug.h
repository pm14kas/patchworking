#pragma once

#include <fstream>
#include <sstream>
#include <time.h>


static class Debug
{
public:

	static const Debug& Instance()
	{
		static Debug logger;
		return logger;
	}
	static void Log(std::string output)
	{
		std::ofstream file;
		file.open("debug.txt", std::ios::app);
		file << time(0) << " : " << output << std::endl;
		file.close();
	}

	static void Log(char output)
	{
		std::ofstream file;
		file.open("debug.txt", std::ios::app);
		file << time(0) << " : " << output << std::endl;
		file.close();
	}

	static void Log(double output)
	{
		std::ofstream file;
		file.open("debug.txt", std::ios::app);
		file << time(0) << " : " << output << std::endl;
		file.close();
	}

	static void Log(int output)
	{
		std::ofstream file;
		file.open("debug.txt", std::ios::app);
		file << time(0) << " : " << output << std::endl;
		file.close();
	}

	static void Log(double output1, double output2)
	{
		std::ofstream file;
		file.open("debug.txt", std::ios::app);
		file << time(0) << " : " << output1 << ", " << output2 << std::endl;
		file.close();
	}

	static void Log(double output1, double output2, double output3)
	{
		std::ofstream file;
		file.open("debug.txt", std::ios::app);
		file << time(0) << " : " << output1 << ", " << output2<<", "<<output3 << std::endl;
		file.close();
	}

private:
	Debug(){}
	Debug(const Debug& root);
	Debug& operator=(const Debug&);
};