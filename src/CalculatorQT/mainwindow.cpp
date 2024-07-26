#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  //    setFixedSize(430, 330);
  setContentsMargins(0, 0, 0, 0);
  resize(430, 330);
  //    setFixedWidth(430);
  //    setMinimumSize(430, 330);
  //
  connect(ui->inputExpression, &QLineEdit::returnPressed, this,
          &MainWindow::on_eqally_clicked);
  //    connect(ui->Graph, &QPushButton::clicked, this,
  //    &MainWindow::expandWindow); QValidator* validator = new
  //    QDoubleValidator(-1000000.0, 1000000.0, 7, this);
  //    ui->valueX->setValidator(validator);
  //    ui->XBegin->setValidator(validator);
  //    ui->XEnd->setValidator(validator);
}

MainWindow::~MainWindow() { delete ui; }

// void MainWindow::expandWindow()
//{
//     // Увеличение размера окна до заданных параметров
//     this->resize(800, 600);
// }

void MainWindow::on_pushButton_9_clicked() {
  //    ui->inputExpression->setText("9");
  // Получаем текущий текст из QLineEdit
  QString currentText = ui->inputExpression->text();

  // Добавляем "9" к текущему тексту
  currentText.append("9");

  // Устанавливаем обновленный текст в QLineEdit
  ui->inputExpression->setText(currentText);
}

void MainWindow::on_pushButton_8_clicked() {
  QString currentText = ui->inputExpression->text();
  currentText.append("8");
  ui->inputExpression->setText(currentText);
}

void MainWindow::on_pushButton_7_clicked() {
  QString currentText = ui->inputExpression->text();
  currentText.append("7");
  ui->inputExpression->setText(currentText);
}

void MainWindow::on_pushButton_6_clicked() {
  QString currentText = ui->inputExpression->text();
  currentText.append("6");
  ui->inputExpression->setText(currentText);
}

void MainWindow::on_pushButton_5_clicked() {
  QString currentText = ui->inputExpression->text();
  currentText.append("5");
  ui->inputExpression->setText(currentText);
}

void MainWindow::on_pushButton_4_clicked() {
  QString currentText = ui->inputExpression->text();
  currentText.append("4");
  ui->inputExpression->setText(currentText);
}

void MainWindow::on_pushButton_3_clicked() {
  QString currentText = ui->inputExpression->text();
  currentText.append("3");
  ui->inputExpression->setText(currentText);
}

void MainWindow::on_pushButton_2_clicked() {
  QString currentText = ui->inputExpression->text();
  currentText.append("2");
  ui->inputExpression->setText(currentText);
}

void MainWindow::on_pushButton_1_clicked() {
  QString currentText = ui->inputExpression->text();
  currentText.append("1");
  ui->inputExpression->setText(currentText);
}

void MainWindow::on_pushButton_10_clicked() {
  QString currentText = ui->inputExpression->text();
  currentText.append("0");
  ui->inputExpression->setText(currentText);
}

void MainWindow::on_point_clicked() {
  QString currentText = ui->inputExpression->text();
  currentText.append(".");
  ui->inputExpression->setText(currentText);
}

void MainWindow::on_plus_clicked() {
  QString currentText = ui->inputExpression->text();
  currentText.append("+");
  ui->inputExpression->setText(currentText);
}

void MainWindow::on_minus_clicked() {
  QString currentText = ui->inputExpression->text();
  currentText.append("-");
  ui->inputExpression->setText(currentText);
}

void MainWindow::on_openBracket_clicked() {
  QString currentText = ui->inputExpression->text();
  currentText.append("(");
  ui->inputExpression->setText(currentText);
}

void MainWindow::on_closeBracket_clicked() {
  QString currentText = ui->inputExpression->text();
  currentText.append(")");
  ui->inputExpression->setText(currentText);
}

void MainWindow::on_multiplication_clicked() {
  QString currentText = ui->inputExpression->text();
  currentText.append("*");
  ui->inputExpression->setText(currentText);
}

void MainWindow::on_division_clicked() {
  QString currentText = ui->inputExpression->text();
  currentText.append("/");
  ui->inputExpression->setText(currentText);
}

void MainWindow::on_sqrt_clicked() {
  QString currentText = ui->inputExpression->text();
  currentText.append("sqrt");
  ui->inputExpression->setText(currentText);
}

