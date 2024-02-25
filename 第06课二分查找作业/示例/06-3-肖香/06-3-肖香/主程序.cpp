#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>//����� 

#define MAX_LEVEL 100 // �����������

//˼·���������������ֱ����ı��ļ���id�����֣�ƽ���������һ�δ���ÿ�������С�
//���е��߼�����ʽ����ṹ����̬�������� 
// ����������Ԫ���ڵײ㣬Ȼ��ͨ���������ȡ��ÿ���ڵ�Ĳ�����Ȼ��Ƚ�������߲���Ǹ����Ƚ�
//����Ǹ����ȱȽϵ�������ô�ͻ�������ڵ����һ�㣬Ȼ�����αȽϣ�ֱ���鵽��ͬ����Ϊֹ�� 
//id�����ֺ�ƽ�������в���Ͳ����Լ������������ƣ�ƽ����Ҫ�ҵ�������ͬ�������� 

// ѧ����Ϣ�ṹ
typedef struct {
    int id;
    char name[50];
    char gender[10];
    char classes[50];
    double score_1;
    double score_2;
    double score_3;
    double average_score;
} Student;

// ����ڵ�ṹ
typedef struct Node {
    int key;
    Student *student;
    struct Node *forward[1]; // ����ʹ����������
    //�������飺�������ڶ���ṹ��ʱʹ��һ����СΪ 0 �����顣��������Ĵ�С��������ʱ��̬����ģ��������ڱ���ʱȷ���� 
} Node;

// ����ṹ
typedef struct {
    int level;//���� 
    Node *header;//ͷָ�� 
    int type;
} SkipList;

//������Ծ�� 
typedef struct {
    SkipList *idSorted;//id���� 
    SkipList *nameSorted;//�������� 
    SkipList *averageScoreSorted;//ƽ�������� 
} CombinedSkipList;

// �����µ�����ڵ�
Node *createNode(int key, Student *student, int level) {
    Node *node = (Node *)malloc(sizeof(Node) + level * sizeof(Node *));
    node->key = key;
    node->student = student;
    return node;
}

// ����type����ָ�����͵�����
SkipList* createSkipList(int type) {
    SkipList* skipList = (SkipList*)malloc(sizeof(SkipList));
    skipList->level = 1;
    Student* dummyStudent = (Student*)malloc(sizeof(Student)); // ����һ���ڱ��ڵ㣨ͷ�ڵ㣩 
    dummyStudent->id = -1;
    strcpy(dummyStudent->name, "Dummy");
    skipList->header = createNode(-1, dummyStudent, MAX_LEVEL); // �ڱ��ڵ��key����Ϊ-1
    for (int i = 0; i < MAX_LEVEL; i++) {
        skipList->header->forward[i] = NULL;
    }
    return skipList;
}

