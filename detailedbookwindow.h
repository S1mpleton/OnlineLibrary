#ifndef DETAILEDBOOKWINDOW_H
#define DETAILEDBOOKWINDOW_H

#include "moduls/book.h"
#include "moduls/bookmanager.h"
#include "auth/authentications.h"

#include <QDialog>

namespace Ui {
class DetailedBookWindow;
}

class DetailedBookWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DetailedBookWindow(QWidget *parent = nullptr);
    ~DetailedBookWindow();

public slots:
    void getBook(const Book &book);

    void loginUser();

    void logoutUser();

private slots:
    void on_changePushButton_clicked();

    void on_deleteBookPushButton_clicked();

    void updateCostForDays(int quantity_days);

    void on_takePushButton_clicked();

private:
    Authentications *auth;
    Book book;
    BookManager *book_manager;
    Ui::DetailedBookWindow *ui;
};

#endif // DETAILEDBOOKWINDOW_H
