#include "Graph.h"
#include "Functions.h"

void Tests(){

    {
        std::ifstream input1("Graph1.txt");
        Graph graph1(input1);
        DynamicArray<int> res = wave_algorithm(graph1,0,4);
        if(res[0] != 0 || res[1] != 4){
            std::cerr << "ERROR CASE 1 !\n";
            std::exit(0);
        }

    }

    {
        std::ifstream input1("Graph2.txt");
        Graph graph1(input1);
        DynamicArray<int> res = wave_algorithm(graph1,0,1);
        if(res[0] != 0 || res[1] != 1){
            std::cerr << "ERROR CASE 2 !\n";
            std::exit(0);
        }
    }

    {
        std::ifstream input1("Graph3.txt");
        Graph graph1(input1);
        DynamicArray<int> res = wave_algorithm(graph1,0,1);
        if(res[0] != 1){
            std::cerr << "ERROR CASE 3 !\n";
            std::exit(0);
        }
    }

    std::cerr << "ALL TESTS ARE DONE !\n";
}