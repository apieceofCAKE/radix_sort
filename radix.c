/*
Data structures class assignment. Performs radix sort on an integer array. The instructions are as follows:
"Cada grupo deverá implementar um programa que recebe como entrada inteiros n e d e gera aleatoriamente
uma lista com n elementos com exatamente d dígitos (o dígito mais significaivo pode ser zero.
O programa deve listar os n elementos gerados e, a seguir, quando solicitado, executar a ordenação
por distribuição.
O programa deve imprimir, a cada iteração, o estado corrente das b filas, bem como o estado corrente da
lista de elementos a ser ordenada.
    * Considerar b (base) = 10
    * Grupos de 3 pessoas
    * Apresentação 22/05
    * As impressoões devem seguir o modelo do livro"  */

//Preprocessor directives
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


//Abstract data types
typedef struct node
{
    int number;
    struct node *next_node;
} Node_t;

typedef struct queue
{
    Node_t *front;
    Node_t *rear;
    int length;
} Queue_t;


//Declaration
int *create_array(int elem_num, int digit_num);
void print_array(int *array, int elem_num);
Queue_t *create_queue();
void enqueue(Queue_t *queue, int number);
int dequeue(Queue_t *queue);
void print_queue(Queue_t *queue);
void print_iteration(Queue_t **queue_array);
void radix_sort(int *array, int elem_num, int digit_num);


//Main
int main()
{
    printf("\n********************");
    printf("\n\nRadix sort program. Made by:\nCaíque Evaristo\nJoão Pedro Loureiro\nMackson Mattos");
    printf("\n\n********************");

    srand(time(NULL));
    int elem_num;  //Number of elements; integer array size
    int digit_num;  //Maximum number of digits of each element

    printf("\n\nEnter the number of digits of the elements to be generated:  ");
    scanf(" %d", &digit_num);
    printf("\nEnter the amount of elements to be generated:  ");
    scanf(" %d", &elem_num);

    int *array = create_array(elem_num, digit_num);

    printf("\n********************");
    printf("\n\nThis is our initial array...\n");
    print_array(array, elem_num);

    printf("\nSorting...\n");
    printf("\n********************");

    radix_sort(array, elem_num, digit_num);

    printf("\nPrinting the sorted array...\n");
    print_array(array, elem_num);

    printf("\nFreeing memory...\n");
    free(array);

    return 0;
}


//Definition
/*
Creates and returns an integer array of ELEM_NUM size. Each integer has a maximum value of ((10**DIGIT_NUM) - 1).  */
int *create_array(int elem_num, int digit_num)
{
    int *array = malloc(sizeof(int) * elem_num);

    for (int i = 0; i < elem_num; i++)
        {
        array[i] = rand() % ((int)(pow(10, digit_num)));
        }

    return array;
}


/*
Prints the integer array.  */
void print_array(int *array, int elem_num)
{
    printf("\nList: ");

    for(int i = 1; i <= elem_num; i++)
        {
        printf("%d ", array[(i - 1)]);

        if ((i % 25) == 0) //Newline after 25 elements are printed
            printf("\n");
        }

    printf("\n");
}


/*
Creates and returns an empty Queue_t queue.  */
Queue_t *create_queue()
{
    Queue_t *new_queue = malloc(sizeof(Queue_t));

    new_queue->rear = NULL;
    new_queue->front = NULL;
    new_queue->length = 0;

    return new_queue;
}


/*
Enqueues NUMBER on QUEUE, creating a new node for it.  */
void enqueue(Queue_t *queue, int number)
{
    Node_t * new_node = NULL;
    new_node = malloc(sizeof(Node_t));

    new_node->number = number;
    new_node->next_node = NULL;

    if(queue->front == NULL)
        {
        queue->front = new_node;
        queue->rear = new_node;
        }

    else
        {
        queue->rear->next_node = new_node;
        queue->rear = new_node;
        }

    queue->length++;
}


/*
Dequeues QUEUE, returning the removed value and freeing the node.  */
int dequeue(Queue_t *queue)
{
    Node_t *removed_node;
    int removed_number;

    if(queue->front != NULL)
        {
        removed_node = queue->front;
        if(queue->rear == queue->front)
            {
            queue->front = NULL;
            queue->rear = NULL;
            }
        else
            {
            queue->front = queue->front->next_node;
            }
        queue->length--;
        }

    else
        {
        printf("\nUnderflow :/\n\n");
        exit(1);
        }

    removed_number = removed_node->number;
    free(removed_node);  //Freeing memory

    return removed_number;
}


/*
Prints the queues, as specified. It's used inside print_iteration function.  */
void print_queue(Queue_t *queue)
{
    Node_t *aux = queue->front;

    while(aux != NULL)
        {
        printf("%d ", aux->number);
        aux = aux->next_node;
        }
}

/*
Prints each itaration of Radix Sort. It's used inside radix_sort function. */
void print_iteration(Queue_t **queue_array)
{
    for(int i = 0; i < 10; i++)
        {
        printf("Queue %d:\t", i);
        print_queue(queue_array[i]);
        printf("\n");
        }

    printf("\n********************\n");
}


/*
Core function. Does radix sort in an integer array of ELEM_NUM elements where each element has a maximum value of
((10**DIGIT_NUM) - 1).  */
void radix_sort(int *array, int elem_num, int digit_num)
{
    Queue_t *queue_array[10];
    int order;
    int index;
    Queue_t *current_queue;

    for(int i = 0; i < 10; i++)
        {
        queue_array[i] = create_queue();
        }

    printf("\n");

    for(int i = 0; i < digit_num; i++)
        {
        order = (int)(pow(10, i));

        for(int j = 0; j < elem_num; j++)
            {
            index = (array[j] % (order * 10)) / order;
            enqueue(queue_array[index], array[j]);
            }

        print_array(array, elem_num);
        printf("\nIteration %d:\n\n", i+1);
        print_iteration(queue_array); //Printing the current state of queues

        index = 0; //Resetting the variable to use it again
        for(int k = 0; k < 10; k++)
            {
            current_queue = queue_array[k];

            while((current_queue->length) > 0)
                {
                array[index] = dequeue(current_queue);
                index++;
                }
            }
    }

    for(int i = 0; i < 10; i++)  //Freeing memory
        {
        free(queue_array[i]);
        }
}
