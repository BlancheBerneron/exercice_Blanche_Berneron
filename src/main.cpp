#include "network.h"
#include "random.h"
#include "simulation.h"
#include <iostream>

 RandomNumbers RNG;

int main(int argc, char **argv) {
    Network net;                    //on créait un objet Network( ccp à coder)
    Simulation sim(&net);           // on creait un objet Simulation qui prend un Network comme pointeur
    int errcode = 0;
    try {
        sim.initialize(argc, argv);
        sim.run();
    } catch(TCLAP::ArgException &e) {
        std::cerr << "Error: " + e.error() + " " + e.argId();
        errcode = 2;
    }
    return errcode;
}
