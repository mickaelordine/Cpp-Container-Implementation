
#include <iostream>
#include <list>
#include <map>
#include <ostream>
#include <iostream>
#include <string>
#include <iomanip>

#include "List.h"
#include "Map.h"

namespace ListTest
    {
        // ===== FUNZIONI DI TEST =====
        void test_basic_operations()
        {
            std::cout << "\n========== TEST: Basic Operations ==========\n";
            MyStl::List<int> list;
            
            std::cout << "Empty list: " << (list.empty() ? "YES" : "NO") << std::endl;
            std::cout << "Size: " << list.size() << std::endl;
            
            list.push_back(10);
            list.push_back(20);
            list.push_back(30);
            list.print();
            
            list.push_front(5);
            list.push_front(1);
            list.print();
            list.print_reverse();
            
            std::cout << "Front: " << list.front() << std::endl;
            std::cout << "Back: " << list.back() << std::endl;
            std::cout << "Size: " << list.size() << std::endl;
            std::cout << "Empty: " << (list.empty() ? "YES" : "NO") << std::endl;
        }

        void test_pop_operations()
        {
            std::cout << "\n========== TEST: Pop Operations ==========\n";
            MyStl::List<int> list;
            
            list.push_back(10);
            list.push_back(20);
            list.push_back(30);
            list.push_back(40);
            list.print();
            
            list.pop_front();
            std::cout << "After pop_front: ";
            list.print();
            
            list.pop_back();
            std::cout << "After pop_back: ";
            list.print();
            
            list.pop_front();
            list.pop_back();
            std::cout << "After popping all: ";
            list.print();
            std::cout << "Empty: " << (list.empty() ? "YES" : "NO") << std::endl;
        }

        void test_copy_constructor()
        {
            std::cout << "\n========== TEST: Copy Constructor ==========\n";
            MyStl::List<int> list1;
            list1.push_back(1);
            list1.push_back(2);
            list1.push_back(3);
            
            std::cout << "Original list: ";
            list1.print();
            
            MyStl::List<int> list2 = list1;
            std::cout << "Copied list: ";
            list2.print();
            
            list1.push_back(999);
            std::cout << "After modifying original: ";
            list1.print();
            std::cout << "Copy unchanged: ";
            list2.print();
        }

        void test_move_constructor()
        {
            std::cout << "\n========== TEST: Move Constructor ==========\n";
            MyStl::List<int> list1;
            list1.push_back(10);
            list1.push_back(20);
            list1.push_back(30);
            
            std::cout << "Original list: ";
            list1.print();
            
            MyStl::List<int> list2 = std::move(list1);
            std::cout << "Moved list: ";
            list2.print();
            std::cout << "Original after move (should be empty): ";
            list1.print();
        }

        void test_assignment_operators()
        {
            std::cout << "\n========== TEST: Assignment Operators ==========\n";
            MyStl::List<int> list1;
            list1.push_back(1);
            list1.push_back(2);
            
            MyStl::List<int> list2;
            list2.push_back(99);
            
            std::cout << "Before assignment:\n";
            std::cout << "List1: ";
            list1.print();
            std::cout << "List2: ";
            list2.print();
            
            list2 = list1;  // Copy assignment
            std::cout << "\nAfter copy assignment:\n";
            std::cout << "List1: ";
            list1.print();
            std::cout << "List2: ";
            list2.print();
            
            MyStl::List<int> list3;
            list3 = std::move(list1);  // Move assignment
            std::cout << "\nAfter move assignment:\n";
            std::cout << "List3: ";
            list3.print();
            std::cout << "List1 (should be empty): ";
            list1.print();
        }

        void test_clear()
        {
            std::cout << "\n========== TEST: Clear ==========\n";
            MyStl::List<int> list;
            list.push_back(10);
            list.push_back(20);
            list.push_back(30);
            
            std::cout << "Before clear: ";
            list.print();
            
            list.clear();
            std::cout << "After clear: ";
            list.print();
            std::cout << "Size: " << list.size() << std::endl;
            std::cout << "Empty: " << (list.empty() ? "YES" : "NO") << std::endl;
            
            // Test che possiamo ancora usare la lista dopo clear
            list.push_back(100);
            std::cout << "After adding element: ";
            list.print();
        }

        void test_exceptions()
        {
            std::cout << "\n========== TEST: Exceptions ==========\n";
            MyStl::List<int> list;
            
            try {
                list.front();
            } catch (const std::out_of_range& e) {
                std::cout << "✓ Caught exception on empty front(): " << e.what() << std::endl;
            }
            
            try {
                list.back();
            } catch (const std::out_of_range& e) {
                std::cout << "✓ Caught exception on empty back(): " << e.what() << std::endl;
            }
            
            try {
                list.pop_front();
            } catch (const std::out_of_range& e) {
                std::cout << "✓ Caught exception on empty pop_front(): " << e.what() << std::endl;
            }
            
            try {
                list.pop_back();
            } catch (const std::out_of_range& e) {
                std::cout << "✓ Caught exception on empty pop_back(): " << e.what() << std::endl;
            }
        }

        void test_with_strings()
        {
            std::cout << "\n========== TEST: With Strings ==========\n";
            MyStl::List<std::string> list;
            
            list.push_back("Hello");
            list.push_back("World");
            list.push_front("C++");
            list.push_back("!");
            
            list.print();
            list.print_reverse();
        }

        void full_test()
        {
            ListTest::test_basic_operations();
            std::cout << "\n===================\n";
            ListTest::test_pop_operations();
            std::cout << "\n===================\n";
            ListTest::test_copy_constructor();
            std::cout << "\n===================\n";
            ListTest::test_move_constructor();
            std::cout << "\n===================\n";
            ListTest::test_assignment_operators();
            std::cout << "\n===================\n";
            ListTest::test_clear();
            std::cout << "\n===================\n";
            ListTest::test_exceptions();
            std::cout << "\n===================\n";
            ListTest::test_with_strings();
            std::cout << "\n===================\n";
        }
    }

