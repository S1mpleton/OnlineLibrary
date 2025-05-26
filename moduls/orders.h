#ifndef ORDERS_H
#define ORDERS_H

#include "moduls/book.h"
#include "moduls/users.h"

#include <QDate>

class Orders
{
public:
    Orders();

    ParametersRequest get_parametrs_request() const;

    Users get_user() const;
    Book get_book() const;
    QDate get_date_receipt() const;
    size_t get_days_rent() const;
    size_t get_id() const;
    bool isAccept() const;

    void set_user(Users user);
    void set_book(Book book);
    void set_date_receipt(QDate date);
    void set_days_rent(size_t days_rent);
    void set_id(size_t id);
    void set_accept(bool is_accept);

private:
    Users user;
    Book book;
    QDate date_receipt;
    size_t days_rent;
    size_t id;
    bool is_accept;


};

#endif // ORDERS_H
