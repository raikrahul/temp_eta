#include <iostream>
#include <type_traits>

// Base device class
struct device
{
    virtual void output() = 0;
    virtual ~device() {}
};

// Template smart device class
template <typename Command,  void (Command::*action)(int, int ), typename RetType, typename ArgType>
struct smart_device : device
{
    smart_device(Command* command, ArgType arg) : cmd(command), arg(arg) {}

    void output() override
    {    // Extract elements from the pair
        int  first_arg = arg.first;
        int  second_arg = arg.second;

        // Use the extracted elements
        (cmd->*action)(first_arg, second_arg);
    }

private:
    Command* cmd;
    ArgType arg;
};

// Command class with multiple actions
struct calculator_command
{
    void add(int a, int b)
    {
        std::cout << "Addition: " << (a + b) << std::endl;
    }

    void subtract(int a, int b)
    {
        std::cout << "Subtraction: " << (a - b) << std::endl;
    }

    void multiply(int a, int b)
    {
        std::cout << "Multiplication: " << (a * b) << std::endl;
    }

    void divide(int a, int b)
    {
        if (b != 0)
            std::cout << "Division: " << (a / b) << std::endl;
        else
            std::cout << "Division by zero error" << std::endl;
    }
};

// Test cases
void test_smart_device()
{
    calculator_command calc_cmd;
    int arg1 = 10;
    int arg2 = 5;

    smart_device<calculator_command, &calculator_command::add, void, std::pair<int, int>> add_device(&calc_cmd, std::make_pair(arg1, arg2));
    smart_device<calculator_command, &calculator_command::subtract, void, std::pair<int, int>> subtract_device(&calc_cmd, std::make_pair(arg1, arg2));
    smart_device<calculator_command, &calculator_command::multiply, void, std::pair<int, int>> multiply_device(&calc_cmd, std::make_pair(arg1, arg2));
    smart_device<calculator_command, &calculator_command::divide, void, std::pair<int, int>> divide_device(&calc_cmd, std::make_pair(arg1, arg2));

    std::cout << "Testing addition..." << std::endl;
    add_device.output(); // Expected: Implement addition logic

    std::cout << "Testing subtraction..." << std::endl;
    subtract_device.output(); // Expected: Implement subtraction logic

    std::cout << "Testing multiplication..." << std::endl;
    multiply_device.output(); // Expected: Implement multiplication logic

    std::cout << "Testing division..." << std::endl;
    divide_device.output(); // Expected: Implement division logic
}

int main()
{
    test_smart_device();
    return 0;
}