namespace MapTest
{
    // Utility per stampare separatori
    void printSeparator(const std::string& title = "")
    {
        std::cout << "\n" << std::string(60, '=') << "\n";
        if (!title.empty())
            std::cout << "  " << title << "\n" << std::string(60, '=') << "\n";
    }

    void printSubSection(const std::string& title)
    {
        std::cout << "\n--- " << title << " ---\n";
    }

    // Helper per stampare una mappa (in-order traversal visivo)
    template<typename K, typename T>
    void printMap(MyStl::Map<K, T>& map, const std::string& name)
    {
        std::cout << "📦 Map [" << name << "] - Size: " << map.size() << "\n";
        std::cout << "   Content: { ";
        // Qui dovresti iterare sulla mappa, per ora stampiamo manualmente
        std::cout << "... }\n";
    }

    // Test 1: Default Constructor
    void testDefaultConstructor()
    {
        printSeparator("TEST 1: Default Constructor");
        
        MyStl::Map<int, std::string> map;
        std::cout << "  Created empty map\n";
        std::cout << "  Size: " << map.size() << " (expected: 0)\n";
        std::cout << "  Empty: " << (map.empty() ? "Yes" : "No") << "\n";
    }

    // Test 2: Insert e accesso con operator[]
    void testInsertAndAccess()
    {
        printSeparator("TEST 2: Insert & Operator[]");
        
        MyStl::Map<int, std::string> map;
        
        printSubSection("Inserting elements");
        std::pair<const int, std::string> p1(10, "Dieci");
        std::pair<const int, std::string> p2(5, "Cinque");
        std::pair<const int, std::string> p3(15, "Quindici");
        std::pair<const int, std::string> p4(3, "Tre");
        std::pair<const int, std::string> p5(7, "Sette");
        
        map.insert(p1);
        std::cout << "  [1] Inserted (10, \"Dieci\") - Size: " << map.size() << "\n";
        
        map.insert(p2);
        std::cout << "  [2] Inserted (5, \"Cinque\") - Size: " << map.size() << "\n";
        
        map.insert(p3);
        std::cout << "  [3] Inserted (15, \"Quindici\") - Size: " << map.size() << "\n";
        
        map.insert(p4);
        std::cout << "  [4] Inserted (3, \"Tre\") - Size: " << map.size() << "\n";
        
        map.insert(p5);
        std::cout << "  [5] Inserted (7, \"Sette\") - Size: " << map.size() << "\n";

        std::cout << "\n  Tree Structure (conceptual):\n";
        std::cout << "           10(Dieci)\n";
        std::cout << "          /          \\\n";
        std::cout << "      5(Cinque)    15(Quindici)\n";
        std::cout << "      /      \\\n";
        std::cout << "   3(Tre)  7(Sette)\n";

        printSubSection("Accessing with operator[]");
        std::cout << "  map[10] = \"" << map[10] << "\"\n";
        std::cout << "  map[5]  = \"" << map[5] << "\"\n";
        std::cout << "  map[15] = \"" << map[15] << "\"\n";
        std::cout << "  map[3]  = \"" << map[3] << "\"\n";
        std::cout << "  map[7]  = \"" << map[7] << "\"\n";

        printSubSection("Creating new element with operator[]");
        std::cout << "  Before: Size = " << map.size() << "\n";
        std::string val = map[20]; // Dovrebbe creare elemento
        std::cout << "  map[20] = \"" << val << "\" (default string)\n";
        std::cout << "  After: Size = " << map.size() << "\n";
    }

