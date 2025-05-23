#include <iostream>
#include <cstring>



void ReadData(char** lines, int32_t* keys, int32_t N)
{
    const int32_t MAX_SIZE{ 100 };
    char buffer[MAX_SIZE]{};
    for (int32_t i{ 0 }; i < N; ++i)
    {
        std::cin.getline(buffer, MAX_SIZE);

        int32_t number{};
        char temp[100]{};
        if (sscanf_s(buffer, "%s %d", temp, (unsigned)sizeof(temp), &number) != 2)
        {
            std::cout << "неверный формат строки " << i + 1 << ".\n";
            for (int32_t j{ 0 }; j < i; ++j)
            {
                delete[] lines[j];
            }
            delete[] lines;
        }
        keys[i] = number;
        int32_t len = std::strlen(buffer);
        lines[i] = new char[len + 1] {};
        strcpy_s(lines[i], len + 1, buffer);
    }
}


void SortData(int32_t* keys, char** lines, int32_t N)
{
    for (int32_t i{ 1 }; i < N; ++i) {
        int32_t currentKey = keys[i];
        char* currentLine = lines[i];
        int32_t j = i - 1;
        while (j >= 0 && keys[j] > currentKey)
        {
            keys[j + 1] = keys[j];
            lines[j + 1] = lines[j];
            --j;
        }
        keys[j + 1] = currentKey;
        lines[j + 1] = currentLine;
    }
}


int32_t sumkey(const int32_t* keys, int32_t N)
{
    int32_t sum{0};
    for (int32_t i{ 0 }; i < N; ++i)
    {
        sum += keys[i];
    }
    return sum;
}


int32_t maxkey(const int32_t* keys, int32_t N)
{
    int32_t max{ keys[1] };
    for (int32_t i{ 0 }; i < N; ++i)
    {
        if (keys[i] > max)
        {
            max = keys[i];
        }
    }
    return max;
}


int32_t minkey(const int32_t* keys, int32_t N)
{
    int32_t min{ keys[1] };
    for (int32_t i{0}; i < N; ++i)
    {
        if (keys[i] < min)
        {
            min = keys[i];
        }
    }
    return min;
}


void OutputArray(char** lines, int32_t N)
{
    std::cout << "\nОтсортированные строки:\n";
    for (int i{ 0 }; i < N; ++i)
    {
        std::cout << lines[i] << "\n";
    }
}


void DeleteArray(char** lines, int32_t N)
{
    for (int32_t i{ 0 }; i < N; ++i)
    {
        delete[] lines[i];
    }
    delete[] lines;
}

int main()
{
    std::setlocale(LC_ALL, "RU");
    int N{};
    std::cout << "Введите количество строк: ";
    std::cin >> N;
    std::cin.ignore(); 
    if (N <= 0)
    {
        std::cout << " количество строк должно быть больше 0 \n";
        return 1;
    }
    char** lines = new char* [N] {};
    int32_t* keys = new int[N] {};
    ReadData(lines, keys, N);
    SortData(keys, lines, N);
    OutputArray(lines, N);
    std::cout << "\nСумма чисел: " << sumkey(keys, N) << "\n" << "Максимальное число: " << maxkey(keys, N) << "\n" << "Минимальное число: " << minkey(keys, N) << "\n";
    DeleteArray(lines, N);
    delete[] keys;
    return 0;
}