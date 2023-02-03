#include <gtest/gtest.h>
#include "printer/printer.h"

#include "printer/Complex.h"
#include "printer/Input.h"
#include "printer/FileManager.h"
#include "printer/Demodulator.h"
#include "printer/Filter.h"
#include "printer/Downsample.h"

/**
 * @brief этот тест ничего не тестирует. это стартовый тест, который был написан до написания кода свомого принтера.
 * если этот тест проходит успешно, то конструкторы этого класса реализованны и с созданием объекта всё ок.
 */
TEST(PrinterTests, Creating) {
	Printing::Printer testedObject;
	Printing::Printer testedObject1(std::cerr);
}
/**
 * @brief TEST в этом тесте не создаётся объектов. поэтому число созданных объектов равно нулю
 */
TEST(PrinterTests, CheckCountCreatedObjects_nothing) {
	ASSERT_EQ(Printing::Printer::getCountCreatedPrinters(), 0);
}
/**
 * @brief TEST создаём три подряд объекта. счётчик созданных объектов равен нулю
 */
TEST(PrinterTests, CheckCountCreatedObjects) {
	Printing::Printer testedObject;
	Printing::Printer testedObject1;
	Printing::Printer testedObject2;

	ASSERT_EQ(Printing::Printer::getCountCreatedPrinters(), 3);
}
/**
 * @brief TEST создаётся три подряд объекта в куче. далее по одному объекты начинают удаляться.
 * после каждого последующего удаления количество созданных принеторов декрементируется.
 * и достигает нуля, когда каждый из созданных обектов уничтожился.
 *
 */
TEST(PrinterTests, CheckCountCreatedObjectsWithDelete) {
	Printing::Printer* testedObject = new Printing::Printer();
	Printing::Printer* testedObject1 = new Printing::Printer();
	Printing::Printer* testedObject2 = new Printing::Printer();

	delete  testedObject;
	ASSERT_EQ(Printing::Printer::getCountCreatedPrinters(), 2);
	delete  testedObject1;
	ASSERT_EQ(Printing::Printer::getCountCreatedPrinters(), 1);
	delete  testedObject2;
	ASSERT_EQ(Printing::Printer::getCountCreatedPrinters(), 0);
}
/**
 * @brief этот тест проверяет печатает ли принтер вообще что-то, результат виден только в виде вывода в консоль
 */
TEST(PrinterTests, printing_stock) {
	Printing::Printer testedObject;
	testedObject.print(" Hello Word! ");
}
/**
 * @brief этот тест проверяет печатает ли принтер путём подстановки собственного потока вывода.
 * в данном случае это объект класса std::stringstream
 * результат печати должен находиться в объекте printString, и должен представлять из себя сторку для печати + escape последовательность '\n'
 * '\n' переводит каретку в начало следующей строки
 */
TEST(PrinterTests, printing_custom) {
	std::stringstream printString;

	Printing::Printer testedObject(printString);

	testedObject.print(" Hello Word! ");

	auto printerResult = printString.str();
	ASSERT_EQ(printerResult, (" Hello Word! \n"));
}

/**
 * @brief Тест проверяет правильность реализации конструктора класса Complex.
 */
TEST(ComplexTests, Creating) {
    Complex<float> testedObject;
    Complex<float> testedObject1(1, 1);
}
/**
 * @brief TEST В этом тесте проверяется работа метода abs при разных вводных данных.
 */
TEST(ComplexTests, CheckMetod_abs) {
    Complex<float> testedObject;
    Complex<float> testedObject1(2, 2);
    Complex<float> testedObject2(6, 8);
    Complex<float> testedObject3(1.2, 0.5);
    ASSERT_FLOAT_EQ(testedObject.abs(), 0);
    ASSERT_FLOAT_EQ(testedObject1.abs(), sqrt(2*2 + 2*2));
    ASSERT_FLOAT_EQ(testedObject2.abs(), 10);
    ASSERT_FLOAT_EQ(testedObject3.abs(), 1.3);
}
/**
 * @brief TEST В этом тесте проверяется работа метода arg при разных вводных данных.
 */
TEST(ComplexTests, CheckMetod_arg) {
    Complex<float> testedObject(2, 2);
    Complex<float> testedObject1(6, 8);
    Complex<float> testedObject2(1.2, 0.5);
    ASSERT_FLOAT_EQ(testedObject.arg(), atan2(2,2));
    ASSERT_FLOAT_EQ(testedObject1.arg(), atan2(8,6));
    ASSERT_FLOAT_EQ(testedObject2.arg(), atan2(0.5,1.2));
}
/**
 * @brief TEST В этом тесте проверяется работа метода argDeg при разных вводных данных.
 */
TEST(ComplexTests, CheckMetod_argDeg) {
    Complex<float> testedObject(2, 2);
    Complex<float> testedObject1(6, 8);
    Complex<float> testedObject2(1.2, 0.5);
    ASSERT_FLOAT_EQ(testedObject.argDeg(), atan2(2,2)*180/3.14159);
    ASSERT_FLOAT_EQ(testedObject1.argDeg(), atan2(8,6)*180/3.14159);
    ASSERT_FLOAT_EQ(testedObject2.argDeg(), atan2(0.5,1.2)*180/3.14159);
}

/**
 * @brief Тест проверяет правильность реализации конструктора и деструктора класса Timer.
 */
TEST(TimerTests, Creating) {
    Timer timer1;
}

/**
 * @brief В этом тесте проверяется работа метода downsample при разных параметрах передискретизации.
 */
