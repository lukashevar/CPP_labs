#include "Simulation.h"

int main() {
    Simulation sim;
    sim.loadEquations("input.txt");
    sim.run();
    return 0;
}
