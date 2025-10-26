#ifndef LL_H
#define LL_H


template <typename T>
class Node 
{
public:
    T data;
    Node* next;
    Node(T value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedList 
{
private:
    Node<T>* head;
    Node<T>* tail;

public:

//-----------------------Constructor - Destructor ----------------------
    LinkedList() : head(nullptr), tail(nullptr) {}

    ~LinkedList() { clear(); }

    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr) 
    {
        Node<T>* cur = other.head;
        while (cur != nullptr) 
        {
            insertAtEnd(cur->data);   
            cur = cur->next;
        }
    }

    LinkedList& operator=(const LinkedList& other)  //assign
    {
        if (this != &other) 
        {
            clear();
            Node<T>* cur = other.head;
            while (cur != nullptr) 
            {
                insertAtEnd(cur->data); 
                cur = cur->next;
            }
        }
        return *this;
    }

//---------------------------------Insert-------------------------------
    void insertAtBegin(T data) 
    {
        Node<T>* newNode = new Node<T>(data);
        newNode->next = head;
        head = newNode;
        if (tail == nullptr) tail = head;
    }

    void insertAtEnd(T data) 
    {
        Node<T>* newNode = new Node<T>(data);
        if (tail == nullptr) 
        {
            head = tail = newNode;
            return;
        }
        tail->next = newNode;
        tail = newNode;
    }

    void insertAfter(Node<T>* prevNode, T data) 
    {
        if (prevNode == nullptr) return;
        Node<T>* newNode = new Node<T>(data);
        newNode->next = prevNode->next;
        prevNode->next = newNode;
        if (prevNode == tail) tail = newNode;
    }

    void insertAtPosition(int pos, T data) 
    {
        if (pos <= 0) 
        {
            insertAtBegin(data);
            return;
        }

        Node<T>* current = head;
        int index = 0;

        while (current != nullptr && index < pos - 1) 
        {
            current = current->next;
            index++;
        }

        if (current == nullptr || current == tail) 
        {
            insertAtEnd(data);
            return;
        }

        insertAfter(current, data);
    }
//---------------------------------Delete-------------------------------

    void deleteAtBegin() 
    {
        if (head == nullptr) return; 

        Node<T>* temp = head;
        head = head->next;

        delete temp;
        temp = nullptr;
    }

    void deleteAtEnd() 
    {
        if (head == nullptr) return; 

        if (head == tail) 
        { 
            delete head;
            head = tail = nullptr;
            return;
        }

        Node<T>* current = head;

        while (current->next != tail) 
        {
            current = current->next;
        }

        delete tail;

        tail = current;
        tail->next = nullptr;
    }

    void deleteFirstByValue(T value) 
    {
        if (head == nullptr) return;

        if (head->data == value) 
        {
            deleteAtBegin();
            return;
        }

        Node<T>* current = head;
        Node<T>* prev = nullptr;

        while (current != nullptr && current->data != value) 
        {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) return;

        prev->next = current->next;

        if (current == tail) tail = prev;
        
        delete current;
        current = nullptr;
    }

    void deleteAtPosition(int pos) {
        if (head == nullptr) return;

        if (pos <= 0) 
        {
            deleteAtBegin();
            return;
        }

        int length = getLength();
        if (pos >= length) 
        {

            return;
        }

        Node<T>* current = head;
        Node<T>* prev = nullptr;
        int index = 0;

        while (current != nullptr && index < pos) 
        {
            prev = current;
            current = current->next;
            index++;
        }

        if (current == nullptr) return;

        prev->next = current->next;
        delete current;
    }

//---------------------------------Ultilies--------------------------------

    void printList() 
    {
        Node<T>* temp = head;
        std::cout << "[ ";
        while (temp != nullptr) 
        {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << "]\n";
    }

    int getLength() 
    {
        int count = 0;
        Node<T>* temp = head;
        while (temp != nullptr) 
        {
            count++;
            temp = temp->next;
        }
        return count;
    }

    Node<T>* getHead() { return head; }

    void clear() 
    {
        Node<T>* current = head;
        while (current != nullptr)
        {
            Node<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr;
    }


};
#endif // LL_H