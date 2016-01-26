#include <stdio.h>
#include <stdlib.h>

typedef struct QUEUE {
    int *elements;
    int maxSize;
    int curSize;
    int front;
} queue;

#define INIT_SIZE 10
#define EMPTY -1

void printQ(queue *q);
int initialize(queue *q);
int isFull(queue *q);
int isEmpty(queue *q);
int enqueue(queue *q, int val);
int dequeue(queue *q);
int front(queue *q);

void main() {

    int val, i = 0;

    //Allocate space and initialize queue
    queue *myQueue = (queue*) malloc(sizeof(queue));
    initialize(myQueue);

    //Prove queue is initially empty
    printQ(myQueue);

    //enqueue 3 items
    enqueue(myQueue, 14);
    enqueue(myQueue, 7);
    enqueue(myQueue, 12);
    printQ(myQueue);

    //dequeue 1 item
    val = dequeue(myQueue);
    printQ(myQueue);
    printf("Value return was %d.\n", val);

    //Over fill queue so that it has to resize
    enqueue(myQueue, 3);
    enqueue(myQueue, 17);
    enqueue(myQueue, 24);
    enqueue(myQueue, 6);
    enqueue(myQueue, 22);
    enqueue(myQueue, 33);
    enqueue(myQueue, 19);
    enqueue(myQueue, 49);
    enqueue(myQueue, 32);
    enqueue(myQueue, 35);
    enqueue(myQueue, 46);
    enqueue(myQueue, 52);
    printQ(myQueue);

    //Inspect the first element
    val = front(myQueue);
    printf("Value return was %d.\n", val);
    printQ(myQueue);

    //dequeue 5 items
    dequeue(myQueue);
    dequeue(myQueue);
    dequeue(myQueue);
    dequeue(myQueue);
    dequeue(myQueue);
    printQ(myQueue);

    //enqueue items until queue is full again
    while( !isFull(myQueue) ) {
        enqueue(myQueue, i);
        printQ(myQueue);
        i++;
    }

    //dequeue all items in the queue
    while( !isEmpty(myQueue) ) {
        dequeue(myQueue);
        printQ(myQueue);
    }

    //memory clean-up
    free(myQueue->elements);
    free(myQueue);
}

//Pre-condition: q points to a valid queue that has been initialized
//Post-condition: if q is empty a message saying so will be printed to the screen
//                  otherwise, all the values in q will be printed to std output
void printQ(queue *q) {
    int i, j, val;

    if( isEmpty(q) ) {
        printf("Queue is empty.");
    }

    for(i = 0; i < q->curSize; i++) {
        j = (q->front + i) % q->maxSize;
        val = q->elements[j];
        printf("%d ", val);
    }
    printf("\n");
}

//Pre-condition: q points to a valid queue
//Post-condition: the queue that 'q' points to will be set to represent an empty queue
int initialize(queue *q) {
    q->elements = (int*) malloc(sizeof(int)*INIT_SIZE);

    if(q->elements == NULL)
        return 0;

    q->maxSize = INIT_SIZE;
    q->curSize = 0;
    q->front = 0;

    return 1;
}

//Pre-condition: q points to a valid queue that has been initialized
//Post-condition: returns true if-and-only-if the queue is full
int isFull(queue *q) {
    if( q->curSize == q->maxSize )
        return 1;
    else
        return 0;
}

//Pre-condition: q points to a valid queue that has been initialized
//Post-condition: returns true iff the queue is empty
int isEmpty(queue *q) {
    if(q->curSize == 0)
        return 1;
    else
        return 0;
}

//Pre-condition: q points to a valid queue that has been initialized, and val is a valid int value to be enqueued
//Post-condition: returns true iff we were able to enqueue val, returns false otherwise
int enqueue(queue *q, int val) {

    //if the queue is not full go ahead and insert to the back of the queue
    if( !isFull(q) ) {
        int index = (q->front + q->curSize) % q->maxSize;
        q->elements[index] = val;
        q->curSize++;
        return 1;
    } else {

        //allocate space for a new array of elements, twice it's previous size
        int *temp = (int*) malloc(sizeof(int)*(2*q->maxSize));
        int i, j;

        //if we were unable to allocate space operation failed
        if(temp == NULL)
            return 0;

        //copy all items from original array to new array with the front of the new array starting at index 0
        for(i = 0; i < q->maxSize; i++) {
            j = (q->front + i) % q->maxSize;
            temp[i] = q->elements[j];
        }

        //free old array and reinitialize
        free(q->elements);
        q->elements = temp;
        q->maxSize *= 2;
        q->front = 0;

        //insert val
        q->elements[ (q->front + q->curSize) % q->maxSize ] = val;
        q->curSize++;

        return 1;   //successful operation
    }
}

//Pre-condition: q points to a valid queue that has been initialized
//Post-condition: returns EMPTY if the queue is empty; otherwise
//                  the front of the queue will be "removed" and the removed item will be returned
int dequeue(queue *q) {

    int temp;

    if( isEmpty(q) )
        return EMPTY;

    temp = q->elements[q->front];
    q->front = (q->front + 1) % q->maxSize;
    q->curSize--;

    return temp;
}

//Pre-condition: q points to a valid queue that has been initialized
//Post-condition: returns EMPTY if the queue is empty; otherwise
//                  returns the current front of the queue
int front(queue *q) {

    if( isEmpty(q) )
        return EMPTY;

    return q->elements[q->front];
}









