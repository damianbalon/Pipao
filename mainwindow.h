#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include "income_types.h"
#include "expense_types.h"
#include "grafy.h"
#include "table.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addIncomeButton_clicked();
    void on_addExpenseButton_clicked();
    void on_graph_clicked();
    void on_viewTableButton_clicked();

    void on_usun_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    void check_sum();
    QString getSelectedIncomeCategory();
    QString getSelectedExpenseCategory();
    void ensureDatabaseTables();
};

#endif // MAINWINDOW_H
