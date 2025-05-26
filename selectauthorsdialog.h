#ifndef SELECTAUTHORSDIALOG_H
#define SELECTAUTHORSDIALOG_H

#include "moduls/bookmanager.h"
#include <QDialog>

namespace Ui {
class SelectAuthorsDialog;
}

class SelectAuthorsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectAuthorsDialog(QWidget *parent = nullptr);
    ~SelectAuthorsDialog();


signals:
    void change_authors(QString lableText);
    void sendAuthors(const BookAuthors &authors);

private slots:
    void on_SearchAuthors_textChanged(const QString &search_str);
    void getAuthors(const BookAuthors &authors);


    void on_addAuthorPushButton_clicked();

    void on_removeAuthorPushButton_clicked();


    void on_updateAuthorsPushButton_clicked();

    void on_addNewPushButton_clicked();

private:
    BookAuthors new_authors;

    Ui::SelectAuthorsDialog *ui;
    BookManager *book_manager;
};

#endif // SELECTAUTHORSDIALOG_H
