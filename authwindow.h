#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include "auth/authentications.h"
#include "moduls/bookmanager.h"
#include <QDialog>

namespace Ui {
class AuthWindow;
}

class AuthWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AuthWindow(QWidget *parent = nullptr);
    ~AuthWindow();

signals:
    void loginUser();

private slots:
    void on_toRegPushButton_clicked();

    void on_toLoginPushButton_clicked();

    void on_acceptPushButton_clicked();

private:
    bool isRegistration;
    Authentications *auth;
    BookManager *book_manager;
    Ui::AuthWindow *ui;
};

#endif // AUTHWINDOW_H
