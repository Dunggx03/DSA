#ifndef VECTOR_H
#define VECTOR_H

template <typename T>
class Vector {
private:
    T* v_begin;
    T* v_end;
    T* v_cap;

public:

//-------------------------Constructor - Destructor------------------------------
    Vector() : v_begin(nullptr), v_end(nullptr), v_cap(nullptr) {} // default

    explicit Vector(int n, const T& value = T()) // init
    {
        v_begin = new T[n];
        for (int i = 0; i < n; i++) v_begin[i] = value;
        v_end = v_begin + n;
        v_cap = v_begin + n;
    }

    Vector(const Vector& other) //copy
    {
        int n = other.size();
        v_begin = new T[n];
        for (int i = 0; i < n; i++) v_begin[i] = other.v_begin[i];
        v_end = v_begin + n;
        v_cap = v_begin + n;
    }

    Vector& operator=(const Vector& other)  //assign
    {
        if (this != &other) 
        {
            delete[] v_begin;
            int n = other.size();
            v_begin = new T[n];
            for (int i = 0; i < n; i++) v_begin[i] = other.v_begin[i];
            v_end = v_begin + n;
            v_cap = v_begin + n;
        }
        return *this;
    }

    Vector(Vector&& other) noexcept     //move ctor
        : v_begin(other.v_begin), v_end(other.v_end), v_cap(other.v_cap) 
    {
    other.v_begin = other.v_end = other.v_cap = nullptr;
    }

    Vector& operator=(Vector&& other) noexcept      // move operator
    {
        if (this != &other) 
        {
            delete[] v_begin;
            v_begin = other.v_begin;
            v_end   = other.v_end;
            v_cap   = other.v_cap;
            other.v_begin = other.v_end = other.v_cap = nullptr;
        }
        return *this;
    }

    ~Vector() 
    {
        delete[] v_begin;
        v_begin = v_end = v_cap = nullptr;
    }

//-------------------------------- Capacity ------------------------------------
    int size() const { return static_cast<int>(v_end - v_begin); }

    int capacity() const { return static_cast<int>(v_cap - v_begin); }

    bool empty() const { return v_begin == v_end; }

    void reserve(int new_cap) // allocate    
    {
        if (new_cap > capacity()) 
        {
            int sz = size();
            T* new_begin = new T[new_cap];
            for (int i = 0; i < sz; i++) new_begin[i] = v_begin[i];
            delete[] v_begin;
            v_begin = new_begin;
            v_end = v_begin + sz;
            v_cap = v_begin + new_cap;
        }
    }

    void resize(int n, const T& value = T()) 
    {
        int sz = size();
        if (n < sz) 
        {
            v_end = v_begin + n;
        } 
        else if (n > sz) 
        {
            reserve(n);
            for (int i = sz; i < n; i++) v_begin[i] = value;
            v_end = v_begin + n;
        }
    }

//--------------------------------- Iterators ------------------------------------
    T* begin() { return v_begin; }

    T* end() { return v_end; }
    
    const T* begin() const{ return v_begin; }
    
    const T* end() const{ return v_end; }

// ------------------------------ Access index ----------------------------------
    T& operator[](int index) { return v_begin[index]; }

    const T& operator[](int index) const{ return v_begin[index]; }

    T& front() { return *v_begin; }
    const T& front() const { return *v_begin; }

    T& back() { return *(v_end - 1); }
    const T& back() const { return *(v_end - 1); }

// ---------------------------------- Modifiers ----------------------------------
    void push_back(const T& value) 
    {
        if (v_end == v_cap) 
        {
            int new_cap = capacity() == 0 ? 1 : capacity() * 2;
            reserve(new_cap);
        }
        *v_end = value;
        ++v_end;
    }
    
    void pop_back()
    {
        if (!empty()) --v_end;
    }

    void insert(int index, const T& value)
    {
        if (index < 0 || index > size()) 
        {
            std::cerr << "Index out of range\n";
            return;
        }
        if (v_end == v_cap) 
        {
            int new_cap = capacity() == 0 ? 1 : capacity() * 2;
            reserve(new_cap);
        }
        
        //for (T* p = v_end; p > v_begin + index; --p) { *p = *(p - 1); }

        // shift right
        std::move_backward(v_begin + index, v_end, v_end + 1);
        
        v_begin[index] = value;
        ++v_end;
    }
    void erase(int index)
    {
        if (index < 0 || index >= size()) 
        {
            std::cerr << "Index out of range\n";
            return;
        }
        //for (int i = index; i < size() - 1; i++) { v_begin[i] = v_begin[i + 1]; }
        std::move(v_begin + index + 1, v_end, v_begin + index);

        --v_end;
        v_end->~T();
    }

    void clear() 
    { 
        while(v_end != v_begin)
        {
            --v_end;
            v_end->~T();
        } 
    }

};

#endif // VECTOR_H