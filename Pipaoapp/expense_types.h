#ifndef EXPENSE_TYPES_H
#define EXPENSE_TYPES_H

#include "expense.h"

class Shopping : public Expense {
public:
    Shopping(const QDate &date, double amount) : Expense(date, amount) {}
};

class Bills : public Expense {
public:
    Bills(const QDate &date, double amount) : Expense(date, amount) {}
};

class Transport : public Expense {
public:
    Transport(const QDate &date, double amount) : Expense(date, amount) {}
};

#endif // EXPENSE_TYPES_H
