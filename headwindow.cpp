#include "headwindow.h"
#include "authwindow.h"

#include "detailedbookwindow.h"
#include "listforrentwindow.h"
#include "changebook.h"
#include "ui_headwindow.h"

#include <QPixmap>
#include <QMainWindow>
#include <QMessageBox>




HeadWindow::HeadWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HeadWindow)
    , last_current_row{0}
{
    // genresSelected = new SelectedComboBox(this);
    auth = &Authentications::getAuthentication();
    book_manager = new BookManager();

    ui->setupUi(this);
    ui->SelectButtun->setEnabled(false);
    ui->lineSerchBook->setMaxLength(20);
    ui->LookGetBook->hide();
    ui->AddBook->hide();

    ui->tableBooks->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableBooks->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableBooks->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableBooks->setColumnHidden(5, true);

    ui->tableBooks->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    load_genres();
    detail_window = new DetailedBookWindow();

    QPixmap search_icon(":/img/resources/images/search-icon-32x32.png");
    QPixmap clean_icon(":/img/resources/images/restore-100x100.png");
    QPixmap genre_icon(":/img/resources/images/open-book-512x512.png");

    ui->icon_search->setPixmap(
        search_icon.scaled(
            ui->icon_search->width(),
            ui->icon_search->height(),
            Qt::KeepAspectRatio
        )
    );

    ui->cleanLabel->setPixmap(
        clean_icon.scaled(
            ui->cleanLabel->width(),
            ui->cleanLabel->height(),
            Qt::KeepAspectRatio
            )
        );

    ui->genreLabel->setPixmap(
        genre_icon.scaled(
            ui->genreLabel->width(),
            ui->genreLabel->height(),
            Qt::KeepAspectRatio
            )
        );



    connect(ui->lineSerchBook, &QLineEdit::textChanged, this, &HeadWindow::on_lineSerchBook_textChanged);
    connect(this, &HeadWindow::sendBook, detail_window, &DetailedBookWindow::getBook);
    connect(ui->login, SIGNAL(triggered()), this, SLOT(updateAuthUser()));
    connect(auth, SIGNAL(login()), this, SLOT(loginUser()));
    connect(auth, SIGNAL(logout()), this, SLOT(logoutUser()));
    connect(ui->tableBooks, SIGNAL(itemSelectionChanged()), this, SLOT(isSelected()));
    connect(ui->genresComboBox, SIGNAL(activated(int)), this, SLOT(selectGanre(int)));




    on_lineSerchBook_textChanged("");
}

HeadWindow::~HeadWindow()
{
    auth->destroyAuthentications();
    delete book_manager;
    delete ui;
    delete detail_window;
}


void HeadWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
}

void HeadWindow::on_lineSerchBook_textChanged(const QString &search_string){
    ui->tableBooks->clearContents();
    ui->tableBooks->setRowCount(0);

    QList<Book> books = book_manager->get_page_books(
        Pagination(100, 1),
        search_string,
        ui->genresComboBox->currentData().value<BookGenres>()
    );

    for (Book book : books) {
        int index = ui->tableBooks->rowCount();
        ui->tableBooks->insertRow(index);

        ui->tableBooks->setItem(index, 0, new QTableWidgetItem(book.get_title()));
        ui->tableBooks->setItem(index, 1, new QTableWidgetItem(book.get_authors()));
        ui->tableBooks->setItem(index, 2, new QTableWidgetItem(book.get_genres()));
        ui->tableBooks->setItem(index, 3, new QTableWidgetItem(QString::number(book.get_security_deposit())));
        ui->tableBooks->setItem(index, 4, new QTableWidgetItem(QString::number(book.get_rental_cost_day())));
        ui->tableBooks->setItem(index, 5, new QTableWidgetItem(QString::number(book.get_id())));
    }

    ui->tableBooks->clearSelection();
    ui->SelectButtun->setEnabled(false);
 }



void HeadWindow::on_SelectButtun_clicked()
{
    if (ui->tableBooks->selectedItems().empty()){
        return;
    }
    size_t book_id = ui->tableBooks->item(ui->tableBooks->currentRow(), 5)->text().toInt();

    Book book = book_manager->get_book_by_id(book_id);
    emit sendBook(book);

    this->hide();
    detail_window->setModal(true);
    detail_window->exec();
    this->show();


    on_lineSerchBook_textChanged(ui->lineSerchBook->text());
}


void HeadWindow::on_AddBook_clicked()
{

    ChangeBook change_book_window;

    this->hide();
    change_book_window.setModal(true);
    change_book_window.exec();
    this->show();

    on_lineSerchBook_textChanged(ui->lineSerchBook->text());
}

void HeadWindow::updateAuthUser(){
    if (auth->get_user().get_id()){
        auth->logout_user();
        return;
    }

    AuthWindow auth_window;
    auth_window.setModal(true);
    auth_window.exec();
}


void HeadWindow::loginUser(){
    ui->login->setText("Выйти из аккаунта");
    if (auth->get_user().check_role(Users::Role::Administrator)){
        ui->AddBook->show();
    }
    else if (auth->get_user().check_role(Users::Role::Librarian)) {
        ui->LookGetBook->show();
    }
}

void HeadWindow::logoutUser(){
    ui->login->setText("Войти а аккаунт");
    ui->AddBook->hide();
    ui->LookGetBook->hide();
}


void HeadWindow::isSelected(){
    if (not ui->tableBooks->selectedItems().isEmpty()){
        ui->tableBooks->verticalHeader()->setSectionResizeMode(last_current_row, QHeaderView::Interactive);
        ui->tableBooks->setRowHeight(last_current_row, 30);
        ui->tableBooks->verticalHeader()->setSectionResizeMode(ui->tableBooks->currentRow(), QHeaderView::ResizeToContents);

        last_current_row = ui->tableBooks->currentRow();

        ui->SelectButtun->setEnabled(true);
    }
}



void HeadWindow::on_LookGetBook_clicked()
{
    ListForRentWindow w4;
    w4.setModal(true);
    w4.exec();
}


void HeadWindow::load_genres(){
    BookGenres genres = book_manager->get_all_genres();

    ui->genresComboBox->clear();
    ui->genresComboBox->addItem("Все жанры",  QVariant::fromValue(BookGenres()));


    for (Genres genre : genres.get_genres()){
        BookGenres gen = BookGenres();
        gen.add_ganre(genre);

        ui->genresComboBox->addItem(genre.get_name(), QVariant::fromValue(gen));
    }
}


void HeadWindow::selectGanre(int index){
    on_lineSerchBook_textChanged(ui->lineSerchBook->text());
}


void HeadWindow::on_clearPushButton_clicked()
{
    QMessageBox::information(this, "В разработке", "В разработке");
}

