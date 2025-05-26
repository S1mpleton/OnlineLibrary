#include "authors.h"

Authors::Authors() :
    Persons()
{}

Authors::Authors(QString surname, QString name, QString patronymic, size_t id) :
    Persons(surname, name, patronymic, id)
{}



BookAuthors::BookAuthors() {}

void BookAuthors::add_author(Authors author){
    authors.append(author);
}

void BookAuthors::remove_author(Authors author){
    authors.removeOne(author);
}

void BookAuthors::set_authors(QList<Authors> authors){
    this->authors = authors;
}


QList<Authors>& BookAuthors::at_authors(){
    return this->authors;
}

QList<Authors> BookAuthors::get_authors() const{
    return this->authors;
}


BookAuthors::operator QString() const {
    QString str = "";
    for (const Authors &author : authors) {
        str.append(author);
        str.append(";\n");
    }
    str.removeLast();
    str.removeLast();
    return str;
}