TEST(DownsampleTests, CheckMetodDownsampleWithDifferentParametersDown) {
    std::vector<float> testedObject(10);
    testedObject = Downsampler<float>::downsample(testedObject,1);
    ASSERT_EQ(testedObject.size(), 10);
    testedObject = Downsampler<float>::downsample(testedObject,2);
    ASSERT_EQ(testedObject.size(), 5);
    testedObject = Downsampler<float>::downsample(testedObject,2);
    ASSERT_EQ(testedObject.size(), 3);
}
/**
 * @brief В этом тесте проверяется работа метода downsample при разных типах входных данных.
 */
TEST(DownsampleTests, CheckMetodDownsampleWithDifferentTypes) {
    std::vector<float> testedObject(10);
    testedObject = Downsampler<float>::downsample(testedObject,2);
    ASSERT_EQ(testedObject.size(), 5);
    std::vector<Complex<float>> testedObject1(10);
    testedObject1 = Downsampler<Complex<float>>::downsample(testedObject1,2);
    ASSERT_EQ(testedObject.size(), 5);
}

/**
 * @brief В этом тесте проверяется работа метода filter при разных типах входных данных.
 */
TEST(FilterTests, CheckMetodFilter) {
    std::vector<float> testedObject(2);
    for(int i=0; i<2; ++i)
    {
        testedObject[i] = i+1;
    }
    testedObject = Filter<float>::filter(testedObject,0);
    std::vector<float> correctAnswer(2);
    correctAnswer[0] = 0.5;
    correctAnswer[1] = 1.5;
    ASSERT_EQ(testedObject, correctAnswer);
    std::vector<float> testedObject1(2);
    for(int i=0; i<2; ++i)
    {
        testedObject1[i] = i+1;
    }
    testedObject1 = Filter<float>::filter(testedObject1,1);
    ASSERT_EQ(testedObject1, correctAnswer);
}

/**
 * @brief Тест проверяет правильность реализации конструктора класса Input.
 */
TEST(InputTests, Creating) {
    Input testedObject("../../../tddProject-master/Input.txt");
}
/**
 * @brief Тест проверяет правильность реализации деструктора класса Input.
 */
TEST(InputTests, Removing) {
    {
        Input testedObject("../../../tddProject-master/Input.txt");
    }
    ASSERT_EQ(Input::getPath(), "test");
    ASSERT_EQ(Input::getFreq(), 16000);
    ASSERT_EQ(Input::getWavpath(), "test.wav");
    ASSERT_EQ(Input::isFilter(), 0);
    ASSERT_EQ(Input::isDownsample(), 0);
    ASSERT_EQ(Input::isType(), 0);
}
/**
 * @brief TEST В этом тесте проверяется работа метода getPath.
 */
TEST(InputTests, CheckMetod_getPath) {
    ASSERT_EQ(Input::getPath(), "test");
}
/**
 * @brief TEST В этом тесте проверяется работа метода getFreq.
 */
TEST(InputTests, CheckMetod_getFreq) {
    ASSERT_EQ(Input::getFreq(), 16000);
}
/**
 * @brief TEST В этом тесте проверяется работа метода getWavpath.
 */
TEST(InputTests, CheckMetod_getWavpath) {
    ASSERT_EQ(Input::getWavpath(), "test.wav");
}
/**
 * @brief TEST В этом тесте проверяется работа метода isFilter, определяющего нужна ли фильтрация.
 */
TEST(InputTests, CheckMetod_isFilter) {
    ASSERT_EQ(Input::isFilter(), 0);
}
/**
 * @brief TEST В этом тесте проверяется работа метода isDownsample, определяющего нужна ли передискретизация.
 */
TEST(InputTests, CheckMetod_isDownsample) {
    ASSERT_EQ(Input::isDownsample(), 0);
}
/**
 * @brief TEST В этом тесте проверяется работа метода isType, определяющего какой тип фильтра использовать.
 */
TEST(InputTests, CheckMetod_isType) {
    ASSERT_EQ(Input::isType(), 0);
}

/**
 * @brief Тест проверяет правильность реализации конструктора класса DemodulatorAM.
 */
TEST(DemodulatorTests, CheckAMDemodulator) {
    std::vector<Complex<float>> signal(10);
    std::vector<float> processedSignal(10);
    std::unique_ptr<Demodulator> demodulatorPtr(getPtr("AM"));
    processedSignal = demodulatorPtr->demodulator(signal);
}
/**
 * @brief Тест проверяет правильность реализации конструктора класса DemodulatorFM.
 */
TEST(DemodulatorTests, CheckFMDemodulator) {
    std::vector<Complex<float>> signal(10);
    std::vector<float> processedSignal(10);
    std::unique_ptr<Demodulator> demodulatorPtr(getPtr("FM"));
    processedSignal = demodulatorPtr->demodulator(signal);
}

/**
 * @brief TEST В этом тесте проверяется работа метода getSamplingFreq.
 */
TEST(FileManagerTests, CheckMetod_getSamplingFreq) {
    ASSERT_EQ(FileManager::getSamplingFreq(), 16000);
}
/**
 * @brief TEST В этом тесте проверяется работа метода getParameterDown.
 */
TEST(FileManagerTests, CheckMetod_getParameterDown) {
    ASSERT_EQ(FileManager::getParameterDown(), 1);
}
/**
 * @brief TEST В этом тесте проверяется работа метода getSize.
 */
TEST(FileManagerTests, CheckMetod_getSize) {
    ASSERT_EQ(FileManager::getSize(), 2);
}
/**
 * @brief TEST В этом тесте проверяется работа метода getModulation.
 */
TEST(FileManagerTests, CheckMetod_getModulation) {
    ASSERT_EQ(FileManager::getModulation(), "AM");
}
