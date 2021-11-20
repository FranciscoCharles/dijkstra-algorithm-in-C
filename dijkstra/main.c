#include "filereader.h"

int main(int argc, char** argv) {
    if(argc > 2) {
        char *filename = argv[1];
        char *start_vertex = argv[2];
        Graph graph = load_graph(filename);
        if(graph) {
            printf("Show graph\n\n");
            print_graph(graph);
            if(graph_find_vertex_by_label(graph, start_vertex)) {
                printf("Dijkstra solution\n\n");
                dijkstra(graph, start_vertex);
            } else {
                fprintf(stderr, "\nError: The selected vertex \"%s\" does not exist in the graph.\n", start_vertex);
            }
            graph = delete_graph(graph);
        }
    } else {
        fprintf(stderr, "\nError: insufficient number of parameters.\n");
    }
    return 0;
}
