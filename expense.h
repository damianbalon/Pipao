#ifndef EXPENSE_H
#define EXPENSE_H

#include <QString>
#include <QDate>

class Expense {
public:
    Expense(const QDate &date, double amount);
    virtual ~Expense() = default;

    QDate getDate() const;
    double getAmount() const;
    virtual QString additionalInfo() = 0;

private:
    QDate date;
    double amount;
};

#endif // EXPENSE_H
