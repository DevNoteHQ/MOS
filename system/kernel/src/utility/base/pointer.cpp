#include "pointer_definition.hpp"

namespace STD {
    template <class T> 
    T&& forward(typename remove_reference<T>::type& t) noexcept {
        return static_cast<typename remove_reference<T>::type&&>(t);
    }
    template <class T> 
    T&& forward(typename remove_reference<T>::type&& t) noexcept {
        return static_cast<typename remove_reference<T>::type&&>(t);
    }

    template <typename T>
    Pointer<T>::Pointer(T* pointer) {
        this->pointer = pointer;
    }

    template <typename T>
    T Pointer<T>::val() {
        return *pointer;
    }

    template <typename T>
    void Pointer<T>::setVal(T value) {
        *pointer = value;
    }

    template <typename T>
    void Pointer<T>::setAddr(T* value) {
        pointer = value;
    }

    template <typename T>
    T* Pointer<T>::addr() {
        return pointer;
    }

    template <typename T>
    uint64_t Pointer<T>::aVal() {
        return (uint64_t) pointer;
    }

    template <typename T>
    template <typename... Args>
    AutoPointer<T>::AutoPointer(Args&&... args): Pointer<T>(new T(forward<Args>(args)...)) {}

    template<typename T>
    AutoPointer<T>::~AutoPointer() {
        delete(this->pointer);
    }
}
