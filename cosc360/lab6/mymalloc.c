
// C

#include "mymalloc.h"
#include <stdio.h>
#include <unistd.h>

typedef struct block{
  unsigned int size;
  struct block* flink;
} *block;

block block_begin= NULL;

void insertBlock(block node){
  //if empty set beginning to node
  if (block_begin==NULL) {
    block_begin= node;
    return;
  }
  block temp;
  for (temp= free_list_begin(); temp->flink!= NULL && node> temp->flink; temp= temp->flink);
  //if at the end add node to the end
  if (temp->flink== NULL) {
    /* code */
    temp->flink= node;
    return;
  }
  //place node in place of temp
  node->flink= temp->flink;
  temp->flink= node;
}

void block_del(block node){
  if (node == block_begin) {
    /* code */
    block_begin= node->flink;
    return;
  }

    block blink = block_begin;
    while(blink->flink != node)
        blink = blink->flink;

    blink->flink = node->flink;
    node = node->flink;
}

block node(size_t size){
  size_t min_val= 8192;
  if (size > 8184) {
    /* code */
    min_val= (size+7+8)&-8;
  }
  //create node for return
  block node_create= (block) sbrk(min_val);
  node_create->size= min_val;
  node_create->flink= NULL;
  //add note_create list
  insertBlock(node_create);
  return node_create;
}

//My_malloc() is a buffered interface to sbrk(), doling out heap memory for programs that call it.
void* my_malloc(size_t size) {
    // Your code here.
    block allocate;
    size_t allocate_size= (size+7+8)&-8;
    //look for node
    for (allocate= free_list_begin();allocate!=NULL;allocate= free_list_next(allocate)) {
      /* code */
      if (allocate->size>= allocate_size) {
        /* code */
        break;
      }
    }
    if (allocate==NULL) {
      /* code */
      allocate= node(size);
    }
    allocate->size-= allocate_size;
    block allocate_2= (void*)allocate+allocate->size;
    if (allocate->size<=16) {
      /* code */
      allocate_size+=allocate->size;
      block_del(allocate);
    }
    allocate_2->size= allocate_size;
    return (void*)allocate_2+8;
}

//my_free(p), the chunk of memory should be returned to the free list
void my_free(void* ptr) {
    // Your code here.
    insertBlock((block)ptr-8);
}

//returns a pointer to the first node on the free list. If the free list is empty, it should return NULL. The first four bytes on a free list node should contain the size of the node (including all metadata, like the size and pointers).
void* free_list_begin() {
    // Your code here.
    return block_begin;
}

//takes a pointer to a free list node and returns a pointer to the next node on the free list. If n is the last node on the free list, then free_list_next(n) should return NULL.
void* free_list_next(void* node) {
    // Your code here.
    return ((block) node)->flink;
}

//coalesce_free_list() should process the free list and combine all adjacent entries.
void coalesce_free_list() {
    // Your code here.
    block temp= free_list_begin();
    while (temp!= NULL) {
      /* code */
      block temp_next= temp->flink;
      if ((void*)temp+ temp->size== temp_next) {
        /* code */
        temp->size+= temp_next->size;
        block_del(temp_next);
      }
      else{
        temp= temp->flink;
      }
    }
}