    // Test 3: Find
    void testFind()
    {
        printSeparator("TEST 3: Find");
        
        MyStl::Map<int, std::string> map;
        map.insert(std::make_pair(100, "Cento"));
        map.insert(std::make_pair(50, "Cinquanta"));
        map.insert(std::make_pair(150, "Centocinquanta"));
        
        printSubSection("Finding existing keys");
        auto result1 = map.find(100);
        std::cout << "  find(100): {" << result1.first << ", \"" << result1.second << "\"}\n";
        
        auto result2 = map.find(50);
        std::cout << "  find(50):  {" << result2.first << ", \"" << result2.second << "\"}\n";

        printSubSection("Finding non-existing key");
        auto result3 = map.find(999);
        std::cout << "  find(999): Should print error message above\n";
    }

    // Test 4: At (con eccezioni)
    void testAt()
    {
        printSeparator("TEST 4: At (with exceptions)");
        
        MyStl::Map<int, std::string> map;
        map.insert(std::make_pair(1, "Uno"));
        map.insert(std::make_pair(2, "Due"));
        
        printSubSection("Accessing existing keys");
        try {
            std::cout << "  map.at(1) = \"" << map.at(1) << "\"\n";
            std::cout << "  map.at(2) = \"" << map.at(2) << "\"\n";
        } catch(const std::exception& e) {
            std::cout << "  ❌ Unexpected exception: " << e.what() << "\n";
        }

        printSubSection("Accessing non-existing key");
        try {
            std::cout << "  Trying map.at(999)...\n";
            std::string val = map.at(999);
            std::cout << "  ❌ Should have thrown exception!\n";
        } catch(const std::exception& e) {
            std::cout <<  e.what() << "  ✓ Exception caught correctly\n";
        }
    }

    // Test 5: Copy Constructor
    void testCopyConstructor()
    {
        printSeparator("TEST 5: Copy Constructor");
        
        MyStl::Map<int, std::string> original;
        original.insert(std::make_pair(1, "Alpha"));
        original.insert(std::make_pair(2, "Beta"));
        original.insert(std::make_pair(3, "Gamma"));
        
        std::cout << "Original map created with 3 elements\n";
        std::cout << "  Size: " << original.size() << "\n";

        printSubSection("Creating copy");
        MyStl::Map<int, std::string> copy(original);
        std::cout << "  Copy size: " << copy.size() << "\n";
        
        printSubSection("Verifying copy content");
        std::cout << "  copy[1] = \"" << copy[1] << "\"\n";
        std::cout << "  copy[2] = \"" << copy[2] << "\"\n";
        std::cout << "  copy[3] = \"" << copy[3] << "\"\n";

        printSubSection("Modifying copy (should not affect original)");
        copy.insert(std::make_pair(4, "Delta"));
        std::cout << "  Inserted (4, \"Delta\") in copy\n";
        std::cout << "  Original size: " << original.size() << " (should be 3)\n";
        std::cout << "  Copy size: " << copy.size() << " (should be 4)\n";
    }

