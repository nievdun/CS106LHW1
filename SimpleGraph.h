#pragma once
 
/*************************************************************************
 * File: SimpleGraph.h
 *
 * A header file defining a set of functions which can be used to visualize a
 * simple graph.  The types declared here and the DrawGraph() function will
 * allow you to render a scaled version of a SimpleGraph you pass in.
 */

#include <vector>
#include <cstddef>

/**
 * Type: Node
 * -----------------------------------------------------------------------
 * A type representing a node in a graph.  Each node stores only the x and
 * y coordinates of where the node is in the plane; all other information
 * about the node is stored implicitly by its position in the SimpleGraph
 * list of nodes.
 */
struct Node {
  double x, y;
};

/**
 * Type: Edge
 * -----------------------------------------------------------------------
 * A type representing an edge in the graph.  It stores its endpoints by
 * the indices in which they occur in the SimpleGraph's list of Nodes.
 */
struct Edge {
  std::size_t start, end;
};

/**
 * Type: SimpleGraph
 * -----------------------------------------------------------------------
 * A type representing a simple graph of nodes and edges.
 */
struct SimpleGraph {
  std::vector<Node> nodes;
  std::vector<Edge> edges;
};



/**
 * Function: DrawGraph(SimpleGraph& graph)
 * -----------------------------------------------------------------------
 * Draws the specified graph.
 */

void DrawGraph(SimpleGraph& userGraph);


/** Redefinition: main
 * -----------------------------------------------------------------------
 * Due to a quirk in the way that the GLUT graphics toolkit works, main
 * actually must be in the graphics module itself.  This macro redefines
 * main to some other harmless term so that in your implementation, you
 * can define main but have it really invoked by the graphics driver.
 * This is a fairly unpleasant hack, but it's necessary to maintain
 * cross-platform compatibility.
 */
#define main _userMain
