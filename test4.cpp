#include <iostream>
#include <type_traits>

// Provided Code Block
namespace n208
{
    template <int V>
    class foo1 {
    public:
        void display() const {
            std::cout << "foo1: " << V << '\n';
        }
    };

    template <int V = 42>
    class foo2 {
    public:
        void display() const {
            std::cout << "foo2: " << V << '\n';
        }
    };

    template <int... V>
    class foo3 {
    public:
        void display() const {
            std::cout << "foo3: ";
            ((std::cout << V << ' '), ...);
            std::cout << '\n';
        }
    };
}

// Exercise Code Block
namespace exercise
{
    // Template class `bar1` that takes a single integer template parameter `V`
    template <int V>
    class bar1 {
    public:
        // Trivial part: display function
        void display() const {
            std::cout << "bar1: " << V << '\n';
        }

        // TODO: Implement this function to return V raised to the power of 2
        constexpr int squared() const
        {
            return V * V;
        }
    };

    // Template class `bar2` that takes a single integer template parameter `V` with a default value of 100
    template <int V = 100>
    class bar2 {
    public:
        // Trivial part: display function
        void display() const {
            std::cout << "bar2: " << V << '\n';
        }

        // TODO: Implement this function to return V raised to the power of 3
        constexpr int cubed() const
        {
            return V * V * V;
        }
    };

    // Template class `bar3` that takes a variadic list of integer template parameters `V`
    template <int... V>
    class bar3 {
    public:
        // Trivial part: display function
        void display() const {
            std::cout << "bar3: ";
            ((std::cout << V << ' '), ...);
            std::cout << '\n';
        }

        // TODO: Implement this function to return the sum of all values in V
        constexpr int sum() const
        {
            int res = 0; 

            res += (V + ...);

            return res;

            
        }
    };
}

// Test cases
int main() {
    using namespace exercise;

    bar1<5> b1;
    b1.display();
    static_assert(b1.squared() == 25, "bar1::squared failed");

    bar2<3> b2;
    b2.display();
    static_assert(b2.cubed() == 27, "bar2::cubed failed");

    bar3<1, 2, 3> b3;
    b3.display();
    static_assert(b3.sum() == 6, "bar3::sum failed");

    std::cout << "All tests passed!\n";
    return 0;
}