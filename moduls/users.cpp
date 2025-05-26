#include "users.h"

Users::Users() :
    Persons(),
    address{""},
    phone{""},
    hash_password{""},
    role{Users::Role::NONE_ROLE}
{}

Users::Users(
    QString surname,
    QString name,
    QString patronymic,
    QString address,
    QString phone,
    QString hash_password,
    QString role,
    size_t points,
    size_t id
) :
    Persons(surname, name, patronymic, id),
    address{address},
    phone{phone},
    hash_password{hash_password},
    points{points}
{
    this->set_role(role);
}


void Users::set_hash_password(QString hash_password){
    this->hash_password = hash_password;
}

void Users::set_address(QString adderss){
    this->address = adderss;
}

void Users::set_phone(QString phone){
    this->phone = phone;
}

void Users::set_role(QString role){
    if (role == "Пользователь"){
        this->role = Users::Role::User;
    }
    else if (role == "Администратор") {
        this->role = Users::Role::Administrator;
    }
    else if (role == "Библиотекарь") {
        this->role = Users::Role::Librarian;
    }
    else{
        throw "Пользователь имеет некорректный статус";
    }
}

void Users::set_points(size_t points){
    this->points = points;
}




QString Users::get_hash_password() const{
    return this->hash_password;
}

QString Users::get_address() const{
    return this->address;
}

QString Users::get_phone() const{
    return this->phone;
}

bool Users::check_role(Users::Role role) const{
    return this->role == role;
}

QString Users::get_role() const{
    switch (this->role){
        case Users::Role::User:
            return "Пользователь";

        case Users::Role::Administrator:
            return "Администратор";

        case Users::Role::Librarian:
            return "Библиотекарь";

        case Users::Role::NONE_ROLE:
            return "";
    }
}

size_t Users::get_points() const{
    return this->points;
}



ParametersRequest Users::get_parametrs_request() const{
    ParametersRequest values = Persons::get_parametrs_request();

    values.insert(":address", address);
    values.insert(":phone", phone);
    values.insert(":hash_password", hash_password);
    values.insert(":role", this->get_role());
    values.insert(":points", points);

    return values;
}











