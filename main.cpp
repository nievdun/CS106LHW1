#include <iostream>
#include "SimpleGraph.h"
using namespace std;

void runGraphViz(){
    cout<<"Enter a word:";
    string word;
    getline(cin,word);
    cout<<word<<endl;
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
