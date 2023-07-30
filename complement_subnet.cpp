#include <iostream>
#include <iomanip>

void printSubnet(unsigned long i, unsigned long network, unsigned long mask)
{
    std::cout << "[" << std::setw(3) << std::setfill('0') << i+1 << std::setw(0) << "]:\t"
                << ((network & 0xFF000000) >> 24) << "."
                << ((network & 0x00FF0000) >> 16) << "."
                << ((network & 0x0000FF00) >> 8) << "."
                << (network & 0x000000FF);
    if (((network & 0xFF000000) >> 24) < 10 &&
        ((network & 0x00FF0000) >> 16) < 10 &&
        ((network & 0x0000FF00) >> 8) < 10 &&
        (network & 0x000000FF) < 10)
        {
            std::cout << "\t";
        }
    std::cout << "\t/ "
                << ((mask & 0xFF000000) >> 24) << "."
                << ((mask & 0x00FF0000) >> 16) << "."
                << ((mask & 0x0000FF00) >> 8) << "."
                << (mask & 0x000000FF)
                << "\t";
    if (((mask & 0xFF000000) >> 24) < 10 ||
        ((mask & 0x00FF0000) >> 16) < 10 ||
        ((mask & 0x0000FF00) >> 8) < 10 ||
        (mask & 0x000000FF) < 10)
        {
            std::cout << "\t";
        }
    std::cout << "; " << "0x"
                << std::hex << std::setw(8) << std::setfill('0') << std::uppercase << network << std::nouppercase << std::dec
                << " / " << "0x"
                << std::hex << std::setw(8) << std::setfill('0') << std::uppercase << mask << std::nouppercase << std::dec
                << std::endl;
}

int main(int argc, char* argv[])
{
    constexpr unsigned long network = (192U << 24) + (168U << 16) + (3U << 8) + 248U; // 32-bit network. Say (192.168.0.0 or 0xC0A80000)
    constexpr unsigned long mask = (255U << 24) + (255U << 16) + (255U << 8) + 248U; // 32-bit mask (0xFFFF0000 for the example case)
    unsigned long invnet, invmask, bitmask; // inverse network, inverse mask, bit mask to extract the bit

    for (unsigned long i = 0; i < 32; i++) // to iterate over the network bits
    {
        bitmask = (unsigned long)(0x80000000 >> i);
        invmask = (unsigned long)(0xFFFFFFFF << (31-i));

        invnet = (invmask & network) ^ bitmask;

        printSubnet(i, invnet, invmask);
        
        if (mask == invmask) break; // only while we have valid mask
    }
}