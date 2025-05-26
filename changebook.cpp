#include "changebook.h"
#include "qabstractitemview.h"
#include "ui_changebook.h"

#include <QMessageBox>

ChangeBook::ChangeBook(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChangeBook)
{
    book_manager = new BookManager();

    ui->setupUi(this);
    ui->ChangeDeposit->setMaximum(10000);
    ui->ChangeRentCost->setMaximum(10000);
    ui->quantityBookSpinBox->setMaximum(10000);

    ui->genresComboBox->setMaxVisibleItems(8);
    ui->genresComboBox->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->genresComboBox->view()->setWindowFlags( Qt::NoDropShadowWindowHint);

    authors_win = new SelectAuthorsDialog(this);


    connect(authors_win, SIGNAL(change_authors(QString)), this, SLOT(updateAuthorsLabel(QString)));
    connect(this, SIGNAL(sendAuthors(BookAuthors)), authors_win, SLOT(getAuthors(BookAuthors)));
    connect(authors_win, SIGNAL(sendAuthors(BookAuthors)), this, SLOT(setAuthors(BookAuthors)));
    connect(ui->genresComboBox, SIGNAL(activated(int)), this, SLOT(selectGanre(int)));
}

ChangeBook::~ChangeBook()
{
    delete authors_win;
    delete book_manager;
    delete ui;
}

void ChangeBook::on_ChangeAuthorsBook_clicked()
{
    emit sendAuthors(book.get_authors());

    authors_win->setModal(true);
    authors_win->exec();

    updateAuthorsLabel(book.get_authors());
}


void ChangeBook::updateAuthorsLabel(const QString &upd_str){
    if (upd_str.isEmpty()){
        ui->labelAuthor->setText("Нет авторов");
    }
    else{
        ui->labelAuthor->setText(upd_str);
    }
}

void ChangeBook::setAuthors(const BookAuthors &authors){
    book.set_authors(authors);
}

void ChangeBook::updateGenresBox(){
    BookGenres genres = book_manager->get_all_genres();
    ui->genresComboBox->clear();
    ui->genresComboBox->addItem("Изменить");

    for (Genres genre : genres.get_genres()){
        if (book.get_genres().get_genres().contains(genre)){
            ui->genresComboBox->addItem("✔ " + genre.get_name(), QVariant::fromValue(genre));
        }
        else{
            ui->genresComboBox->addItem(genre.get_name(), QVariant::fromValue(genre));
        }
    }

    if (book.get_genres().get_genres().empty()){
        ui->labelGenres->setText("Нет жанров");
    }
    else{
        ui->labelGenres->setText(book.get_genres());
    }
}

void ChangeBook::selectGanre(const int &index){
    if (index > 0) {
        Genres ganre = ui->genresComboBox->currentData().value<Genres>();
        if (book.get_genres().get_genres().contains(ganre)){
            book.at_genres().remove_genre(ganre);
        }
        else{
            book.at_genres().add_ganre(ganre);
        }
    }

    ui->genresComboBox->setCurrentIndex(0);
    updateGenresBox();
}

void ChangeBook::setBook(const Book &book){
    this->book = book;

    ui->EditTitle->setText(book.get_title());
    ui->EditDescription->setText(book.get_description());

    ui->ChangeDeposit->setValue(book.get_security_deposit());
    ui->ChangeRentCost->setValue(book.get_rental_cost_day());
    updateAuthorsLabel(this->book.get_authors());

    emit sendAuthors(book.get_authors());
    updateGenresBox();
}

void ChangeBook::on_savePushButton_clicked()
{
    book.set_description(ui->EditDescription->toPlainText());
    book.set_title(ui->EditTitle->text());
    book.set_rental_cost_day(ui->ChangeRentCost->value());
    book.set_security_deposit(ui->ChangeDeposit->value());
    book.set_quantity(ui->quantityBookSpinBox->value());


    if (ui->EditTitle->text().isEmpty()){
        QMessageBox::warning(this, "Внимание", "Название книги должно быть заполнено!");
        return;
    }
    if (ui->EditDescription->toPlainText().isEmpty()){
        QMessageBox::warning(this, "Внимание", "Описание должно присутствовать!");
        return;
    }

    if (book.get_id()){
        book_manager->update_book(book);
        QMessageBox::information(this, "Изменения", "Изменения были успешно внесены");

    }
    else{
        book_manager->add_book(book);
        QMessageBox::information(this, "Сохранение", "Книга была успешно добавлена");
    }
    this->close();
}



