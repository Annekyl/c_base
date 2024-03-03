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

// ��ͨ�ڵ�
typedef struct Node {
    int nextVertex;
    struct Node *next;
} *Node;

// ͷ�ڵ�
struct HeadNode {
    E element;  // ��ŵ��ַ�
    int time;   // ʹ��ʱ��
    int input;    // �������
    struct Node *next;
};

// �ڽӱ�
typedef struct AdjacencyGraph {
    int vertexCount;    // ������
    int edgeCount;  // ����
    struct HeadNode vertex[MaxVertex];
} *Graph;

// ��ʼ��
Graph create() {
    Graph graph = malloc(sizeof(struct AdjacencyGraph));
    graph->vertexCount = graph->edgeCount = 0;
    for (int i = 0; i < MaxVertex; ++i) {
        graph->vertex[i].input = 0;
        graph->vertex[i].time = INT_MAX;
    }
    return graph;
}

// ���ͷ�ڵ�
void addVertex(Graph graph, E element) {
    if (graph->vertexCount >= MaxVertex) return;
    graph->vertex[graph->vertexCount].element = element;
    graph->vertex[graph->vertexCount].next = NULL;
    graph->vertexCount++;
}

// ��ӱ�
void addEdge(Graph graph, int a, int b) {
    Node node = graph->vertex[a].next;

    // �����½ڵ�
    Node newNode = (Node) malloc(sizeof(struct Node));
    newNode->nextVertex = b;
    newNode->next = NULL;

    // ���ͷ�ڵ���һ���ǿ�ָ�룬��ôֱ������ȥ
    if (!node) {
        graph->vertex[a].next = newNode;
    } else {     // ����˵����ǰ�����Ѿ�����������һ����������
        while (node->next) {
            // ����Ѿ����ӹ���Ӧ�Ķ��㣬ֱ�ӷ���
            if (node->nextVertex == b) {
                free(newNode);
                return;
            }
            node = node->next;
        }
        // ��������β����δ�ҵ��ظ��ߣ�����½ڵ�
        node->next = newNode;
    }

    // �ɹ���ӱߺ�����Ŀ�궥������
    graph->vertex[b].input += 1;
    graph->edgeCount++;
}

