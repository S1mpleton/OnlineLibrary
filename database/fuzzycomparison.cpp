#include "fuzzycomparison.h"
#include "qsqldriver.h"


#include <QSqlDatabase>
#include <QVariant>
// #include <QSQLiteDriver>

FuzzyComparison::FuzzyComparison(QObject *parent)
    : QObject{parent}
{}

FuzzyComparison::~FuzzyComparison()
{}

float FuzzyComparison::comparison_without_capitals(const QString &s1, const QString &s2){
    const QString s1_l = s1.toLower();
    const QString s2_l = s2.toLower();

    int len1 = s1_l.length();
    int len2 = s2_l.length();

    QVector<QVector<int>> distance_matrix(len1 + 1, QVector<int>(len2 + 1));

    for (int i = 0; i <= len1; ++i)
        distance_matrix[i][0] = i;

    for (int j = 0; j <= len2; ++j)
        distance_matrix[0][j] = j;

    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            int cost = (s1_l[i - 1] == s2_l[j - 1]) ? 0 : 1;

            distance_matrix[i][j] = std::min(
                {
                    distance_matrix[i - 1][j] + 1,        // Удаление
                    distance_matrix[i][j - 1] + 1,        // Вставка
                    distance_matrix[i - 1][j - 1] + cost  // Замена
                }
            );
        }
    }

    return result_by_percentage(std::max(len1, len2), distance_matrix[len1][len2]);
}

float FuzzyComparison::result_by_percentage(int max_len, int distance){
    return ((max_len - distance) / (float)max_len) * 100;
}

// void registerLevenshteinSearch(QSqlDatabase &db) {
//     // Регистрация пользовательской функции
//     db.driver()->registerFunction("STRING_LENGTH", [](const QVariant &value) {
//         return value.toString().length();
//     });
// }
