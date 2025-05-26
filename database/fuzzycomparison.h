#ifndef FUZZYCOMPARISON_H
#define FUZZYCOMPARISON_H

#include <QObject>
#include <QDebug>

class FuzzyComparison: public QObject
{
    Q_OBJECT
public:
    explicit FuzzyComparison(QObject *parent = nullptr);
    ~FuzzyComparison();

    float static comparison_without_capitals(const QString &s1, const QString &s2);

private:
    float static result_by_percentage(int max_len, int distance);

signals:
};

#endif // FUZZYCOMPARISON_H
