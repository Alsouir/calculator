#include "SmartCalc_C.h"

double calc_total(double amount, int term, double int_rate, int frq_pay,
                  int capitalization, double replenishments, double withdraws) {
  double interest = int_rate * 0.01, amount_buff = amount, total_earn = 0;
  if (term >= frq_pay) {
    for (int m = 1; m <= term; m++) {
      double buff_of_earn = 0;
      if (frq_pay == 1) {
        buff_of_earn = amount_buff * interest / 12.0;
      } else if (frq_pay == 12 && m % 12 == 0) {
        buff_of_earn = amount_buff * interest;
      }
      amount_buff = amount_buff + replenishments - withdraws;
      if (capitalization == 1) amount_buff += buff_of_earn;
      total_earn += buff_of_earn;
    }
  }
  return total_earn;
}

double calc_total_deposit(double total_amount, double amount, int term,
                          double replenishments, double withdraws) {
  double repl_and_wtdrw = (replenishments - withdraws) * term;
  return amount + total_amount + repl_and_wtdrw;
}