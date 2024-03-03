//
// Created by 30694 on 2024/3/2.
//
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "ctype.h"
#include "limits.h"

#define MaxVertex 30

typedef char E;

// 普通节点
typedef struct Node {
    int nextVertex;
    struct Node *next;
} *Node;

// 头节点
struct HeadNode {
    E element;  // 存放的字符
    int time;   // 使用时间
    int input;    // 入度数量
    struct Node *next;
};

// 邻接表
typedef struct AdjacencyGraph {
    int vertexCount;    // 顶点数
    int edgeCount;  // 边数
    struct HeadNode vertex[MaxVertex];
} *Graph;

// 初始化
Graph create() {
    Graph graph = malloc(sizeof(struct AdjacencyGraph));
    graph->vertexCount = graph->edgeCount = 0;
    for (int i = 0; i < MaxVertex; ++i) {
        graph->vertex[i].input = 0;
        graph->vertex[i].time = INT_MAX;
    }
    return graph;
}

// 添加头节点
void addVertex(Graph graph, E element) {
    if (graph->vertexCount >= MaxVertex) return;
    graph->vertex[graph->vertexCount].element = element;
    graph->vertex[graph->vertexCount].next = NULL;
    graph->vertexCount++;
}

// 添加边
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

// 打印邻接表
void printGraph(Graph graph) {
    printf("邻接表为：\n");
    printf("序号\t入度数\t时间\t字符\n");
    for (int i = 0; i < graph->vertexCount; ++i) {
        printf("%d\t%d\t%d\t%c", i, graph->vertex[i].input, graph->vertex[i].time, graph->vertex[i].element);
        Node node = graph->vertex[i].next;
        while (node) {
            printf(" -> %d", node->nextVertex);
            node = node->next;
        }
        printf("^\n");
    }
}

// 读取数据
void ReadData(Graph graph, char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("打开文件失败");
        return;
    }
    char line[20];

    // 添加头节点
    while (fgets(line, sizeof(line), file)) {
        //添加头节点
        char *token = strtok(line, ",^\n");
        if (token == NULL) return;
        addVertex(graph, *token);
    }

    // 文件指针重置到开头
    rewind(file);

    // 添加普通节点
    while (fgets(line, sizeof(line), file)) {
        //跳过第一个头节点
        char *token = strtok(line, ",^\n");
        if (token == NULL) return;
        int b = (int) *token - 'A';

        //添加前置节点
        while (1) {
            token = strtok(NULL, ",^\n");
            if (token == NULL || *token == '^') break;
            if (isdigit(*token)) {
                graph->vertex[b].time = *token - '0';
            } else {
                int a = (int) *token - 'A';
                addEdge(graph, a, b);
            }
        }
    }
}

// 栈
typedef struct Stack {
    int *array;
    int capacity;
    int top;
} *ArrayStack;

// 初始化栈
bool initStack(ArrayStack stack, int capacity) {
    stack->array = (int *) malloc(sizeof(E) * capacity);
    if (stack->array == NULL) {
        printf("内存分配失败");
        return 0;
    }
    stack->capacity = capacity;
    stack->top = -1;
    return 1;
}

// 栈是否为空
bool isEmpty(ArrayStack stack) {
    return stack->top == -1;
}

// 入栈
bool push(ArrayStack stack, int element) {
    //如果栈已满，对栈进行扩容
    if (stack->top + 1 == stack->capacity) {
        int newCapacity = stack->capacity + (stack->capacity >> 1); //通过位操作，对栈扩容为原来的1.5倍
        int *newArray = realloc(stack->array, sizeof(E) * newCapacity);
        if (newArray == NULL) return 0;
        stack->array = newArray;
        stack->capacity = newCapacity;
    }
    stack->array[++stack->top] = element;
    return 1;
}

// 出栈
int pop(ArrayStack stack) {
    if (isEmpty(stack))return 0;
    return stack->array[stack->top--];
}

