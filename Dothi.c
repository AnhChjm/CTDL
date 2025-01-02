#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node* adjLists[MAX];
    int visited[MAX];
} Graph;

// Tạo một đỉnh mới
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Tạo đồ thị
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Thêm cạnh vào đồ thị
void addEdge(Graph* graph, int src, int dest) {
    // Thêm đỉnh dest vào danh sách kề của src
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Thêm đỉnh src vào danh sách kề của dest 
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Duyệt DFS
void DFS(Graph* graph, int vertex) {
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    Node* temp = graph->adjLists[vertex];

    while (temp) {
        int adjVertex = temp->vertex;

        if (graph->visited[adjVertex] == 0) {
            DFS(graph, adjVertex);
        }

        temp = temp->next;
    }
}

// Duyệt BFS
void BFS(Graph* graph, int startVertex) {
    int queue[MAX], front = 0, rear = 0;

    graph->visited[startVertex] = 1;
    queue[rear++] = startVertex;

    while (front < rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        Node* temp = graph->adjLists[currentVertex];

        while (temp) {
            int adjVertex = temp->vertex;

            if (graph->visited[adjVertex] == 0) {
                graph->visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
            }

            temp = temp->next;
        }
    }
}

// Reset trạng thái 
void resetVisited(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0;
    }
}

int main() {
    int vertices, edges, src, dest;

    printf("Nhap so dinh: ");
    scanf("%d", &vertices);

    Graph* graph = createGraph(vertices);

    printf("Nhap so canh: ");
    scanf("%d", &edges);

    printf("Nhap cac canh (dinh1 dinh2):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    printf("\nDuyet DFS bat dau tu dinh 0: ");
    DFS(graph, 0);

    resetVisited(graph);

    printf("\nDuyet BFS bat dau tu dinh 0: ");
    BFS(graph, 0);

    return 0;
}
