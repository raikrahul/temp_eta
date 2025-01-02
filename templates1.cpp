#include <iostream>
#include <type_traits>
#include <vector>

// Concept to check if a type is an integral type
template <typename T>
concept Integral = std::is_integral_v<T>;

// Concept to check if a type is a floating-point type
template <typename T>
concept FloatingPoint = std::is_floating_point_v<T>;

// Template class that only accepts integral types
template <Integral T>
class IntegralWrapper {
public:
    IntegralWrapper(T value) : value_(value) {}

    T getValue() const { return value_; }

    // TODO: Implement a function to increment the value by a given amount
    void increment(T amount)
    {
        value_ += amount;
    }

private:
    T value_;
};

// Template class that only accepts floating-point types
template <FloatingPoint T>
class FloatingPointWrapper {
public:
    FloatingPointWrapper(T value) : value_(value) {}

    T getValue() const { return value_; }

    // TODO: Implement a function to multiply the value by a given factor
    void multiply(T factor)
    {
        value_ *= factor;
    }

private:
    T value_;
};

// Test cases
void runTests() {
    // Test case for IntegralWrapper
    IntegralWrapper<int> intWrapper(10);
    std::cout << "Initial IntegralWrapper value: " << intWrapper.getValue() << std::endl;
    intWrapper.increment(5);
    std::cout << "After incrementing by 5: " << intWrapper.getValue() << std::endl;

    // Test case for FloatingPointWrapper
    FloatingPointWrapper<double> floatWrapper(2.5);
    std::cout << "Initial FloatingPointWrapper value: " << floatWrapper.getValue() << std::endl;
    floatWrapper.multiply(2.0);
    std::cout << "After multiplying by 2.0: " << floatWrapper.getValue() << std::endl;
}

int main() {
    runTests();
    return 0;
}