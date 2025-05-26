#include "selectauthorsdialog.h"
#include "ui_selectauthorsdialog.h"

#include <QSet>
#include <QAbstractItemView>
#include <QMessageBox>

SelectAuthorsDialog::SelectAuthorsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SelectAuthorsDialog)
{
    ui->setupUi(this);
    ui->SearchAuthors->setMaxLength(25);
    ui->authorsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->authorsTable->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->authorsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->authorsTable->setColumnWidth(4, 0);
    // ui->authorsTable->horizontalHeader()->hide();


    book_manager = new BookManager();

    connect(ui->SearchAuthors, &QLineEdit::textChanged, this, &SelectAuthorsDialog::on_SearchAuthors_textChanged);
}

SelectAuthorsDialog::~SelectAuthorsDialog()
{
    delete book_manager;
    delete ui;
}

void SelectAuthorsDialog::getAuthors(const BookAuthors &authors){
    this->new_authors.set_authors(authors.get_authors());
    on_SearchAuthors_textChanged("");
}


void SelectAuthorsDialog::on_SearchAuthors_textChanged(const QString &search_str)
{
    BookAuthors authors = book_manager->get_page_authors(Pagination(100, 1), search_str);

    ui->authorsTable->setRowCount(0);
    for (Authors author : authors.get_authors()) {
        int index = ui->authorsTable->rowCount();
        ui->authorsTable->insertRow(index);

        if (new_authors.get_authors().contains(author)){
            ui->authorsTable->setItem(index, 0, new QTableWidgetItem("✔"));
        }
        else{
            ui->authorsTable->setItem(index, 0, new QTableWidgetItem(""));

        }
        ui->authorsTable->setItem(index, 1, new QTableWidgetItem(author.get_surname()));
        ui->authorsTable->setItem(index, 2, new QTableWidgetItem(author.get_name()));
        ui->authorsTable->setItem(index, 3, new QTableWidgetItem(author.get_patronymic()));
        ui->authorsTable->setItem(index, 4, new QTableWidgetItem(QString::number(author.get_id())));
    }
    // emit change_authors(new_authors);
}


void SelectAuthorsDialog::on_addAuthorPushButton_clicked()
{
    QList<QTableWidgetItem*> selectedItems = ui->authorsTable->selectedItems();

    for (int i = 4; i < selectedItems.count(); i += 5){
        if (selectedItems.at(i-4)->text().isEmpty()){
            Authors author = book_manager->get_author_by_id(selectedItems.at(i)->text().toInt());
            new_authors.add_author(author);
        }
    }
    on_SearchAuthors_textChanged(ui->SearchAuthors->text());
}


void SelectAuthorsDialog::on_removeAuthorPushButton_clicked()
{
    Authors tmp_authors;

    QList<QTableWidgetItem*> selectedItems = ui->authorsTable->selectedItems();

    for (int i = 4; i < selectedItems.count(); i += 5){
        if (not selectedItems.at(i-4)->text().isEmpty()){
            Authors author = book_manager->get_author_by_id(selectedItems.at(i)->text().toInt());
            new_authors.remove_author(author);
        }
    }

    on_SearchAuthors_textChanged(ui->SearchAuthors->text());
}




void SelectAuthorsDialog::on_updateAuthorsPushButton_clicked()
{
    emit sendAuthors(new_authors);
    close();
}


void SelectAuthorsDialog::on_addNewPushButton_clicked()
{
    QMessageBox::information(this, "В разработке", "В разработке");
}

