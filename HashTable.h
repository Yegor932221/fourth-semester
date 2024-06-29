#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <list>
#include <assert.h>
#include <iterator>

class HashFunction {
public:
    virtual ~HashFunction() = default;
    virtual int hash(const int key, const int m_tableSize) const = 0;
    virtual HashFunction* clone() const = 0;
};

class FirstHashFunction : public HashFunction {
public:
    ~FirstHashFunction() override = default;
    int hash(const int key, const int m_tableSize) const override;
    HashFunction* clone() const override {
        return new FirstHashFunction(*this);
    }
private:
    static constexpr int c = 9 % 5;
    static constexpr int d = 9 % 7;
};

class SecondHashFunction : public HashFunction {
public:
    ~SecondHashFunction() override = default;
    int hash(const int key, const int m_tableSize) const override;
    HashFunction* clone() const override {
        return new SecondHashFunction(*this);
    }
};

class ThirdHashFunction : public HashFunction {
public:
    ~ThirdHashFunction() override = default;
    int hash(const int key, const int m_tableSize) const override;
    HashFunction* clone() const override {
        return new ThirdHashFunction(*this);
    }
};

template <typename T>
class HashTable
{
private:
    struct Node
    {
        int m_key = 0;
        T m_value;
        Node(int key, const T& value) : m_key(key), m_value(value) {}
    };
private:
    int m_tableSize=10;
    std::vector<std::list<Node>> m_table;
    HashFunction* m_hashFunction;
public:
    HashTable();
    HashTable(HashTable &other);
    HashTable(HashFunction* hashFunc, int size);
    ~HashTable();
    bool  AddEl(int key, const T& value);
    bool Contains(const int key)const;
    bool Erase(const int key) ;
    void Print() const;
    HashTable<T>& operator=(const HashTable& other);
    T& operator[](const int key);
    bool Resize(const int size);
    void ChangeHashFunction(HashFunction* function);
    void Clear();
    typename std::list<Node>::const_iterator  Iter(int const key, int& i) const;
    int Getsize() const ;
public:
    friend class HashTableWidget;
};

template <typename T>
HashTable<T>::HashTable() :m_tableSize(10), m_table(10), m_hashFunction(new FirstHashFunction()) {};

template <typename T>
HashTable<T>::HashTable(HashTable& other) :m_table(other.m_table), m_tableSize(other.m_tableSize), m_hashFunction(other.m_hashFunction->clone()) {}

template <typename T>
HashTable<T>::HashTable(HashFunction* hashFunc, int size) : m_tableSize(size), m_table(size), m_hashFunction(hashFunc->clone()) {}

template <typename T>
HashTable<T>::~HashTable()
{
    delete m_hashFunction;
}

template <typename T>
bool HashTable<T>::AddEl(int key, const T& value)
{
    int i = 0;
    auto it = Iter(key, i);
    if (it != m_table[i].end())
    {
        std::cerr << "Error: Key " << key << " already exists in the table." << std::endl;
        return false;
    }
    m_table[i].push_back(Node(key, value));
    return true;
}

template <typename T>
void HashTable<T>::Print() const {
    for (int i = 0; i < m_tableSize; ++i) {
        std::cout << i << ": ";
        for (const auto& node : m_table[i]) {
            std::cout << "(" << node.m_key << ", " << node.m_value << ") -> ";
        }
        std::cout << std::endl;
    }
}

template <typename T>
bool HashTable<T>::Contains(int const key) const
{
    int i = 0;
    auto it=Iter(key, i);
    if (it != m_table[i].end())
    {
        return true;
    }
    else return false;
}

    template <typename T>
    bool HashTable<T>::Erase(const int key)
    {
        int i = 0;
        auto it = Iter(key, i);
        if (it != m_table[i].end())
        {
            m_table[i].erase(it);
            return true;
        }
        else return false;
    }

    template <typename T>
    HashTable<T>& HashTable<T>::operator=(const HashTable& other)
    {
        if (&other==this) return *this;
        delete m_hashFunction;
        m_hashFunction = other.m_hashFunction->clone();
        m_tableSize = other.m_tableSize;
        m_table = other.m_table;
        return *this;
    }

    template <typename T>
    T& HashTable<T>::operator[](const int key)
    {
        int i = m_hashFunction->hash(key, m_tableSize);
        for (auto it = m_table[i].begin(); it != m_table[i].end(); ++it) {
            if (it->m_key == key) {
                return it->m_value;
            }
        }
        std::cerr << "Error: there is no element with a key:"<<key << std::endl;
        for ( auto& list : m_table) {
            for ( auto& node : list) {
                return node.m_value;;
            }
        }
    }

    template <typename T>
    bool HashTable<T>::Resize(const int size) {
        if (size <= 0)
        {
            std::cerr << "Error: size <=0" << std::endl;
            return false;
        }
        std::vector<std::list<Node>> newTable(size);
        for (const auto& list : m_table) {
            for (const auto& node : list) {
                int i = m_hashFunction->hash(node.m_key, size);
                newTable[i].push_back(node);
            }
        }
        m_table.swap(newTable);
        m_tableSize = size;
        return true;
    }

    template <typename T>
    void HashTable<T>::ChangeHashFunction(HashFunction* function) {
        delete m_hashFunction;
        m_hashFunction = function->clone();
        std::vector<std::list<Node>> newTable(m_tableSize);
        for (const auto& list : m_table) {
            for (const auto& node : list) {
                int i = m_hashFunction->hash(node.m_key, m_tableSize);
                newTable[i].push_back(node);
            }
        }
        m_table.swap(newTable);
    }

    template <typename T>
    void HashTable<T>::Clear() {
        for (auto& list : m_table) {
            list.clear();
        }
    }


    template <typename T>
    typename std::list<typename HashTable<T>::Node>::const_iterator HashTable<T>::Iter(int const key,int& i) const {
        i = m_hashFunction->hash(key, m_tableSize);
        for (auto it = m_table[i].begin(); it != m_table[i].end(); ++it) {
            if (it->m_key == key) {
                return it;
            }
        }
        return m_table[i].end();
    }

    template <typename T>
    int HashTable<T>::Getsize() const {
        return m_tableSize;
    }
