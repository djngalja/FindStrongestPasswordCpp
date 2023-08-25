#include "Table.h"

int main()
{
    std::cout << "Enter passwords separated by white spaces:" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    Table comprison_table(input);
    comprison_table.PrintTable();

    system("pause");
    return 0;
}
