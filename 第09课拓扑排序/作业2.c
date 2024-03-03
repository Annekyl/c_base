//
// Created by 30694 on 2024/3/2.
//
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

#define MaxVertex 10

typedef char E;

//��ͨ�ڵ�
typedef struct Node {
    int nextVertex;
    struct Node *next;
} *Node;

//ͷ�ڵ�
struct HeadNode {
    E element;  //��ŵ��ַ�
    int input;    //�������
    struct Node *next;
};

//�ڽӱ�
typedef struct AdjacencyGraph {
    int vertexCount;    //������
    int edgeCount;  //����
    struct HeadNode vertex[MaxVertex];
} *Graph;

//��ʼ��
Graph create() {
    Graph graph = malloc(sizeof(struct AdjacencyGraph));
    graph->vertexCount = graph->edgeCount = 0;
    for (int i = 0; i < MaxVertex; ++i) {
        graph->vertex[i].input = 0;
    }
    return graph;
}

//���ͷ�ڵ�
void addVertex(Graph graph, E element) {
    if (graph->vertexCount >= MaxVertex) return;
    graph->vertex[graph->vertexCount].element = element;
    graph->vertex[graph->vertexCount].next = NULL;
    graph->vertexCount++;
}

//��ӱ�
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

//��ӡ�ڽӱ�
void printGraph(Graph graph) {
    printf("���\t�����\t�ַ�\n");
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

//��ȡ����
void ReadData(Graph graph) {
    FILE *file = fopen("p01.txt", "r");
    char line[20];

    //���ͷ�ڵ�
    while (fgets(line, sizeof(line), file)) {
        //���ͷ�ڵ�
        char *token = strtok(line, ",\n");
        if (token == NULL) return;
        addVertex(graph, *token);
    }

    //�ļ�ָ�����õ���ͷ
    rewind(file);

    //�����ͨ�ڵ�
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

//ջ
typedef struct Stack {
    int *array;
    int capacity;
    int top;
} *ArrayStack;

//��ʼ��ջ
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

//ջ�Ƿ�Ϊ��
bool isEmpty(ArrayStack stack) {
    return stack->top == -1;
}

//��ջ
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

//��ջ
int pop(ArrayStack stack) {
    if (isEmpty(stack))return 0;
    return stack->array[stack->top--];
}

//��ȡ��������
char *sequence(Graph graph) {
    //����ջ����ʼ��
    struct Stack stack;
    initStack(&stack, 10);

    //��������ָ��
    char *result = (char *) malloc(sizeof(char) * graph->vertexCount);
    int n = 0;

    //ѡ�����Ϊ0�Ķ�����ջ
    for (int i = 0; i < graph->vertexCount; ++i) {
        if (graph->vertex[i].input == 0) push(&stack, i);
    }

    //������������
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
    //������������
    if (n != graph->vertexCount) return NULL;
    return result;
}

int main() {
    //�����ڽӱ�
    Graph graph = create();

    //��ȡ����
    ReadData(graph);

    //��ӡ�ڽӱ�
    printGraph(graph);

    //��ȡ��������
    char *result = sequence(graph);
    if (result == NULL) printf("��ȡ��������ʧ��");
    else printf("��������Ϊ��%s\n", result);

    return 0;
}