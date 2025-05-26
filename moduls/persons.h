#ifndef PERSONS_H
#define PERSONS_H

#include "database/databasecore.h"

#include <QString>

class Persons
{
public:
    Persons();
    Persons(QString surname, QString name, QString patronymic = "", size_t id = 0);

    ParametersRequest get_parametrs_request() const;

    void set_surname(QString surname);
    void set_name(QString name);
    void set_patronymic(QString patronymic);
    void set_id(size_t id);

    QString get_surname() const;
    QString get_name() const;
    QString get_patronymic() const;
    int get_id() const;

    bool operator==(const Persons& other) const;
    bool operator!=(const Persons& other) const;
    operator QString() const;

protected:
    size_t id;
    QString surname;
    QString name;
    QString patronymic;

};

#endif // PERSONS_H
