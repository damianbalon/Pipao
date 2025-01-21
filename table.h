#ifndef TABLE_H
#define TABLE_H

#include <QDialog>
#include <QTableWidget>
#include <QSqlQuery>
#include "income.h"
#include "expense.h"

namespace Ui {
class Table;
}

class Table : public QDialog {
    Q_OBJECT

public:
    explicit Table(QWidget *parent = nullptr);
    ~Table();

private:
    Ui::Table *ui;
    void setupTable(); // Konfiguracja tabeli
    Income* createIncome(const QDate &date, double amount, const QString &category);
    Expense* createExpense(const QDate &date, double amount, const QString &category);
};

#endif // TABLE_H
