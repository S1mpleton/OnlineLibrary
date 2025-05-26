#include "authwindow.h"
#include "moduls/users.h"
#include "ui_authwindow.h"

#include <QMessageBox>

AuthWindow::AuthWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AuthWindow)
{
    isRegistration = true;
    auth = &Authentications::getAuthentication();
    book_manager = new BookManager();

    ui->setupUi(this);
    ui->toRegPushButton->hide();

    setWindowTitle("Регистрация");

}

AuthWindow::~AuthWindow()
{
    delete book_manager;
    delete ui;
}

void AuthWindow::on_toRegPushButton_clicked()
{
    ui->acceptPushButton->setText("Зарегистрироваться");
    setWindowTitle("Регистрация");
    isRegistration = true;
}


void AuthWindow::on_toLoginPushButton_clicked()
{
    setWindowTitle("Вход");
    ui->acceptPushButton->setText("Войти");
    isRegistration = false;
}



void AuthWindow::on_acceptPushButton_clicked()
{
    if (ui->phoneLineEdit->text().isEmpty()){
        QMessageBox::warning(this, "Введите ваш телефон", "Телефон не заполнен");
        return;
    }
    if (ui->passwordLineEdit->text().isEmpty()){
        QMessageBox::warning(this, "Введите ваш пароль", "Пароль не заполнен");
        return;
    }

    if (isRegistration){
        if (ui->nameLineEdit->text().isEmpty()){
            QMessageBox::warning(this, "Введите ваше имя", "Имя не заполнено");
            return;
        }
        if (ui->surnameLineEdit->text().isEmpty()){
            QMessageBox::warning(this, "Введите вашу фамилию", "Фамилия не заполнена");
            return;
        }
        if (ui->adressLineEdit->text().isEmpty()){
            QMessageBox::warning(this, "Введите ваш адрес", "Адрес не заполнен");
            return;
        }

        Users user(
            ui->surnameLineEdit->text(),
            ui->nameLineEdit->text(),
            ui->patlineEdit->text(),
            ui->adressLineEdit->text(),
            ui->phoneLineEdit->text(),
            ui->passwordLineEdit->text(),
            "Пользователь"
        );

        if (not auth->registration_user(user)){
            QMessageBox::warning(this, "Регистрация", "Этот телефон уже используется");
            return;
        }

        QMessageBox::information(this, "Регистрация", "Вы были успешно зарегистрированы");

    }
    else{

        if (not auth->authentications_user(ui->phoneLineEdit->text(), ui->passwordLineEdit->text())){
            QMessageBox::warning(this, "Авторизация", "Неверны телефон или пароль");
            return;
        }
        QMessageBox::information(this, "Авторизация", "Вы были успешно авторизованы");
    }

    close();
}

