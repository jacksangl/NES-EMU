#include <fstream>
#include <iostream>
#include "olc6502.h"   // now pulls in your stub Bus.h

int main() {
    Bus bus;            // this is your stub
    olc6502 cpu;
    cpu.ConnectBus(&bus);

    // load the file
    std::ifstream f("6502_functional_test.bin", std::ios::binary);
    if (!f.is_open()) { // Added a check to see if file opened
        std::cerr << "ERROR: Could not open \n";
        return 1;
    }
    f.read(reinterpret_cast<char*>(bus.ram.data()), bus.ram.size());
    f.close(); // Good practice to close the file

    cpu.reset(); // pc should be set by reset vector in the .bin file

    // A common way to run Klaus's test is to check if PC gets stuck
    // at the success address (0x3469 for many versions).
    // The test usually puts the CPU in an infinite loop there on success.
    // We'll also keep your original success/fail memory checks for now.
    
    // It's often useful to have a maximum cycle count to prevent infinite loops on failure.
    // For example, around 30-40 million cycles should be more than enough for this test.
    long long max_cycles = 40000000; 
    long long current_cycles = 0;
    uint16_t last_pc = 0;
    int stuck_counter = 0;


    while (current_cycles < max_cycles) {
       cpu.clock();
       current_cycles++;

        // Klaus test success: PC loops at a specific address (e.g., 0x3469)
        if (cpu.pc == 0x3469) { 
            // To confirm it's looping and not just passing through:
            if (last_pc == cpu.pc) {
                stuck_counter++;
                if (stuck_counter > 100) { // Arbitrary number to confirm it's stuck in a loop
                    std::cout << "ALL TESTS PASSED (PC trapped at " << std::hex << cpu.pc << ")\n";
                    return 0; 
                }
            } else {
                last_pc = cpu.pc;
                stuck_counter = 0;
            }
        } else {
            last_pc = cpu.pc;
            stuck_counter = 0;
        }

        // Your original failure condition (check if still relevant for your test ROM version)
        // This condition might indicate an error written by the ROM.
        if (bus.ram[0x0000] == 0x00 && current_cycles > 1000) { // Added a small delay before checking this
            std::cerr << "TEST FAILED (RAM[0x0000] == 0x00) @ PC=" << std::hex << cpu.pc << "\n";
            // You might want to dump some CPU state here for debugging
            // e.g., std::cerr << "A:" << (int)cpu.a << " X:" << (int)cpu.x << " Y:" << (int)cpu.y << " P:" << (int)cpu.status << " SP:" << (int)cpu.stkp << std::endl;
            return 1; 
        }
        
        // A more general failure: if PC gets stuck somewhere else
        // This is a very basic check; real test harnesses are more sophisticated.
        if (current_cycles > 100000) { // After some initial cycles
            if (cpu.pc == last_pc) {
                stuck_counter++;
                 if (stuck_counter > 20000 && cpu.pc != 0x3469) { // If stuck for a long time NOT at success
                    std::cerr << "TEST FAILED (PC stuck at " << std::hex << cpu.pc << ")\n";
                    return 1;
                 }
            } else {
                last_pc = cpu.pc;
                stuck_counter = 0;
            }
        }
    }

    if (current_cycles >= max_cycles) {
        std::cerr << "TEST TIMED OUT @ PC=" << std::hex << cpu.pc << "\n";
        return 1;
    }

    return 0; // Should be reached by pass/fail conditions above
}