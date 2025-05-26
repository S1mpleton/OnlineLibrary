#include "orders.h"

Orders::Orders() :
    id{0}
{}


ParametersRequest Orders::get_parametrs_request() const{
    ParametersRequest values;

    if (id){
        values.insert(":id", id);
    }
    values.insert(":user_id", user.get_id());
    values.insert(":book_id", book.get_id());
    values.insert(":date_receipt", date_receipt.toString("yyyy-MM-dd"));
    values.insert(":days_rent", days_rent);
    values.insert(":is_accept", is_accept);

    return values;
}

Users Orders::get_user() const{
    return this->user;
}

Book Orders::get_book() const{
    return this->book;
}

QDate Orders::get_date_receipt() const{
    return this->date_receipt;
}

size_t Orders::get_days_rent() const{
    return this->days_rent;
}

size_t Orders::get_id() const{
    return this->id;
}

bool Orders::isAccept() const{
    return this->is_accept;
}



void Orders::set_user(Users user){
    this->user = user;
}

void Orders::set_book(Book book){
    this->book = book;
}

void Orders::set_date_receipt(QDate date){
    this->date_receipt = date;
}

void Orders::set_days_rent(size_t days_rent){
    this->days_rent = days_rent;
}

void Orders::set_id(size_t id){
    this->id = id;
}

void Orders::set_accept(bool is_accept){
    this->is_accept = is_accept;
}






