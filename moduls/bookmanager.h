#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H

#include "database/bookstoredatabase.h"
#include "moduls/genres.h"
#include "book.h"
#include "moduls/orders.h"
#include "moduls/users.h"
#include "core/pagination.h"

#include <QObject>




class BookManager
    : public QObject
{
    Q_OBJECT
public:
    explicit BookManager(QObject *parent = nullptr);
    ~BookManager();

    // User
    Users get_user_by_phone(const QString &phone);
    Users get_user_by_id(const size_t &id);
    bool add_user(Users &user);

    // Genres
    BookGenres get_all_genres();
    bool add_genres(const BookGenres &genres);
    bool add_genres(const Genres &genre);

    // Authorsip
    bool add_book_authorship(const Book &book);
    bool delete_book_authorship(const Book &book);

    // Belonging genres
    bool add_book_belonging_genres(const Book &book);
    bool delete_book_belonging_genres(const Book &book);

    // Authors
    BookAuthors get_page_authors(const Pagination &pagination = Pagination(1000, 1), const QString &search_string = "");
    Authors get_author_by_id(const size_t &id); 
    bool add_authors(const BookAuthors &authors);
    bool add_authors(const Authors &author);

    // Books
    QList<Book> get_page_books(
        const Pagination &pagination = Pagination(1000, 1),
        const QString &search_string = "",
        const BookGenres &select_genres = BookGenres()
    );
    Book get_book_by_id(const size_t &id);
    bool update_book(Book &book);
    bool add_book(Book &book);
    bool delete_book(const Book &book);

    // Orders
    bool add_order(const Users &user, const Book &book, const size_t &days_rent);
    bool update_order(const Orders &order);
    QList<Orders> get_all_orders();
    Orders get_order_by_id(const size_t &id);
    bool delete_order(const Orders &order);


private:
    bool load_genres_book(Book &book);
    bool load_authors_book(Book &book);

    BookStoreDataBase *db;

};

#endif // BOOKMANAGER_H
