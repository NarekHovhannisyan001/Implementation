#include <iostream>

unsigned int* arr = nullptr;
class bit_vector {
private:
    static int size_bit;
    bool test1(int size, int bit) {
        if (size >= bit) return true;
        return false;
    }

public:
    bit_vector(const int size) {
        arr = new unsigned int[size / sizeof(int) + 1]();
        size_bit = size;
    }

    void set(int bit) {
        if (!test1(size_bit, bit)) {
            std::cout << "That bit is not held" << std::endl;
            return;
        }
        int balance = bit % sizeof(int);
        (arr[bit / sizeof(int)]) |= 1u << balance;
    }

    void set() {
        for (int i = 0; i < size_bit; ++i) {
            set(i);
        }
    }

    void reset(int bit) {
        if (!test1(size_bit, bit)) {
            std::cout << "That bit is not held" << std::endl;
            return;
        }
        int balance = bit % sizeof(int);
        (arr[bit / sizeof(int)]) &= ~(1u << balance);
    }

    void reset() {
        for (int i = 0; i < size_bit; ++i) {
            reset(i);
        }
    }

    bool test(int bit) {
        if (!test1(size_bit, bit)) {
            std::cout << "That bit is not held" << std::endl;
            return false;
        }
        int balance = bit % sizeof(int);
        return (arr[bit / sizeof(int)] >> balance) & 1u;
    }

    void flip(int bit) {
        if (!test1(size_bit, bit)) {
            std::cout << "That bit is not held" << std::endl;
            return;
        }
        if (test(bit)) {
            reset(bit);
            return;
        }
        set(bit);
    }

    void flip() {
        for (int i = 0; i < size_bit; ++i) {
            flip(i);
        }
    }

    unsigned long to_ulong() {
        unsigned long res{};
        int number = size_bit / sizeof(unsigned int) + 1;
        for (int i = number - 1; i >= 0; --i) {
            res =  (res << size_bit) | arr[i];
        }
        return res;
    }

    unsigned long long to_ullong() {
        unsigned long long res{};
        int number = size_bit / sizeof(unsigned int) + 1;
        for (int i = number - 1; i >= 0; --i) {
            res = (res << size_bit) | arr[i];
        }
        return res;
    }

    int size() {
        return size_bit;
    }

    int count() {
        int c{};
        for (int i = 0; i < size(); ++i) {
            if (test(i)) {
                c++;
            }
        }
        return c;
    }

    bool operator[](int bit) {
        return test(bit);
    }

    ~bit_vector() {
        delete[] arr;
        arr = nullptr;
    }
};

int bit_vector::size_bit = 0;

int main() {
    bit_vector bv(64);

    bv.set(1);
    bv.set(3);
    bv.set(5);
    bv.set(66);

    for (int i = 0; i < bv.size(); ++i) {
        std::cout << "Bit at index " << i << " is set? " << bv.test(i) << std::endl;
    }

    unsigned long ul = bv.to_ulong();
    std::cout << "Bit Vector as unsigned long: " << ul << std::endl;

    unsigned long long ull = bv.to_ullong();
    std::cout << "Bit Vector as unsigned long long: " << ull << std::endl;

    bv.reset();

    for (int i = 0; i < bv.size(); ++i) {
        std::cout << "Bit at index " << i << " is set? " << bv.test(i) << std::endl;
    }

    return 0;
}
