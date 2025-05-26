#include "persons.h"

Persons::Persons() :
    id{0}, surname{""}, name{""}, patronymic{""}
{}

Persons::Persons(QString surname, QString name, QString patronymic, size_t id) :
    id{id}, surname{surname}, name{name}, patronymic{patronymic}
{}

void Persons::set_surname(QString surname){
    this->surname = surname;
}

void Persons::set_name(QString name){
    this->name = name;
}

void Persons::set_patronymic(QString patronymic){
    this->patronymic = patronymic;
}

void Persons::set_id(size_t id){
    this->id = id;
}



QString Persons::get_surname() const{
    return this->surname;
}

QString Persons::get_name() const{
    return this->name;
}

QString Persons::get_patronymic() const{
    return this->patronymic;
}

int Persons::get_id() const{
    return this->id;
}

bool Persons::operator==(const Persons& other) const{
    return (other.get_id() == this->get_id());
}

bool Persons::operator!=(const Persons& other) const{
    return !(*this == other);
}

Persons::operator QString() const {
    QString short_name = "";

    short_name.append(this->get_name().at(0).toUpper() + '.' + ' ');

    if (not this->get_patronymic().isEmpty()){
        short_name.append(this->get_patronymic().at(0).toUpper() + '.' + ' ');
    }

    short_name.append(this->get_surname());

    return short_name;
}


ParametersRequest Persons::get_parametrs_request() const{
    ParametersRequest values;

    if (id){
        values.insert(":id", id);
    }
    values.insert(":surname", surname);
    values.insert(":name", name);
    values.insert(":patronymic", patronymic);

    return values;
}

