#ifndef AUTHENTICATIONS_H
#define AUTHENTICATIONS_H

#include "moduls/bookmanager.h"
#include <QObject>

class Authentications : public QObject
{
    Q_OBJECT

private:
    explicit Authentications(QObject *parent = nullptr);

    Authentications(const Authentications&) = delete;
    Authentications& operator=(const Authentications&) = delete;


public:
    ~Authentications();

    static Authentications& getAuthentication();

    static void destroyAuthentications();

signals:
    void login();
    void logout();


public slots:
    bool logout_user();
    bool authentications_user(QString phone, QString password);
    bool registration_user(Users user);

    const Users get_user() const;

private:
    static Authentications* authentication;
    Users user;
    BookManager *book_manager;

};

#endif // AUTHENTICATIONS_H
