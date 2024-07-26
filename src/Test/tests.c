#include <check.h>
#include <string.h>

#include "../Calc_C/SmartCalc_C.h"

START_TEST(calculate_1) {
  char expression[] = "cos(sin(tan(0.5)))";
  double value_x = 0;
  double result = 0;
  int exit_status =
      calculation_reverse_polish_notation(expression, value_x, &result);
  double true_result = 0.8680519;
  ck_assert_double_eq_tol(result, true_result, 1e-06);
  ck_assert_int_eq(exit_status, 1);
}
END_TEST

START_TEST(calculate_2) {
  char expression[] = "-8/(2+3)*(7-2)+6";
  double value_x = 0;
  double result = 0;
  int exit_status =
      calculation_reverse_polish_notation(expression, value_x, &result);
  double true_result = -2;
  ck_assert_double_eq_tol(result, true_result, 1e-06);
  ck_assert_int_eq(exit_status, 1);
}

START_TEST(calculate_3) {
  char expression[] = "(10.5-2.2)*(4.8+2.3)-1.7/3";
  double value_x = 0;
  double result = 0;
  int exit_status =
      calculation_reverse_polish_notation(expression, value_x, &result);
  double true_result = 58.3633333;
  ck_assert_double_eq_tol(result, true_result, 1e-06);
  ck_assert_int_eq(exit_status, 1);
}

START_TEST(calculate_4) {
  char expression[] =
      "((5.5^3 + 3^2) * (2.7^2 - 6^3)) / (2^4 + 10^2) * (4.2^5 - 1.2^6)";
  double value_x = 0;
  double result = 0;
  int exit_status =
      calculation_reverse_polish_notation(expression, value_x, &result);
  double true_result = -411439.5250193;
  ck_assert_double_eq_tol(result, true_result, 1e-06);
  ck_assert_int_eq(exit_status, 1);
}

START_TEST(calculate_5) {
  char expression[] = "sqrt(16)+ln(1)*log(10)/sqrt(25)";
  double value_x = 0;
  double result = 0;
  int exit_status =
      calculation_reverse_polish_notation(expression, value_x, &result);
  double true_result = 4;
  ck_assert_double_eq_tol(result, true_result, 1e-06);
  ck_assert_int_eq(exit_status, 1);
}

START_TEST(calculate_6) {
  char expression[] =
      "(sqrt(16)+sin(1)*cos(2)/"
      "tan(0.5)-asin(0.5)^acos(0.3)*atan(0.8)*ln(2)*log(100))/"
      "cos(sin(tan(0.5)))";
  double value_x = 0;
  double result = 0;
  int exit_status =
      calculation_reverse_polish_notation(expression, value_x, &result);
  double true_result = 3.3946194645;
  ck_assert_double_eq_tol(result, true_result, 1e-06);
  ck_assert_int_eq(exit_status, 1);
}

START_TEST(calculate_7) {
  char expression[] = "x^3 - 6*x^2 + 4*x + 12";
  double value_x = 0.5;
  double result = 0;
  int exit_status =
      calculation_reverse_polish_notation(expression, value_x, &result);
  double true_result = 12.625;
  ck_assert_double_eq_tol(result, true_result, 1e-06);
  ck_assert_int_eq(exit_status, 1);
}

START_TEST(calculate_8) {
  char expression[] =
      "-500 mod 45 + log(1000) -96/5+ (-6)";  //-500mod45 + log(1000) -96/5+
                                              //(-6)
  double value_x = 0;
  double result = 0;
  int exit_status =
      calculation_reverse_polish_notation(expression, value_x, &result);
  double true_result = -27.2;
  ck_assert_double_eq_tol(result, true_result, 1e-06);
  ck_assert_int_eq(exit_status, 1);
}

// деление на ноль

START_TEST(calculate_9) {
  char expression[] =
      "(4 + sin(x) * cos(2) / 0 - asin(x)^acos(0.3) mod 2 * atan(x) * ln(2) * "
      "log(100)) / cos(sin(tan(x)))";
  double value_x = 0.49879;
  double result = 0;
  int exit_status =
      calculation_reverse_polish_notation(expression, value_x, &result);
  ck_assert_int_eq(exit_status, 3);
}

// ошибка в вырадение

START_TEST(calculate_10) {
  char expression[] =
      "(4 + sin(x) * cos(2)) - asin(x)^acos(0.3) mod 2 * atan(x) * ln(2) * "
      "log(100)) / cos(sin(tan(x)))";
  double value_x = 0;
  double result = 0;
  int exit_status =
      calculation_reverse_polish_notation(expression, value_x, &result);
  ck_assert_int_eq(exit_status, 2);
}

