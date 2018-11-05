#include "random.h"
#include "simulation.h"
#include "network.h"
#include <iostream>

Simulation::Simulation(Network *_net) : _network(_net), stepnum(10) {}

void Simulation::initialize(int argc, char **argv) {
    TCLAP::CmdLine cmd("Network simulation");
    TCLAP::ValueArg<int> argNode("n", "nodes", "Number of nodes", false, 0, "int");
    cmd.add(argNode);
    TCLAP::ValueArg<long> argSeed("S", "seed", "Random seed", false, 0, "long"); //?
    cmd.add(argSeed);
    TCLAP::ValueArg<double> argDegree("d", "degree", "Mean node degree", false, 4, "double");
    cmd.add(argDegree);
    TCLAP::ValueArg<int> argTime("t", "time", "Number of steps to simulate", false, 10, "int");
    cmd.add(argTime);

    cmd.parse(argc, argv);

    RNG.initialize(argSeed.getValue());
    int nodes(argNode.getValue());       //nombree de nodes
    if (nodes < 1) nodes = RNG.poisson(50);   // si nous avons pas de nodes on  lui donne un nombre aleatoire grace à l'utilisation la loi de poisson
    _network->resize(nodes);                 //Resizes the list of nodes
    double degree(argDegree.getValue());       // stock la valeur donné par le arg dans une nouvelle variable degree
    if (degree < 1) degree = RNG.uniform_double(1, std::sqrt(nodes));  // si nous avons rien dans cette valeur on lui donne une valleur aléatoire grace à la loi uniform
    size_t nlink = _network->random_connect(degree);   //on donne a la variable nlink (nombre de link total) --> degree: nombre de liens en moyenne par noodle  de la network
    std::cout << _network->size() << " nodes, " << nlink << " links\n";
    maxtime = argTime.getValue();
}


void Simulation::run() {
    for (int time=0; time<maxtime; time++) {
        if ((time % stepnum) == 0) print(time);
        step();
    }
    print(maxtime);
}

void Simulation::print(const int &time) const {
    std::cout << time << ": ";
    std::vector<double> vals = _network->sorted_values();
    for (auto I : vals) std::cout << I << " ";
    std::cout << std::endl;
}

void Simulation::step() const {
    std::vector<double> next_values(_network->size());  //meme taille que values
    std::vector<double> epsilon(_network->size());    //la valeur suivante doit differer d'epsilon
    RNG.uniform_double(epsilon);     //remplie le tableau avec des nombres aleatooires qui suivent la loi uniforme
    for (size_t node=0; node<next_values.size(); node++) {  //remplir le tableau de next value avec des valeurs qui suivent un calcul savant
        double cumul_neighbs = 0;   //cumulateur des valeurs de noodle courrante
        for (auto I : _network->neighbors(node)) cumul_neighbs += _network->value(I);
        double ddeg(_network->degree(node));
        next_values[node] = epsilon[node]*cumul_neighbs/ddeg+(1-epsilon[node])*_network->value(node);
    }
    _network->set_values(next_values);
}
