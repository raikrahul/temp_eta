#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <type_traits>

namespace MailProcessing
{

    // Represents a letter in a 1950s office environment
    struct Letter
    {
        std::string recipient;
        std::string department;
        std::string contents;
        bool urgent;
    };

    // Different routing strategies for mail
    template <typename LetterType>
    struct InternalMailRoute
    {
        void route(const LetterType &letter, const std::string &message)
        {
            std::cout << "[Internal Mail] To: " << letter.recipient << " (" << letter.department << "), Message: " << message << std::endl;
        }
    };

    template <typename LetterType>
    struct ExternalMailRoute
    {
        void route(const LetterType &letter, const std::string &message)
        {
            std::cout << "[External Mail] To: " << letter.recipient << ", Message: " << message << std::endl;
        }
    };

    // Different sorting actions based on priority
    struct DepartmentSort
    {
    };
    struct UrgencySort
    {
    };

    // Default handling rule - no special handling
    template <typename LetterType>
    struct DefaultHandler
    {
        bool handle(const LetterType &letter)
        {
            return true;
        }
    };

    // Rule to handle urgent mail specifically
    template <typename LetterType>
    struct UrgentMailHandler
    {
        bool handle(const LetterType &letter)
        {
            return letter.urgent;
        }
    };

    // Main template for processing mail
    template <typename LetterType,
              template <typename> typename Router,
              typename SortAction,
              template <typename> typename Handler = DefaultHandler>
    class MailProcessor
    {
    public:
        MailProcessor() = default;

        bool process(LetterType letter)
        {
            static_assert(std::is_same_v<SortAction, DepartmentSort> || std::is_same_v<SortAction, UrgencySort>,
                          "Invalid SortAction provided.");

            Handler<LetterType> handler;
            if (!handler.handle(letter))
            {
                router_.route(letter, "Handling rule not met.");
                return false;
            }

            // The core sorting logic - this is your task
            if constexpr (std::is_same_v<SortAction, DepartmentSort>)
            {
                // TODO: Implement the logic to sort mail by department.
                //       This might involve adding the letter to a department-specific pile.
                //       This is the HARD PART.
                router_.route(letter, "Sorted by department.");
                return true;
            }
            else if constexpr (std::is_same_v<SortAction, UrgencySort>)
            {
                // TODO: Implement the logic to sort mail by urgency.
                //       This might involve placing urgent mail in a priority tray.
                //       This is the HARD PART.
                router_.route(letter, "Sorted by urgency.");
                return true;
            }
            return false; // Should not reach here due to static_assert
        }

    private:
        Router<LetterType> router_;
    };

} // namespace MailProcessing

bool test_department_sort_internal()
{
    using namespace MailProcessing;
    MailProcessor<Letter, InternalMailRoute, DepartmentSort> processor;
    Letter letter{"Bob Cratchit", "Accounting", "Payroll Report", false};
    return processor.process(letter);
}

bool test_urgency_sort_external_urgent()
{
    using namespace MailProcessing;
    MailProcessor<Letter, ExternalMailRoute, UrgencySort> processor;
    Letter letter{"Ebenezer Scrooge", "Management", "Urgent Business Proposal", true};
    return processor.process(letter);
}

bool test_urgency_sort_internal_not_urgent()
{
    using namespace MailProcessing;
    MailProcessor<Letter, InternalMailRoute, UrgencySort> processor;
    Letter letter{"Tiny Tim", "Logistics", "Christmas List", false};
    return processor.process(letter);
}

bool test_department_sort_external()
{
    using namespace MailProcessing;
    MailProcessor<Letter, ExternalMailRoute, DepartmentSort> processor;
    Letter letter{"Jacob Marley", "Consulting", "Audit Findings", false};
    return processor.process(letter);
}

bool test_urgent_mail_handler_blocks()
{
    using namespace MailProcessing;
    MailProcessor<Letter, InternalMailRoute, DepartmentSort, UrgentMailHandler> processor;
    Letter not_urgent{"Unknown", "Sales", "Flyer", false};
    return !processor.process(not_urgent); // Expecting it to be blocked by the handler
}

bool test_urgent_mail_handler_allows()
{
    using namespace MailProcessing;
    MailProcessor<Letter, InternalMailRoute, DepartmentSort, UrgentMailHandler> processor;
    Letter urgent{"Important Person", "HR", "Confidential Memo", true};
    return processor.process(urgent);
}

template <typename T>
concept InvalidSortAction = !std::is_same_v<T, MailProcessing::DepartmentSort> && !std::is_same_v<T, MailProcessing::UrgencySort>;

void static_assert_test()
{
    using namespace MailProcessing;
    // This will cause a compilation error due to the static_assert
    // using BadProcessor = MailProcessor<Letter, InternalMailRoute, int>; // Invalid SortAction
    static_assert(true, "This test confirms the static_assert for invalid SortAction compiles.");
}

int main()
{
    int failures = 0;

    std::cout << "Running tests for Mail Processing System (1950s Edition):" << std::endl;

    if (test_department_sort_internal())
    {
        std::cout << "[PASSED] Department Sort - Internal Mail" << std::endl;
    }
    else
    {
        std::cout << "[FAILED] Department Sort - Internal Mail" << std::endl;
        failures++;
    }

    if (test_urgency_sort_external_urgent())
    {
        std::cout << "[PASSED] Urgency Sort - External Mail (Urgent)" << std::endl;
    }
    else
    {
        std::cout << "[FAILED] Urgency Sort - External Mail (Urgent)" << std::endl;
        failures++;
    }

    if (test_urgency_sort_internal_not_urgent())
    {
        std::cout << "[PASSED] Urgency Sort - Internal Mail (Not Urgent)" << std::endl;
    }
    else
    {
        std::cout << "[FAILED] Urgency Sort - Internal Mail (Not Urgent)" << std::endl;
        failures++;
    }

    if (test_department_sort_external())
    {
        std::cout << "[PASSED] Department Sort - External Mail" << std::endl;
    }
    else
    {
        std::cout << "[FAILED] Department Sort - External Mail" << std::endl;
        failures++;
    }

    if (test_urgent_mail_handler_blocks())
    {
        std::cout << "[PASSED] Urgent Mail Handler - Blocks Non-Urgent" << std::endl;
    }
    else
    {
        std::cout << "[FAILED] Urgent Mail Handler - Blocks Non-Urgent" << std::endl;
        failures++;
    }

    if (test_urgent_mail_handler_allows())
    {
        std::cout << "[PASSED] Urgent Mail Handler - Allows Urgent" << std::endl;
    }
    else
    {
        std::cout << "[FAILED] Urgent Mail Handler - Allows Urgent" << std::endl;
        failures++;
    }

    std::cout << "\nStatic Assert Test (Compilation Check):" << std::endl;
    static_assert_test(); // This test primarily checks for compilation

    if (failures == 0)
    {
        std::cout << "\nAll tests passed. Proceed to fill in the TODO sections." << std::endl;
    }
    else
    {
        std::cout << "\nSome tests failed. Review the output and then fill in the TODO sections." << std::endl;
    }

    return failures;
}
