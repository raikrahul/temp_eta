#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include <list>

namespace InventorySystem {

    // Forward declarations
    template <typename ItemType, typename LocationType>
    class WarehouseInventory;

    template <typename ItemType, template <typename> class DataContainer>
    class Catalog;

    // Catalog: Records different items in various warehouses (the location).
    // Catalog should accept any type of data container.
    template <typename ItemType = std::string, template <typename X = std::string> class DataContainer = std::vector>
    class Catalog {
    public:
        using Item = ItemType;
        using Container = DataContainer<ItemType>;

        Container item_list_;
        Catalog() {};

        void add_item(ItemType const &item) {
            item_list_.push_back(item);
        }

        ItemType getItemAt(size_t i) const { return item_list_[i]; }

        size_t size() const { return item_list_.size(); }

        ~Catalog() = default;
    };

    // Represents the stock of a specific type of item.
    template <typename ItemType = std::string, typename LocationType = std::string>
    class WarehouseInventory {
    public:
        using Item = ItemType;
        using Location = LocationType;

        Item item_name_;
        Location location_;

        WarehouseInventory() = default;

        WarehouseInventory(Item const &item, Location const &location)
            : item_name_(item), location_(location) {}

        // Returns the item name.
        Item getItemName() const { return item_name_; }

        // Returns the location.
        Location getLocation() const { return location_; }

        virtual ~WarehouseInventory() = default;

        // Shows the type for every kind of inventory created.
        template <typename... Args>
        static void ShowInventoryDetails(std::ostream &os, Args &&...args) {
            os << "Inventory Record: Item - " << typeid(Item).name()
               << ", Location - " << typeid(Location).name() << "\n";

            // Print extra items.
            ([&](auto &&...x) { ((os << "Extra Item: " << x << "\n"), ...); }(std::forward<Args>(args)...));
        }
    };

    // Specialized Warehouse for electronics.
    template <typename LocationType>
    class WarehouseInventory<std::pair<std::string, float>, LocationType> {
    public:
        using Item = std::pair<std::string, float>;
        using Location = LocationType;

        Item item_name_;
        Location location_;
        int shelf_;

        WarehouseInventory(const Item &item, const Location &location, int shelf)
            : item_name_(item), location_(location), shelf_(shelf) {}

        int getShelfNumber() const { return shelf_; }

        // Overloaded ShowInventoryDetails for electronics.
        static void ShowInventoryDetails(std::ostream &os, const std::string &extra1, const std::string &extra2) {
            os << "Inventory Record (ELECTRONICS ONLY): Item - " << typeid(Item).name()
               << ", Location - " << typeid(Location).name() << "\n";
            os << "Extra Info 1: " << extra1 << "\n";
            os << "Extra Info 2: " << extra2 << "\n";
        }
    };

    // Helper function to create some inventories.
    template <typename ItemType, typename LocationType>
    WarehouseInventory<ItemType, LocationType> CreateWarehouseItem(const ItemType &item, const LocationType &location) {
        return {item, location};
    }
} // end of namespace InventorySystem

namespace Tests {
    template <typename T>
    struct LinkedListDataContainer {
        std::list<T> linked_list_;

        void push_back(T const &x) {
            linked_list_.push_back(x);
        }

        T operator[](int index) const {
            auto it = linked_list_.begin();
            std::advance(it, index);
            return *it;
        }

        size_t size() const {
            return linked_list_.size();
        }

        ~LinkedListDataContainer() = default;
    };

