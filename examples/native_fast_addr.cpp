#include <utfast_addr.h>
#include <iostream>

int main() {
    utb::fint32_t reg(0b10110010);

    std::cout << "Value: " << reg.get_value() << "\n";
    std::cout << "Ones:  " << reg.num_ones() << "\n";
    std::cout << "Zeros: " << reg.num_zeros() << "\n";

    reg.flip(1);
    reg.flip(7);

    std::cout << "After flip: " << reg.get_value() << "\n";
    std::cout << "Ones:  " << reg.num_ones() << "\n";
    std::cout << "Zeros: " << reg.num_zeros() << "\n";
    
    return 0;
}