    // Test 6: Copy Assignment
    void testCopyAssignment()
    {
        printSeparator("TEST 6: Copy Assignment");
        
        MyStl::Map<int, std::string> map1;
        map1.insert(std::make_pair(10, "Ten"));
        map1.insert(std::make_pair(20, "Twenty"));
        
        MyStl::Map<int, std::string> map2;
        map2.insert(std::make_pair(99, "NinetyNine"));
        
        std::cout << "Map1 size: " << map1.size() << "\n";
        std::cout << "Map2 size: " << map2.size() << "\n";

        printSubSection("Assignment: map2 = map1");
        map2 = map1;
        
        std::cout << "  Map2 size after assignment: " << map2.size() << " (should be 2)\n";
        std::cout << "  map2[10] = \"" << map2[10] << "\"\n";
        std::cout << "  map2[20] = \"" << map2[20] << "\"\n";

        printSubSection("Self-assignment test");
        map1 = map1;
        std::cout << "  Map1 size after self-assignment: " << map1.size() << " (should be 2)\n";
    }

    // Test 7: Move Constructor
    void testMoveConstructor()
    {
        printSeparator("TEST 7: Move Constructor");
        
        MyStl::Map<int, std::string> original;
        original.insert(std::make_pair(5, "Five"));
        original.insert(std::make_pair(10, "Ten"));
        
        std::cout << "Original map size: " << original.size() << "\n";

        printSubSection("Moving to new map");
        MyStl::Map<int, std::string> moved(std::move(original));
        
        std::cout << "  Moved map size: " << moved.size() << " (should be 2)\n";
        std::cout << "  Original map size: " << original.size() << " (should be 0)\n";
        std::cout << "  moved[5] = \"" << moved[5] << "\"\n";
    }

    // Test 8: Move Assignment
    void testMoveAssignment()
    {
        printSeparator("TEST 8: Move Assignment");
        
        MyStl::Map<int, std::string> map1;
        map1.insert(std::make_pair(100, "Hundred"));
        
        MyStl::Map<int, std::string> map2;
        map2.insert(std::make_pair(200, "TwoHundred"));
        map2.insert(std::make_pair(300, "ThreeHundred"));
        
        std::cout << "Map1 size: " << map1.size() << "\n";
        std::cout << "Map2 size: " << map2.size() << "\n";

        printSubSection("Move assignment: map1 = std::move(map2)");
        map1 = std::move(map2);
        
        std::cout << "  Map1 size: " << map1.size() << " (should be 2)\n";
        std::cout << "  Map2 size: " << map2.size() << " (should be 0)\n";
        std::cout << "  map1[200] = \"" << map1[200] << "\"\n";
    }

    // Test 9: Clear
    void testClear()
    {
        printSeparator("TEST 9: Clear");
        
        MyStl::Map<int, std::string> map;
        map.insert(std::make_pair(1, "One"));
        map.insert(std::make_pair(2, "Two"));
        map.insert(std::make_pair(3, "Three"));
        map.insert(std::make_pair(4, "Four"));
        map.insert(std::make_pair(5, "Five"));
        
        std::cout << "Map size before clear: " << map.size() << "\n";
        
        printSubSection("Clearing map");
        map.clear();
        
        std::cout << "  Map size after clear: " << map.size() << " (should be 0)\n";
        std::cout << "  Empty: " << (map.empty() ? "Yes" : "No") << "\n";

        printSubSection("Inserting after clear");
        map.insert(std::make_pair(99, "NinetyNine"));
        std::cout << "  Map size: " << map.size() << " (should be 1)\n";
        std::cout << "  map[99] = \"" << map[99] << "\"\n";
    }

