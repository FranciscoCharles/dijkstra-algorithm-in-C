#ifndef _FILEREADER_H_
#define _FILEREADER_H_

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

#include "dijkstra.h"

bool load_vertexs(FILE *file, Graph graph, unsigned *n_vertex) {
    char label[80] = "";
    bool error = fscanf(file, "%u\n", n_vertex) < 1 || ferror(file);
    unsigned temp_n_vertex = *n_vertex;
    while(!error && (temp_n_vertex--) > 0) {
        error = fscanf(file, "%s\n",label) < 1 || ferror(file);
        if(!error) {
            graph_add_vertex(graph, label);
        }
    }
    return error;
}
bool load_edges(FILE *file, Graph graph, char* label, unsigned n_edges) {
    unsigned weight = 0;
    char destination[80] = "";
    bool error;
    do {
        error = fscanf(file, "%s %u\n", destination, &weight) < 2 || ferror(file);
        if(!error) {
            graph_add_edge_in_vertex(graph, label, destination, weight);
        }
    } while(!error && (--n_edges) > 0);
    return error;
}
Graph load_graph(char* filename) {
    FILE *file = fopen(filename,"r");
    bool error = false;
    unsigned n_vertexs, n_edges;
    char label[80] = "";
    Graph graph = create_graph();
    if(file != NULL) {
        error = load_vertexs(file, graph, &n_vertexs);
        while(!error && (n_vertexs--) > 0) {
            error = (fscanf(file, "%s %u\n", label, &n_edges) < 2 )
                    || ferror(file)
                    || load_edges(file,graph,label, n_edges);
        }
        if(error) {
            fprintf(stderr, "\nError: File cannot be read, check file syntax or read permissions.\n");
            graph = delete_graph(graph);
        }
        fclose(file);
        file = NULL;
    }
    return graph;
}
#endif
