#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <string>
#include <fstream>

#include "printer/Complex.h"
#include "printer/Input.h"
#include "printer/Wav.h"

// Файл менеджер
struct FileManager {
		
	// Чтение файла
	std::vector<Complex<float>> loadFile(const std::string& path);

	// Вывод в файл
	void saveSignal(const std::string& wavFile, const std::vector<float>& signal);
	
	static int getSamplingFreq();

	static int getParameterDown();

	static uint32_t getSize();

	static std::string getModulation();

	private:
		static std::string modulation; // Тип модуляции
		static int samplingFreq;	// Частота дискретизации
		static int parameterDown; // Параметр передискретизации
		static uint32_t size; // Размер файла
};

#endif
