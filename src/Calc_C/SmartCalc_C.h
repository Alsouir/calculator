#ifndef SMARTCALC_C_H
#define SMARTCALC_C_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 255

typedef enum {
  num = 1,
  x = 2,
  plus = 3,
  minus = 4,
  mult = 5,
  division = 6,
  mod = 7,
  sqr = 8,
  sinus = 9,
  cosine = 10,
  tangent = 11,
  arcsin = 12,
  arccos = 13,
  arctan = 14,
  square_root = 15,
  natur_log = 16,
  decimal_log = 17,
  bracket_open = 18,
  bracket_close = 19,

} type_t;

typedef struct Stack {
  double value;
  int priority;
  struct Stack *next;
  type_t type;
} Stack_exp;

int push(Stack_exp **stack, double value, int priority, type_t type);
Stack_exp *pop(Stack_exp **stack);
Stack_exp *peek(Stack_exp *stack);
Stack_exp *copy_stack(Stack_exp *stack);
void delete_stack(Stack_exp **stack);

int check_expression(const char *expression);
int check_arith_operation(char symbol);
int check_functions(const char *expression, int *j);
void add_zero(char *expression);
void remove_spaces(char *expression);

void parser(const char *expression, Stack_exp **new_stack);
double str_to_double(const char *expression, int *j);
Stack_exp *reverse_polish_notation(const char *expression);
void parser_operation(Stack_exp **stack, char operation);

int calculation_reverse_polish_notation(char *expression, double value_x,
                                        double *result);
void decision(Stack_exp **RPN, int *flag_push, Stack_exp **value_of_number,
              double value_x, int *flag);
double calc_operation(double operand1, double operand2, int type_operation);
double calc_function(double operand, int type_function);

double get_monthly_payment_annuity(double loan_amount, double interest_rate,
                                   double term);
double get_total_payment_annuity(double annuity, double term);
double get_total_payment_diff(double loan_amount, double term,
                              double interest_rate, double *first_pay,
                              double *last_pay);
double get_overpayment_on_credit(double loan_amount, double total_payment);
double convert_years_to_months(double years);

double calc_total(double amount, int term, double int_rate, int frq_pay,
                  int capitalization, double replenishments, double withdraws);
double calc_total_deposit(double total_amount, double amount, int term,
                          double replenishments, double withdraws);

#endif