void MainWindow::on_sqr_clicked() {
  QString currentText = ui->inputExpression->text();
  currentText.append("^");
  ui->inputExpression->setText(currentText);
}

void MainWindow::on_sin_clicked() {
  QString currentText = ui->inputExpression->text();
  currentText.append("sin");
  ui->inputExpression->setText(currentText);
}

void MainWindow::on_cos_clicked() {
  QString currentText = ui->inputExpression->text();
  currentText.append("cos");
  ui->inputExpression->setText(currentText);
}

void MainWindow::on_tan_clicked() {
  QString currentText = ui->inputExpression->text();
  currentText.append("tan");
  ui->inputExpression->setText(currentText);
}

void MainWindow::on_asin_clicked() {
  QString currentText = ui->inputExpression->text();
  currentText.append("asin");
  ui->inputExpression->setText(currentText);
}

void MainWindow::readExpression(char* expression,
                                const QString& stringExpression) {
  int i;
  for (i = 0; i < stringExpression.size(); i++) {
    expression[i] = static_cast<char>(stringExpression.at(i).unicode());
  }
  expression[i] = '\0';
}

void MainWindow::on_eqally_clicked() {
  char expression[MAX_STACK_SIZE];

  QString inputExpression = ui->inputExpression->text();

  readExpression(expression, inputExpression);
  double value_x = ui->valueX->value();
  //    QString inputX = ui->->text();
  //    if (inputX == "") {
  //        inputX = "0";
  //    }, value_x[MAX_STACK_SIZE]
  //    readExpression(value_x, inputX);
  double num = 0;
  int execution_result =
      calculation_reverse_polish_notation(expression, value_x, &num);
  if (execution_result == 1) {
    QString result = QString::number(static_cast<double>(num));
    ui->inputExpression->setText(result);
    ui->expressionLabel->setText(inputExpression);
    // ui->valueX->clear();
  } else {
    if (execution_result == 2)
      ui->expressionLabel->setText("Ошибка в выражение");
    if (execution_result == 3) ui->expressionLabel->setText("Деление на ноль");
    if (execution_result == 4) ui->expressionLabel->setText("4");
    ui->inputExpression->setText(inputExpression);
  }
  ui->valueX->setValue(0.0);
  //    ui->inputExpression->setText("result");
}

// void MainWindow::onEnterPressed() {
//     MainWindow::on_eqally_clicked();
// }

void MainWindow::on_deleteChar_clicked() {
  QString text = ui->inputExpression->text();
  text.chop(1);
  ui->inputExpression->setText(text);
}

void MainWindow::on_deleteAll_clicked() {
  QString text = ui->inputExpression->text();
  text.clear();
  ui->inputExpression->setText(text);
  ui->valueX->clear();
}

void MainWindow::on_X__clicked() {
  QString currentText = ui->inputExpression->text();
  currentText.append("x");
  ui->inputExpression->setText(currentText);
}

void MainWindow::on_Graph_clicked() {
  if (width() == 430 || height() == 800) {
    resize(800, 330);
  } else {
    resize(430, 330);
  }
}

void MainWindow::on_BuildGraph_clicked() {
  char expression[MAX_STACK_SIZE];
  ui->widget->clearGraphs();
  x.clear();
  y.clear();

  QString inputExpression = ui->inputExpression->text();
  ui->expressionLabel->setText(inputExpression);
  readExpression(expression, inputExpression);

  h = 0.1;
  //    QString strXBegin = ui->XBegin->text();
  //    xBegin = strXBegin.toDouble();
  //    QString strXEnd = ui->XEnd->text();
  //    xEnd = strXEnd.toDouble();

  if (ui->XBegin->value() < ui->XEnd->value()) {
    xBegin = ui->XBegin->value();
    xEnd = ui->XEnd->value();
  } else {
    xBegin = ui->XEnd->value();
    xEnd = ui->XBegin->value();
  }

  ui->widget->xAxis->setRange(xBegin, xEnd);
  //

  N = (xEnd - xBegin) / h + 2;
  double yBegin = -1, yEnd = 1;
  for (X = xBegin; X <= xEnd; X += h) {
    x.push_back(X);
    //        char buffer[20];
    //        sprintf(buffer, "%.7f", X);
    double result = 0;
    calculation_reverse_polish_notation(expression, X, &result);
    y.push_back(result);
    if (result < yBegin) {
      yBegin = result;
    } else if (result > yEnd) {
      yEnd = result;
    }
  }
  ui->widget->yAxis->setRange(std::round(yEnd) + 1, std::round(yBegin) - 1);
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
}

