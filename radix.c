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
    * Apresentação 20/05
    * As impressoões devem seguir o modelo do livro (página 35)"  */


//Preprocessor directives
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define BASE 10


//Abstract data types
typedef struct node
{
    int value;
    struct node *next;
} Node_t;


typedef struct queue
{
    Node_t *front;
    Node_t *rear;
    int length;
} Queue_t;


//Declaration
int *create_array(int element_size, int element_amount);
void print_array(int *array);
Queue_t *create_queue();
void enqueue(Queue_t *queue, int value);
int dequeue(Queue_t *queue);
void print_queue(Queue_t *queue);
void radix_sort(int *array, int element_amount, int element_size);


//Main
int main(void) {

    int element_amount, element_size;

    printf("\n\nEnter the size (number of digits) of the elements to be generated:\t");
    scanf(" %d", &element_size);
    printf("\n\nEnter the amount of elements to be generated:\t");
    scanf(" %d", &element_amount);

    int *array = create_array(element_size, element_amount);

    //Before sorting
    print_array(array);

    radix_sort(array, element_amount, element_size);

    //After sorting
    print_array(array);
    return 0;
}


//Definition
/*
Returns and integer array of ELEMENT_AMOUNT elements, with ELEMENT_SIZE digits each, randomly generated.  */
int *create_array(int element_size, int element_amount)
{

}


/*
Prints the given array in an user friendly way.  */
void print_array(int *array)
{

}


/*
Initializes and returns a pointer to a Queue_t structure.  */
Queue_t * create_queue(){
    Queue_t * novaFila = malloc(sizeof(Queue_t));
    novaFila->rear = NULL;
    novaFila->front = NULL;
    novaFila->length = 0;
    return novaFila;
}


/*
Performs enqueue on a given Queue_t structure.  */
void enqueue(Queue_t *queue, int value){
    Node_t * novoNo = malloc(sizeof(Node_t));
    novoNo->value = value;
    novoNo->next = NULL;

    if(queue->front == NULL){
        queue->front = novoNo;
        queue->rear = novoNo;
    }else{
        queue->rear->next = novoNo;
        queue->rear = novoNo;
    }
    queue->length++;
}


/*
Performs dequeue on a given Queue_t structure.  */
int dequeue(Queue_t *queue){
    Node_t * removido;
    if(queue->front != NULL){
        removido = queue->front;
        if(queue->rear == queue->front){
            queue->front = NULL;
            queue->rear = NULL;
        }else{
            queue->front = queue->front->next;
        }
        queue->length--;
        int valorRemovido = removido->value;
        free(removido);
        return valorRemovido;

    }else{
        // underflow
    }
}


/*
Prints a Queue_t structure in an user friendly way.  */
void print_queue(Queue_t *queue){
    Node_t * no = queue->front;
    while(no != NULL){
        printf("%d \n", no->value);
        no = no->next;
    }
}


/*
Performs radix sort on a given integer array. It calls print_queue during the process to show what's
happening.  */
void radix_sort(int *array, int element_amount, int element_size){

    Queue_t * radixVet[10];
    for(int i = 0; i < 10; i++){
        radixVet[i] = create_queue();
    }

    for(int i = 0; i < element_size; i++){
        int base = pow(10, i);
        for(int j = 0; j < element_amount; j++){
            int radixInd = (array[j] % (base * 10)) / base;
            enqueue(radixVet[radixInd], array[j]);
        }
        int vetPos = 0;
        for(int j = 0; j < 10; j++){
            Queue_t * fila = radixVet[j];
            while(fila->length > 0){
                array[vetPos] = dequeue(fila);
                vetPos++;
            }
        }
    }
}
