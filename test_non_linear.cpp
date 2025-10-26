#include <iostream>
#include <string>
#include <type_traits>
#include "bst.h"
#include "avl.h"
#include "rb.h"

using namespace std;

//-----------------------------Auto Test---------------------------------------------
template <typename Tree, typename K, typename V>
void autoTest(const string& treeName)
{
    cout << "\n--------------------- Testing " << treeName << " --------------------\n";
    Tree tree;

    cout << "Inserting elements...\n";

    K keys[7];
    V values[7];


    if constexpr (is_same_v<K, string>) 
    {
        string sampleKeys[] = {"Delta", "Alpha", "Echo", "Bravo", "Charlie", "Golf", "Foxtrot"};
        string sampleVals[] = {"D", "A", "E", "B", "C", "G", "F"};
        
        for (int i = 0; i < 7; ++i) 
        {
            keys[i] = sampleKeys[i];
            values[i] = sampleVals[i];
        }
    }

    else if constexpr (is_same_v<K, char>) 
    {
        char sampleKeys[] = {'D', 'A', 'E', 'B', 'C', 'G', 'F'};
        
        for (int i = 0; i < 7; ++i) 
        {
            keys[i] = sampleKeys[i];
            values[i] = static_cast<V>(i * 10);
        }
    }

    else 
    {
        K sampleKeys[] = {K(10), K(20), K(5), K(15), K(25), K(1), K(30)};
        V sampleVals[] = {V(100), V(200), V(50), V(150), V(250), V(10), V(300)};
        
        for (int i = 0; i < 7; ++i) 
        {
            keys[i] = sampleKeys[i];
            values[i] = sampleVals[i];
        }
    }

    for (int i = 0; i < 7; i++)
        tree.insert(keys[i], values[i]);

    cout << "Inorder after insertion:\n";
    tree.inorder();

    cout << "\nFinding some keys...\n";
    V val;
    
    if (tree.find(keys[2], val))
        cout << "Found key " << keys[2] << " -> value = " << val << "\n";
    
    if (tree.find(keys[4], val))
        cout << "Found key " << keys[4] << " -> value = " << val << "\n";
    
    if (!tree.find(K{}, val))
        cout << "Key (default) not found.\n";

    cout << "\nErasing two keys...\n";
    
    tree.erase(keys[1]);
    tree.erase(keys[0]);
    
    cout << "Inorder after erase:\n";
    tree.inorder();
    cout << "\n";
}


void runAllAutoTests()
{
    cout << "\n------------------------------- Auto Test -------------------------------------\n";

    // Integer test
    autoTest<BST<int, int>, int, int>("BST<int,int>");
    autoTest<AVL<int, int>, int, int>("AVL<int,int>");
    autoTest<RBTree<int, int>, int, int>("RBTree<int,int>");

    // Double test
    autoTest<BST<double, double>, double, double>("BST<double,double>");
    autoTest<AVL<double, double>, double, double>("AVL<double,double>");
    autoTest<RBTree<double, double>, double, double>("RBTree<double,double>");

    // String test
    autoTest<BST<string, string>, string, string>("BST<string,string>");
    autoTest<AVL<string, string>, string, string>("AVL<string,string>");
    autoTest<RBTree<string, string>, string, string>("RBTree<string,string>");

    // Char test
    autoTest<BST<char, int>, char, int>("BST<char,int>");
    autoTest<AVL<char, int>, char, int>("AVL<char,int>");
    autoTest<RBTree<char, int>, char, int>("RBTree<char,int>");

    cout << "\n-----------------------------  Completed  -------------------------------------\n";
}

//-----------------------------------Manual Test (For int only)------------------------------------------------
template <typename Tree>
void manualTest(Tree& tree)
{
    while (true)
    {
        cout << "\n------------------------ TREE FUNCTION MENU -------------------------------\n";
        cout << "1. Insert (key, value)\n";
        cout << "2. Erase (key)\n";
        cout << "3. Find (key)\n";
        cout << "4. Inorder Traversal\n";
        cout << "5. Clear Tree\n";
        cout << "0. Back\n";
        cout << "Choose: ";

        int choice;
        cin >> choice;
        if (choice == 0) break;

        switch (choice)
        {
            case 1:
            {
                int key, value;
                cout << "Enter key: "; cin >> key;
                cout << "Enter value: "; cin >> value;
                tree.insert(key, value);
                cout << "Inserted (" << key << ", " << value << ")\n";
                break;
            }
            case 2:
            {
                int key;
                cout << "Enter key to erase: "; cin >> key;
                tree.erase(key);
                cout << "Erased key " << key << "\n";
                break;
            }
            case 3:
            {
                int key, val;
                cout << "Enter key to find: "; cin >> key;
                if (tree.find(key, val))
                    cout << "Found key " << key << " -> value = " << val << "\n";
                else
                    cout << "Key not found.\n";
                break;
            }
            case 4:
                cout << "Inorder: ";
                tree.inorder();
                break;

            case 5:
                tree.clear();
                cout << "Cleared tree.\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }
    }
}


//-----------------------------------Main Menu---------------------------------------
int main()
{
    while (true)
    {
        cout << "\n=========================== TREE TEST MENU ========================\n";
        cout << "1. Binary Search Tree\n";
        cout << "2. AVL Tree\n";
        cout << "3. Red-Black Tree\n";
        cout << "4. Auto Test \n";
        cout << "0. Exit\n";
        cout << "Choose: ";

        int choice;
        cin >> choice;
        if (choice == 0) break;

        switch (choice)
        {
            case 1:
            {
                BST<int, int> tree;
                cout << "\nBinary Search Tree selected.\n";
                manualTest(tree);
                break;
            }
            case 2:
            {
                AVL<int, int> tree;
                cout << "\nAVL Tree selected.\n";
                manualTest(tree);
                break;
            }
            case 3:
            {
                RBTree<int, int> tree;
                cout << "\nRed-Black Tree selected.\n";
                manualTest(tree);
                break;
            }
            case 4:
                runAllAutoTests();
                break;
            default:
                cout << "Invalid choice.\n";
        }
    }

    cout << "\nProgram ended.\n";
    return 0;
}
