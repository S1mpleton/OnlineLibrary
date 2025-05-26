#ifndef GENRES_H
#define GENRES_H

#include "database/databasecore.h"

#include <QList>
#include <QString>


class Genres
{
public:
    Genres(size_t id, QString name);
    Genres();

    ParametersRequest get_parametrs_request() const;

    void set_id(size_t id);
    void set_name(QString name);

    size_t get_id() const;
    QString get_name() const;

    bool operator==(const Genres& other) const;
    bool operator!=(const Genres& other) const;

private:
    size_t id;
    QString name;
};


class BookGenres
{
public:
    BookGenres();

    void add_ganre(Genres genre);
    void remove_genre(const Genres &genre);

    QList<Genres> get_genres() const;


    operator QString() const;

private:
    QList<Genres> ganres;
};

#endif // GENRES_H
