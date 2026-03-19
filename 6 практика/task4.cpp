#include <iostream>
#include <string>

class FileHandler
{
private:
    std::string fileName;
    bool isOpen;
    int* buffer;

public:
    FileHandler(std::string name) : fileName(name), isOpen(false), buffer(nullptr)
    {
        std::cout << "Попытка открыть файл " << fileName << "..." << std::endl;
        
        // Имитация открытия и выделения памяти
        isOpen = true;
        buffer = new int[1024]; // Выделяем 1024 байта (имитация)
        
        std::cout << "Файл " << fileName << " открыт, буфер выделен" << std::endl;
    }

    ~FileHandler()
    {
        if (isOpen)
        {
            delete[] buffer; // Освобождаем память
            buffer = nullptr;
            isOpen = false;
            std::cout << "Файл " << fileName << " закрыт, буфер освобожден" << std::endl;
        }
    }

    // Метод записи
    void write(const std::string& data)
    {
        if (isOpen)
          std::cout << "Запись в файл " << fileName << ": \"" << data << "\"" << std::endl;
        else
          std::cerr << "Ошибка. Попытка записи в закрытый файл" << std::endl;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");

    std::cout << "=== Сценарий 1: Правильное использование RAII ===" << std::endl;
    {
        FileHandler log("system.log");
        log.write("Инициализация системы...");
        log.write("Работа выполнена успешно.");
    } // Здесь объект log уничтожается автоматически
    std::cout << "--- Блок завершен ---" << std::endl;

    std::cout << "\n=== Сценарий 2: Имитация утечки ресурсов ===" << std::endl;
    FileHandler* leakyFile = new FileHandler("leak.txt");
    leakyFile->write("Эти данные могут быть потеряны...");
    
    // Намеренно НЕ вызываем delete leakyFile;
    std::cout << "!!! Внимание: delete не вызван. Программа завершается." << std::endl;

    return 0;
}
