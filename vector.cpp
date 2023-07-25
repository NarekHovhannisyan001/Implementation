#include<iostream>
#include<vector>

template<typename T>
struct Array
{
    int m_capacity;
    int m_size;
    T* m_arr;
};

template<typename T>
T* begin(Array<T>& vec){
    return vec.m_arr;
}

template<typename T>
T* end(Array<T>& vec){
    return vec.m_arr + vec.m_size - 1;
}

template<typename T>
T at(Array<T>& vec, int index){
    if ( index >= 0 && index < vec.m_size){
        return vec.m_arr[index];
    }
    throw std::out_of_range("Out of range");
}

template<typename T>
T front(Array<T>& vec){
    return vec.m_arr[0];
}

template<typename T>
T back(Array<T>& vec){
    return vec.m_arr[vec.m_size - 1];
}

template<typename T>
bool empty(Array<T>& vec){
    return vec.m_size == 0;
}

template<typename T>
int size(Array<T>& vec){
    return vec.m_size;
}

template<typename T>
int max_size(Array<T>& vec){
    return vec.m_capacity;
}

template<typename T>
void reserve(Array<T>& vec, int newCapacity){
    if (vec.m_capacity >= newCapacity){
        return;
    }
    T* newArr = new T[newCapacity];
    std::copy(vec.m_arr, vec.m_arr + vec.m_size, newArr);
    delete[] vec.m_arr;
    vec.m_arr = newArr;
    vec.m_capacity = newCapacity;
}

template<typename T>
void clear(Array<T>& vec){
    delete[] vec.m_arr;
    vec.m_size = 0;
}

template<typename T>
void erase(Array<T>& vec, T* index){
    if (index < begin(vec) || index > end(vec)){
        throw std::out_of_range("Invalid index");
    }
    for(T* i = index; i < end(vec); ++i) {
        *i = *(i + 1);
    }
    --vec.m_size;
}

template<typename T>
void insert(Array<T>& vec, int index, const T& element){
    if (index < 0 || index > vec.m_size){
        throw std::out_of_range("Invalid index");
    }
    if (vec.m_size == vec.m_capacity){
        int newCapacity = 2 * vec.m_capacity;
        T* newArr = new T[newCapacity];
        std::copy(vec.m_arr, vec.m_arr + index, newArr);
        newArr[index] = element;
        std::copy(vec.m_arr + index + 1, vec.m_arr + vec.m_size, newArr + index + 1);
        delete[] vec.m_arr;
        vec.m_arr = newArr;
        vec.m_size++;
        vec.m_capacity = newCapacity;
    }
    else{
        for ( T* i = vec.m_arr + vec.m_size; i > vec.m_arr + index; --i){
            *i = *(i - 1);
        }
        vec.m_arr[index] = element;
        vec.m_size++;
    }
}

template<typename T>
void push_back(Array<T>& vec, const T& element){
    if (vec.m_size == vec.m_capacity){
        int newCapacity = vec.m_capacity > 0 ? 2 * vec.m_capacity : 1;
        T* newArr = new T[newCapacity];
        std::copy(vec.m_arr, vec.m_arr + vec.m_size, newArr);
        delete[] vec.m_arr;
        vec.m_arr = newArr;
        vec.m_capacity = newCapacity;
    }
    vec.m_arr[vec.m_size] = element;
    vec.m_size++;
}

template<typename T>
void pop_back(Array<T>& vec){
    if (vec.m_size > 0){
        vec.m_size--;
    }
}

int main(){
    Array<int> Vec;
    Vec.m_size = 0;
    Vec.m_capacity = 0;
    int* arr = new int[0];
    Vec.m_arr = arr;
    push_back(Vec, 1);
    push_back(Vec, 2);
    push_back(Vec, 3);
    push_back(Vec, 7);
    // pop_back(Vec);
    insert(Vec, 2, 999);
    // std::cout << back(Vec);
    erase(Vec, begin(Vec) + 1);
    std::cout << front(Vec);
    // for ( int i = 0; i < size(Vec); ++i){
    //     std::cout << Vec.m_arr[i] << " ";
    // }
}
