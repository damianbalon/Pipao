#ifndef INCOME_TYPES_H
#define INCOME_TYPES_H

#include "income.h"

class Salary : public Income {
public:
    Salary(const QDate &date, double amount) : Income(date, amount) {}
};

class Bonus : public Income {
public:
    Bonus(const QDate &date, double amount) : Income(date, amount) {}
};

class Interest : public Income {
public:
    Interest(const QDate &date, double amount) : Income(date, amount) {}
};

#endif // INCOME_TYPES_H
