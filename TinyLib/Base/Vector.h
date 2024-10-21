#pragma once
#include "Memory.h"


namespace tl {
    template<typename T>
    class Vector {
    public:
        Vector();
        ~Vector();
        void push(const T& value);
        T pop();
        T& operator[](size_t index);
        const T& operator[](size_t index) const;
        void resize(size_t new_capacity);
        void clear();
        size_t getSize() const;
        size_t getCapacity() const;
        void insert(size_t pos, const T& value);
        void erase(size_t pos);

        // Iterator stuff specifically to be used in range-based for loops.
        T* begin() { return data; }
        T* end() { return data + size; }
        const T* begin() const { return data; }
        const T* end() const { return data + size; }

    private:
        T* data;
        size_t size = 0;
        size_t capacity = 0;
    };


    /// @brief Create a new empty vector.
    /// @tparam T What type this vector will hold.
    template<typename T>
    Vector<T>::Vector()
    {
        data = nullptr;
        size = 0;
        capacity = 0;
    }


    /// @brief Clean up vector data.
    /// @tparam T How much memory is freed depends on the data type you used.
    template<typename T>
    Vector<T>::~Vector()
    {
        if (data != nullptr) {
            tl::free(data);
            data = nullptr;
        }
    }


    /// @brief Adds a new element to the end of the vector.
    /// @tparam T Must match the type for this vector.
    /// @param value Element to add. 
    template<typename T>
    void Vector<T>::push(const T& value)
    {
        if (size == capacity)
            resize(capacity == 0 ? 1 : capacity + 1);

        data[size++] = value;
    }


    /// @brief Get the last element and remove it from the vector.
    /// @tparam T Must match the type for this vector.
    /// @return The removed element.
    template<typename T>
    T Vector<T>::pop()
    {
        if (size > 0)
        {
            T element = data[--size];
            return element;
        }
    }


    /// @brief Write access to elements.
    /// @tparam T Must match the type for this vector.
    /// @param index Element to overwrite.
    /// @return Reference to element to overwrite.
    template<typename T>
    T& Vector<T>::operator[](size_t index)
    {
        return data[index];
    }


    /// @brief Read access to elements.
    /// @tparam T Must match the type for this vector.
    /// @param index Element to read.
    /// @return Reference to element to read.
    template<typename T>
    const T& Vector<T>::operator[](size_t index) const
    {
        return data[index];
    }


    /// @brief Resize the max capacity for this vector.
    /// @tparam T Must match the type for this vector.
    /// @param new_capacity New capacity.
    /// 
    /// If you don't use push or pop, you can also manually resize the
    /// vector with this, and can then access elements within capacity using [].
    template<typename T>
    void Vector<T>::resize(size_t new_capacity)
    {
        T* new_data = static_cast<T*>(tl::malloc(new_capacity * sizeof(T)));

        for (size_t i = 0; i < size; ++i)
            new_data[i] = data[i];

        if (data != nullptr)
            tl::free(data);

        data = new_data;
        capacity = new_capacity;
    }


    /// @brief Clear vector size for most vector methods.
    /// @tparam T Must match the type for this vector.
    template<typename T>
    void Vector<T>::clear()
    {
        size = 0;
    }


    /// @brief Get the size of this vector.
    /// @tparam T Must match the type for this vector.
    /// @return Current size of vector.
    /// 
    /// Size is based on how many elements actually exist in the vector.
    template<typename T>
    size_t Vector<T>::getSize() const
    {
        return size;
    }


    /// @brief Get the capacity of this vector.
    /// @tparam T Must match the type for this vector.
    /// @return Current capacity of vector.
    /// 
    /// Capacity is how big the internal array is for this vector.
    /// Good to check to make sure you don't go out of bounds with [].
    template<typename T>
    size_t Vector<T>::getCapacity() const
    {
        return capacity;
    }


    /// @brief Insert an element anywhere in the vector.
    /// @tparam T T Must match the type for this vector.
    /// @param pos Position to insert element at.
    /// @param value Element to insert.
    template<typename T>
    void Vector<T>::insert(size_t pos, const T& value)
    {
        if (size == capacity)
            resize(capacity == 0 ? 1 : capacity + 1);

        for (size_t i = size; i > pos; --i)
            data[i] = data[i - 1];

        data[pos] = value, size++;
    }


    /// @brief Delete an element and shift the rest of the vector to fit.
    /// @tparam T T Must match the type for this vector.
    /// @param pos Index of element to delete.
    /// 
    /// When you erase an element, everything to the right of that element
    /// will be shifted left in the vector to not leave an empty space.
    template<typename T>
    void Vector<T>::erase(size_t pos)
    {
        if (pos < size) {
            for (size_t i = pos; i < size - 1; ++i)
                data[i] = data[i + 1];
            size--;
        }
    }
}