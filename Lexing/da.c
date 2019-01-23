/*
Program written by Alex Johnson - 9/12/2018
-Stores void* items in a dynamic array that doubles and shrinks
-Make sure to free all memory
*/

#include "da.h"
#include <assert.h>
#include <stdlib.h>

typedef struct da
{
    void **array;
    int size;
    int capacity;
    int flag;
    int max;

    void (*display)(void *, FILE *);
    void (*free)(void *);
} DA;

DA *newDA(void)
{
    // Constructor
    DA *d = malloc(sizeof(DA));
    assert(d != 0);
    d->array = malloc(sizeof(void*));
    d->array[0] = NULL;

    d->size = 0;
    d->capacity = 1;
    d->flag = 0;

    d->display = NULL;
    d->free = NULL;

    return d;
}

void setDAdisplay(DA *items, void (*f)(void *, FILE *))
{
    // Set the display to the passed in function
    items->display = f;
}

void setDAfree(DA *items, void (*f)(void *))
{
    // Set the free to the passed in function
    items->free = f;
}

void insertDA(DA *items, int index, void *value)
{
    // Insert the passed in item at the given index
    assert(sizeof(value) != 0);
    assert(index <= items->size && index >= 0);

    if (items->capacity <= items->size) {
        // Array is full, double the capacity
        items->capacity *= 2;
        items->array = realloc(items->array, sizeof(void*) * items->capacity);
        int i;
        for (i = items->capacity/2; i < items->capacity; i++) {
            items->array[i] = NULL;
        }
    }

    int i = items->size;

    while (i > index) {
        // Shift items right
        items->array[i] = items->array[i-1];
        i--;
    }

    items->array[index] = value;
    items->size++;
}

void *removeDA(DA *items, int index)
{
    // Return the item at the given index, remove from array
    assert(index >= 0 && index < items->size);
    assert(items->size > 0);

    int i = index;

    void *p = items->array[index];

    items->size--;

    while (i < items->size) {
        // Shift items left
        items->array[i] = items->array[i+1];
        i++;
    }
    items->array[i] = NULL;


    if ((float)items->size / (float)items->capacity < 0.25) {
        // Shrink array capacity if number of items / capacity is less than 1/4
        int i;

        for (i = (items->capacity)/2; i < items->capacity; i++) {
            free(items->array[i]);
        }
        items->capacity = items->capacity / 2;
    }



    if (items->size == 0) {
        // Ensure capacity never drops below one
        items->capacity = 1;
    }

    assert(items->capacity >= 1);

    return p;
}

void unionDA(DA* recipient, DA* donor)
{
    // Adds all items from donor da to end of recipient da
    // Create temp array from donor by removing from the back, insert into recipient
    // Free temp array
    while (donor->size > 0) {
        insertDA(recipient, recipient->size, removeDA(donor, 0));
    }
}

void *getDA(DA *items, int index)
{
    // Returns item at given index without popping
    assert(index >= 0 && index < items->size);
    return items->array[index];
}

void *setDA(DA *items, int index, void *value)
{
    // If index is at the end, insert value. Otherwise set that index equal to
    // passed in value and return original value.
    assert(index >= 0 && index <= items->size);

    if (index == items->size) {
        insertDA(items, index, value);
        return NULL;
    }
    else {
        void *p = items->array[index];
        items->array[index] = value;
        return p;
    }
}

int sizeDA(DA *items)
{
    // Return number of items in array
    return items->size;
}

void displayDA(DA *items, FILE *fp)
{
    // Function for displaying array using passed in display function. If no
    // display function, displays the item's pointer.
    fprintf(fp, "[");
    int i = 0;
    for (i = 0; i < items->size; i++) {
        if (items->display != NULL) {
            items->display(items->array[i], fp);
            if (i < items->size - 1) fprintf(fp, ",");
        }
        else {
            fprintf(fp, "@%p", items->array[i]);
            if (i < items->size - 1) fprintf(fp, ",");
        }
    }

    if (items->flag > 0) {
        if (items->size == 0) fprintf(fp, "[%d]", items->capacity - items->size);
        else fprintf(fp, ",[%d]", items->capacity-items->size);
    }
    fprintf(fp, "]");
}

int debugDA(DA *items, int level)
{
    // Set the debug level in the da and return previous value
    int temp = items->flag;
    items->flag = level;
    return temp;
}

void freeDA(DA *items)
{
    // Free all allocated memory
    if (items->free != NULL) {
        int i;
        for (i = 0; i < items->capacity; i++) {
            items->free(items->array[i]);
        }
    }
    
    free(items->array);
    free(items);
}
