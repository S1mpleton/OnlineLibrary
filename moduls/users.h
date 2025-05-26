#ifndef USERS_H
#define USERS_H

#include "moduls/persons.h"


class Users : public Persons
{
public:
    Users();
    Users(
        QString surname,
        QString name,
        QString patronymic,
        QString address,
        QString phone,
        QString hash_password,
        QString role,
        size_t points = 0,
        size_t id = 0
    );

    void set_hash_password(QString hash_password);
    void set_address(QString address);
    void set_phone(QString phone);
    void set_role(QString role);
    void set_points(size_t points);

    QString get_hash_password() const;
    QString get_address() const;
    QString get_phone() const;
    QString get_role() const;
    size_t get_points() const;

    enum Role {
        Administrator, Librarian, User, NONE_ROLE
    };



    bool check_role(Users::Role role) const;
    ParametersRequest get_parametrs_request() const;


private:
    QString address;
    QString phone;
    QString hash_password;
    Role role;
    size_t points;


};

#endif // USERS_H
