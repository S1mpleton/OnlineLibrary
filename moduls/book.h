#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include "database/databasecore.h"
#include "moduls/genres.h"
#include "moduls/authors.h"

class Book
{
public:
    Book();
    Book(
        QString title,
        QString description,
        size_t security_deposit,
        size_t rental_cost_day,
        size_t quantity,
        size_t id = 0
    );

    ParametersRequest get_parametrs_request() const;

    void set_id(size_t id);
    void set_title(QString title);
    void set_description(QString description);
    void set_security_deposit(size_t security_deposit);
    void set_rental_cost_day(size_t rental_cost_day);
    void set_genres(BookGenres genres);
    void set_authors(BookAuthors authors);
    void set_quantity(size_t quantity);


    size_t get_id() const;
    QString get_title() const;
    QString get_description() const;
    size_t get_security_deposit() const;
    size_t get_rental_cost_day() const;
    size_t get_quantity() const;
    BookGenres get_genres() const;
    BookGenres& at_genres();
    BookAuthors get_authors() const;
    BookAuthors& at_authors();

private:
    size_t id;
    QString title;
    QString description;
    size_t security_deposit;
    size_t rental_cost_day;
    size_t quantity;

    BookGenres genres;
    BookAuthors authors;

};

#endif // BOOK_H