// �������в���ڵ�(��ID)
void insertElementbyID(SkipList *list, int key, Student *student) {
    Node *update[MAX_LEVEL];
    Node *current = list->header;

    for (int i = list->level - 1; i >= 0; i--) {//�������� 
        while (current->forward[i] != NULL && current->forward[i]->key < key) {//�Ƚϱ����������һ���� 
            current = current->forward[i];
        }
        update[i] = current;
    }
    current = current->forward[0];

    if (current == NULL || current->key != key) {
	//�ڲ����½ڵ�֮ǰȷ���½ڵ�Ĳ�����������Ҫʱ���������������������ָ�� 
        int newLevel = 1;
        while (rand() < RAND_MAX / 2 && newLevel < MAX_LEVEL) {
            newLevel++;
        }

        if (newLevel > list->level) {
            for (int i = list->level; i < newLevel; i++) {
                update[i] = list->header;
            }
            list->level = newLevel;
        }

        Node *newNode = createNode(key, student, newLevel);
        //ȷ���Ĳ������½ڵ���뵽�����еĸ����㼶������ 
        for (int i = 0; i < newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
}

// �������в���ڵ�(������)
void insertElementbyname(SkipList *list, Student *student) {
    Node *update[MAX_LEVEL];
    Node *current = list->header;

    for (int i = list->level - 1; i >= 0; i--) {
        while (current->forward[i] != NULL && strcmp(current->forward[i]->student->name, student->name) < 0) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    current = current->forward[0];

    // ��ԭ�нڵ�Ϊ�ջ�ѧ�����������ڵ�ǰ����ѧ������ʱִ�в������
    if (current == NULL || strcmp(current->student->name, student->name) != 0) {
        int newLevel = 1;
        while (rand() < RAND_MAX / 2 && newLevel < MAX_LEVEL) {
            newLevel++;
        }

        if (newLevel > list->level) {
            for (int i = list->level; i < newLevel; i++) {
                update[i] = list->header;
            }
            list->level = newLevel;
        }

        Node *newNode = createNode(student->id, student, newLevel);
        for (int i = 0; i < newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
}

// �������в���ڵ�(�ɷ���)
void insertElementbyscore(SkipList *list, Student *student) {
    Node *update[MAX_LEVEL];
    Node *current = list->header;

    for (int i = list->level - 1; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->student->average_score < student->average_score) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    current = current->forward[0];

    // ��ԭ�нڵ�Ϊ�ջ�ѧ����ƽ�����������ڵ�ǰ����ѧ����ƽ������ʱִ�в������
    if (current == NULL || current->student->average_score >= student->average_score) {
        int newLevel = 1;
        while (rand() < RAND_MAX / 2 && newLevel < MAX_LEVEL) {
            newLevel++;
        }

        if (newLevel > list->level) {
            for (int i = list->level; i < newLevel; i++) {
                update[i] = list->header;
            }
            list->level = newLevel;
        }

        Node *newNode = createNode(student->id, student, newLevel);
        for (int i = 0; i < newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
}

// ��ȡ�ı��ļ��е�ѧ����Ϣ�����뵽������(id
void readStudentDataid(const char *fileName, SkipList *skipList) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("�޷����ļ� %s\n", fileName);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Student *student = (Student *)malloc(sizeof(Student));
        if (sscanf(line, "%d,%49[^,],%9[^,],%49[^,],%lf,%lf,%lf,%lf",
                   &student->id, student->name, student->gender, student->classes,
                   &student->score_1, &student->score_2, &student->score_3, &student->average_score) == 8) {
            insertElementbyID(skipList, student->id, student); // ��ѧ�����ݲ��뵽������
        }
    }
    fclose(file);
}

// ��ȡ�ı��ļ��е�ѧ����Ϣ�����뵽������(name
void readStudentDataname(const char *fileName, SkipList *skipList) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("�޷����ļ� %s\n", fileName);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Student *student = (Student *)malloc(sizeof(Student));
        if (sscanf(line, "%d,%49[^,],%9[^,],%49[^,],%lf,%lf,%lf,%lf",
                   &student->id, student->name, student->gender, student->classes,
                   &student->score_1, &student->score_2, &student->score_3, &student->average_score) == 8) {
            insertElementbyname(skipList, student); // ��ѧ�����ݲ��뵽������
        }
    }
    fclose(file);
}

// ��ȡ�ı��ļ��е�ѧ����Ϣ�����뵽������(score
void readStudentDatascore(const char *fileName, SkipList *skipList) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("�޷����ļ� %s\n", fileName);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Student *student = (Student *)malloc(sizeof(Student));
        if (sscanf(line, "%d,%49[^,],%9[^,],%49[^,],%lf,%lf,%lf,%lf",
                   &student->id, student->name, student->gender, student->classes,
                   &student->score_1, &student->score_2, &student->score_3, &student->average_score) == 8) {
            insertElementbyscore(skipList, student); // ��ѧ�����ݲ��뵽������
        }
    }
    fclose(file);
}

// �������а��������ҽڵ�(��ID)
Node *findElementByID(SkipList *list, int id) {
    Node *current = list->header;
    for (int i = list->level - 1; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->student->id < id) {
            current = current->forward[i];
        }
    }
    current = current->forward[0];
    if (current != NULL && current->student->id == id) {//ֱ���鵽Ŀ��id 
        return current;
    } else {
        return NULL;
    }
}

