#include <iostream>

int main()
{
    int i = 65;
    double d = 3.99;
    float f = 2.5f;
    char c = 'A';
    bool b = true;

    // int <-> double
    double iToD = static_cast<double>(i);
    int dToI = static_cast<int>(d);
    std::cout << "int 65 to double: " << iToD << "\n";
    std::cout << "double 3.99 to int: " << dToI << "\n";

    //double <-> flooat
    float dToF = static_cast<float>(d);
    std::cout << "double to float: " << dToF << "\n";

    //char <-> int
    int cToI = static_cast<int>(c);
    char iToC = static_cast<char>(i + 1);
    std::cout << "char 'A' to int: " << cToI << "\n";
    std::cout << "int 66 to char: " << iToC << "\n";

    //bool <-> int
    int bToI = static_cast<int>(b);
    bool iToB = static_cast<bool>(0);
    std::cout << "bool true to int: " << bToI << "\n";
    std::cout << "int 0 to bool: " << std::boolalpha << iToB << " \n";

    //выход за пределы char
    int bigNum = 300;
    char overflowChar = static_cast<char>(bigNum);
    std::cout << "int 300 to char: " << (int)overflowChar << "\n";

    return 0;
}
