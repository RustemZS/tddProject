#include "printer/Input.h"

Input::Input(std::string start)
{
	Timer timer;
	std::ifstream in;
	in.open(start);
	if (!in.is_open())
	{
		std::cout << "Файл не открылся" << std::endl;
		exit(1);
	}
	else
	{

		std::getline(in, data);
		std::cout << data << std::endl;
		read.assign(data, 25, data.length() - 25);
		path = read;

		std::getline(in, data);
		std::cout << data << std::endl;
		read.assign(data, 18, data.length() - 18);
		wavFile = read;

		std::getline(in, data);
		std::cout << data << std::endl;
		intToBool = std::stoi(read.assign(data, 59, data.length() - 59));
		if (intToBool == 0)
		{
			needFilter = 0;
		}
		else if (intToBool == 1)
		{
			needFilter = 1;
		}

		std::getline(in, data);
		std::cout << data << std::endl;
		intToBool = std::stoi(read.assign(data, 78, data.length() - 78));
		if (intToBool == 0)
		{
			filterType = 0;
		}
		else if (intToBool == 1)
		{
			filterType = 1;
		}

		std::getline(in, data);
		std::cout << data << std::endl;
		frequency = std::stoi(read.assign(data, 37, data.length() - 37));

		std::getline(in, data);
		std::cout << data << std::endl;
		intToBool = std::stoi(read.assign(data, 65, data.length() - 65));
		if (intToBool == 0)
		{
			needDownsampling = 0;
		}
		else if (intToBool == 1)
		{
			needDownsampling = 1;
		}
	}
	in.close();
}

Input::~Input()
{
    path = "test";
    wavFile = "test.wav";
    frequency = 16000;
    needFilter = 0;
    filterType = 0;
    needDownsampling = 0;
}

std::string Input::getPath()
{
	return path;
}

std::string Input::getWavpath()
{
	return wavFile;
}

int Input::getFreq()
{
	return frequency;
}

bool Input::isFilter()
{
	return needFilter;
}

bool Input::isDownsample()
{
	return needDownsampling;
}

bool Input::isType()
{
	return filterType;
}

std::string data = " ";
std::string read = " ";
int intToBool = 0;

std::string Input::path = "test";
std::string Input::wavFile = "test.wav";
int Input::frequency = 16000;
bool Input::needFilter = 0;
bool Input::filterType = 0;
bool Input::needDownsampling = 0;
