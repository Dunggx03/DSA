#include <iostream>
#include <string>
#include "LL.h"
#include "vector.h"
#include "unordered_map.h"

template <typename T>

//-----------------------------------Manual Test--------------------------------
void manualLinkedList() {
    LinkedList<T> list;
    int choice, pos, val;

    do 
    {
        std::cout << "\n------------ LinkedList Menu --------------\n";
        std::cout << "1. Insert at begin\n";
        std::cout << "2. Insert at end\n";
        std::cout << "3. Insert at position\n";
        std::cout << "4. Delete at begin\n";
        std::cout << "5. Delete at end\n";
        std::cout << "6. Delete first by value\n";
        std::cout << "7. Print list\n";
        std::cout << "8. Clear list\n";
        std::cout << "0. Back\n";
        std::cout << "Choose: ";
        std::cin >> choice;

        switch (choice) 
        {
        case 1:
            std::cout << "Enter value: ";
            std::cin >> val;
            list.insertAtBegin(val);
            break;

        case 2:
            std::cout << "Enter value: ";
            std::cin >> val;
            list.insertAtEnd(val);
            break;

        case 3:
            std::cout << "Enter position and value: ";
            std::cin >> pos >> val;
            list.insertAtPosition(pos, val);
            break;

        case 4:
            list.deleteAtBegin();
            break;

        case 5:
            list.deleteAtEnd();
            break;

        case 6:
            std::cout << "Enter value to delete: ";
            std::cin >> val;
            list.deleteFirstByValue(val);
            break;

        case 7:
            list.printList();
            break;

        case 8:
            list.clear();
            break;

        case 0:
            break;

        default:
            std::cout << "Invalid choice!\n";
        }
    } while (choice != 0);
}


template <typename T>
void manualVector() {
    Vector<T> vec;
    int choice, index, val;

    do 
    {
        std::cout << "\n------------- Vector Menu --------------\n";
        std::cout << "1. Push back\n";
        std::cout << "2. Insert at index\n";
        std::cout << "3. Erase at index\n";
        std::cout << "4. Pop back\n";
        std::cout << "5. Print vector\n";
        std::cout << "6. Clear vector\n";
        std::cout << "0. Back\n";
        std::cout << "Choose: ";
        std::cin >> choice;

        switch (choice) 
        {
        case 1:
            std::cout << "Enter value: ";
            std::cin >> val;
            vec.push_back(val);
            break;

        case 2:
            std::cout << "Enter index and value: ";
            std::cin >> index >> val;
            vec.insert(index, val);
            break;

        case 3:
            std::cout << "Enter index to erase: ";
            std::cin >> index;
            vec.erase(index);
            break;

        case 4:
            vec.pop_back();
            break;

        case 5:
            std::cout << "Vector: ";
            for (int i = 0; i < vec.size(); i++) std::cout << vec[i] << " ";
            std::cout << "\n";
            break;

        case 6:
            vec.clear();
            break;

        case 0:
            break;

        default:
            std::cout << "Invalid choice!\n";
        }
    } 

    while (choice != 0);
}


template <typename K, typename V>
void manualUnorderedMap() {
    UnorderedMap<K, V> umap(4);
    int choice;
    K key;
    V value;

    do 
    {
        std::cout << "\n---------------- UnorderedMap Menu ---------------\n";
        std::cout << "1. Insert key-value\n";
        std::cout << "2. Find key\n";
        std::cout << "3. Erase key\n";
        std::cout << "4. Access with []\n";
        std::cout << "5. Print map\n";
        std::cout << "0. Back\n";
        std::cout << "Choose: ";
        std::cin >> choice;

        switch (choice) 
        {
        case 1:
            std::cout << "Enter key and value: ";
            std::cin >> key >> value;
            umap.insert(key, value);
            break;

        case 2:
            std::cout << "Enter key to find: ";
            std::cin >> key;
            if (auto v = umap.find(key)) std::cout << "Found: " << *v << "\n";
            else std::cout << "Not found\n";
            break;

        case 3:
            std::cout << "Enter key to erase: ";
            std::cin >> key;
            umap.erase(key);
            break;

        case 4:
            std::cout << "Enter key to access: ";
            std::cin >> key;
            std::cout << "Value = " << umap[key] << "\n";
            break;

        case 5:
            umap.print();
            break;

        case 0:
            break;

        default:
            std::cout << "Invalid choice!\n";
        }
    } 
    while (choice != 0);
}

//--------------------------Auto Test (case: for int)---------------------------
void autoTests() {
    std::cout << "\n----------------AUTO TEST ALL (For int)--------------\n";

    // LinkedList
    LinkedList<int> list;
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtBegin(5);
    list.insertAtPosition(1, 15);
    std::cout << "LinkedList: ";
    list.printList();
    list.deleteFirstByValue(10);
    list.printList();

    // Vector
    Vector<int> vec;
    for (int i = 1; i <= 5; i++) vec.push_back(i);
    vec.insert(2, 99);
    vec.erase(1);
    std::cout << "Vector: ";
    for (int i = 0; i < vec.size(); i++) std::cout << vec[i] << " ";
    std::cout << "\n";

    // UnorderedMap
    UnorderedMap<int, std::string> umap(6);
    for (int i = 0; i < 10; i++) umap.insert(i, "val" + std::to_string(i));
    umap.erase(2);
    umap[10] = "new";
    umap.print();

    std::cout << "\n Auto test complete.\n";
}

void mainMenu() 
{
    int choice;

    do 
    {
        std::cout << "\n---------------- MAIN MENU ------------------\n";
        std::cout << "1. LinkedList<int>\n";
        std::cout << "2. Vector<int>\n";
        std::cout << "3. UnorderedMap<int, std::string>\n";
        std::cout << "4. Auto Test \n";
        std::cout << "0. Exit\n";
        std::cout << "Choose: ";
        std::cin >> choice;

        switch (choice) 
        {
            case 1: manualLinkedList<int>(); break;
            
            case 2: manualVector<int>(); break;
            
            case 3: manualUnorderedMap<int, std::string>(); break;
            
            case 4: autoTests(); break;
            
            case 0: std::cout << "Exit program.\n"; break;
            
            default: std::cout << "Invalid choice!\n";
        }
    } 
    while (choice != 0);
}

int main() {
    mainMenu();
    return 0;
}
