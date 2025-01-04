// #include <iostream>
// #include <string>
// #include <concepts>
// #include <type_traits>
// // THIS CODE IS WRONG 
// namespace n221_exercise
// {

// // 1950s Business Context: A Department Store Ordering System

// // Forward Declarations (To avoid circular dependencies if needed later)
// template <typename ItemType, typename ProcessingPolicy , typename Currency, typename InvoiceFormat >
// class OrderForm;

// // --- Supporting Types and Concepts ---

// // Concept for Item Types (could have properties like name, base price)
// template <typename T>
// concept InventoryItemConcept = requires(T a) {
//     { a.getName() } -> std::same_as<std::string>;
// };

// // Basic Inventory Item Structure
// template <const char* ItemName>
// struct InventoryItem
// {
    
//     static constexpr const char*  name = ItemName;
//     std::string getName() const { return std::string(name); }
// };

// // Processing Policies
// struct DefaultProcessingPolicy { static constexpr double markup_percentage = 0.10; };
// struct ExpeditedProcessingPolicy { static constexpr double markup_percentage = 0.25; };
// struct BulkOrderProcessing { static constexpr double discount_percentage = 0.05; };

// // Currencies
// struct USDollar { static constexpr std::string_view symbol = "$"; };
// struct CanadianDollar { static constexpr std::string_view symbol = "CAD"; };

// // Invoice Formats
// struct CarbonCopyInvoice { static constexpr std::string_view format_type = "Carbon Copy"; };
// struct TypedInvoice { static constexpr std::string_view format_type = "Typed"; };

// // --- Main OrderForm Template ---

// template <typename ItemType, typename ProcessingPolicy, typename Currency, typename InvoiceFormat>
// class OrderForm
// {
// public:
//     // Static Assert to ensure ItemType meets the concept
//     static_assert(InventoryItemConcept<ItemType>, "ItemType must satisfy the InventoryItemConcept.");

//     using item_type = ItemType;
//     using processing_policy = ProcessingPolicy;
//     using currency_type = Currency;
//     using invoice_format = InvoiceFormat;

//     OrderForm(int quantity) : quantity_(quantity) {}

//     std::string getItemName() const { return item_type::name; }
//     int getQuantity() const { return quantity_; }
//     std::string getCurrencySymbol() const { return currency_type::symbol; }
//     std::string getInvoiceFormatType() const { return invoice_format::format_type; }

//     // TO-DO: This is the hardest part - Calculate the total price based on quantity and policies.
//     double calculateTotalPrice() const
//     {
//         // Access policy specifics using processing_policy::markup_percentage etc.
//         // Consider bulk order discounts if applicable.
//         // Make sure to think about potential interactions between different policies.
//         // You might need SFINAE or if constexpr for different policy types.
//         // The core logic needs careful consideration of all factors.
//         // Think about edge cases and different combinations.
//         // This part should be challenging but achievable with the template parameters available.

//         // Placeholder - REPLACE THIS WITH YOUR LOGIC
//         return -1.0; // Indicate not yet implemented
//     }

//     // Boilerplate function to print order details
//     void printOrder() const
//     {
//         std::cout << "--- Order Details ---\n";
//         std::cout << "Item: " << getItemName() << "\n";
//         std::cout << "Quantity: " << getQuantity() << "\n";
//         std::cout << "Processing: ";
//         if constexpr (std::is_same_v<ProcessingPolicy, DefaultProcessingPolicy>) {
//             std::cout << "Standard\n";
//         } else if constexpr (std::is_same_v<ProcessingPolicy, ExpeditedProcessingPolicy>) {
//             std::cout << "Expedited\n";
//         } else if constexpr (std::is_same_v<ProcessingPolicy, BulkOrderProcessing>) {
//             std::cout << "Bulk\n";
//         } else {
//             std::cout << "Custom\n";
//         }
//         std::cout << "Currency: " << getCurrencySymbol() << "\n";
//         std::cout << "Invoice Format: " << getInvoiceFormatType() << "\n";
//         double total = calculateTotalPrice();
//         std::cout << "Total Price: ";
//         if (total >= 0) {
//             std::cout << total << getCurrencySymbol() << "\n";
//         } else {
//             std::cout << "[Calculation Pending]\n";
//         }
//         std::cout << "--------------------\n";
//     }

