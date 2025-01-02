#include <iostream>
#include <tuple>
#include <type_traits>

// Define the WrappableType concept
template <typename T>
concept WrappableType = std::is_trivial_v<T>;

// Define wrapper7 with a default template parameter
template <WrappableType T = int>
class wrapper7 {
public:
    wrapper7(T value) : value_(value) {}

    void display() const {
        std::cout << "wrapper7 value: " << value_ << std::endl;
    }

private:
    T value_;
};

// Define wrapper8 as a variadic template
template <WrappableType... T>
class wrapper8 {
public:
    wrapper8(T... values) : values_(std::make_tuple(values...)) {}

    void display() const {
        std::apply([](auto&&... args) { ((std::cout << args << ' '), ...); }, values_);
        std::cout << std::endl;
    }

private:
    std::tuple<T...> values_;
};

// Test cases
int main() {
    // Test wrapper7 with default int type
    wrapper7<> w7_default(42);
    w7_default.display(); // Expected output: wrapper7 value: 42

    // Test wrapper7 with custom type
    wrapper7<float> w7_custom(3.14f);
    w7_custom.display(); // Expected output: wrapper7 value: 3.14

    // Test wrapper8 with multiple types
    wrapper8<int, float, char> w8(1, 2.5f, 'a');
    w8.display(); // Expected output: 1 2.5 a

    // Static assertions to ensure types meet the WrappableType concept
    static_assert(WrappableType<int>);
    static_assert(WrappableType<float>);
    static_assert(WrappableType<char>);
    static_assert(!WrappableType<std::string>); // Should fail

    return 0;
}