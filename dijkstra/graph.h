#ifndef _GRAPH_H_
#define _GRAPH_H_

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

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define INFINITY (INT_MAX)

typedef struct Vertex* Vertex;
typedef struct Graph* Graph;
typedef struct Edge* Edge;

unsigned global_id_count = 0;

struct Edge {
    unsigned weigth;
    unsigned id_vertex;
    Edge next;
};

struct Vertex {
    /*Data for Dijkstra algorithm*/
    bool open;
    unsigned distance;
    Vertex predecessor;

    unsigned id;
    char label[80];
    Edge edges;
    Vertex next;
};

struct Graph {
    unsigned size;
    Vertex vertexs;
};

Graph create_graph(void) {
    Graph graph = malloc(sizeof(struct Graph));
    graph->vertexs = NULL;
    graph->size = 0;
    return graph;
}

Vertex create_vertex(char* label) {
    if(global_id_count + 1 == INT_MAX) {
        exit(EXIT_FAILURE);
    }
    Vertex vertex = malloc(sizeof(struct Vertex));
    vertex->edges = NULL;
    vertex->open = true;
    vertex->id = global_id_count++;
    strcpy(vertex->label, label);
    vertex->next = NULL;
    vertex->predecessor = NULL;
    return vertex;
}
void graph_add_vertex(Graph graph, char *label) {
    Vertex iterator = graph->vertexs;
    char* new_label = calloc(1, strlen(label)+1);
    strcpy(new_label, label);
    Vertex new_vertex = create_vertex(label);

    if(iterator == NULL) {
        graph->vertexs = new_vertex;
    } else {
        while(iterator->next != NULL) {
            iterator = iterator->next;
        }
        iterator->next = new_vertex;
    }
    graph->size++;
}
void vertex_add_edge(Vertex vertex,unsigned weight, unsigned id_vertex_dest) {
    Edge iterator = vertex->edges;
    Edge new_edge = malloc(sizeof(struct Edge));
    new_edge->weigth = weight;
    new_edge->id_vertex = id_vertex_dest;
    new_edge->next = NULL;
    if(iterator == NULL) {
        vertex->edges = new_edge;
    } else {
        while(iterator->next != NULL) {
            iterator = iterator->next;
        }
        iterator->next = new_edge;
    }
}
Vertex graph_find_vertex_by_id(Graph graph, unsigned id) {
    Vertex iterator = graph->vertexs;
    while(iterator!=NULL && iterator->id!=id) {
        iterator = iterator->next;
    }
    return iterator;
}
Vertex graph_find_vertex_by_label(Graph graph, char *label) {
    Vertex iterator = graph->vertexs;
    while(iterator!=NULL && strcmp(iterator->label, label)!=0) {
        iterator = iterator->next;
    }
    return iterator;
}
Edge delete_all_edges(Edge edges) {
    Edge iterator = edges;
    Edge temp = NULL;

    while(iterator!=NULL) {

        temp = iterator->next;
        free(iterator);
        iterator = temp;
    }
    return iterator;
}
Vertex delete_all_vertex(Vertex vertexs) {
    Vertex iterator = vertexs;
    Vertex temp = NULL;

    while(iterator!=NULL) {

        temp = iterator->next;
        iterator->edges = delete_all_edges(iterator->edges);
        free(iterator);
        iterator = temp;
    }
    return iterator;
}
void graph_resete_dijkstra(Graph graph) {
    Vertex iterator = graph->vertexs;

    while(iterator!=NULL) {

        iterator->open = true;
        iterator->distance = INFINITY;
        iterator->predecessor = NULL;
        iterator = iterator->next;
    }
}
Graph delete_graph(Graph graph) {
    graph->vertexs = delete_all_vertex(graph->vertexs);
    free(graph);
    graph = NULL;
    return graph;
}
void graph_add_edge_in_vertex(Graph graph, char *label_src, char *label_dst, unsigned weight_edge) {
    Vertex vertex_src = graph_find_vertex_by_label(graph, label_src);
    Vertex vertex_dst = graph_find_vertex_by_label(graph, label_dst);
    if(vertex_src && vertex_dst) {
        vertex_add_edge(vertex_src, weight_edge, vertex_dst->id);
    }
}
void print_edges(Edge edges) {
    Edge iterator = edges;
    unsigned index = 0;
    while(iterator!=NULL) {
        printf("\tedge %d : { weight : %3u, destination : %3u}\n", index, iterator->weigth, iterator->id_vertex);
        iterator = iterator->next;
        index++;
    }
}
void print_vertex(Vertex vertexs) {
    Vertex iterator = vertexs;
    unsigned index = 0;
    while(iterator!=NULL) {
        printf("vertex %d :\n\t{ id : %3u, label : %s}\n", index, iterator->id, iterator->label);
        print_edges(iterator->edges);
        iterator = iterator->next;
        index++;
    }
}
void print_graph(Graph graph) {
    Vertex iterator = graph->vertexs;
    print_vertex(iterator);
    printf("\n");
}
#endif
