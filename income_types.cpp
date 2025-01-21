#include "income_types.h"

Salary::Salary(const QDate &date, double amount)
    : Income(date, amount) {}

double Salary::calculateAnnualSalary() const {
    return getAmount() * 12;
}

QString Salary::additionalInfo()  {

    QString s = QString::number(calculateAnnualSalary());
    return "Salary in a year : " + s;
}

Bonus::Bonus(const QDate &date, double amount)
    : Income(date, amount) {}

double Bonus::addBonus(double additionalAmount) {
    double newAmount = getAmount() + additionalAmount;
    return newAmount;
}

QString Bonus::additionalInfo()  {

    QString s = QString::number(addBonus(100));
    return "Bonus: Extra payment based on performance or time of year. " + s;
}

Interest::Interest(const QDate &date, double amount)
    : Income(date, amount) {}

double Interest::applyInterestRate(double rate, int months) {
    double newAmount = getAmount();
    for (int i = 0; i < months; ++i) {
        newAmount += newAmount * rate / 100;
    }
    return newAmount;
}

QString Interest::additionalInfo()  {

    QString s = QString::number(applyInterestRate(10, 1));

    return "Interest: Earnings from investments or savings. " + s;
}
