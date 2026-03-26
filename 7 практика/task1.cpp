#include <iostream>
#include <iomanip>

int main() {
    int i = 65;
    double d = 3.99;
    float f = 2.5f;
    char c = 'A';
    bool b = true;

    // 1. int <-> double
    double iToD = static_cast<double>(i);
    int dToI = static_cast<int>(d); 
    std::cout << "int 65 to double: " << iToD << " (без потерь)\n";
    std::cout << "double 3.99 to int: " << dToI << " (дробная часть отброшена)\n"; // [cite: 120]

    // 2. double <-> flooat
    float dToF = static_cast<float>(d);
    std::cout << "double to float: " << dToF << " (возможна потеря точности)\n";

    // 3. char <-> int
    int cToI = static_cast<int>(c);
    char iToC = static_cast<char>(i + 1);
    std::cout << "char 'A' to int: " << cToI << " (код ASCII)\n";
    std::cout << "int 66 to char: " << iToC << " (символ 'B')\n";

    // 4. bool <-> int
    int bToI = static_cast<int>(b);
    bool iToB = static_cast<bool>(0);
    std::cout << "bool true to int: " << bToI << "\n";
    std::cout << "int 0 to bool: " << std::boolalpha << iToB << "\n";

    // Особое внимание: выход за пределы char
    int bigNum = 300;
    char overflowChar = static_cast<char>(bigNum);
    std::cout << "int 300 to char: " << (int)overflowChar << " (переполнение/зацикливание)\n";

    return 0;
}
