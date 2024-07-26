#include "SmartCalc_C.h"

int push(Stack_exp **stack, double value, int priority, type_t type) {
  Stack_exp *new_stack = malloc(sizeof(Stack_exp));
  int result = 1;
  if (new_stack == NULL) {
    result = 5;
  } else {
    new_stack->value = value;
    new_stack->priority = priority;
    new_stack->type = type;
    new_stack->next = *stack;
    *stack = new_stack;
  }
  return result;
}

Stack_exp *pop(Stack_exp **stack) {
  if (*stack == NULL) {
    return NULL;
  } else {
    Stack_exp *temp = *stack;
    *stack = (*stack)->next;
    // temp->next = NULL;
    return temp;
  }
}

Stack_exp *peek(Stack_exp *stack) {
  if (stack == NULL) {
    return NULL;
  } else {
    return stack;
  }
}

Stack_exp *copy_stack(Stack_exp *stack) {
  Stack_exp *copy_stack = NULL;
  while (stack != NULL) {
    Stack_exp *temp = pop(&stack);
    push(&copy_stack, temp->value, temp->priority, temp->type);
    free(temp);
  }
  return copy_stack;
}

void delete_stack(Stack_exp **stack) {
  Stack_exp *temp;
  while (*stack != NULL) {
    temp = pop(stack);
    free(temp);
  }
}