#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "library.h"

stack create_stack(int _elementSize){
  stack stc;
  stc = malloc(sizeof(struct _stack));
  if (!stc) {
    return NULL;
  }
  stc->element_size = _elementSize;
  stc->top = NULL;
  stc->buffer = malloc(stc->element_size);
  return stc;
}

int push(stack _stack, void *_element){
  struct stack_element *stc_el;

  stc_el = malloc(sizeof(struct stack_element));
  if (!stc_el) {
    return -1;
  }
  stc_el->element = malloc(_stack->element_size);
  stc_el->prev = _stack->top;
  memcpy(stc_el->element, _element, _stack->element_size);
  _stack->top = stc_el;

  return 0;
}

void *pop(stack _stack){
  struct stack_element *stc_el;

  if (!_stack->top) {
    return NULL;
  }
  stc_el = _stack->top;
  memcpy(_stack->buffer, stc_el->element, _stack->element_size);
  //  _stack->buffer = stc_el->element;
  _stack->top = stc_el->prev;
  free(stc_el->element);
  free(stc_el);

  return _stack->buffer;
}

void delete_stack(stack _stack){
  struct stack_element *stc_el;
  stc_el = _stack->top;
  while (stc_el) {
    _stack->top = stc_el->prev;
    free(stc_el->element);
    free(stc_el);
    stc_el = _stack->top;
  }
  free(_stack);

  return;
}

void print_stack(stack _stack, void (*print_head)(), void (*print_body)(void *_element), void (*print_foot)()){
  struct stack_element *c = _stack->top;
  print_head();
  while (c) {
                  print_body(c->element);
                  c = c->prev;
  }
  print_foot();
}
