#include <iostream>
#include <utility>

int main()
{
    unsigned int original = 42;

    unsigned int result = std::exchange(original, 0);

    std::cout << "result   = " << result << '\n';
    std::cout << "original = " << original << '\n';

    return 0;
}