#include "genres.h"


Genres::Genres(size_t id, QString name) :
    id{id}, name{name}
{
}

Genres::Genres() :
    id{0}
{
}

void Genres::set_id(size_t id){
    this->id = id;
}

void Genres::set_name(QString name){
    this->name = name;
}

size_t Genres::get_id() const{
    return this->id;
}

QString Genres::get_name() const{
    return this->name;
}

ParametersRequest Genres::get_parametrs_request() const{
    ParametersRequest values;

    if (id){
        values.insert(":id", id);
    }
    values.insert(":name", name);

    return values;
}

bool Genres::operator==(const Genres& other) const{
    return (other.get_id() == this->get_id());
}

bool Genres::operator!=(const Genres& other) const{
    return !(*this == other);
}







BookGenres::BookGenres() {}

void BookGenres::add_ganre(Genres genre){
    ganres.append(genre);
}

void BookGenres::remove_genre(const Genres &genre){
    ganres.removeOne(genre);
}

QList<Genres> BookGenres::get_genres() const{
    return this->ganres;
}

BookGenres::operator QString() const {
    QString str = "";
    for (const Genres &genre : ganres) {
        str.append(genre.get_name());
        str.append(";\n");
    }
    str.removeLast();
    str.removeLast();
    return str;
}

