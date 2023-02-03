// Подключение файлов
#include "printer/Complex.h"
#include "printer/Input.h"
#include "printer/FileManager.h"
#include "printer/Filter.h"
#include "printer/Downsample.h"
#include "printer/Demodulator.h"
#include "printer/Timer.h"
#include <memory>

int main()
{
	Timer timer;
	setlocale(LC_ALL, "ru-RU");
    std::cout << "Начало работы программы" << std::endl;
	FileManager anotherFile;

	// Ввод данных
    Input inFile("../../../tddProject/Input.txt");

	// Считывание отсчётов сигнала из файла
	std::vector<Complex<float>> signal = anotherFile.loadFile(Input::getPath());
	std::vector<float> processedSignal(FileManager::getSize() / 2);
	
	// Фильтрация AM
	if (Input::isFilter() && (FileManager::getModulation() == "AM"))
        signal = Filter<Complex<float>>::filter(signal, Input::isType());
	// Демодуляция
    std::unique_ptr<Demodulator> demodulatorPtr(getPtr(FileManager::getModulation()));
	processedSignal = demodulatorPtr->demodulator(signal);
	
	// Фильтрация FM
	if (Input::isFilter() && (FileManager::getModulation() == "FM"))
        processedSignal = Filter<float>::filter(processedSignal, Input::isType());
	
	// Передискретизация
	if (Input::isDownsample())
        processedSignal = Downsampler<float>::downsample(processedSignal, FileManager::getParameterDown());
	
	// Вывод сигнала
	anotherFile.saveSignal(Input::getWavpath(), processedSignal);

	system("pause");
	return 0;
}
