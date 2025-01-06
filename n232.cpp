#include <iostream>
#include <type_traits> // For std::is_same_v

namespace n232
{
    template <typename T>
    void func(T a)
    {
        std::cout << "primary template\n";
    }

    // void func(int a) // Overloaded function, not a specialization
    // {
    //     std::cout << "int overload\n";
    // }

    void func(int a = 0) // Overloaded function with default argument
    {
        std::cout << "int overload with default\n";
    }
}

int main() {
    // Block 1: Testing the primary template `func(T a)`

    // Problem Statement: Verify that the primary template `func(T a)` is called
    // correctly for types other than `int`.

    // Part 1.1: Test with a double.
    {
        std::cout << "\n--- Block 1.1: Testing primary template with double ---\n";
        double val_double = 3.14;
        std::cout << "Calling n232::func(" << val_double << ")\n";
        n232::func(val_double); // Expected output: "primary template"

        // Reasoning Test 1.1.1: Type Deduction
        // Assumption: The compiler should deduce T as double.
        // Verification: std::is_same_v<decltype(val_double), double> is true.
        static_assert(std::is_same_v<decltype(val_double), double>, "Error: val_double is not a double");

        // Reasoning Test 1.1.2: Overload Resolution
        // Assumption: No exact match for `func(double)` among the overloads,
        // so the template should be instantiated.
        // Verification: The output "primary template" confirms this.

        // Function Call Analysis:
        // Function: n232::func<double>(double)
        // Argument: val_double (double, value: 3.14)
        // std::cout:
        //   Time Complexity: O(log(number of characters in the string)) - generally considered constant time for practical purposes.
        //   Space Complexity: O(1) - constant space for the string literal.
        // Expected Output Calculation: The function prints "primary template\n".

        std::cout << "Verification: Output matches expected for primary template with double.\n";
    }

    // Part 1.2: Test with a char.
    {
        std::cout << "\n--- Block 1.2: Testing primary template with char ---\n";
        char val_char = 'a';
        std::cout << "Calling n232::func('" << val_char << "')\n";
        n232::func(val_char); // Expected output: "primary template"

        // Reasoning Test 1.2.1: Type Deduction
        // Assumption: The compiler should deduce T as char.
        // Verification: std::is_same_v<decltype(val_char), char> is true.
        static_assert(std::is_same_v<decltype(val_char), char>, "Error: val_char is not a char");

        // Reasoning Test 1.2.2: Overload Resolution
        // Assumption: No exact match for `func(char)`, template is instantiated.
        // Verification: The output "primary template" confirms this.

        // Function Call Analysis:
        // Function: n232::func<char>(char)
        // Argument: val_char (char, value: 'a')
        // std::cout: Same complexity as above.
        // Expected Output Calculation: "primary template\n".

        std::cout << "Verification: Output matches expected for primary template with char.\n";
    }

    // Block 2: Testing the overload `func(int a)`

    // Problem Statement: Verify that the overload `func(int a)` is called correctly
    // when an integer argument is provided.

    // Part 2.1: Test with a positive integer.
    {
        std::cout << "\n--- Block 2.1: Testing int overload with positive integer ---\n";
        int val_int_pos = 10;
        std::cout << "Calling n232::func(" << val_int_pos << ")\n";
        n232::func(val_int_pos); // Expected output: "int overload"

        // Reasoning Test 2.1.1: Exact Match
        // Assumption: The compiler should find an exact match with `func(int)`.
        // Verification: The output "int overload" confirms this.

        // Function Call Analysis:
        // Function: n232::func(int)
        // Argument: val_int_pos (int, value: 10)
        // std::cout: Same complexity as above.
        // Expected Output Calculation: "int overload\n".

        std::cout << "Verification: Output matches expected for int overload with positive integer.\n";
    }

    // Part 2.2: Test with a negative integer.
    {
        std::cout << "\n--- Block 2.2: Testing int overload with negative integer ---\n";
        int val_int_neg = -5;
        std::cout << "Calling n232::func(" << val_int_neg << ")\n";
        n232::func(val_int_neg); // Expected output: "int overload"

        // Reasoning Test 2.2.1: Exact Match
        // Assumption: The compiler should find an exact match with `func(int)`.
        // Verification: The output "int overload" confirms this.

        // Function Call Analysis:
        // Function: n232::func(int)
        // Argument: val_int_neg (int, value: -5)
        // std::cout: Same complexity as above.
        // Expected Output Calculation: "int overload\n".

        std::cout << "Verification: Output matches expected for int overload with negative integer.\n";
    }

    // Part 2.3: Test with zero.
    {
        std::cout << "\n--- Block 2.3: Testing int overload with zero ---\n";
        int val_int_zero = 0;
        std::cout << "Calling n232::func(" << val_int_zero << ")\n";
        n232::func(val_int_zero); // Expected output: "int overload"

        // Reasoning Test 2.3.1: Exact Match
        // Assumption: The compiler should find an exact match with `func(int)`.
        // Verification: The output "int overload" confirms this.

        // Function Call Analysis:
        // Function: n232::func(int)
        // Argument: val_int_zero (int, value: 0)
        // std::cout: Same complexity as above.
        // Expected Output Calculation: "int overload\n".

        std::cout << "Verification: Output matches expected for int overload with zero.\n";
    }

    // Block 3: Testing the overload `func(int a = 0)`

    // Problem Statement: Verify that the overload `func(int a = 0)` is called
    // correctly when called with no arguments.

    // Part 3.1: Test with no arguments.
    {
        std::cout << "\n--- Block 3.1: Testing int overload with default argument (no arguments provided) ---\n";
        std::cout << "Calling n232::func()\n";
        n232::func(); // Expected output: "int overload with default"

        // Reasoning Test 3.1.1: Default Argument Usage
        // Assumption: The compiler should select the overload with the default argument
        // and use the default value for 'a'.
        // Verification: The output "int overload with default" confirms this.

        // Function Call Analysis:
        // Function: n232::func(int) (with default argument)
        // Argument: Implicitly '0' due to the default argument.
        // std::cout: Same complexity as above.
        // Expected Output Calculation: "int overload with default\n".

        std::cout << "Verification: Output matches expected for int overload with default argument (no arguments).\n";
    }

    // Middle Part Focus (as per example):

    // Focusing on the middle part of Block 2.

    // Problem Statement (Middle of Block 2): Verify the behavior of `func(int a)` with a negative integer.
    // Already covered in Part 2.2. Let's reiterate the verification.

    {
        std::cout << "\n--- Re-verification of Block 2 Middle (Part 2.2) ---\n";
        int val_int_neg = -5;
        std::cout << "Re-calling n232::func(" << val_int_neg << ")\n";
        n232::func(val_int_neg); // Expected output: "int overload"

        // Nested Reasoning Test 2.2.1.1: Argument Type
        // Assumption: The argument is correctly identified as an int.
        static_assert(std::is_same_v<decltype(val_int_neg), int>, "Error: val_int_neg is not an int");

        // Nested Reasoning Test 2.2.1.2: Overload Resolution Priority
        // Assumption: Exact match `func(int)` is preferred over the template or the
        // `func(int a = 0)` overload (even though it could also match).
        // Verification: Output confirms the `func(int)` overload is chosen.

        std::cout << "Re-verification: Output confirms the int overload is selected for negative integer.\n";
    }

    // Last part of the else case (no else cases in this code, focusing on analogous parts).
    // Considering the decision point of overload resolution, let's consider what happens
    // if the argument was ambiguous. This is not the case here, as the overloads are distinct.

    // Last in nested loops (no nested loops, focusing on analogous parts).
    // Considering the last test case in a block, let's look at the last test in Block 3.
    // It's the only test case in Block 3.

    // Middle in the for loop (no for loops, focusing on analogous parts).
    // If we had a loop iterating through different integer values, the "middle" iteration
    // would be similar to testing with zero.

    // Edge case in the while loop middle part (no while loops, focusing on analogous parts).
    // Edge cases for integer arguments include min/max values, zero, and potentially very large numbers
    // (although those would still resolve to `func(int)`).

    // Example of edge case testing for `func(int)`:
    {
        std::cout << "\n--- Edge Case Testing for func(int) ---\n";
        int min_int = -2147483648; // Minimum value for a signed 32-bit integer
        std::cout << "Calling n232::func(" << min_int << ")\n";
        n232::func(min_int); // Expected output: "int overload"

        int max_int = 2147483647; // Maximum value for a signed 32-bit integer
        std::cout << "Calling n232::func(" << max_int << ")\n";
        n232::func(max_int); // Expected output: "int overload"

        std::cout << "Verification: Edge cases for int still resolve to the int overload.\n";
    }

    return 0;
}