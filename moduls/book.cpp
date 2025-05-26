#include "book.h"

Book::Book() :
    id{0}
{
}

Book::Book(
    QString title,
    QString description,
    size_t security_deposit,
    size_t rental_cost_day,
    size_t quantity,
    size_t id
) :
    id{id},
    title{title},
    description{description},
    security_deposit{security_deposit},
    rental_cost_day{rental_cost_day},
    quantity{quantity}
{

}


void Book::set_id(size_t id){
    this->id = id;
}

void Book::set_title(QString title){
    this->title = title;
}

void Book::set_description(QString description){
    this->description = description;
}

void Book::set_security_deposit(size_t security_deposit){
    this->security_deposit = security_deposit;
}

void Book::set_rental_cost_day(size_t rental_cost_day){
    this->rental_cost_day = rental_cost_day;
}

void Book::set_genres(BookGenres genres){
    this->genres = genres;
}

void Book::set_authors(BookAuthors authors){
    this->authors = authors;
}

void Book::set_quantity(size_t quantity){
    this->quantity = quantity;
}





BookGenres Book::get_genres() const{
    return this->genres;
}

BookGenres& Book::at_genres(){
    return this->genres;
}

size_t Book::get_id() const{
    return this->id;
}

QString Book::get_title() const{
    return this->title;
}

QString Book::get_description() const{
    return this->description;
}

size_t Book::get_security_deposit() const{
    return this->security_deposit;
}

size_t Book::get_rental_cost_day() const{
    return this->rental_cost_day;
}

size_t Book::get_quantity() const{
    return this->quantity;
}

BookAuthors Book::get_authors() const{
    return this->authors;
}

BookAuthors &Book::at_authors(){
    return this->authors;
}


ParametersRequest Book::get_parametrs_request() const{
    ParametersRequest values;

    if (id){
        values.insert(":id", id);
    }
    values.insert(":title", title);
    values.insert(":description", description);
    values.insert(":security_deposit", security_deposit);
    values.insert(":rental_cost_day", rental_cost_day);
    values.insert(":quantity", quantity);

    return values;
}