// 获取拓扑序列
char *sequence(Graph graph) {
    //创建栈并初始化
    struct Stack stack;
    initStack(&stack, 10);

    //拓扑序列指针
    char *result = (char *) malloc(sizeof(char) * (graph->vertexCount));
    int n = 0;

    //选出入度为0的顶点入栈
    for (int i = 0; i < graph->vertexCount; ++i) {
        if (graph->vertex[i].input == 0) push(&stack, i);
    }

    //拓扑排序
    while (!isEmpty(&stack)) {
        int index = pop(&stack);
        result[n++] = graph->vertex[index].element;

        Node node = graph->vertex[index].next;
        while (node) {
            graph->vertex[node->nextVertex].input--;
            if (graph->vertex[node->nextVertex].input == 0) push(&stack, node->nextVertex);
            node = node->next;
        }
    }

    //判断是否有环
    for (int i = 0; i < graph->vertexCount; ++i) {
        if (graph->vertex[i].input != 0) {
            printf("有环\n");
            printf("环所在位置为：%c <-> ", graph->vertex[i].element);
            Node node = graph->vertex[i].next;
            while (node) {
                struct HeadNode headNode = graph->vertex[node->nextVertex];
                Node node2 = headNode.next;
                while (node2) {
                    if (node2->nextVertex == i) {
                        printf("%c\n", headNode.element);
                        return NULL;
                    }
                    node2 = node2->next;
                }
                node = node->next;
            }
        }
    }

    //返回结果
    if (n != graph->vertexCount) return NULL;
    return result;
}

/**
 * 获取最短路径(迪杰斯特拉算法)
 * @param graph 邻接表
 * @param source 源点
 * @param dist 最短距离数组
 * @param pred 前驱节点数据
 */
void dijkstra(Graph graph, int source, int dist[], int pred[]) {
    int n = graph->vertexCount;
    bool visited[n]; //记录是否已访问

    // 初始化距离数组和visited
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX, visited[i] = false, pred[i] = -1;
    }

    // 源点到自身的距离是0
    dist[source] = 0;

    // 找到所有顶点的最短路径
    for (int count = 0; count < n - 1; count++) {
        // 选择最小距离顶点，从尚未处理的顶点集合
        int u = -1;
        int minDist = INT_MAX;
        for (int v = 0; v < n; v++) {
            if (!visited[v] && dist[v] <= minDist) {
                minDist = dist[v], u = v;
            }
        }

        // 标记选中顶点为已处理
        visited[u] = true;

        // 更新相邻顶点的距离值
        Node node = graph->vertex[u].next;
        while (node) {
            int v = node->nextVertex;
            if (!visited[v] && dist[u] != INT_MAX && dist[u] + graph->vertex[u].time < dist[v]) {
                dist[v] = dist[u] + graph->vertex[u].time;
                pred[v] = u;
            }
            node = node->next;
        }
    }
}

/**
 * 通过递归打印从源点到目标顶点的路径
 * @param pred 前驱节点数组
 * @param vertex 当前顶点的索引
 * @param graph 邻接表
 */
void printPath(int pred[], int vertex, Graph graph) {
    // 如果前驱节点的索引为-1，则到达源点
    if (pred[vertex] == -1) {
        printf("%c", graph->vertex[vertex].element);
        return;
    }
    printPath(pred, pred[vertex], graph); // 递归地打印前驱顶点的路径
    printf(" -> %c", graph->vertex[vertex].element); // 打印当前顶点
}

int main() {
    //创建邻接表
    Graph graph = create();

    //读取数据
    char *filename = malloc(sizeof(char) * 10);
    if (filename == NULL) {
        printf("内存分配失败\n");
        return 1;
    }
    printf("请输入文件名");
    scanf("%s", filename);
    ReadData(graph, filename);

    //打印邻接表
    printGraph(graph);

    //获取拓扑序列并判断是否有环
    char *result = sequence(graph);
    if (result == NULL) {
        printf("获取拓扑序列失败\n");
        return 1;
    } else {
        printf("拓扑序列为：");
        for (int i = 0; i < graph->vertexCount; ++i)
            printf("%c", result[i]);
        putchar('\n');
    }

    //获取最短路径
    int source = 0; // 假设从第一个顶点作为源点
    int dist[graph->vertexCount];   //存放最短距离大小
    int pred[graph->vertexCount];   //存放前驱节点的索引
    dijkstra(graph, source, dist, pred);

    printf("\n从顶点 %c 到其他顶点的最短路径:\n", graph->vertex[source].element);
    for (int i = 0; i < graph->vertexCount; ++i) {
        if (i != source) {
            printf("%c 到 %c 的最短路径长度: %d, 路径: ", graph->vertex[source].element, graph->vertex[i].element,
                   dist[i]);
            printPath(pred, i, graph); // 打印具体路径
            putchar('\n');
        }
    }
    return 0;
}