#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

/*
MIT License

Copyright (c) 2021 FranciscoCharles

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "graph.h"

Vertex get_min_vertex(Vertex* vertex, unsigned size) {
    unsigned i;
    Vertex min_vertex = NULL;
    for(i = 0; i < size; i++) {
        if(vertex[i]->open
                && ( min_vertex==NULL || ( min_vertex->distance > vertex[i]->distance))) {
            min_vertex = vertex[i];
        }
    }
    return min_vertex;
}
Vertex* remove_vertex(Vertex* array, Vertex vertex, unsigned n_vertex) {
    unsigned i = 0;
    for(i = 0; i < n_vertex; i++) {
        if(array[i]->id == vertex->id) {
            for(; i < (n_vertex - 1); i++) {
                array[i] = array[i+1];
            }
            break;
        }
    }
    return array;
}
void dijkstra(Graph graph, char *label_start_vertex) {
    unsigned n_vertex = graph->size;
    unsigned index_solution = 0;
    Vertex* array_vertex = calloc(n_vertex, sizeof(Vertex));
    Vertex* solution = calloc(n_vertex, sizeof( Vertex));
    unsigned i = 0;
    Vertex iterator = graph->vertexs;

    graph_resete_dijkstra(graph);

    while(iterator!=NULL) {
        array_vertex[i] = iterator;
        solution[i] = NULL;
        iterator = iterator->next;
        i++;
    }

    Vertex min_vertex = graph_find_vertex_by_label(graph, label_start_vertex);
    min_vertex->distance = 0;
    Edge iterator_edge = NULL;
    Vertex neighbor = NULL;
    unsigned distance = 0;

    while(n_vertex > 0) {
        min_vertex = get_min_vertex(array_vertex, n_vertex);

        min_vertex->open = false;
        solution[index_solution++] = min_vertex;
        iterator_edge = min_vertex->edges;
        while(iterator_edge!=NULL) {
            neighbor = graph_find_vertex_by_id(graph, iterator_edge->id_vertex);
            distance = min_vertex->distance + iterator_edge->Weight;
            if(distance < neighbor->distance) {
                neighbor->distance = distance;
                neighbor->predecessor = min_vertex;
            }
            iterator_edge = iterator_edge->next;
        }
        array_vertex = remove_vertex(array_vertex, min_vertex, n_vertex);
        n_vertex--;
    }

    n_vertex = graph->size;
    for(i = 0; i < n_vertex; i++) {
        if(solution[i]->predecessor) {
            printf("%s : { predecessor %s, distance %3u}\n", solution[i]->label, solution[i]->predecessor->label,solution[i]->distance);
        } else {
            printf("%s : { predecessor NULL, distance %3u}\n", solution[i]->label,solution[i]->distance);
        }
    }
    free(solution);
    free(array_vertex);

}
#endif
