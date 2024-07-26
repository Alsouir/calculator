#include "SmartCalc_C.h"

// 6.9+96*cos(58/8.3) valgrind --tool=memcheck --leak-check=yes  .
//  int main () {
//      char expression[MAX_STACK_SIZE];
//      scanf("%s", expression);
//      char value_x[MAX_STACK_SIZE];
//      scanf("%s", value_x);
//      double result = 0;
//      int result_calc = calculation_reverse_polish_notation (expression,
//      value_x, &result); printf("%f\n", result); printf("%d\n", result_calc);
//      return 0;
//  }

int calculation_reverse_polish_notation(char *expression, double value_x,
                                        double *result) {
  Stack_exp *RPN = NULL;
  remove_spaces(expression);
  add_zero(expression);
  int flag = 1, flag_push = 1;
  if (check_expression(expression) != 1) {
    flag = 2;
  }
  if (flag == 1) RPN = reverse_polish_notation(expression);
  Stack_exp *value_of_number = NULL;
  Stack_exp *temp;
  while (RPN != NULL && flag == 1 && flag_push == 1) {
    decision(&RPN, &flag_push, &value_of_number, value_x, &flag);

    if (flag_push != 1) {
      flag = flag_push;
    }
  }
  if (flag == 1) {
    temp = pop(&value_of_number);
    *result = temp->value;
    free(temp);
  } else {
    delete_stack(&RPN);
    delete_stack(&value_of_number);
  }
  return flag;
}

void decision(Stack_exp **RPN, int *flag_push, Stack_exp **value_of_number,
              double value_x, int *flag) {
  Stack_exp *temp_v1, *temp_v2;
  Stack_exp *temp;
  temp = pop(RPN);
  if (temp->type == num) {
    *flag_push = push(value_of_number, temp->value, temp->priority, temp->type);
  } else if (temp->type == x) {
    *flag_push = push(value_of_number, value_x, temp->priority, temp->type);
  } else if (temp->type > 2 && temp->type < 9) {
    temp_v2 = pop(value_of_number);
    temp_v1 = pop(value_of_number);
    double operand1, operand2, result_operation;
    operand2 = temp_v2->value;
    operand1 = temp_v1->value;
    if (temp->type == 6 && operand2 == 0) {
      *flag = 3;
      free(temp_v1);
      free(temp_v2);
    } else {
      result_operation = calc_operation(operand1, operand2, temp->type);
      *flag_push = push(value_of_number, result_operation, 0, 1);
      free(temp_v1);
      free(temp_v2);
    }

  } else if (temp->type > 8 && temp->type < 18) {
    double operand1, result_function;
    temp_v1 = pop(value_of_number);
    operand1 = temp_v1->value;
    result_function = calc_function(operand1, temp->type);
    *flag_push = push(value_of_number, result_function, 0, 1);
    free(temp_v1);
  }
  free(temp);
}

Stack_exp *reverse_polish_notation(const char *expression) {
  Stack_exp *stack = NULL;
  parser(expression, &stack);
  Stack_exp *RPN = NULL;
  Stack_exp *support = NULL;
  Stack_exp *temp, *temp2;
  int flag_bracket = 0, flag_priority = 0;
  int i = 0;
  while (stack != NULL) {
    i++;
    temp = pop(&stack);
    if (temp->type == num || temp->type == x) {
      push(&RPN, temp->value, temp->priority, temp->type);
    } else if (support == NULL) {
      push(&support, temp->value, temp->priority, temp->type);
    } else if (support != NULL && temp->type != bracket_close) {
      while (support != NULL && flag_priority != 1 && flag_bracket != 1) {
        temp2 = peek(support);
        if (temp2->type == bracket_open) {
          push(&support, temp->value, temp->priority, temp->type);
          flag_bracket = 1;
        } else if (temp2->priority < temp->priority) {
          push(&support, temp->value, temp->priority, temp->type);
          flag_priority = 1;
        } else if (temp2->priority >= temp->priority) {
          temp2 = pop(&support);
          push(&RPN, temp2->value, temp2->priority, temp2->type);
          free(temp2);
        }
      }
      if (support == NULL && flag_priority != 1) {
        push(&support, temp->value, temp->priority, temp->type);
      }
      flag_priority = 0;
      flag_bracket = 0;
    } else if (support != NULL && temp->type == bracket_close) {
      while (flag_bracket != 1) {
        temp2 = pop(&support);
        if (temp2->type != bracket_open) {
          push(&RPN, temp2->value, temp2->priority, temp2->type);
        } else
          flag_bracket = 1;
        free(temp2);
      }
      flag_bracket = 0;
    }
    free(temp);
  }
  Stack_exp *temp3;
  while (support != NULL) {
    temp3 = pop(&support);
    push(&RPN, temp3->value, temp3->priority, temp3->type);
    free(temp3);
  }
  Stack_exp *back_RPN = copy_stack(RPN);
  return back_RPN;
}

