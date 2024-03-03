//
// Created by 30694 on 2024/3/2.
//
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MaxVertex 10

typedef char E;

//普通节点
typedef struct Node {
    int nextVertex;
    struct Node *next;
} *Node;

//头节点
struct HeadNode {
    E element;  //存放的字符
    int input;    //入度数量
    struct Node *next;
};

//邻接表
typedef struct AdjacencyGraph {
    int vertexCount;    //顶点数
    int edgeCount;  //边数
    struct HeadNode vertex[MaxVertex];
} *Graph;

//初始化
Graph create() {
    Graph graph = malloc(sizeof(struct AdjacencyGraph));
    graph->vertexCount = graph->edgeCount = 0;
    for (int i = 0; i < MaxVertex; ++i) {
        graph->vertex[i].input = 0;
    }
    return graph;
}

//添加头节点
void addVertex(Graph graph, E element) {
    if (graph->vertexCount >= MaxVertex) return;
    graph->vertex[graph->vertexCount].element = element;
    graph->vertex[graph->vertexCount].next = NULL;
    graph->vertexCount++;
}

//添加边
void addEdge(Graph graph, int a, int b) {
    Node node = graph->vertex[a].next;

    // 申请新节点
    Node newNode = (Node) malloc(sizeof(struct Node));
    newNode->nextVertex = b;
    newNode->next = NULL;

    // 如果头节点下一个是空指针，那么直接连上去
    if (!node) {
        graph->vertex[a].next = newNode;
    } else {     // 否则说明当前顶点已经连接了至少一个其他顶点
        while (node->next) {
            // 如果已经连接过对应的顶点，直接返回
            if (node->nextVertex == b) {
                free(newNode);
                return;
            }
            node = node->next;
        }
        // 到达链表尾部，未找到重复边，添加新节点
        node->next = newNode;
    }

    // 成功添加边后，增加目标顶点的入度
    graph->vertex[b].input += 1;
    graph->edgeCount++;
}

//打印邻接表
void printGraph(Graph graph) {
    printf("序号\t入度数\t字符\n");
    for (int i = 0; i < graph->vertexCount; ++i) {
        printf("%d\t%d\t%c", i, graph->vertex[i].input, graph->vertex[i].element);
        Node node = graph->vertex[i].next;
        while (node) {
            printf(" -> %d", node->nextVertex);
            node = node->next;
        }
        printf("^\n");
    }
}

//读取数据
void ReadData(Graph graph) {
    FILE *file = fopen("p01.txt", "r");
    char line[20];

    //添加头节点
    while (fgets(line, sizeof(line), file)) {
        //添加头节点
        char *token = strtok(line, ",\n");
        if (token == NULL) return;
        addVertex(graph, *token);
    }

    //文件指针重置到开头
    rewind(file);

    //添加普通节点
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",\n");
        if (token == NULL) return;
        int b = (int) *token - 'A';
        while (1) {
            token = strtok(NULL, ",\n");
            if (token == NULL || *token == '^') break;
            int a = (int) *token - 'A';
            addEdge(graph, a, b);
        }
    }
}

int main() {
    //创建邻接表
    Graph graph = create();

    //读取数据
    ReadData(graph);

    //打印邻接表
    printGraph(graph);
    return 0;
}