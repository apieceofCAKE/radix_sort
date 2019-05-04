/*
Data structures class assignment. Performs radix_sort sort.  */


//Preprocessor directives
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


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
Queue_t *create_queue();
void enqueue(Queue_t *queue, int value);
int dequeue(Queue_t *queue);
void print_queue(Queue_t *queue);
void radix_sort(int *vector, int vector_size, int max_digits);


//Main
int main(void) {
    int vet[] = {1,200,0,45,15,67,7,87,900,0,43343,2423,12122};
    int vetSize = 13;

    radix_sort(vet, vetSize, 5);

    //results
    for(int i = 0; i < vetSize; i++){
        printf("%d \n", vet[i]);
    }
    return 0;
}


//Definition
Queue_t * create_queue(){
    Queue_t * novaFila = malloc(sizeof(Queue_t));
    novaFila->rear = NULL;
    novaFila->front = NULL;
    novaFila->length = 0;
    return novaFila;
}


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


void print_queue(Queue_t *queue){
    Node_t * no = queue->front;
    while(no != NULL){
        printf("%d \n", no->value);
        no = no->next;
    }
}


void radix_sort(int *vector, int vector_size, int max_digits){

    Queue_t * radixVet[10];
    for(int i = 0; i < 10; i++){
        radixVet[i] = create_queue();
    }

    for(int i = 0; i < max_digits; i++){
        int base = pow(10, i);
        for(int j = 0; j < vector_size; j++){
            int radixInd = (vector[j] % (base * 10)) / base;
            enqueue(radixVet[radixInd], vector[j]);
        }
        int vetPos = 0;
        for(int j = 0; j < 10; j++){
            Queue_t * fila = radixVet[j];
            while(fila->length > 0){
                vector[vetPos] = dequeue(fila);
                vetPos++;
            }
        }
    }
}
