#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <sstream>
#include "SimpleGraph.h"
using namespace std;

const double kPi = 3.14159265358979323;
const double k_repel = 0.001;

vector<Node> initializeNodes(int numNodes){
    vector<Node> nodes;
    for(int i=0;i<numNodes;i++){
        Node currNode;
        currNode.x=cos(2*kPi*i/((double)numNodes));
        currNode.y=sin(2*kPi*i/((double)numNodes));
        nodes.push_back(currNode);
    }
    return nodes;
}

vector<Edge> getEdges(ifstream & input){
    vector<Edge> edges;
    while(true){
        int start;
        int end;
        input>>start;
        input>>end;
        if(input.fail())
            break;
        Edge currEdge;
        currEdge.start=start;
        currEdge.end=end;
        edges.push_back(currEdge);
    }
    return edges;
}

SimpleGraph adjustByRepel(SimpleGraph & graph){
    for(size_t i=0; i<graph.nodes.size()-1;i++){
        Node *currNode = &(graph.nodes.at(i));
        for(size_t j=i+1; j<graph.nodes.size();j++){
            Node *otherNode = &(graph.nodes.at(j));
            double f_repel = k_repel/sqrt(pow((currNode->x-otherNode->x),2)+pow((currNode->y-otherNode->y),2));
            double theta = atan2(otherNode->y-currNode->y, otherNode->x-currNode->x);
            currNode->x = currNode->x - f_repel*cos(theta);
            currNode->y = currNode->y - f_repel*sin(theta);
            otherNode->x = otherNode->x + f_repel*cos(theta);
            otherNode->y = otherNode->y + f_repel*sin(theta);
        }
    }
    return graph;
}

SimpleGraph adjustByAttract(SimpleGraph & graph){
    for(size_t i=0; i<graph.edges.size();i++){
        int start = graph.edges.at(i).start;
        int end = graph.edges.at(i).end;
        Node *startNode = &(graph.nodes.at(start));
        Node *endNode = &(graph.nodes.at(end));
        double f_attract = k_repel*(pow((endNode->y-startNode->y),2)+pow((endNode->x-startNode->x),2));
        double theta = atan2(endNode->y-startNode->y, endNode->x-startNode->x);
        startNode->x = startNode->x + f_attract*cos(theta);
        startNode->y = startNode->y + f_attract*sin(theta);
        endNode->x = endNode->x - f_attract*cos(theta);
        endNode->y = endNode->y - f_attract*sin(theta);
    }
    return graph;
}

void iteratePositions(SimpleGraph & graph, double max_time){
    time_t startTime = time(NULL);
    while(difftime(time(NULL),startTime)<=max_time){
        adjustByRepel(graph);
        adjustByAttract(graph);
        DrawGraph(graph);
    }
}

string promptForFileName(){
    cout<<"Enter name of file:";
    string fileName;
    getline(cin, fileName);
    return fileName;
}

double promptForNumSecs(){
    double numSecs;
    while(true){
        cout<<"Enter number of seconds to run:";
        string line;
        getline(cin,line);
        stringstream converter;
        converter<<line;
        if(converter>>numSecs && numSecs>0){
            return numSecs;
        }
        else{
            cout<<"Invalid input for seconds. Must be a positive number."<<endl;
        }
    }
    return numSecs;
}

void runGraphViz(){
    string fileName = promptForFileName();
    double numSecs = promptForNumSecs();
    ifstream input;
    input.open(fileName);
    int numNodes;
    input>>numNodes;
    cout<<"Number of nodes are: "<<numNodes<<endl;
    vector<Node> nodes = initializeNodes(numNodes);
    vector<Edge> edges = getEdges(input);
    SimpleGraph graph;
    graph.nodes=nodes;
    graph.edges=edges;
    iteratePositions(graph, numSecs);
    input.close();
}

int main() {
    while(true){
        runGraphViz();
        string keepGoing;
        cout<<"Do you want to continue?(y for yes, no otherwise)";
        getline(cin,keepGoing);
        if(keepGoing!="y")
            break;
    }
    cout<<"Program Ended."<<endl;
    return 0;
}
