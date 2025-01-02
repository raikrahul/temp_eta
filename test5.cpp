#include <iostream>
#include <array>
#include <type_traits>

namespace exercise
{
    template <typename T, size_t S>
    class circular_buffer
    {
        static_assert(S > 0, "Size of the buffer must be greater than 0");

        T data_[S];
        size_t head_ = 0;
        size_t tail_ = 0;
        bool full_ = false;

    public:
        constexpr void push(const T& value)
        {
            data_[head_] = value;
            if (full_)
            {
                tail_ = (tail_ + 1) % S;
            }
            head_ = (head_ + 1) % S;
            full_ = head_ == tail_;
        }

        constexpr T pop()
        {
            // TODO: Implement the pop logic to remove and return the value from the tail
            // If the buffer is empty, return a default-constructed value of type T
            if (is_empty())
            {
                return T{};
            }

            T value = data_[tail_];
            full_ = false;
            tail_ = (tail_ + 1) % S;
            return value;
            
        }

        constexpr bool is_empty() const
        {
            return (!full_ && (head_ == tail_));
        }

        constexpr bool is_full() const
        {
            return full_;
        }

        constexpr size_t size() const
        {
            size_t size = S;

            if (!full_)
            {
                if (head_ >= tail_)
                {
                    size = head_ - tail_;
                }
                else
                {
                    size = S + head_ - tail_;
                }
            }

            return size;
        }

        constexpr T const& operator[](size_t const index) const
        {
            return data_[(tail_ + index) % S];
        }
    };

    template <typename T, size_t S>
    circular_buffer<T, S> make_circular_buffer()
    {
        return {};
    }
}

int main()
{
    using namespace exercise;

    circular_buffer<int, 5> buffer;

    buffer.push(1);
    buffer.push(2);
    buffer.push(3);

    std::cout << "Buffer size: " << buffer.size() << "\n";
    std::cout << "Is buffer full? " << std::boolalpha << buffer.is_full() << "\n";

    buffer.push(4);
    buffer.push(5);
    buffer.push(6); // This should overwrite the first element (1)

    std::cout << "Buffer size after pushing 6 elements: " << buffer.size() << "\n";
    std::cout << "Is buffer full? " << std::boolalpha << buffer.is_full() << "\n";
    std::cout << "Element at index 0: " << buffer[0] << "\n"; // Should be 2

    // TODO: Implement the pop logic and then test it here
    // std::cout << "Popped element: " << buffer.pop() << "\n"; // Should be 2
    // std::cout << "Buffer size after popping one element: " << buffer.size() << "\n";

    return 0;
}