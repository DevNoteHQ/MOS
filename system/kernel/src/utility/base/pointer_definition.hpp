
#ifndef POINTER_DEFINITON_HPP
#define POINTER_DEFINITON_HPP

template <class T>
struct remove_reference { 
    typedef T type; 
};

template <class T>
struct remove_reference<T&> { 
    typedef T type; 
};

template <class T>
struct remove_reference<T&&> { 
    typedef T type;
};

template <class T> 
T&& forward(typename remove_reference<T>::type& t) noexcept;
template <class T> 
T&& forward(typename remove_reference<T>::type&& t) noexcept;

template <typename T>
class Pointer {
protected:
    T* pointer;
public:
    Pointer(T* pointer);
    T getValue();
    void setValue(T value);
    T* getAddress();
    uint64_t getAddressValue();
};

template <typename T>
class AutoPointer : public Pointer<T> {
public:
    template<typename... Args>
    AutoPointer(Args&&... args);
    ~AutoPointer();
};

#endif