void MainWindow::on_Credit_clicked() {
  if ((width() == 430 || width() == 800) && height() == 330) {
    resize(430, 800);
  } else {
    resize(430, 330);
    ui->deposit_accr_persent->setText("");

    ui->deposit_plus_persent->setText("");
    ui->credit_monthly_payment->setText("");

    ui->total_credit->setText("");

    ui->credit_accr_percent->setText("");
  }
  //    resize(430, 330); || height() == 800)
  //    scroll(0, -290);
  //    update();
  //    repaint();
}

void MainWindow::on_credit_calc_clicked() {
  resize(800, 800);
  double year = ui->credit_term->value();
  double term = convert_years_to_months(year);
  double loan_amount = ui->credit_summ->value();
  double percent = ui->credit_percent->value();

  if (ui->annu->isChecked()) {
    double annuity = get_monthly_payment_annuity(loan_amount, percent, term);
    double total_payment = get_total_payment_annuity(annuity, term);
    double over_payment = get_overpayment_on_credit(loan_amount, total_payment);
    QString result_annuity = QString::number((annuity));
    ui->credit_monthly_payment->setText(result_annuity);
    QString result_total_payment = QString::number((total_payment));
    ui->total_credit->setText(result_total_payment);
    QString result_over_payment = QString::number((over_payment));
    ui->credit_accr_percent->setText(result_over_payment);
  } else if (ui->diff->isChecked()) {
    double first_pay = 0, last_pay = 0;
    double total_payment = get_total_payment_diff(loan_amount, term, percent,
                                                  &first_pay, &last_pay);
    double over_payment = get_overpayment_on_credit(loan_amount, total_payment);
    QString result_first_pay = QString::number((first_pay));
    QString result_last_pay = QString::number((last_pay));
    QString result;
    result.append(result_first_pay + " ... " + result_last_pay);
    ui->credit_monthly_payment->setText(result);
    //        QString result_total_payment = QString::number(( total_payment));
    ui->total_credit->setText(QString::number(total_payment));
    QString result_over_payment = QString::number((over_payment));
    ui->credit_accr_percent->setText(result_over_payment);
  }
}

void MainWindow::on_deposit_calc_clicked() {
  resize(800, 800);
  double year = ui->deposit_term->value();
  double loan_amount = ui->deposit_summ->value();
  double percent = ui->deposit_percent->value();
  int capit;
  if (ui->checkBox->isChecked()) {
    capit = 1;
  } else {
    capit = 0;
  }
  double repl = ui->deposit_repl->value();
  double with = ui->deposit_with->value();
  double period = ui->deposit_period->value();

  double total_interest =
      calc_total(loan_amount, year, percent, period, capit, repl, with);
  double end_balance =
      calc_total_deposit(total_interest, loan_amount, year, repl, with);
  QString result_total_interest = QString::number((total_interest));
  ui->deposit_accr_persent->setText(result_total_interest);
  QString result_end_balance = QString::number((end_balance));
  ui->deposit_plus_persent->setText(result_end_balance);
}

void MainWindow::on_ln_clicked() {
  QString currentText = ui->inputExpression->text();
  currentText.append("ln");
  ui->inputExpression->setText(currentText);
}

void MainWindow::on_log_clicked()
{
  QString currentText = ui->inputExpression->text();
  currentText.append("log");
  ui->inputExpression->setText(currentText);
}


void MainWindow::on_mod_clicked()
{
  QString currentText = ui->inputExpression->text();
  currentText.append("mod");
  ui->inputExpression->setText(currentText);
}


void MainWindow::on_atan_clicked()
{
  QString currentText = ui->inputExpression->text();
  currentText.append("atan");
  ui->inputExpression->setText(currentText);
}



void MainWindow::on_acos_clicked()
{
  QString currentText = ui->inputExpression->text();
  currentText.append("acos");
  ui->inputExpression->setText(currentText);
}

