#include "authentications.h"


Authentications* Authentications::authentication = nullptr;


Authentications::Authentications(QObject *parent)
    : QObject{parent}
{
    book_manager = new BookManager();
}

Authentications::~Authentications(){
    delete book_manager;
}



Authentications& Authentications::getAuthentication(){
    if (not authentication){
        Authentications::authentication = new Authentications();
    }
    return *Authentications::authentication;
}


void Authentications::destroyAuthentications(){

    if (Authentications::authentication){
        delete Authentications::authentication;
    }
    Authentications::authentication = nullptr;
}

bool Authentications::logout_user(){
    user = Users();
    emit logout();
    return true;
}

bool Authentications::authentications_user(QString phone, QString password){
    Users new_user = book_manager->get_user_by_phone(phone);

    if (not new_user.get_id()){
        return false;
    }

    if (not (new_user.get_hash_password() == password)){
        return false;
    }

    user = new_user;

    emit login();
    return true;
}

bool Authentications::registration_user(Users user){
    Users check_user = book_manager->get_user_by_phone(user.get_phone());
    if (check_user.get_id()){
        return false;
    }

    book_manager->add_user(user);
    Authentications::user = user;

    emit login();
    return true;
}


const Users Authentications::get_user() const{
    return Authentications::user;
}