double calc_operation(double operand1, double operand2, int type_operation) {
  double result = 0;
  switch (type_operation) {
    case 3:
      result = operand1 + operand2;
      break;
    case 4:
      result = operand1 - operand2;
      break;
    case 5:
      result = operand1 * operand2;
      break;
    case 6:
      result = operand1 / operand2;
      break;
    case 7:
      result = fmod(operand1, operand2);
      break;
    case 8:
      result = pow(operand1, operand2);
      break;
    default:
      break;
  }
  return result;
}

double calc_function(double operand, int type_function) {
  double result = 0;
  switch (type_function) {
    case 9:
      result = sin(operand);
      break;
    case 10:
      result = cos(operand);
      break;
    case 11:
      result = tan(operand);
      break;
    case 12:
      result = asin(operand);
      break;
    case 13:
      result = acos(operand);
      break;
    case 14:
      result = atan(operand);
      break;
    case 15:
      result = sqrt(operand);
      break;
    case 16:
      result = log(operand);
      break;
    case 17:
      result = log10(operand);
      break;
    default:
      break;
  }
  return result;
}

void parser(const char *expression, Stack_exp **new_stack) {
  Stack_exp *stack = NULL;
  for (int i = 0; expression[i] != '\0'; i++) {
    if (isdigit(expression[i]) != 0)
      push(&stack, str_to_double(expression, &i), 0, 1);
    else if (expression[i] == 'x')
      push(&stack, expression[i], 0, 2);
    else if (expression[i] == '+' || expression[i] == '-' ||
             expression[i] == '*' || expression[i] == '/' ||
             expression[i] == '^' || expression[i] == '(' ||
             expression[i] == ')')
      parser_operation(&stack, expression[i]);
    else if (expression[i] == 'm' && expression[i + 1] == 'o' &&
             expression[i + 2] == 'd') {
      push(&stack, 0, 2, 7);
      i = i + 2;
    } else if (expression[i] == 's' && expression[i + 1] == 'i' &&
               expression[i + 2] == 'n') {
      push(&stack, 0, 4, 9);
      i = i + 2;
    } else if (expression[i] == 'c' && expression[i + 1] == 'o' &&
               expression[i + 2] == 's') {
      push(&stack, 0, 4, 10);
      i = i + 2;
    } else if (expression[i] == 't' && expression[i + 1] == 'a' &&
               expression[i + 2] == 'n') {
      push(&stack, 0, 4, 11);
      i = i + 2;
    } else if (expression[i] == 'a' && expression[i + 1] == 's' &&
               expression[i + 2] == 'i' && expression[i + 3] == 'n') {
      push(&stack, 0, 4, 12);
      i = i + 3;
    } else if (expression[i] == 'a' && expression[i + 1] == 'c' &&
               expression[i + 2] == 'o' && expression[i + 3] == 's') {
      push(&stack, 0, 4, 13);
      i = i + 3;
    } else if (expression[i] == 'a' && expression[i + 1] == 't' &&
               expression[i + 2] == 'a' && expression[i + 3] == 'n') {
      push(&stack, 0, 4, 14);
      i = i + 3;
    } else if (expression[i] == 's' && expression[i + 1] == 'q' &&
               expression[i + 2] == 'r' && expression[i + 3] == 't') {
      push(&stack, 0, 4, 15);
      i = i + 3;
    } else if (expression[i] == 'l' && expression[i + 1] == 'n') {
      push(&stack, 0, 4, 16);
      i = i + 1;
    } else if (expression[i] == 'l' && expression[i + 1] == 'o' &&
               expression[i + 2] == 'g') {
      push(&stack, 0, 4, 17);
      i = i + 2;
    }
  }
  *new_stack = copy_stack(stack);
}

void parser_operation(Stack_exp **stack, char operation) {
  if (operation == '+')
    push(stack, operation, 1, 3);
  else if (operation == '-')
    push(stack, operation, 1, 4);
  else if (operation == '*')
    push(stack, operation, 2, 5);
  else if (operation == '/')
    push(stack, operation, 2, 6);
  else if (operation == '^')
    push(stack, operation, 3, 8);
  else if (operation == '(')
    push(stack, operation, 5, 18);
  else if (operation == ')')
    push(stack, operation, 5, 19);
}

double str_to_double(const char *expression, int *j) {
  char number_exp[MAX_STACK_SIZE];
  int i = 0, k = 0;
  for (i = *j; isdigit(expression[i]) != 0 || expression[i] == '.'; i++) {
    number_exp[k] = expression[i];
    k++;
  }
  *j = *j + k - 1;
  number_exp[k] = '\0';
  double double_number = atof(number_exp);
  return double_number;
}
