#include "linked_list.h"

node *linked_list_init(){
    node *head = (node*)malloc(sizeof(node));
    head->count = 0;
    head->next = NULL;
    return head;
}

void linked_list_free(node *head){
    node *cur = head;
    node *last;
    while(cur != NULL){
        last = cur;
        cur = cur->next;
        free(last);
    }
}

char linked_list_string[0x10000];

char *linked_list_tostring(node *head){
    node *cur = head->next;
    char *position;
    int length = 0;
    while(cur != NULL){
        position = linked_list_string + length;
        length += sprintf(position, "%d", cur->value);
        cur = cur->next;
        if(cur != NULL){
            position = linked_list_string + length;
            length += sprintf(position, "->");
        }
    }
    position = linked_list_string + length;
    length += sprintf(position, "%c", '\0');
    return linked_list_string;
}

int linked_list_size(node *head){
    return head->count;
}

void linked_list_append(node *head, int val){
    node *cur = head;
    node *new_node;
    while(cur->next != NULL){
        cur = cur->next;
    }
    new_node = (node*)malloc(sizeof(node));
    new_node->value = val;
    new_node->next = NULL;
    cur->next = new_node;
    head->count++;
}

/* your implementation goes here */

void linked_list_insert(node *head, int val, int index) {
    if (index<0 || index>head->count)
        return;

    node *new_node = (node*)malloc(sizeof(node));
    new_node->value = val;
    head->count++;

    node *cur = head;
    while (index--)
        cur=cur->next;

    node *nxt=cur->next;
    cur->next=new_node;
    new_node->next=nxt;
}

void linked_list_delete(node *head, int index){
    if (index<0 || index>=head->count)
        return;
    node *cur = head;
    while (index--)
        cur=cur->next;
    node *nxt=cur->next=cur->next->next;
    head->count--;
}

void linked_list_remove(node *head, int val){
    node *cur=head->next;
    node *before=head;

    while (cur && cur->value!=val) {
        before=cur;
        cur=cur->next;
    }

    if (cur) {
        before->next=cur->next;
        head->count--;
    }
}

void linked_list_remove_all(node *head, int val){
    node *before=head;

    for (node *cur=head->next;cur;cur=cur->next) {
        if (cur->value==val) {
            before->next=cur->next;
            head->count--;
        }
        else
            before=before->next;
    }
}

int linked_list_get(node *head, int index){
    if (index<0 || index>=head->count)
        return -0x80000000;
    
    node *cur = head->next;
    while (index--)
        cur=cur->next;
    return cur->value;
}

int linked_list_search(node *head, int val){
    int index=0;
    for (node *cur=head->next;cur;cur=cur->next) {
        if (cur->value==val)
            return index;
        index++;
    }
    return -1;
}

node *linked_list_search_all(node *head, int val){
    node *new_head=linked_list_init();

    int index=0;
    for (node *cur=head->next;cur;cur=cur->next) {
        if (cur->value==val)
            linked_list_append(new_head, index);
        index++;
    }
    return new_head;
}
