//
// Created by Blanche Berneron on 22/10/2018.
//

#include "network.h"


void Network::resize(const size_t & n) {
    values.resize(n);   //creer un tableau d une taille n
    RNG.normal(values); //rempli le tableau ou change les valeurs du tableau distribution normal 
}


bool Network::add_link(const size_t & a , const size_t & b ) {

    //inserer un element dans une multimap -> mymap.insert(size_t, size_t)
    if (a < size() and b < size() and a != b){  //nodes exist

        for( auto I: neighbors(a)) {

            if (I == b) {       //link does exist
                return false;
            }                       // a ne peut pas etre voisin de b si a n'est pas voisin de b (bi dirrectionnel)
        }
        links.insert(std::pair<size_t,size_t>(a,b));   //mais bi directionnels donc creer le lien inverse
        links.insert(std::pair<size_t,size_t>(b,a));
        return true;

    } else {
        return false;
        }

}

size_t Network::random_connect(const double & n) {
    links.clear(); //On clear all links --> on elimine dans la map en entier
    size_t count(0);

    std::vector <int> test (size()); //remplir avec les liens que tu veux creer
    std::vector<size_t> indices;

    for (size_t i (0); i < size() ; ++i){
        indices.push_back(i);
    }

    RNG.poisson(test,n);

    for(size_t node(0); node < size(); ++node){

        RNG.shuffle(indices);

        for (int j(0); j < test[node]; ++j){
            if (add_link (node, indices[j])){
             ++count;
            } else {
                RNG.shuffle(indices);
                --j;
            }

        }

    }


    return count;
}

size_t Network::set_values(const std::vector<double> & next_values) {
    //succesfully reset? considerons le cas que next_value ne soit pas de la même taille --> retournera la taille de values courante

      if ( values.size() < next_values. size()) {
        for (int i(0); i < values.size(); ++i)  { values[i] = next_values[i]; }
      return values.size();
      } else {
          for (int i(0); i < next_values.size(); ++i)  { values[i] = next_values[i]; }
       return next_values.size();
      }
}

size_t Network::size() const {
    return values.size(); //nombres of nodes
}

size_t Network::degree(const size_t &_n) const {
    unsigned long error (0);
    try {
        return links.count(_n);
    } catch (const std::out_of_range& oor){
        std::cerr<< "Out of range: " << oor.what() << '\n';
    } return error;
}


double Network::value(const size_t &_n) const {
    double error (0.0);
    try {
        return values[_n];
    }
    catch (const std::out_of_range& oor){
        std::cerr<< "Out of range: " << oor.what() << '\n';
    }
    return error;

}

std::vector<double> Network::sorted_values() const {
    std::vector<double> descending_values = values;
    sort(descending_values.begin() , descending_values.end() , std::greater<double>());

    return descending_values;
}

std::vector<size_t> Network::neighbors(const size_t & n) const {
    std::vector<size_t> neighbors;

    for(auto it = links.begin() ; it != links.end(); ++it){
        if (it -> first  == n){
            neighbors.push_back(it -> second);
        }
    }

    return neighbors;
}
