#ifndef INCOME_TYPES_H
#define INCOME_TYPES_H

#include "income.h"

class Salary : public Income {
public:
    Salary(const QDate &date, double amount);
    double calculateAnnualSalary() const;
    QString additionalInfo()  override;
};

class Bonus : public Income {
public:
    Bonus(const QDate &date, double amount);
    double addBonus(double additionalAmount);
    QString additionalInfo()  override;
};

class Interest : public Income {
public:
    Interest(const QDate &date, double amount);
    double applyInterestRate(double rate, int months);
    QString additionalInfo() override;
};

#endif // INCOME_TYPES_H
