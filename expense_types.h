#ifndef EXPENSE_TYPES_H
#define EXPENSE_TYPES_H

#include "expense.h"

class Shopping : public Expense {
public:
    Shopping(const QDate &date, double amount);
    QString getDetails() const;
    QString additionalInfo() override;
};

class Bills : public Expense {
public:
    Bills(const QDate &date, double amount);
    double applyDiscount(double percentage);
    QString additionalInfo() override;
};

class Transport : public Expense {
public:
    Transport(const QDate &date, double amount);
    double calculateMileageCost(double mileage, double costPerMile);
    QString additionalInfo() override;
};

#endif // EXPENSE_TYPES_H
