#include <iostream>
#include <type_traits>

// Concept to check if a type is trivial
template <typename T>
concept TrivialType = std::is_trivial_v<T>;

// Wrapper class using the TrivialType concept
template <TrivialType T>
class Wrapper {
public:
    Wrapper(T const v) : value(v) {}

    T const& get() const { return value; }

    // Function to be implemented by the user
    template <typename U>
    U convert() const
    {
        return static_cast<U>(value);
    }

private:
    T value;
};

// Main function to test the Wrapper class
int main() {
    Wrapper<int> intWrapper(42);
    Wrapper<double> doubleWrapper(3.14);

    std::cout << "Wrapper<int>: " << intWrapper.get() << std::endl;
    std::cout << "Wrapper<double>: " << doubleWrapper.get() << std::endl;

    // Testing the convert function
    std::cout << "Wrapper<int> converted to double: " << intWrapper.convert<double>() << std::endl;
    std::cout << "Wrapper<double> converted to int: " << doubleWrapper.convert<int>() << std::endl;

    return 0;
}

// Note: The convert function should be implemented by the user.
// The function should take the stored value and convert it to the specified type U.