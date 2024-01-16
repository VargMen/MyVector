#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <initializer_list>
#include <cassert>
#include <algorithm> // for std::copy_n


template<typename T>
class MyVector
{
public:
    explicit MyVector(int size);
    MyVector(std::initializer_list<T> list);
    MyVector(const MyVector<T>& vec);
    MyVector(MyVector<T>&& vec) noexcept;
    ~MyVector() { delete[] m_data; }

    MyVector& operator=(MyVector&& vec) noexcept
    {
        if(&vec == this)
            return *this;

        delete[] m_data;
        m_size = vec.m_size;
        m_data = vec.m_data;

        vec.m_size = 0;
        vec.m_data = nullptr;

        return *this;
    }

    T operator[](int index) const
    {
        assert((index >= 0 && index < m_size) && "Index out of bounds in operator[]");

        return m_data[index];
    }

    friend std::ostream& operator<<(std::ostream& out, const MyVector& vec)
    {
        out << '(';
        if(!vec.m_size) //vec.m_size == 0
        {
            out << ')';
            return out;
        }
        for(int i{0}; i < vec.m_size; ++i)
        {
            if(i == vec.m_size - 1)
            {
                out << vec[i] << ')';
                break;
            }
            out << vec[i] << ", ";
        }
        return out;
    }

    void erase();
    void reallocate(int newSize);
    void resize(int newSize);
    T remove(int index);
    void insert(const T& value, int index);
    void push_back(const T& value) { insert(value, m_size - 1); }
    T pop_back() { return remove(m_size - 1); }
    int size() const { return m_size; }

private:

    T* m_data{};
    int m_size{};
};


template<typename T>
MyVector<T>::MyVector(int size)
        : m_size{ size }, m_data{ new T[size]{} }
{
    assert(size > 0 && "Negative size of array!\n");
}

template<typename T>
MyVector<T>::MyVector(std::initializer_list<T> list)
        : MyVector(list.size())
{
    int count{};
    for(const auto& e: list)
    {
    m_data[count] = e;
    ++count;
    }
}

template<typename T>
MyVector<T>::MyVector(const MyVector<T>& vec)
{
    delete[] m_data;
    m_size = vec.m_size;
    m_data = new T[m_size];
    for(int i{0}; i < m_size; ++i)
    {
        m_data[i] = vec[i];
    }
}

template<typename T>
MyVector<T>::MyVector(MyVector<T>&& vec) noexcept
        :m_data(vec.m_data), m_size(vec.m_size)
{
    vec.m_size = 0;
    vec.m_data = nullptr;
}

template<typename T>
void MyVector<T>::erase()
{
    delete[] m_data;
    m_data = nullptr;
    m_size = 0;
}

template<typename T>
void MyVector<T>::reallocate(int newSize)
{
    erase();

    if(newSize <= 0)
        return;
    m_data = new T[newSize]{};
    m_size = newSize;
}

template<typename T>
void MyVector<T>::resize(int newSize)
{
    assert(newSize >= 0 && "Invalid size for resize");

    if(m_size == newSize)
        return;

    if(!newSize) // newSize == 0
    {
        erase();
        return;
    }

    T* data {new T[newSize]{} };

    if(m_size > 0) // if our vector is not empty
    {
        int elementsToCopy { (newSize > m_size) ? m_size : newSize };
        std::copy_n(m_data, elementsToCopy, data);
    }
    delete[] m_data;

    m_data = data;
    m_size = newSize;
}

template<typename T>
T MyVector<T>::remove(int index)
{
    assert(m_size > 0 && "Remove from empty vector");
    assert((index >= 0 && index < m_size) && "Index out of bounds in remove");

    T value { m_data[index] }; //this value will be returned

    T* data { new T[m_size - 1]{} };

    std::copy_n(m_data, index, data);
    std::copy_n(m_data + index + 1, m_size - index - 1, data + index);

    delete[] m_data;
    m_data = data;
    --m_size;
    return value;
}

template<typename T>
void MyVector<T>::insert(const T& value, int index)
{
    assert((index >= 0 && index < m_size) && "Index out of bounds in insert");

    T* data { new T[m_size + 1]{} };

    std::copy_n(m_data, index, data);
    data[index] = value;
    std::copy_n(m_data + index, m_size - index, data + index + 1);

    delete[] m_data;
    m_data = data;
    ++m_size;
}


#endif //MYVECTOR_H
