#include "expense.h"

Expense::Expense(const QDate &date, double amount)
    : date(date), amount(amount) {}

QDate Expense::getDate() const {
    return date;
}

double Expense::getAmount() const {
    return amount;
}