START_TEST(calculate_credit_1) {
  double term = convert_years_to_months(10);
  double loan_amount = 3000000;
  double annuity = get_monthly_payment_annuity(loan_amount, 15.7, term);
  double total_payment = get_total_payment_annuity(annuity, term);
  double over_payment = get_overpayment_on_credit(loan_amount, total_payment);
  ck_assert_double_eq_tol(49694.51, annuity, 0.01);
  // printf("%f", over_payment);
  ck_assert_double_eq_tol(2963341.20, over_payment, 0.5);
  ck_assert_double_eq_tol(5963341.20, total_payment, 0.5);
}

START_TEST(calculate_credit_2) {
  double term = convert_years_to_months(0.5);
  double loan_amount = 300000;
  double annuity = get_monthly_payment_annuity(loan_amount, 10, term);
  double total_payment = get_total_payment_annuity(annuity, term);
  double over_payment = get_overpayment_on_credit(loan_amount, total_payment);
  ck_assert_double_eq_tol(51468.42, annuity, 0.01);
  // printf("%f", over_payment);
  ck_assert_double_eq_tol(8810.52, over_payment, 0.5);
  ck_assert_double_eq_tol(308810.52, total_payment, 0.5);
}

START_TEST(calculate_credit_3) {
  double term = convert_years_to_months(10);
  double loan_amount = 3000000;
  double first_pay = 0, last_pay = 0;
  double total_payment =
      get_total_payment_diff(loan_amount, term, 15.7, &first_pay, &last_pay);
  double over_payment = get_overpayment_on_credit(loan_amount, total_payment);
  ck_assert_double_eq_tol(64250.00, first_pay, 0.01);
  ck_assert_double_eq_tol(25327.08, last_pay, 0.01);
  // printf("%f", over_payment);
  ck_assert_double_eq_tol(2374625.00, over_payment, 0.5);
  ck_assert_double_eq_tol(5374625.00, total_payment, 0.5);
}

START_TEST(calculate_credit_4) {
  double term = convert_years_to_months(0.5);
  double loan_amount = 300000;
  double first_pay = 0, last_pay = 0;
  double total_payment =
      get_total_payment_diff(loan_amount, term, 10, &first_pay, &last_pay);
  double over_payment = get_overpayment_on_credit(loan_amount, total_payment);
  ck_assert_double_eq_tol(52500.00, first_pay, 0.01);
  ck_assert_double_eq_tol(50416.67, last_pay, 0.01);
  // printf("%f", over_payment);
  ck_assert_double_eq_tol(8750.00, over_payment, 0.5);
  ck_assert_double_eq_tol(308750.00, total_payment, 0.5);
}

START_TEST(calculate_deposit_1) {
  double total_interest = calc_total(1000000, 12, 10, 1, 1, 0, 0);
  double end_balance = calc_total_deposit(total_interest, 1000000, 12, 0, 0);
  ck_assert_double_eq_tol(104712.98, total_interest, 0.5);
  ck_assert_double_eq_tol(1104712.98, end_balance, 0.5);
}

START_TEST(calculate_deposit_2) {
  double total_interest = calc_total(1000000, 18, 10, 1, 0, 0, 50000);
  double end_balance =
      calc_total_deposit(total_interest, 1000000, 18, 0, 50000);
  ck_assert_double_eq_tol(86250, total_interest, 0.5);
  ck_assert_double_eq_tol(186250, end_balance, 0.5);
}

int main() {
  Suite *s1 = suite_create("Calc");
  TCase *smart_calc = tcase_create("smart_calc");
  TCase *credit_calc = tcase_create("credit_calc");
  TCase *deposit_calc = tcase_create("deposit_calc");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, smart_calc);
  tcase_add_test(smart_calc, calculate_1);
  tcase_add_test(smart_calc, calculate_2);
  tcase_add_test(smart_calc, calculate_3);
  tcase_add_test(smart_calc, calculate_4);
  tcase_add_test(smart_calc, calculate_5);
  tcase_add_test(smart_calc, calculate_6);
  tcase_add_test(smart_calc, calculate_7);
  tcase_add_test(smart_calc, calculate_8);
  tcase_add_test(smart_calc, calculate_9);
  tcase_add_test(smart_calc, calculate_10);

  suite_add_tcase(s1, credit_calc);
  tcase_add_test(credit_calc, calculate_credit_1);
  tcase_add_test(credit_calc, calculate_credit_2);
  tcase_add_test(credit_calc, calculate_credit_3);
  tcase_add_test(credit_calc, calculate_credit_4);

  suite_add_tcase(s1, deposit_calc);
  tcase_add_test(deposit_calc, calculate_deposit_1);
  tcase_add_test(deposit_calc, calculate_deposit_2);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
