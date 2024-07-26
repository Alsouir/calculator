#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QString>
#include <QVector>

extern "C" {
#include "../Calc_C/SmartCalc_C.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButton_9_clicked();

  void on_pushButton_8_clicked();

  void on_pushButton_7_clicked();

  void on_pushButton_6_clicked();

  void on_pushButton_5_clicked();

  void on_pushButton_1_clicked();

  void on_pushButton_4_clicked();

  void on_pushButton_3_clicked();

  void on_pushButton_2_clicked();

  void on_pushButton_10_clicked();

  void on_point_clicked();

  void on_plus_clicked();

  void on_minus_clicked();

  void on_openBracket_clicked();

  void on_closeBracket_clicked();

  void on_multiplication_clicked();

  void on_division_clicked();

  void on_sqrt_clicked();

  void on_sqr_clicked();

  void on_sin_clicked();

  void on_cos_clicked();

  void on_tan_clicked();

  void on_asin_clicked();

  void on_eqally_clicked();

  void on_deleteChar_clicked();

  void on_deleteAll_clicked();

  void on_X__clicked();

  void on_Graph_clicked();

  void on_BuildGraph_clicked();

  void on_Credit_clicked();

  void on_credit_calc_clicked();

  void on_deposit_calc_clicked();

  void on_ln_clicked();

  void on_log_clicked();

  void on_mod_clicked();

  void on_atan_clicked();

  void on_acos_clicked();

 private:
  Ui::MainWindow *ui;
  double xBegin, xEnd, h, X;
  int N;

  QVector<double> x, y;

  void readExpression(char *, const QString &);
};
#endif  // MAINWINDOW_H