    void TestCatalog() {
        // Using default template args
        InventorySystem::Catalog catalog_default;

        catalog_default.add_item("Washing machine");
        catalog_default.add_item("Vacuum cleaner");

        static_assert(std::is_same_v<decltype(catalog_default.getItemAt(0)), std::string>, "Item should be string");

        if (catalog_default.getItemAt(0) == "Washing machine" && catalog_default.getItemAt(1) == "Vacuum cleaner") {
            std::cout << "Default Catalog Test Passed" << std::endl;
        } else {
            throw std::runtime_error("Default Catalog Test failed");
        }

        // Providing ItemType but not Container type: should default to vector
        InventorySystem::Catalog<int> catalog_int_default_container;
        catalog_int_default_container.add_item(1);
        catalog_int_default_container.add_item(2);

        if (catalog_int_default_container.getItemAt(0) == 1 && catalog_int_default_container.getItemAt(1) == 2) {
            std::cout << "Int catalog with default container Passed" << std::endl;
        } else {
            throw std::runtime_error("Int catalog with default container FAILED");
        }

        // Providing non-default Container: using a different data Container type (customized Data container type)
        InventorySystem::Catalog<std::string, LinkedListDataContainer> catalog_with_custom_data_container;

        catalog_with_custom_data_container.add_item("Refrigerator");
        catalog_with_custom_data_container.add_item("Radio");

        if (catalog_with_custom_data_container.getItemAt(0) == "Refrigerator" &&
            catalog_with_custom_data_container.getItemAt(1) == "Radio") {
            std::cout << "Custom container Data type Passed" << std::endl;
        } else {
            throw std::runtime_error("Custom container type test Failed");
        }

        // Testing that Data container is independent and items can be different for other datastructure
        InventorySystem::Catalog<double, LinkedListDataContainer> double_catalog;
        double_catalog.add_item(1.0);
        double_catalog.add_item(2.0);

        if (double_catalog.getItemAt(0) == 1.0 && double_catalog.getItemAt(1) == 2.0) {
            std::cout << "Independent double linked list Passed" << std::endl;
        } else {
            throw std::runtime_error("Independent list failed");
        }
    }

    void TestWarehouseInventory() {
        // Default creation
        InventorySystem::WarehouseInventory item1;

        std::cout << "Warehouse Inventory Type: " << typeid(item1).name() << std::endl;

        // Item, Location Default to string: Default creation.
        auto inventory1 = InventorySystem::CreateWarehouseItem(std::string("Iron"), std::string("Warehouse A"));
        static_assert(std::is_same_v<decltype(inventory1.getItemName()), std::string>, "Item should be default string");

        if (inventory1.getItemName() == "Iron" && inventory1.getLocation() == "Warehouse A") {
            std::cout << "Inventory Creation, Defaults Pass: " << inventory1.getItemName() << " located at " << inventory1.getLocation() << std::endl;
        } else {
            throw std::runtime_error("Inventory Creation, Defaults fail");
        }

        // Non-default parameters but default type for locations
        InventorySystem::WarehouseInventory<int> inventory2(121, "Warehouse B");
        static_assert(std::is_same_v<decltype(inventory2.getItemName()), int>, "Item should be int");

        if (inventory2.getItemName() == 121 && inventory2.getLocation() == "Warehouse B") {
            std::cout << "Inventory Creation Type parameter, String Location Type Passed: " << inventory2.getItemName() << " located at " << inventory2.getLocation() << std::endl;
        } else {
            throw std::runtime_error("Creation with type passed but default string fail");
        }

        // Fully type specification
        InventorySystem::WarehouseInventory<float, int> inventory3(12.3f, 4345);

        if (inventory3.getItemName() == 12.3f && inventory3.getLocation() == 4345) {
            std::cout << "Inventory Creation, fully Type Parameters Pass: " << inventory3.getItemName() << " location " << inventory3.getLocation() << std::endl;
        } else {
            throw std::runtime_error("Fully Type Inventory creation fails");
        }

        InventorySystem::WarehouseInventory<int, int> inv_test{1, 2};

        static_assert(std::is_same_v<decltype(inv_test.getItemName()), int>, "Type should be int for Item");
        static_assert(std::is_same_v<decltype(inv_test.getLocation()), int>, "Type should be int for Location");

        std::cout << "Item test item, Location, Int type parameters passed: Item name: " << inv_test.getItemName() << " Location: " << inv_test.getLocation() << std::endl;

        // Test Partial specialization
        InventorySystem::WarehouseInventory<std::pair<std::string, float>, std::string> electronic_inventory({"Transistor", 1.0}, "Warehouse C", 3);

        // This check should pass for base class
        InventorySystem::WarehouseInventory<std::pair<std::string, float>, std::string>::ShowInventoryDetails(std::cout, "Extra info1", "Extra Info2");

        static_assert(std::is_same_v<decltype(electronic_inventory.item_name_), std::pair<std::string, float>>, "Item should be a pair");

        if (electronic_inventory.item_name_.first == "Transistor" && electronic_inventory.getShelfNumber() == 3) {
            std::cout << "Partial Specialization works: Item name " << electronic_inventory.item_name_.first << ", Shelf: " << electronic_inventory.getShelfNumber() << std::endl;
        } else {
            throw std::runtime_error("Partial Specialization does not match");
        }
    }

    void RunTests() {
        TestCatalog();
        TestWarehouseInventory();

        std::cout << "All tests Completed Successfully" << std::endl;
    }
} // namespace Tests

int main() {
    Tests::RunTests();
    return 0;
}