#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_LEN 32
#define VAL_T int
typedef long long ll;

typedef struct entry {
    char key[KEY_LEN + 1];
    VAL_T value;
} entry;

void entry_init(entry* self, char* key, VAL_T value) {
    sprintf(self->key, "%s", key);
    self->value = value;
}

/*
 * symbol table type, hash table (separate chaining) impl
 */
#define TABLE_SIZE 0x1003
struct _node {
    entry entry;
    struct _node* next;
};
typedef struct _node* symtab[TABLE_SIZE];

// ************************************************************
//    Your implementation goes here
// ************************************************************

symtab* symtab_init() {
    symtab* self = malloc(sizeof(symtab));
    for (int i = 0; i < TABLE_SIZE; i++) {
        (*self)[i] = malloc(sizeof(struct _node));
        (*self)[i]->entry.key[0] = 0;
        (*self)[i]->entry.value = 0;
        (*self)[i]->next = NULL;
    }
    return self;
}

int hash(char* key) {
    ll hashcode = 0;
    for (int i = 0; i < KEY_LEN; i++) {
        if (key[i] == '\0') {
            break;
        }
        hashcode += key[i] * 5;
    }
    return (hashcode % TABLE_SIZE + TABLE_SIZE) % TABLE_SIZE;
}

int symtab_insert(symtab* self, char* key, VAL_T value) {
    int hashcode = hash(key);

    struct _node* ptr = (*self)[hashcode];
    struct _node* prev;
    while (ptr) {
        if (strcmp(ptr->entry.key, key) == 0) {
            return 0;
        }
        prev = ptr;
        ptr = ptr->next;
    }

    struct _node* new_node = malloc(sizeof(struct _node));
    entry_init(&new_node->entry, key, value);
    new_node->next = NULL;
    prev->next = new_node;
    return 1;
}

VAL_T symtab_lookup(symtab* self, char* key) {
    int hashcode = hash(key);
    printf("%d\n", hashcode);
    struct _node* ptr = (*self)[hashcode];
    while (ptr) {
        if (strcmp(ptr->entry.key, key) == 0)
            return ptr->entry.value;
        ptr = ptr->next;
    }
    return -1;
}

int symtab_remove(symtab* self, char* key) {
    int hashcode = hash(key);
    struct _node* ptr = (*self)[hashcode];
    struct _node* prev;
    while (ptr) {
        if (strcmp(ptr->entry.key, key) == 0) {
            prev->next = ptr->next;
            return 1;
        }
        prev = ptr;
        ptr = ptr->next;
    }
    return 0;
}
