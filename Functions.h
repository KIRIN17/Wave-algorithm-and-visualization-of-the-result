#pragma once
#include "Graph.h"
#include "LinkedList.h"
#include <limits>
#include <queue>

DynamicArray<int> wave_algorithm(Graph& graph,int start,int finish){
    DynamicArray<int> dist(graph.vertices_count + 1);
    for (int i = 0; i < dist.GetSize(); ++i) {
        dist[i] = std::numeric_limits<int>::max();
    }

    DynamicArray<int> prev(graph.vertices_count + 1);
    for (int i = 0; i < prev.GetSize(); ++i) {
        prev[i] = -1;
    }

    dist[start] = 0;
    LinkedList<int> queue;
    queue.push(start);

    while (!queue.empty()){
        int u = queue.pop();
        for (int i = 0; i < graph.Get(u).GetSize(); ++i) {
            if(dist[graph.Get(u).Get(i)] == std::numeric_limits<int>::max()){
                dist[graph.Get(u).Get(i)] = dist[u] + 1;
                queue.push(graph.Get(u).Get(i));
                prev[graph.Get(u).Get(i)] = u;
            }
        }
    }


    DynamicArray<int> answer;
    int curr = finish;
    while (curr != -1){
        answer.Append(curr);
        curr = prev[curr];
    }

    for (int i = 0; i < answer.GetSize() / 2; ++i) {
        int tmp = answer[i];
        answer[i] = answer[answer.GetSize() - i - 1];
        answer[answer.GetSize() - i - 1] = tmp;
    }
    return answer;
}