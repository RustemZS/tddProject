#ifndef FILTER_H
#define FILTER_H

#include "printer/Complex.h"
#include "printer/FileManager.h"
#include "printer/Input.h"

// Фильтр скользящего среднего
template <class T>
struct Filter {
    static std::vector<T> filter(const std::vector<T>& inSignal, bool filterType)
	{
		Timer time;
		std::vector<T> outSignal(inSignal.size());
		uint32_t window = (2 * Input::getFreq() / FileManager::getSamplingFreq());

        if (filterType)
		{
			// Нерекурсивный фильтр
			// window - Количество отсчетов интервала усреднения
			std::cout << "Работает нерекурсивный фильтр" << std::endl;
			T sumx; // Сумма отсчетов на интервале
			sumx = 0;
			for (uint32_t i = 0; i < inSignal.size(); ++i) {
				uint32_t j = 0;
				while (i >= j)
				{
					sumx = sumx + inSignal[i - j];
					j++;
					if (j > window - 1)
					{
						j = i + 1;
					}

				}
				outSignal[i] = sumx / window;
				sumx = 0;
			}
		}
		else
		{
			// Рекурсивный фильтр
			// window - Количество отсчетов интервала усреднения
			std::cout << "Работает рекурсивный фильтр" << std::endl;
			T sumx; // Сумма отсчетов на интервале
			sumx = 0;
			T* mas; // Массив для хранения window отсчетов
			uint32_t index = 0; // Индекс элемента массива
			mas = new T[window];
			for (uint32_t i = 0; i < window; ++i)
				mas[i] = 0;
			for (uint32_t i = 0; i < inSignal.size(); ++i) {
				sumx = sumx - mas[index];
				mas[index] = inSignal[i];
				sumx = sumx + mas[index];
				index++;
				if (index >= window)
					index = 0; // Возврат к началу "окна"
				outSignal[i] = sumx / window;
			}
			delete[] mas;
		}
		return outSignal;
	}
};

#endif