    // Test 10: Stress Test
    void testStress()
    {
        printSeparator("TEST 10: Stress Test");
        
        MyStl::Map<int, int> map;
        const int N = 1000;
        
        printSubSection("Inserting 1000 elements");
        for (int i = 0; i < N; ++i) {
            map.insert(std::make_pair(i, i * 10));
        }
        std::cout << "  ✓ Inserted " << N << " elements\n";
        std::cout << "  Final size: " << map.size() << "\n";

        printSubSection("Accessing random elements");
        std::cout << "  map[0] = " << map[0] << "\n";
        std::cout << "  map[500] = " << map[500] << "\n";
        std::cout << "  map[999] = " << map[999] << "\n";

        printSubSection("Clearing large map");
        map.clear();
        std::cout << "  ✓ Cleared map\n";
        std::cout << "  Size after clear: " << map.size() << "\n";
    }
    
    // Test 11: Erase
    void testErase()
    {
        MyStl::Map<int, std::string> map;
    
        // Costruisci albero
        map.insert({10, "Ten"});
        map.insert({5, "Five"});
        map.insert({15, "Fifteen"});
        map.insert({3, "Three"});
        map.insert({7, "Seven"});
        map.insert({12, "Twelve"});
        map.insert({20, "Twenty"});
    
        std::cout << "Initial size: " << map.size() << "\n\n";
    
        // Caso 1: Foglia
        std::cout << "=== Test 1: Erase leaf (3) ===\n";
        map.erase(3);
        std::cout << "Size: " << map.size() << "\n\n";
    
        // Caso 2: Un figlio
        std::cout << "=== Test 2: Erase node with one child (5) ===\n";
        map.erase(5);
        std::cout << "Size: " << map.size() << "\n\n";
    
        // Caso 3: Due figli
        std::cout << "=== Test 3: Erase node with two children (15) ===\n";
        map.erase(15);
        std::cout << "Size: " << map.size() << "\n\n";
    
        // Verifica contenuto
        std::cout << "=== Remaining elements ===\n";
        std::cout << "map[10] = " << map[10] << "\n";
        std::cout << "map[7] = " << map[7] << "\n";
        std::cout << "map[20] = " << map[20] << "\n";
    }

    // Test 12: Iterator
    void testIterator()
    {
        MyStl::Map<int, std::string> map;
        map.insert({10, "Ten"});
        map.insert({5, "Five"});
        map.insert({15, "Fifteen"});
        map.insert({3, "Three"});
        map.insert({7, "Seven"});
    
        std::cout << "=== Iterating with range-based for ===\n";
        for (auto& pair : map)
        {
            std::cout << pair.first << " -> " << pair.second << "\n";
        }
    
        std::cout << "\n=== Iterating with explicit iterator ===\n";
        for (auto it = map.begin(); it != map.end(); ++it)
        {
            std::cout << it->first << " -> " << it->second << "\n";
        }
    
        std::cout << "\n=== Modifying values through iterator ===\n";
        for (auto it = map.begin(); it != map.end(); ++it)
        {
            it->second += "!";  // Modifica il valore
        }
    
        for (auto& pair : map)
        {
            std::cout << pair.first << " -> " << pair.second << "\n";
        }
    }
    
    // Funzione principale per eseguire tutti i test
    void runAllTests()
    {
        std::cout << "\n";
        std::cout << "//////////////////////////////////////////////////////////////\n";
        std::cout << "/           MyStl::Map - COMPREHENSIVE TEST SUITE            /\n";
        std::cout << "//////////////////////////////////////////////////////////////\n";

        try {
            testDefaultConstructor();
            testInsertAndAccess();
            testFind();
            testAt();
            testCopyConstructor();
            testCopyAssignment();
            testMoveConstructor();
            testMoveAssignment();
            testClear();
            testStress();
            testErase();
            testIterator();

            printSeparator("SUMMARY");
            std::cout << "✓ All tests completed!\n";
            std::cout << "  Check output above for any issues.\n\n";

        } catch (const std::exception& e) {
            std::cout << "\n❌ FATAL ERROR: " << e.what() << "\n\n";
        }
    }
}

int main(int argc, char* argv[])
{
    //ListTest::full_test();
    //MapTest::runAllTests();
    
    
    return 0;
}
