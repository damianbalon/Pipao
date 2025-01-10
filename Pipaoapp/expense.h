#ifndef EXPENSE_H
#define EXPENSE_H

#include <QString>
#include <QDate>

class Expense {
public:
    Expense(const QDate &date, double amount);

    QDate getDate() const;
    double getAmount() const;

private:
    QDate date;
    double amount;
};
#endif // EXPENSE_H
