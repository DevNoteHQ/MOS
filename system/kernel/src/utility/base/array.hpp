
#ifndef ARRAY_HPP
#define ARRAY_HPP

template<typename E, uint64_t S>
class Array {  
    public:
        E data[S];

        Array() = default;
        Array(const E *addr);
        void assignData(const E *addr);
};
#endif