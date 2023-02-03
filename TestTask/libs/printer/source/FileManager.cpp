#include "printer/FileManager.h"

std::vector<Complex<float>> FileManager::loadFile(const std::string& path)
{
	Timer timer;
	std::ifstream file;

	size_t pos = path.rfind(".");
	if (!path.compare(pos + 1, 3, "dat"))
	{
		samplingFreq = 16000;
		modulation = "AM";
		parameterDown = Input::getFreq() / samplingFreq;
	}
	else if (!path.compare(pos + 1, 3, "bin"))
	{
		samplingFreq = 32000;
		modulation = "FM";
		parameterDown = Input::getFreq() / samplingFreq;
	}

	file.open(path, std::ios::binary | std::ios::in);
	if (!file.is_open())
	{
		std::cout << "Файл не открылся" << std::endl;
		exit(1);
	}
	else
	{
		std::cout << "Файл открылся" << std::endl;

		file.seekg(0, std::ios::end);
		size = file.tellg() / 4;

		std::cout << "Частота дискретизации: " << samplingFreq << std::endl;
		std::cout << "Модуляция: " << modulation << std::endl;
		std::cout << "Параметр передискретизации: " << parameterDown << std::endl;
		std::cout << "Размер файла: " << size << std::endl;

		file.seekg(0, std::ios::beg);

		std::vector<Complex<float>> signal(size / 2);
		int data_re = 0;
		int data_im = 0;

		if (modulation == "AM")
		{
			for (uint32_t i = 0; i < size/2; i++)
			{
				file.read((char*)&data_re, sizeof data_re);
				file.read((char*)&data_im, sizeof data_im);
				Complex<float> sample_int(data_re, data_im);
				signal[i] = sample_int;
			}
		}
		else if (modulation == "FM")
		{
			file.read(reinterpret_cast<char*>(signal.data()), size*4);
		}

		file.close();
		return signal;
	}
}

void FileManager::saveSignal(const std::string& wavFile, const std::vector<float>& signal)
{
	Timer timer;
	std::cout << "Запись wav файла" << std::endl;
	static_assert(sizeof(wavHdr) == 44, "");
	std::string outName = wavFile; // raw pcm data without wave header
	uint32_t wavSize = signal.size();
	
	std::cout << "file size: " << wavSize << std::endl;

	wavHdr wav;
	wav.samplesPerSec = samplingFreq;
	wav.bytesPerSec = 2 * samplingFreq;
	wav.chunkSize = wavSize + sizeof(wavHdr) - 8;
	wav.subchunk2Size = wavSize;

	std::ofstream out(outName, std::ios::binary);

	out.write(reinterpret_cast<const char*>(&wav), sizeof(wav));
	int16_t outSample;
	for (uint32_t i = 0; i < wavSize; ++i) {
		// TODO: read/write in blocks
		outSample = signal[i];
		out.write(reinterpret_cast<char*>(&outSample), sizeof(int16_t));
	}
}

int FileManager::getSamplingFreq()
{
	return samplingFreq;
}

int FileManager::getParameterDown()
{
	return parameterDown;
}

uint32_t FileManager::getSize()
{
	return size;
}

std::string FileManager::getModulation()
{
	return modulation;
}

std::string FileManager::modulation = "AM";
int FileManager::samplingFreq = 16000;
int FileManager::parameterDown = 1;
uint32_t FileManager::size = 2;
