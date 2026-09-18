#include <print>

int fibonacci_recursive(const int value)
{
    if (value < 0) {
        return -1;
    }

    if (value == 0 || value == 1) { 
        return value;
    }

    return fibonacci_recursive(value - 1) + fibonacci_recursive(value - 2);
}

int fibonacci_iterative(const int value)
{
    if (value < 0) {
        return -1;
    }

    if (value == 0 || value == 1) { 
        return value;
    }

    int prev1 = 1;
    int prev2 = 0;
    int current = prev1 + prev2;

    for (size_t i = 2; i <= value; ++i) {
        current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }

    return current;
}

int main(int argc, char** argv)
{
    std::print("{}\n", fibonacci_recursive(2));
    std::print("{}\n", fibonacci_recursive(10));

    std::print("{}\n", fibonacci_iterative(2));
    std::print("{}\n", fibonacci_iterative(10));
    
    return 0;
}