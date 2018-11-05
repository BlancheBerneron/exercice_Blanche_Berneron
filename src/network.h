#include <map>
#include <vector>
#include <iostream>
#include "random.h"
#include <exception>
#include <stdexcept>
/*!
  This is a network of nodes with bidirectional links: if <b>(a, b)</b> is a link then <b>(b, a)</b> is also a link.

  Each node supports a *double* value, and the list of nodes is in fact defined by the list of their values.
 */

class Network {

public:
    Network() {}

/*! Resizes the list of nodes (\ref values) */
    void resize(const size_t&);

/*! Adds a bidirectional link between two nodes
  @param[in] a,b the indexes if the two nodes 
  @param[out] success the link was succesfully inserted (true if both nodes exist and the link did not exist yet)
 */
    bool add_link(const size_t&, const size_t&);

/*! Creates random connections between nodes: each node *n* will be linked with *degree(n)* other nodes (randomly chosen) where *degree(n)* is Poisson-distributed.
  All previous links are cleared first.
  @param mean_deg the average of the Poisson distribution.
 */
    size_t random_connect(const double&);  // pas bien compris pourquoi pas void? on retourne quoi?

/*! Resets all node values.
  @param[in] vector of new node values
  @param[out] number of nodes succesfully reset
 */
    size_t set_values(const std::vector<double>&);

/*! Number of nodes */
    size_t size() const;

/*! Degree (number of links) of node no *n* */
    size_t degree(const size_t &_n) const;

/*! Value of node no *n* */
    double value(const size_t &_n) const;

/*! All node values in descending order */
    std::vector<double> sorted_values() const;

/*! All neighbors (linked) nodes of node no *n* */
    std::vector<size_t> neighbors(const size_t& n) const; //return un vecteur de nood qui sont liee à la noode n

private:
    std::vector<double> values;  //valeur des noueds la size respresente le network
    std::multimap<size_t, size_t> links;   //les liens sont caracterises par les positions des deux nodes dans le tableau value

};

