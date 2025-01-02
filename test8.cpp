#include <iostream>
#include <memory>
#include <type_traits>

// Original namespace and code
namespace n212
{
    struct device
    {
        virtual void output() = 0;
        virtual ~device() {}
    };

    template <void (*action)()>
    struct smart_device : device
    {
        void output() override
        {
            (*action)();
        }
    };

    void say_hello_in_english()
    {
        std::cout << "Hello, world!\n";
    }

    void say_hello_in_spanish()
    {
        std::cout << "Hola mundo!\n";
    }
}

// Exercise namespace and code
namespace exercise
{
    struct device
    {
        virtual void output() = 0;
        virtual ~device() {}
    };

    template <typename T, void (T::*action)()>
    struct smart_device : device
    {
        T* obj;
        smart_device(T* object) : obj(object) {}
        
        void output() override
        {
            (obj->*action)();
        }
    };

    struct greetings
    {
        void say_hello_in_french()
        {
            std::cout << "Bonjour le monde!\n";
        }

        void say_hello_in_german()
        {
            std::cout << "Hallo Welt!\n";
        }
    };
}

int main()
{
    using namespace exercise;

    greetings greet;

    auto device1 = std::make_unique<smart_device<greetings, &greetings::say_hello_in_french>>(&greet);
    device1->output();

    auto device2 = std::make_unique<smart_device<greetings, &greetings::say_hello_in_german>>(&greet);
    device2->output();

    static_assert(!std::is_same_v<decltype(device1), decltype(device2)>);

    return 0;
}