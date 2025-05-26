
#ifndef AUTHORS_H
#define AUTHORS_H

#include "moduls/persons.h"

#include <QList>


class Authors : public Persons
{
public:
    Authors();
    Authors(QString surname, QString name, QString patronymic = "", size_t id = 0);
};


class BookAuthors
{
public:
    BookAuthors();

    void add_author(Authors author);
    void remove_author(Authors author);

    void set_authors(QList<Authors> authors);

    QList<Authors>& at_authors();
    QList<Authors> get_authors() const;

    operator QString() const;

private:
    QList<Authors> authors;
};

#endif // AUTHORS_H
