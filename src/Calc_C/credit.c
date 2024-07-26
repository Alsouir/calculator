#include "SmartCalc_C.h"

double get_monthly_payment_annuity(double loan_amount, double interest_rate,
                                   double term) {
  double monthly_interest = interest_rate / 12 / 100;
  double annuity_coefficient = monthly_interest *
                               powl(1 + monthly_interest, term) /
                               (powl(1 + monthly_interest, term) - 1);
  double annuity = annuity_coefficient * loan_amount;
  return annuity;
}

double get_total_payment_annuity(double annuity, double term) {
  return annuity * term;
}

double get_total_payment_diff(double loan_amount, double term,
                              double interest_rate, double *first_pay,
                              double *last_pay) {
  double non_diff_monthly_payment = loan_amount / term;
  double total_payment = 0;

  for (int month = 0; month < term; month++) {
    double left_to_pay = loan_amount - (non_diff_monthly_payment * month);
    double interest_payment = left_to_pay * (interest_rate / 100 / 12);
    double monthly_payment = non_diff_monthly_payment + interest_payment;
    if (month == 0) *first_pay = monthly_payment;
    if (month + 1 >= term) *last_pay = monthly_payment;
    total_payment += monthly_payment;
  }
  return total_payment;
}

double get_overpayment_on_credit(double loan_amount, double total_payment) {
  return total_payment - loan_amount;
}

double convert_years_to_months(double years) { return (years * 12); }  // ceil