// ��ӡ�ڽӱ�
void printGraph(Graph graph) {
    printf("�ڽӱ�Ϊ��\n");
    printf("���\t�����\tʱ��\t�ַ�\n");
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

// ��ȡ����
void ReadData(Graph graph, char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("���ļ�ʧ��");
        return;
    }
    char line[20];

    // ���ͷ�ڵ�
    while (fgets(line, sizeof(line), file)) {
        //���ͷ�ڵ�
        char *token = strtok(line, ",^\n");
        if (token == NULL) return;
        addVertex(graph, *token);
    }

    // �ļ�ָ�����õ���ͷ
    rewind(file);

    // �����ͨ�ڵ�
    while (fgets(line, sizeof(line), file)) {
        //������һ��ͷ�ڵ�
        char *token = strtok(line, ",^\n");
        if (token == NULL) return;
        int b = (int) *token - 'A';

        //���ǰ�ýڵ�
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

// ջ
typedef struct Stack {
    int *array;
    int capacity;
    int top;
} *ArrayStack;

// ��ʼ��ջ
bool initStack(ArrayStack stack, int capacity) {
    stack->array = (int *) malloc(sizeof(E) * capacity);
    if (stack->array == NULL) {
        printf("�ڴ����ʧ��");
        return 0;
    }
    stack->capacity = capacity;
    stack->top = -1;
    return 1;
}

// ջ�Ƿ�Ϊ��
bool isEmpty(ArrayStack stack) {
    return stack->top == -1;
}

// ��ջ
bool push(ArrayStack stack, int element) {
    //���ջ��������ջ��������
    if (stack->top + 1 == stack->capacity) {
        int newCapacity = stack->capacity + (stack->capacity >> 1); //ͨ��λ��������ջ����Ϊԭ����1.5��
        int *newArray = realloc(stack->array, sizeof(E) * newCapacity);
        if (newArray == NULL) return 0;
        stack->array = newArray;
        stack->capacity = newCapacity;
    }
    stack->array[++stack->top] = element;
    return 1;
}

// ��ջ
int pop(ArrayStack stack) {
    if (isEmpty(stack))return 0;
    return stack->array[stack->top--];
}

// ��ȡ��������
char *sequence(Graph graph) {
    //����ջ����ʼ��
    struct Stack stack;
    initStack(&stack, 10);

    //��������ָ��
    char *result = (char *) malloc(sizeof(char) * (graph->vertexCount));
    int n = 0;

    //ѡ�����Ϊ0�Ķ�����ջ
    for (int i = 0; i < graph->vertexCount; ++i) {
        if (graph->vertex[i].input == 0) push(&stack, i);
    }

    //��������
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

    //�ж��Ƿ��л�
    for (int i = 0; i < graph->vertexCount; ++i) {
        if (graph->vertex[i].input != 0) {
            printf("�л�\n");
            printf("������λ��Ϊ��%c <-> ", graph->vertex[i].element);
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

    //���ؽ��
    if (n != graph->vertexCount) return NULL;
    return result;
}

/**
 * ��ȡ���·��(�Ͻ�˹�����㷨)
 * @param graph �ڽӱ�
 * @param source Դ��
 * @param dist ��̾�������
 * @param pred ǰ���ڵ�����
 */
void dijkstra(Graph graph, int source, int dist[], int pred[]) {
    int n = graph->vertexCount;
    bool visited[n]; //��¼�Ƿ��ѷ���

    // ��ʼ�����������visited
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX, visited[i] = false, pred[i] = -1;
    }

    // Դ�㵽����ľ�����0
    dist[source] = 0;

    // �ҵ����ж�������·��
    for (int count = 0; count < n - 1; count++) {
        // ѡ����С���붥�㣬����δ����Ķ��㼯��
        int u = -1;
        int minDist = INT_MAX;
        for (int v = 0; v < n; v++) {
            if (!visited[v] && dist[v] <= minDist) {
                minDist = dist[v], u = v;
            }
        }

        // ���ѡ�ж���Ϊ�Ѵ���
        visited[u] = true;

        // �������ڶ���ľ���ֵ
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
 * ͨ���ݹ��ӡ��Դ�㵽Ŀ�궥���·��
 * @param pred ǰ���ڵ�����
 * @param vertex ��ǰ���������
 * @param graph �ڽӱ�
 */
void printPath(int pred[], int vertex, Graph graph) {
    // ���ǰ���ڵ������Ϊ-1���򵽴�Դ��
    if (pred[vertex] == -1) {
        printf("%c", graph->vertex[vertex].element);
        return;
    }
    printPath(pred, pred[vertex], graph); // �ݹ�ش�ӡǰ�������·��
    printf(" -> %c", graph->vertex[vertex].element); // ��ӡ��ǰ����
}

int main() {
    //�����ڽӱ�
    Graph graph = create();

    //��ȡ����
    char *filename = malloc(sizeof(char) * 10);
    if (filename == NULL) {
        printf("�ڴ����ʧ��\n");
        return 1;
    }
    printf("�������ļ���");
    scanf("%s", filename);
    ReadData(graph, filename);

    //��ӡ�ڽӱ�
    printGraph(graph);

    //��ȡ�������в��ж��Ƿ��л�
    char *result = sequence(graph);
    if (result == NULL) {
        printf("��ȡ��������ʧ��\n");
        return 1;
    } else {
        printf("��������Ϊ��");
        for (int i = 0; i < graph->vertexCount; ++i)
            printf("%c", result[i]);
        putchar('\n');
    }

    //��ȡ���·��
    int source = 0; // ����ӵ�һ��������ΪԴ��
    int dist[graph->vertexCount];   //�����̾����С
    int pred[graph->vertexCount];   //���ǰ���ڵ������
    dijkstra(graph, source, dist, pred);

    printf("\n�Ӷ��� %c ��������������·��:\n", graph->vertex[source].element);
    for (int i = 0; i < graph->vertexCount; ++i) {
        if (i != source) {
            printf("%c �� %c �����·������: %d, ·��: ", graph->vertex[source].element, graph->vertex[i].element,
                   dist[i]);
            printPath(pred, i, graph); // ��ӡ����·��
            putchar('\n');
        }
    }
    return 0;
}