#include <iostream>
#include <functional>
#include "vector.h"
#include "LL.h"

template <typename K, typename V>
class UnorderedMap 
{
private:
    Vector<LinkedList<std::pair<K,V>>> buckets;
    int num_elements;
    float max_load_factor;  // threshold

    int getBucketIndex(const K& key, int bucket_count) const 
    {
        std::hash<K> hasher;
        return hasher(key) % bucket_count;
    }

    void rehash(int new_bucket_count) 
    {
        Vector<LinkedList<std::pair<K,V>>> newBuckets(new_bucket_count);

        for (int i = 0; i < new_bucket_count; i++) 
        {
            newBuckets[i] = LinkedList<std::pair<K,V>>();
        }

        for (int i = 0; i < buckets.size(); i++) 
        {
            Node<std::pair<K,V>>* cur = buckets[i].getHead();
            while (cur != nullptr) 
            {
                int newIdx = getBucketIndex(cur->data.first, new_bucket_count);
                newBuckets[newIdx].insertAtEnd(cur->data);
                cur = cur->next;
            }
        }

        for (int i = 0; i < buckets.size(); i++) 
        {
            buckets[i].clear();
        }

        buckets = newBuckets;
    }


    void checkLoadFactorAndRehash() 
    {
        float lf = (float)num_elements / buckets.size();
        if (lf > max_load_factor) 
        {
            int new_bucket_count = buckets.size() * 2;
            rehash(new_bucket_count);
        }
    }

public:
    UnorderedMap(int bucketCount =  8, float loadFactor = 0.75f) 
        : buckets(bucketCount), num_elements(0), max_load_factor(loadFactor) 
    {
        for (int i = 0; i < bucketCount; i++) 
        {
            buckets[i] = LinkedList<std::pair<K,V>>();
        }
    }

    int size() const { return num_elements; }

    bool empty() const { return num_elements == 0; }


    void insert(const K& key, const V& value) 
    {
        int idx = getBucketIndex(key, buckets.size());
        LinkedList<std::pair<K,V>>& bucket = buckets[idx];


        Node<std::pair<K,V>>* cur = bucket.getHead();
        while (cur != nullptr) 
        {
            if (cur->data.first == key) 
            {
                cur->data.second = value; // update
                return;
            }
            cur = cur->next;
        }
        bucket.insertAtEnd(std::make_pair(key, value)); // insert mới
        num_elements++;

        checkLoadFactorAndRehash();
    }

    // Find value by key
    V* find(const K& key) 
    {
        int idx = getBucketIndex(key, buckets.size());
        LinkedList<std::pair<K,V>>& bucket = buckets[idx];

        Node<std::pair<K,V>>* cur = bucket.getHead();
        while (cur != nullptr) 
        {
            if (cur->data.first == key) 
            {
                return &(cur->data.second);
            }
            cur = cur->next;
        }
        return nullptr;
    }

    // Erase key
    void erase(const K& key) 
    {
        int idx = getBucketIndex(key, buckets.size());
        LinkedList<std::pair<K,V>>& bucket = buckets[idx];

        Node<std::pair<K,V>>* cur = bucket.getHead();
        Node<std::pair<K,V>>* prev = nullptr;

        while (cur != nullptr) 
        {
            if (cur->data.first == key) 
            {
                if (prev == nullptr) 
                {
                    bucket.deleteAtBegin();
                } 
                else 
                {
                    prev->next = cur->next;
                    delete cur;
                }
                num_elements--;
                return;
            }
            prev = cur;
            cur = cur->next;
        }
    }

    // Operator []
    V& operator[](const K& key) 
    {
        V* found = find(key);
        if (found != nullptr) return *found;
        insert(key, V());
        return *find(key);
    }

    // Debug print
    void print() 
    {
        for (int i = 0; i < buckets.size(); i++) 
        {
            std::cout << "Bucket " << i << ": ";
            Node<std::pair<K,V>>* cur = buckets[i].getHead();
            while (cur != nullptr) 
            {
                std::cout << "(" << cur->data.first << "," << cur->data.second << ") ";
                cur = cur->next;
            }
            std::cout << "\n";
        }
    }
};