// �������а��������ҽڵ�(������)
Node *findElementByName(SkipList *list, const char *name) {
    Node *current = list->header;
    for (int i = list->level - 1; i >= 0; i--) {
        while (current->forward[i] != NULL && strcmp(current->forward[i]->student->name, name) < 0) {
            current = current->forward[i];
        }
    }
    current = current->forward[0];
    if (current != NULL && strcmp(current->student->name, name)==0) {
        return current;
    } else {
        return NULL;
    }
}

//���������ҵõ�������ͬ�ķ������ˣ� 
void findStudentsWithSameAverage(SkipList *list, double averageScore) {
    Node *current = list->header;
    int found = 0;
    char resultString[10000]; // ���ڴ洢������ַ���
    strcpy(resultString, "ѧ����Ϣ��\n");

    // ����߲㿪ʼ���Ҿ�����ͬƽ��ֵ��ѧ���ڵ�
    for (int i = list->level - 1; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->student->average_score < averageScore) {
            current = current->forward[i];
        }
        if (current->forward[i] != NULL && current->forward[i]->student->average_score == averageScore) {
            Node *temp = current->forward[i];
            while (temp != NULL && temp->student->average_score == averageScore) {
                char tempString[200]; // ��ʱ�洢����ѧ����Ϣ���ַ���
                snprintf(tempString, sizeof(tempString), "ѧ�ţ�%d\n������%s\n�Ա�%s\n�༶��%s\n����1��%.1lf\n����2��%.1lf\n����3��%.1lf\nƽ���ɼ���%.1lf\n", 
                        temp->key, temp->student->name, temp->student->gender, temp->student->classes,
                        temp->student->score_1, temp->student->score_2, temp->student->score_3, temp->student->average_score);
                strncat(resultString, tempString, sizeof(resultString) - strlen(resultString) - 1); // ʹ��strncat()ȷ�����ᳬ������ַ����Ľ���
                temp = temp->forward[0];
                found = 1;
            }
            break; // �������ѭ��
        }
    }
    if (found) {
        printf("%s", resultString); // ��ӡ������ͬƽ��ֵѧ������Ϣ
    } else {
        printf("δ�ҵ�����ƽ��ֵΪ %.1lf ��ѧ����Ϣ\n", averageScore);
    }
}

// ��ӡ����
void printSkipList(SkipList *list) {
    for (int level = list->level - 1; level >= 0; level--) {
        printf("Level %d: ", level);
        Node *current = list->header->forward[level];
        while (current != NULL) {
            printf("%d, %s, %s, %s, %.1lf, %.1lf, %.1lf, %.1lf\n", current->key, current->student->name,current->student->gender, current->student->classes,
                   current->student->score_1, current->student->score_2, current->student->score_3, current->student->average_score);
            current = current->forward[level];
        }
        printf("NULL\n");
    }
}

// ��������
void destroySkipList(SkipList *list) {
    Node *current = list->header->forward[0];
    while (current != NULL) {
        Node *temp = current;
        current = current->forward[0];
        free(temp->student); // �ͷ�ѧ����Ϣ�ڴ�
        free(temp); // �ͷŽڵ��ڴ�
    }
    free(list->header); // �ͷ��ڱ��ڵ�
    free(list); // �ͷ�����ṹ�ڴ�
}


