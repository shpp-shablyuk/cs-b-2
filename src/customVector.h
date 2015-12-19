#ifndef CUSTOMVECTOR_H
#define CUSTOMVECTOR_H

#include <iterator>

template<typename ValueType>
class CustomVector
{
public:
    CustomVector();
    CustomVector(int n, ValueType value);

    ~CustomVector();

    int size() const;
    int capacity() const;
    bool empty() const;

    ValueType& operator[](int index);
    ValueType& at(int index);
    ValueType& front();
    ValueType& back();

    void push_back(ValueType value);
    void pop_back();
    void insert(int index, ValueType value);
    void erase(int index);
    void clear();

    typedef ValueType* iterator;

    iterator begin() {
        return array;
    }

    iterator end() {
        return array + count;
    }

    CustomVector(const CustomVector<ValueType>& src);
    CustomVector<ValueType>& operator=(const CustomVector<ValueType>& src);
private:
    static const int INITIAL_CAPACITY = 10;

    std::iterator<std::random_access_iterator_tag, ValueType> it;

    ValueType* array;
    int vCapacity;
    int count;

    void deepCopy(const CustomVector<ValueType>& src);
    void expandCapacity();

    bool isIndexInRange(int index);

};

template<typename ValueType>
CustomVector<ValueType>::CustomVector() {
    vCapacity = INITIAL_CAPACITY;
    array = new ValueType[vCapacity];
    count = 0;
}

template<typename ValueType>
CustomVector<ValueType>::CustomVector(int n, ValueType value) {
    vCapacity = (n > INITIAL_CAPACITY) ? n : INITIAL_CAPACITY;
    count = n;
    array = new ValueType[vCapacity];
    for (int i = 0; i < n; i++) {
        array[i] = value;
    }
}

template<typename ValueType>
CustomVector<ValueType>::~CustomVector() {
    delete [] array;
}

template<typename ValueType>
int CustomVector<ValueType>::size() const {
    return count;
}

template<typename ValueType>
int CustomVector<ValueType>::capacity() const {
    return vCapacity;
}

template<typename ValueType>
bool CustomVector<ValueType>::empty() const {
    return count == 0;
}

template<typename ValueType>
ValueType& CustomVector<ValueType>::operator[](int index) {
    return array[index];
}

template<typename ValueType>
ValueType& CustomVector<ValueType>::at(int index) {
    if (!isIndexInRange(index)) {
        throw "at: index out of range";
    }
    return array[index];
}

template<typename ValueType>
ValueType& CustomVector<ValueType>::front() {
    if (vCapacity == 0) {
        throw "front: vector is empty";
    }
    return array[0];
}

template<typename ValueType>
ValueType& CustomVector<ValueType>::back() {
    if (vCapacity == 0) {
        throw "back: vector is empty";
    }
    return array[count - 1];
}

template<typename ValueType>
void CustomVector<ValueType>::push_back(ValueType value) {
    if (count == vCapacity) {
        expandCapacity();
    }
    array[count++] = value;
}

template<typename ValueType>
void CustomVector<ValueType>::pop_back() {
    if (vCapacity == 0) {
        throw "pop_back: vector is empty";
    }
    count--;
}

template<typename ValueType>
void CustomVector<ValueType>::insert(int index, ValueType value) {
    if (!isIndexInRange(index)) {
        throw "insert: index out of range";
    }
    if (count == vCapacity) {
        expandCapacity();
    }
    for (int i = count; i > index; i--) {
        array[i] = array[i - 1];
    }
    array[index] = value;
    count++;
}

template<typename ValueType>
void CustomVector<ValueType>::erase(int index) {
    if (!isIndexInRange(index)) {
        throw "erase: index out of range";
    }
    for (int i = index; i < count - 1; i++) {
        array[i] = array[i + 1];
    }
    count--;
}

template<typename ValueType>
void CustomVector<ValueType>::clear() {
    count = 0;
}

template<typename ValueType>
CustomVector<ValueType>::CustomVector(const CustomVector<ValueType>& src) {
    deepCopy(src);
}

template<typename ValueType>
CustomVector<ValueType>& CustomVector<ValueType>::operator=(const CustomVector<ValueType>& src) {
    if (this != &src) {
        delete [] array;
        deepCopy();
    }
    return *this;
}

template<typename ValueType>
void CustomVector<ValueType>::deepCopy(const CustomVector<ValueType>& src) {
    vCapacity = src.vCapacity;
    count = src.count;
    array = new ValueType[vCapacity];
    for (int i = 0; i < count; i++) {
        array[i] = src.array[i];
    }
}

template<typename ValueType>
void CustomVector<ValueType>::expandCapacity() {
    ValueType* oldAray = array;
    vCapacity *= 2;
    array = new ValueType[vCapacity];
    for (int i = 0; i < count; i++) {
        array[i] = oldAray[i];
    }
    delete [] oldAray;
}

template<typename ValueType>
bool CustomVector<ValueType>::isIndexInRange(int index) {
    return (index >= 0) || (index < vCapacity);
}

#endif // CUSTOMVECTOR_H
