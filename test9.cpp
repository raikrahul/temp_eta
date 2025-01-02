#include <iostream>
#include <array>
#include <string>
#include <algorithm>
#include <cassert>
#include <cstring>

namespace n214
{
   template<size_t N>
   struct string_literal
   {
      constexpr string_literal(const char(&str)[N])
      {
         std::copy_n(str, N, value);
      }

      char value[N];
   };

   template <string_literal x>
   struct foo
   {
   };

   // Imagine a 1950s automotive company tracking parts information.
   // We want to categorize parts based on their name, the production line they belong to,
   // their expected lifespan (in years), and whether they are a critical component.

   template <string_literal PartName, char ProductionLine, int LifespanYears, bool IsCritical>
   struct PartSpecification
   {
      static constexpr string_literal part_name = PartName;
      static constexpr char production_line = ProductionLine;
      static constexpr int lifespan_years = LifespanYears;
      static constexpr bool is_critical = IsCritical;
      static_assert(lifespan_years > 0, "Lifespan must be a positive number of years.");

      // Insight 1: Using string_literal allows us to have the part name available at compile time.
      // Insight 2: We are using multiple non-type template parameters of different types (string_literal, char, int, bool).

      // Trivial function to get the part name
      constexpr auto getPartName() const { return part_name.value; }

      // Trivial function to get the production line
      constexpr auto getProductionLine() const { return production_line; }

      // Trivial function to get the lifespan
      constexpr auto getLifespanYears() const { return lifespan_years; }

      // Trivial function to check if it's a critical component
      constexpr auto isCritical() const { return is_critical; }

      // TODO: The hardest part - a function to determine if the part name contains a specific material.
      // The material will be provided as a template argument to this member function.
      template <string_literal Material>
      constexpr bool containsMaterial() const
      {
         // TODO: Implement the logic to check if part_name.value contains Material.value.
     
        
         // return strstr(part_name.value, Material.value) != nullptr;

         return false; // Placeholder return value
      }
   };

   void testPartSpecification()
   {
      // Test Case 1: A standard part
      using Part1 = PartSpecification<string_literal{"Spark Plug"}, 'A', 2, false>;
      static_assert(Part1::part_name.value[0] == 'S', "Test Case 1 Failed: Part name mismatch");
      static_assert(Part1::production_line == 'A', "Test Case 1 Failed: Production line mismatch");
      static_assert(Part1::lifespan_years == 2, "Test Case 1 Failed: Lifespan mismatch");
      static_assert(Part1::is_critical == false, "Test Case 1 Failed: Critical mismatch");

      // Test Case 2: A critical part with a longer name
      using Part2 = PartSpecification<string_literal{"Engine Block Assembly"}, 'B', 10, true>;
      static_assert(Part2::part_name.value[0] == 'E', "Test Case 2 Failed: Part name mismatch");
      static_assert(Part2::production_line == 'B', "Test Case 2 Failed: Production line mismatch");
      static_assert(Part2::lifespan_years == 10, "Test Case 2 Failed: Lifespan mismatch");
      static_assert(Part2::is_critical == true, "Test Case 2 Failed: Critical mismatch");

      // Test Case 3: Another standard part from a different production line
      using Part3 = PartSpecification<string_literal{"Wheel Bearing"}, 'C', 5, false>;
      static_assert(Part3::part_name.value[0] == 'W', "Test Case 3 Failed: Part name mismatch");
      static_assert(Part3::production_line == 'C', "Test Case 3 Failed: Production line mismatch");
      static_assert(Part3::lifespan_years == 5, "Test Case 3 Failed: Lifespan mismatch");
      static_assert(Part3::is_critical == false, "Test Case 3 Failed: Critical mismatch");

      // Test Case 4: A critical part with a shorter lifespan
      using Part4 = PartSpecification<string_literal{"Brake Pad"}, 'A', 1, true>;
      static_assert(Part4::part_name.value[0] == 'B', "Test Case 4 Failed: Part name mismatch");
      static_assert(Part4::production_line == 'A', "Test Case 4 Failed: Production line mismatch");
      static_assert(Part4::lifespan_years == 1, "Test Case 4 Failed: Lifespan mismatch");
      static_assert(Part4::is_critical == true, "Test Case 4 Failed: Critical mismatch");

      // Test Case 5: Testing the trivial getter functions
      constexpr Part1 p1{};
      static_assert(std::string_view(p1.getPartName()) == "Spark Plug", "Test Case 5 Failed: getPartName mismatch");
      static_assert(p1.getProductionLine() == 'A', "Test Case 5 Failed: getProductionLine mismatch");
      static_assert(p1.getLifespanYears() == 2, "Test Case 5 Failed: getLifespanYears mismatch");
      static_assert(p1.isCritical() == false, "Test Case 5 Failed: isCritical mismatch");

      constexpr Part2 p2{};
      static_assert(std::string_view(p2.getPartName()) == "Engine Block Assembly", "Test Case 5 Failed: getPartName mismatch");
      static_assert(p2.getProductionLine() == 'B', "Test Case 5 Failed: getProductionLine mismatch");
      static_assert(p2.getLifespanYears() == 10, "Test Case 5 Failed: getLifespanYears mismatch");
      static_assert(p2.isCritical() == true, "Test Case 5 Failed: isCritical mismatch");

      // Test Case 6: Testing the containsMaterial function (TODO part - these tests will initially fail)
      constexpr Part1 p6{};
      static_assert(p6.containsMaterial<string_literal{"Steel"}>() == false, "Test Case 6 Failed: Material check not implemented yet");
      static_assert(p6.containsMaterial<string_literal{"Plug"}>() == false, "Test Case 6 Failed: Material check not implemented yet");

      constexpr Part2 p7{};
      static_assert(p7.containsMaterial<string_literal{"Iron"}>() == false, "Test Case 7 Failed: Material check not implemented yet");
      static_assert(p7.containsMaterial<string_literal{"Assembly"}>() == false, "Test Case 7 Failed: Material check not implemented yet");
   }
} // namespace n214

int main()
{
   n214::testPartSpecification();
   std::cout << "All initial tests passed (except for the material check)!" << std::endl;
   return 0;
}