int main() {
	
    CombinedSkipList combinedSkipList;
    
    int judge = 1;
    while (judge == 1) {
        int type;
        printf("�������ѯ���ͣ�1=ѧ��/2=����/3=�ɼ���: ");
        scanf("%d", &type);
        srand((unsigned)time(NULL)); // ����� 

        if (type == 1) {
		    combinedSkipList.idSorted = createSkipList(1);
		
		    // ���ļ��ж�ȡѧ����Ϣ�����뵽������
		    readStudentDataid("ID����ĳɼ���.txt", combinedSkipList.idSorted); 
		    
		    // ��ӡ����
		    //printSkipList(combinedSkipList.idSorted);
		    
		    // ��ѯѧ����Ϣ
		    int queryID;
		    printf("������Ҫ��ѯ��ѧ��ID��");
		    scanf("%d", &queryID);
		
		    // �������а�ID����ѧ��
		    Node *result = findElementByID(combinedSkipList.idSorted, queryID);
		    if (result != NULL) {
		        printf("�ҵ���ѧ����Ϣ��\n");
		        printf("ѧ�ţ�%d\n������%s\n�Ա�%s\n�༶��%s\n����1��%.1lf\n����2��%.1lf\n����3��%.1lf\nƽ���ɼ���%.1lf\n", 
		               result->student->id, result->student->name, result->student->gender, result->student->classes,
		               result->student->score_1, result->student->score_2, result->student->score_3, result->student->average_score);
		    } else {
		        printf("û���ҵ�ָ��ID��ѧ����Ϣ��\n");
		    }
		
		    // �����ͷ��ڴ�Ĵ��루�����Ҫ��
		    destroySkipList(combinedSkipList.idSorted);
		            
        } 
		else if (type == 2) {
        	
		    combinedSkipList.nameSorted = createSkipList(2);
		    
		    readStudentDataname("��������ĳɼ���.txt", combinedSkipList.nameSorted); // ���ļ��ж�ȡѧ����Ϣ�����뵽������
		    //printSkipList(combinedSkipList.nameSorted);
		    
		    // ��ѯѧ����Ϣ
		    char queryname[50];
		    printf("������Ҫ��ѯ��ѧ�����֣�");
		    scanf("%49s", queryname);
		    
		    Node *result = findElementByName(combinedSkipList.nameSorted, queryname); // �������а���������ѧ��
		    if (result != NULL) {
		        printf("�ҵ���ѧ����Ϣ��\n");
		        printf("ѧ�ţ�%d\n������%s\n�Ա�%s\n�༶��%s\n����1��%.1lf\n����2��%.1lf\n����3��%.1lf\nƽ���ɼ���%.1lf\n", result->key, result->student->name,result->student->gender, result->student->classes,
		                   result->student->score_1, result->student->score_2, result->student->score_3, result->student->average_score);
		    } else {
		        printf("û���ҵ�ָ��������ѧ����Ϣ��\n");
		    }
		
		    destroySkipList(combinedSkipList.nameSorted); // �ͷ�����ṹ�ڴ�

            
        }                  
		else if (type == 3) {
        	
		    combinedSkipList.averageScoreSorted = createSkipList(3); // ����һ���µ�����
		
		    // ���ļ��ж�ȡѧ����Ϣ�����뵽������
		    readStudentDatascore("ƽ��ֵ����ĳɼ���.txt", combinedSkipList.averageScoreSorted);
		    
		    // ��ӡ����
		    //printSkipList(combinedSkipList.averageScoreSorted);
		
		    // ��ѯѧ����Ϣ
		    double queryScore;
		    printf("������Ҫ��ѯ��ѧ��ƽ��������");
		    scanf("%lf", &queryScore);
		
		    findStudentsWithSameAverage(combinedSkipList.averageScoreSorted, queryScore);
		
		    // ��������
		    destroySkipList(combinedSkipList.averageScoreSorted);
            
        } 
		else {
            printf("��ѯ���ʹ���\n");
        }

        printf("�Ƿ������ѯ����1=��/0=�񣩣�");
        scanf("%d", &judge);
    }
    return 0;
}
