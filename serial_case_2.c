#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<time.h>

const int max = pow(2,16);
int *insertingNumbers;
struct node* head;

struct node
{
    int data;
    struct node* next;
} node;

void create()
{
    head = NULL;
}


bool member(int value)
{
    struct node* tempNode = head;
    while(tempNode != NULL)
    {
        if(tempNode->data == value)
        {
            return true;
        }
        else
        {
            tempNode = tempNode->next;
        }
    }
    return false;
}

void insert(int value)
{
    if(head == NULL)
    {
        head = malloc(sizeof(node));
        head->data = value;
        head->next = NULL;
    }
    else
    {
        struct node* tempNode = head;
        while(tempNode->next != NULL)
        {
            tempNode = tempNode->next;
        }
        tempNode->next = malloc(sizeof(node));
        tempNode->next->data = value;
        tempNode->next->next = NULL;
    }

}


void delete(int value)
{
    if(head->data == value)
    {
        head = head->next;
    }
    else
    {
        struct node* previouseTempNode = head;
        struct node* middleTempNode = previouseTempNode->next;
        while(middleTempNode != NULL)
        {
            struct node* nextTempNode = middleTempNode->next;
            if(middleTempNode->data == value)
            {
                previouseTempNode->next = nextTempNode;
                return;
            }
            if(nextTempNode == NULL)
            {
                return;
            }
            previouseTempNode = previouseTempNode->next;
            middleTempNode = previouseTempNode->next;
            nextTempNode = middleTempNode->next;
        }
    }
    return;
}

int* randomNumber(int howMany, int numberOfInsert)
{
    int *numberArray = malloc(max * sizeof(int));
    for (int i = 0; i < max; i++)
    {
        numberArray[i] = i;
    }
    srand(time(NULL));
    for (int i = 0; i < max; i++)
    {
        int randNum = rand()%(max);
        int temp = numberArray[i];
        numberArray[i] = numberArray[randNum];
        numberArray[randNum] = temp;
    }

    int* randomArray = malloc(howMany * sizeof(int));

    for(int i =0; i < howMany; i++)
    {
        randomArray[i] = numberArray[i];
    }

    insertingNumbers = malloc(numberOfInsert * sizeof(int));

    for(int i = 0; i < numberOfInsert; i++)
    {
        insertingNumbers[i] = numberArray[howMany + i];
    }
    free(numberArray);
    return randomArray;

}

int* randomFunction(int m, float m_member, float m_insert, float m_delete)
{

    int numberOfMember = m * m_member;
    int numberOfInsert = m * m_insert;
    int numberOfDelete = m * m_delete;

    printf("\nNumber of member operations : %d\n",numberOfMember);
    printf("Number of insert operations : %d\n",numberOfInsert);
    printf("Number of delete operations : %d\n",numberOfDelete);

    int m_real = numberOfMember + numberOfInsert + numberOfDelete;

    if(1 != (int)(m_member + m_insert + m_delete))
    {
        printf("\nSum of fractions should be 1.\n");
    }

    int* functionArray = malloc(m_real * sizeof(int));
    for (int i = 0; i < numberOfMember; i++)
    {
        functionArray[i] = 0;// 0 = member
    }
    for (int i = 0; i < numberOfInsert; i++)
    {
        functionArray[numberOfMember + i] = 1;// 1 = insert
    }
    for (int i = 0; i < numberOfDelete; i++)
    {
        functionArray[numberOfMember + numberOfInsert + i] = 2;// 2 = delete
    }
    srand(time(NULL));
    for(int i = 0; i < m_real; i++)
    {
        int randNum = rand()%(m_real);
        int temp = functionArray[i];
        functionArray[i] = functionArray[randNum];
        functionArray[randNum] = temp;
    }

    return functionArray;
}


int main()
{
    int n, m;
    printf("Input \"n\": ");
    n = 1000;
    printf("%d\n",n);
    //scanf("%d",&n);
    printf("Input \"m\": ");
    m = 10000;
    printf("%d",m);
    //scanf("%d",&m);
    printf("\n");

    float m_member, m_insert, m_delete;
    printf("Enter fractions:\n");
    printf("\tMember: ");
    m_member = 0.90;
    printf("%f\n",m_member);
    //scanf("%f",&m_member);
    printf("\tInsert: ");
    m_insert = 0.05;
    printf("%f\n",m_insert);
    //scanf("%f",&m_insert);
    printf("\tDelete: ");
    m_delete = 0.05;
    printf("%f\n",m_delete);
    //scanf("%f",&m_delete);

    create();//create the linked list
    int *randomNumberArray = randomNumber(n, m * m_insert);

    for(int i = 0; i < n; i++)
    {
        insert(randomNumberArray[i]); //populate the array
    }

    int *randomFunctionArray = randomFunction(m, m_member, m_insert, m_delete);

    int func;
    int j = 0;
    srand(time(NULL));
    clock_t start, end;
    double processTime;
    printf("\nProcess started.");
    start = clock();//time starts here
    for(int i = 0; i < m; i++)
    {
        func = randomFunctionArray[i];
        if(func == 0)
        {
            member(rand() % max);
        }
        else if(func == 1)
        {
            insert(insertingNumbers[j]);
            j++;
        }
        else if(func == 2)
        {
            delete(randomNumberArray[rand() % n]);
        }
    }
    end = clock();//time ends here
    printf("\nProcess finished.");
    double elapsedTime = 1000 * ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nElapsed time (Serial_case_2) = %f millisecs.\n\n", elapsedTime);

    FILE *f = fopen("serial_case_2.txt", "a");
    //fprintf(f, "n = %d, m = %d, m_member = %f, m_insert = %f, m_delete = %f\n", n, m, m_member, m_insert, m_delete);
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(f, "%f\n", elapsedTime);
    fclose(f);

    free(randomNumberArray);
    free(randomFunctionArray);

    return 0;
}
