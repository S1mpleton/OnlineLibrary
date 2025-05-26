#include "authwindow.h"
#include "changebook.h"
#include "detailedbookwindow.h"
#include "ui_detailedbookwindow.h"

#include <QMessageBox>

DetailedBookWindow::DetailedBookWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DetailedBookWindow)
{
    book_manager = new BookManager();
    auth = &Authentications::getAuthentication();

    ui->setupUi(this);
    ui->deleteBookPushButton->hide();
    ui->changePushButton->hide();

    ui->quantityDays->setMinimum(1);

    connect(ui->quantityDays, SIGNAL(valueChanged(int)), this, SLOT(updateCostForDays(int)));
    connect(auth, SIGNAL(login()), this, SLOT(loginUser()));
    connect(auth, SIGNAL(logout()), this, SLOT(logoutUser()));
}

DetailedBookWindow::~DetailedBookWindow()
{
    delete book_manager;
    delete ui;
}



void DetailedBookWindow::getBook(const Book &book){
    this->book = book;

    ui->titleField->setText(book.get_title());
    ui->descriptionField->setText(book.get_description());
    ui->authorsField->setText(book.get_authors());
    ui->genresFeild->setText(book.get_genres());

    ui->depositLabel->setText(QString::number(book.get_security_deposit()));
    ui->rentalCostLabel->setText(QString::number(book.get_rental_cost_day()));

    ui->quantityDays->setValue(1);
    ui->labelCost->setText(QString::number(book.get_rental_cost_day()));

}

void DetailedBookWindow::loginUser(){
    if (auth->get_user().check_role(Users::Role::Administrator)){
        ui->deleteBookPushButton->show();
        ui->changePushButton->show();
    }
}

void DetailedBookWindow::logoutUser(){
    ui->deleteBookPushButton->hide();
    ui->changePushButton->hide();
}

void DetailedBookWindow::on_changePushButton_clicked()
{
    ChangeBook change_window;
    change_window.setBook(book);

    change_window.setModal(true);
    change_window.exec();

    getBook(book_manager->get_book_by_id(book.get_id()));
}


void DetailedBookWindow::on_deleteBookPushButton_clicked()
{
    QMessageBox::StandardButton but = QMessageBox::question(this, "Подтверждение", "Вы уверены, что хотите удалить книгу?");

    if (but == QMessageBox::Yes){
        book_manager->delete_book(book);
        QMessageBox::information(this, "Удаление", "Книга была удалена");
        this->close();
    }
}


void DetailedBookWindow::updateCostForDays(int quantity_days){
    int cost = quantity_days * book.get_rental_cost_day();
    ui->labelCost->setText(QString::number(cost));
}


void DetailedBookWindow::on_takePushButton_clicked()
{
    if (not auth->get_user().get_id()){
        AuthWindow auth_window;
        auth_window.setModal(true);
        auth_window.exec();
        return;
    }

    if (book_manager->add_order(auth->get_user(), book, ui->quantityDays->value())){
        QMessageBox::information(this, "Информация", "Книга была зарезервирована на 1 день.\nУспейте забрать ее в нашей библиотеке");
    }
    else{
        QMessageBox::warning(this, "Внимание", "Вы уже взяли эту книгу");
    }

}

