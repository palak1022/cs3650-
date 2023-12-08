/**
 * Vector implementation.
 *
 * - Implement each of the functions to create a working growable array (vector).
 * - Do not change any of the structs
 * - When submitting, You should not have any 'printf' statements in your vector 
 *   functions.
 *
 * IMPORTANT: The initial capacity and the vector's growth factor should be 
 * expressed in terms of the configuration constants in vect.h
 */
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "vect.h"

/** Main data structure for the vector. */
struct vect {
  char **data;             /* Array containing the actual data. */
  unsigned int size;       /* Number of items currently in the vector. */
  unsigned int capacity;   /* Maximum number of items the vector can hold before growing. */
};

vect_t *vect_new() {
    vect_t *v = (vect_t *)malloc(sizeof(vect_t));
    if (v == NULL) {
        perror("Failed to allocate memory for Vector");
        exit(EXIT_FAILURE);
    }

    v->data = (char **)calloc(INITIAL_CAPACITY, sizeof(char *));
    if (v->data == NULL) {
        perror("Failed to allocate memory for data in Vector");
        free(v);
        exit(EXIT_FAILURE);
    }

    v->size = 0;
    v->capacity = INITIAL_CAPACITY;
    return v;
}

void vect_delete(vect_t *v) {
    if (v == NULL) {
        return;
    }

    for (unsigned int i = 0; i < v->size; i++) {
        free(v->data[i]);
    }
    free(v->data);
    free(v);
}

const char *vect_get(vect_t *v, unsigned int idx) {
    if (v == NULL || idx >= v->size) {
        return NULL;
    }
    return v->data[idx];
}

char *vect_get_copy(vect_t *v, unsigned int idx) {
  // vector of data at that index copy to another and check for its length and create a variable for malloc of that variable 
    if (v == NULL || idx >= v->size) {
        return NULL;
    }
    return strdup(v->data[idx]);
  //malloc on the size of the strig at v-> data and then copy it using strig copy method.
}

void vect_set(vect_t *v, unsigned int idx, const char *elt) {
    if (v == NULL || idx >= v->size) {
        return;
    }
    free(v->data[idx]);
    v->data[idx] = strdup(elt);
  //same as above 
}

void vect_add(vect_t *v, const char *elt) {
    // Ensure the vector is not null before proceeding
    if (v == NULL) {
        return;
    }

    // If the vector is full, create a new node
      v->size ++;
    if (v->size >= v->capacity) {
     
        size_t new_capacity = v->capacity * VECT_GROWTH_FACTOR;
        char **new_data = (char **)realloc(v->data, new_capacity * sizeof(char *));
        if (new_data == NULL) {
            perror("Failed to reallocate memory for Vector");
            exit(EXIT_FAILURE);
        }

        v->data = new_data;
        v->capacity = new_capacity;
    }

    // Store the string in the vector
    v->data[v->size] = strdup(elt);
    if (v->data[v->size] == NULL) {
        perror("Failed to duplicate string for Vector");
        exit(EXIT_FAILURE);
    }

    v->size++;
}


void vect_remove_last(vect_t *v) {
    if (v == NULL || v->size == 0) {
        return;
    }
    free(v->data[v->size - 1]);
    v->size--;
}

unsigned int vect_size(vect_t *v) {
    if (v == NULL) {
        return 0;
    }
    return v->size;
}

unsigned int vect_current_capacity(vect_t *v) {
    if (v == NULL) {
        return 0;
    }
    return v->capacity;
}
