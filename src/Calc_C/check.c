#include "SmartCalc_C.h"

// #include <stdio.h>
// #include <ctype.h>
// #include <string.h>

// #define MAX_STACK_SIZE 255

// int main () {
//     char expression[255];
//     scanf("%[^\n]", expression);
//     remove_spaces(expression);
//     printf ("re%s\n", expression);
//     add_zero(expression);
//     printf ("ad%s\n", expression);
//     int i = 0;
//     int result = check_expression (expression, &i);
//     printf("%d\n", result);
//     return 0;
// }

void remove_spaces(char *expression) {
  char support[MAX_STACK_SIZE];
  strcpy(support, expression);
  int j = 0;
  for (int i = 0; support[i] != '\0'; i++) {
    if (support[i] != ' ') {
      if (support[i] == ',') {
        expression[j] = '.';
      } else if (support[i] == '%') {
        expression[j] = 'm';
        expression[j + 1] = 'o';
        expression[j + 2] = 'd';
        j += 2;
      } else
        expression[j] = support[i];
      j++;
    }
  }
  expression[j] = '\0';
}

void add_zero(char *expression) {
  char support[MAX_STACK_SIZE];
  strcpy(support, expression);
  int j = 0, i;
  if (support[0] == '-') {
    expression[0] = '0';
    j++;
  }
  for (i = 0; support[i + 1] != '\0'; i++) {
    if (support[i] == '(' && support[i + 1] == '-') {
      expression[j] = '(';
      expression[j + 1] = '0';
      j += 2;
    } else {
      expression[j] = support[i];
      j++;
    }
  }

  for (i = i; support[i] != '\0'; i++) {
    expression[j] = support[i];
    j++;
  }
  expression[j] = '\0';
}

int check_expression(const char *expression) {
  int flag = 1;
  int number = 0, bracket_begin = 0, arith = 1, funct = 0, funct_m = 0;
  int num_check = 0, arith_check = 0;  //, func_cheak = 0 ,bracket_end = 0
  if (check_arith_operation(expression[0]) == 1 && (expression[0] != '-'))
    flag = 0;  // expression[0] != '+' &&
  for (int i = 0; expression[i] != '\0' && flag == 1; i++) {
    num_check = isdigit(expression[i]);
    arith_check = check_arith_operation(expression[i]);
    if ((num_check == 0 && arith_check == 0) &&
        (arith_check == 1 && number == 0)) {
      flag = 0;
    } else if (num_check != 0 || expression[i] == 'x') {
      number = 1;
      arith = 0;
    } else if (arith_check == 1 && number == 1) {
      number = 0;
      arith = 1;
    } else if ((expression[i] ==
                '.')) {  //&& (isdigit(expression[i+1]) != 0 || number != 0)
      flag = 1;
    } else if (expression[i] == '(' &&
               (arith == 1 || funct == 1 || funct_m == 1)) {
      bracket_begin++;
    } else if (expression[i] == '(' &&
               (arith != 1 && funct != 1 && funct_m != 1)) {
      flag = 0;
    } else if (expression[i] == ')' && number == 1 && bracket_begin > 0) {
      bracket_begin--;
    } else if (expression[i] == ')' && bracket_begin == 0) {
      flag = 0;
    } else if (expression[i] == 'c' || expression[i] == 's' ||
               expression[i] == 't' || expression[i] == 'a' ||
               expression[i] == 'l') {
      if (check_functions(expression, &i) == 0)
        flag = 0;
      else if (expression[i] != '(')
        flag = 0;
      bracket_begin++;
      funct = 1;
    } else if (expression[i] == 'm' && expression[i + 1] == 'o' &&
               expression[i + 2] == 'd') {
      if (expression[i + 3] == '(') {
        funct_m = 1;
      }
      i = i + 3;
    } else
      flag = 0;
  }
  if (bracket_begin != 0 || arith != 0) flag = 0;
  return flag;
}

int check_arith_operation(char symbol) {
  int flag = 0;
  if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' ||
      symbol == '^') {
    flag = 1;
  }
  return flag;
}

int check_functions(const char *expression, int *j) {
  int flag = 1, end = 0;
  int i = 0;
  for (i = *j; expression[i] != '\0' && flag == 1 && end == 0;) {
    if (expression[i] == 's' && expression[i + 1] == 'i' &&
        expression[i + 2] == 'n') {
      *j = i + 3;
      break;
    } else if (expression[i] == 'c' && expression[i + 1] == 'o' &&
               expression[i + 2] == 's') {
      *j = i + 3;
      break;
    } else if (expression[i] == 't' && expression[i + 1] == 'a' &&
               expression[i + 2] == 'n') {
      *j = i + 3;
      break;
    } else if (expression[i] == 'a' && expression[i + 1] == 'c' &&
               expression[i + 2] == 'o' && expression[i + 3] == 's') {
      *j = i + 4;
      break;
    } else if (expression[i] == 'a' && expression[i + 1] == 's' &&
               expression[i + 2] == 'i' && expression[i + 3] == 'n') {
      *j = i + 4;
      break;
    } else if (expression[i] == 'a' && expression[i + 1] == 't' &&
               expression[i + 2] == 'a' && expression[i + 3] == 'n') {
      *j = i + 4;
      break;
    } else if (expression[i] == 's' && expression[i + 1] == 'q' &&
               expression[i + 2] == 'r' && expression[i + 3] == 't') {
      *j = i + 4;
      break;
    } else if (expression[i] == 'l' && expression[i + 1] == 'n') {
      *j = i + 2;
      break;
    } else if (expression[i] == 'l' && expression[i + 1] == 'o' &&
               expression[i + 2] == 'g') {
      *j = i + 3;
      break;
    } else {
      flag = 0;
      break;
    }
  }
  return flag;
}
