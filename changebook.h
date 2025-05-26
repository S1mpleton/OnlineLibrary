#ifndef CHANGEBOOK_H
#define CHANGEBOOK_H


#include "moduls/bookmanager.h"
#include "selectauthorsdialog.h"

#include <QDialog>

namespace Ui {
class ChangeBook;
}

class ChangeBook : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeBook(QWidget *parent = nullptr);
    ~ChangeBook();

signals:
    void sendAuthors(const BookAuthors &authors);

public slots:
    void setBook(const Book &book);

private slots:
    void on_ChangeAuthorsBook_clicked();
    void updateAuthorsLabel(const QString &upd_str);
    void setAuthors(const BookAuthors &authors);
    void updateGenresBox();
    void selectGanre(const int &index);


    void on_savePushButton_clicked();

private:
    SelectAuthorsDialog *authors_win;
    Ui::ChangeBook *ui;

    BookManager *book_manager;
    Book book;
};

#endif // CHANGEBOOK_H
