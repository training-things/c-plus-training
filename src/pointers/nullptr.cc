#include <iostream>

int main()
{
    char *table_dir_path = nullptr;

    if (table_dir_path == NULL)
    {
        std::cout << "nullptr == NULL" << std::endl;
    }
    else
    {
        std::cout << "nullptr != NULL" << std::endl;
    }

    if (table_dir_path)
    {
        std::cout << "nullptr free" << std::endl;
        free(table_dir_path);
    }

    auto s = strdup(NULL);

    std::cout << "s = " << s << std::endl;
}