// private:
//     int quantity_;
// };

// } // namespace n221_exercise

// namespace n221_exercise_test
// {
//     using namespace n221_exercise;

//     void run_tests()
//     {
//         // Test Case 1: Simple order with default settings
//         OrderForm<InventoryItem<"Hat">, DefaultProcessingPolicy, USDollar, CarbonCopyInvoice> order1(2);
//         static_assert(std::is_same_v<decltype(order1)::item_type, InventoryItem<"Hat">>);
//         static_assert(std::is_same_v<decltype(order1)::processing_policy, DefaultProcessingPolicy>);
//         static_assert(std::is_same_v<decltype(order1)::currency_type, USDollar>);
//         static_assert(std::is_same_v<decltype(order1)::invoice_format, CarbonCopyInvoice>);
//         // The core logic is missing, so we can't assert the price yet.
//         std::cout << "Test Case 1:\n";
//         order1.printOrder();
//         std::cout << "\n";

//         // Test Case 2: Order with expedited processing
//         OrderForm<InventoryItem<"Dress">, ExpeditedProcessingPolicy, USDollar, CarbonCopyInvoice> order2(1);
//         static_assert(std::is_same_v<decltype(order2)::processing_policy, ExpeditedProcessingPolicy>);
//         std::cout << "Test Case 2:\n";
//         order2.printOrder();
//         std::cout << "\n";

//         // Test Case 3: Order with Canadian dollars and typed invoice
//         OrderForm<InventoryItem<"Suit">, DefaultProcessingPolicy, CanadianDollar, TypedInvoice> order3(3);
//         static_assert(std::is_same_v<decltype(order3)::currency_type, CanadianDollar>);
//         static_assert(std::is_same_v<decltype(order3)::invoice_format, TypedInvoice>);
//         std::cout << "Test Case 3:\n";
//         order3.printOrder();
//         std::cout << "\n";

//         // Test Case 4: Bulk order with discount
//         OrderForm<InventoryItem<"Gloves">, BulkOrderProcessing, USDollar, CarbonCopyInvoice> order4(10);
//         static_assert(std::is_same_v<decltype(order4)::processing_policy, BulkOrderProcessing>);
//         std::cout << "Test Case 4:\n";
//         order4.printOrder();
//         std::cout << "\n";

//         // Test Case 5: Using default template arguments explicitly
//         OrderForm<InventoryItem<"Shirt">> order5(5);
//         static_assert(std::is_same_v<decltype(order5)::processing_policy, DefaultProcessingPolicy>);
//         static_assert(std::is_same_v<decltype(order5)::currency_type, USDollar>);
//         static_assert(std::is_same_v<decltype(order5)::invoice_format, CarbonCopyInvoice>);
//         std::cout << "Test Case 5:\n";
//         order5.printOrder();
//         std::cout << "\n";

//          // Static Assert demonstrating the concept requirement
//         struct InvalidItem { int getName() { return 1; } }; // Doesn't meet the concept
//         // static_assert(!InventoryItemConcept<InvalidItem>, "Intentional fail if concept check is wrong");
//         // The following line should cause a compilation error due to the static_assert in OrderForm
//         // OrderForm<InvalidItem> invalid_order(1); // Uncommenting this will cause a compile error

//         std::cout << "All basic tests completed (core logic tests pending implementation).\n";
//     }
// } // namespace n221_exercise_test

// int main()
// {
//     n221_exercise_test::run_tests();
//     return 0;
// }



#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}