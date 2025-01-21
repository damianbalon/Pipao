#ifndef INCOME_H
#define INCOME_H

#include <QString>
#include <QDate>

class Income {
public:
    Income(const QDate &date, double amount);
    virtual ~Income() = default;

    QDate getDate() const;
    double getAmount() const;
    virtual QString additionalInfo() = 0;

private:
    QDate date;
    double amount;
};

#endif // INCOME_H
