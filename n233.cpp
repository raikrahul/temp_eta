#include <iostream>
#include <string>
#include <type_traits>
#include <cstring>

namespace manufacturing_quotas
{

    struct Widget
    {
    };
    struct Gadget
    {
    };
    struct Sprocket
    {
    };
    struct Thingamajig
    {
    };

    struct Assembly
    {
    };
    struct Finishing
    {
    };
    struct Packaging
    {
    };

    struct Monthly
    {
    };
    struct Quarterly
    {
    };
    struct Annually
    {
    };

    // Primary template with constexpr members
    template <typename Product, typename Department, typename TimePeriod>
    struct ProductionQuota
    {
        static constexpr int quota_amount = 100;
        static constexpr const char* description = "Standard production quota.";
    };

    // Partial specialization for Widgets
    template <typename Department, typename TimePeriod>
    struct ProductionQuota<Widget, Department, TimePeriod>
    {
        static constexpr int quota_amount = 150;
        static constexpr const char* description = "Increased quota for our flagship Widgets.";
    };

    // Partial specialization for Gadgets in Assembly
    template <typename TimePeriod>
    struct ProductionQuota<Gadget, Assembly, TimePeriod>
    {
        static constexpr int quota_amount = 200;
        static constexpr const char* description = "Higher quota for Gadgets in Assembly due to new machinery.";
    };

    // Partial specialization for Sprockets Monthly
    template <typename Department>
    struct ProductionQuota<Sprocket, Department, Monthly>
    {
        static constexpr int quota_amount = 75;
        static constexpr const char* description = "Reduced monthly quota for Sprockets to manage inventory.";
    };

    // Full specializations
    template <>
    struct ProductionQuota<Sprocket, Packaging, Annually>
    {
        static constexpr int quota_amount = 500;
        static constexpr const char* description = "Special annual quota for Sprockets in Packaging.";
    };

    template <>
    struct ProductionQuota<Widget, Finishing, Quarterly>
    {
        static constexpr int quota_amount = 175;
        static constexpr const char* description = "Higher quota for Widgets in Finishing during the quarter.";
    };

    template <>
    struct ProductionQuota<Gadget, Packaging, Monthly>
    {
        static constexpr int quota_amount = 50;
        static constexpr const char* description = "Low monthly quota for Gadgets in Packaging due to complexity.";
    };

    template <>
    struct ProductionQuota<Thingamajig, Assembly, Annually>
    {
        static constexpr int quota_amount = 997;
        static constexpr const char* description = "Specific annual quota for experimental Thingamajigs in Assembly.";
    };

    // Add constexpr string comparison
    constexpr bool str_equals(const char* a, const char* b) {
        if (a == b) return true;
        while (*a && *b && *a == *b) { ++a; ++b; }
        return *a == *b;
    }

    void run_tests()
    {
        // Test cases to verify the correct specializations are applied
        static_assert(ProductionQuota<Sprocket, Assembly, Quarterly>::quota_amount == 100);
        static_assert(str_equals(ProductionQuota<Sprocket, Assembly, Quarterly>::description, 
                            "Standard production quota."));

        static_assert(ProductionQuota<Widget, Finishing, Monthly>::quota_amount == 150);
        static_assert(str_equals(ProductionQuota<Widget, Finishing, Monthly>::description,
                            "Increased quota for our flagship Widgets."));

        static_assert(ProductionQuota<Gadget, Assembly, Annually>::quota_amount == 200);
        static_assert(str_equals(ProductionQuota<Gadget, Assembly, Annually>::description,
                            "Higher quota for Gadgets in Assembly due to new machinery."));

        static_assert(ProductionQuota<Sprocket, Packaging, Monthly>::quota_amount == 75);
        static_assert(str_equals(ProductionQuota<Sprocket, Packaging, Monthly>::description,
                            "Reduced monthly quota for Sprockets to manage inventory."));

        static_assert(ProductionQuota<Sprocket, Packaging, Annually>::quota_amount == 500);
        static_assert(str_equals(ProductionQuota<Sprocket, Packaging, Annually>::description,
                            "Special annual quota for Sprockets in Packaging."));

        static_assert(ProductionQuota<Widget, Finishing, Quarterly>::quota_amount == 175, "Test Case 6 Failed: TODO 1");
        static_assert(str_equals(ProductionQuota<Widget, Finishing, Quarterly>::description, "Higher quota for Widgets in Finishing during the quarter."));

        static_assert(ProductionQuota<Gadget, Packaging, Monthly>::quota_amount == 50, "Test Case 7 Failed: TODO 2");
        static_assert(str_equals(ProductionQuota<Gadget, Packaging, Monthly>::description, "Low monthly quota for Gadgets in Packaging due to complexity."));

        static_assert(ProductionQuota<Thingamajig, Assembly, Annually>::quota_amount == 997, "Test Case 8 Failed: TODO 3");
        static_assert(str_equals(ProductionQuota<Thingamajig, Assembly, Annually>::description, "Specific annual quota for experimental Thingamajigs in Assembly."));

        std::cout << "All tests passed!" << std::endl;
    }

} // namespace manufacturing_quotas

int main()
{
    manufacturing_quotas::run_tests();
    return 0;
}