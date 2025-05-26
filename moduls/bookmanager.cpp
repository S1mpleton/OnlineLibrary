#include "bookmanager.h"
#include "database/SQLrequests.h"
#include "database/bookstoredatabase.h"
#include <QMultiMap>

BookManager::BookManager(QObject *parent)
    : QObject{parent}
{
    db = new BookStoreDataBase();

    add_genres(InitialData::GENRES());
    add_authors(InitialData::AUTHORS());
    for (Book book : InitialData::BOOK()){
        add_book(book);
    }
}

BookManager::~BookManager(){
    delete db;
}

Users BookManager::get_user_by_phone(const QString &phone){
    ParametersRequest parameters;
    parameters.insert(":phone", phone);
    QSqlQuery responce = db->get_user_by_phone(parameters);

    Users user;

    if (responce.next()){
        QSqlRecord record = responce.record();

        user.set_surname(record.value("surname").toString());
        user.set_name(record.value("name").toString());
        user.set_patronymic(record.value("patronymic").toString());
        user.set_address(record.value("address").toString());
        user.set_phone(record.value("phone").toString());
        user.set_hash_password(record.value("hash_password").toString());
        user.set_role(record.value("role").toString());
        user.set_points(record.value("points").toInt());
        user.set_id(record.value("id").toInt());
    }

    return user;
}

Users BookManager::get_user_by_id(const size_t &id){
    ParametersRequest parameters;
    parameters.insert(":id", id);

    QSqlQuery responce = db->get_user_by_id(parameters);

    Users user;

    if (responce.next()){
        QSqlRecord record = responce.record();

        user.set_surname(record.value("surname").toString());
        user.set_name(record.value("name").toString());
        user.set_patronymic(record.value("patronymic").toString());
        user.set_address(record.value("address").toString());
        user.set_phone(record.value("phone").toString());
        user.set_hash_password(record.value("hash_password").toString());
        user.set_role(record.value("role").toString());
        user.set_points(record.value("points").toInt());
        user.set_id(record.value("id").toInt());
    }

    return user;
}

bool BookManager::add_user(Users &user){
    ParametersRequest parameters = user.get_parametrs_request();
    QSqlQuery responce = db->add_user(parameters);

    if (responce.numRowsAffected()){
        QSqlRecord record = responce.record();

        user.set_id(responce.lastInsertId().toInt());
        return true;
    }
    return false;
}




BookGenres BookManager::get_all_genres(){
    QSqlQuery responce = db->get_all_genres();
    BookGenres genres;


    while (responce.next()){
        QSqlRecord record = responce.record();

        Genres genre(
            record.value("id").toInt(),
            record.value("name").toString()
        );
        genres.add_ganre(genre);

    }
    return genres;
}




bool BookManager::add_book_authorship(const Book &book){
    ParametersRequest parameters = book.get_parametrs_request();
    parameters.insert(":book_id", parameters.take(":id"));

    for (Authors author : book.get_authors().get_authors()){
        parameters.unite(author.get_parametrs_request());
        parameters.insert(":author_id", parameters.take(":id"));

        QSqlQuery responce = db->add_authorship(parameters);

        if (not responce.numRowsAffected()){
            return false;
        }
        parameters.remove(":author_id");
    }
    return true;
}

bool BookManager::delete_book_authorship(const Book &book){
    ParametersRequest parameters = book.get_parametrs_request();
    parameters.insert(":book_id", parameters.take(":id"));

    QSqlQuery responce = db->delete_authorship_by_book(parameters);
    if (not responce.numRowsAffected()){
        return false;
    }
    return true;
}




bool BookManager::add_book_belonging_genres(const Book &book){
    ParametersRequest parameters = book.get_parametrs_request();
    parameters.insert(":book_id", parameters.take(":id"));

    for (Genres genre : book.get_genres().get_genres()){
        parameters.unite(genre.get_parametrs_request());
        parameters.insert(":genre_id", parameters.take(":id"));

        QSqlQuery responce = db->add_belonging_genres(parameters);
        if (not responce.numRowsAffected()){
            return false;
        }

        parameters.remove(":genre_id");
    }
    return true;
}

bool BookManager::delete_book_belonging_genres(const Book &book){
    ParametersRequest parameters = book.get_parametrs_request();
    parameters.insert(":book_id", parameters.take(":id"));

    QSqlQuery responce = db->delete_belonging_genres_by_book(parameters);
    if (not responce.numRowsAffected()){
        return false;
    }
    return true;
}




BookAuthors BookManager::get_page_authors(const Pagination &pagination, const QString &search_string){
    ParametersRequest parameters = pagination.get_parametrs_request();
    parameters.insert(":search_string", search_string);

    QSqlQuery responce = db->get_page_authors(parameters);
    BookAuthors authors;
    
    while (responce.next()){
        QSqlRecord record = responce.record();

        Authors author(
            record.value("surname").toString(),
            record.value("name").toString(),
            record.value("patronymic").toString(),
            record.value("id").toInt()
        );
        
        authors.add_author(author);
    }
    
    return authors;
}

Authors BookManager::get_author_by_id(const size_t &id){
    ParametersRequest parameters;
    parameters.insert(":id", id);

    QSqlQuery responce = db->get_author_by_id(parameters);
    responce.next();
    QSqlRecord record = responce.record();

    Authors author(
        record.value("surname").toString(),
        record.value("name").toString(),
        record.value("patronymic").toString(),
        record.value("id").toInt()
    );

    return author;
}




QList<Book> BookManager::get_page_books(
    const Pagination &pagination,
    const QString &search_string,
    const BookGenres &select_genres
){
    ParametersRequest parameters = pagination.get_parametrs_request();
    parameters.insert(":search_string", search_string);

    QSqlQuery responce = db->get_page_books(parameters);
    QList<Book> books;
    while (responce.next()){
        QSqlRecord record = responce.record();

        Book book(
            record.value("title").toString(),
            record.value("description").toString(),
            record.value("security_deposit").toInt(),
            record.value("rental_cost_day").toInt(),
            record.value("quantity").toInt(),
            record.value("id").toInt()
            );

        BookManager::load_genres_book(book);
        BookManager::load_authors_book(book);

        bool isExist = false;

        for (Genres genre : select_genres.get_genres()){
            if (book.get_genres().get_genres().contains(genre)){
                isExist = true;
                break;
            }
        }

        if (isExist or select_genres.get_genres().isEmpty()){
            books.append(book);
        }
    }

    return books;
}

Book BookManager::get_book_by_id(const size_t &id){
    ParametersRequest parameters;
    parameters.insert(":id", id);

    QSqlQuery responce = db->get_book_by_id(parameters);
    responce.next();
    QSqlRecord record = responce.record();

    Book book(
        record.value("title").toString(),
        record.value("description").toString(),
        record.value("security_deposit").toInt(),
        record.value("rental_cost_day").toInt(),
        record.value("quantity").toInt(),
        record.value("id").toInt()
    );

    BookManager::load_genres_book(book);
    BookManager::load_authors_book(book);
    return book;
}

bool BookManager::update_book(Book &book){
    ParametersRequest parameters = book.get_parametrs_request();
    db->update_book(parameters);

    delete_book_belonging_genres(book);
    delete_book_authorship(book);

    add_book_belonging_genres(book);
    add_book_authorship(book);

    return true;
}


bool BookManager::add_book(Book &book){
    ParametersRequest parameters = book.get_parametrs_request();

    QSqlQuery responce = db->add_book(parameters);

    if (not responce.numRowsAffected()){
        return false;
    }
    book.set_id(responce.lastInsertId().toInt());

    add_book_authorship(book);
    add_book_belonging_genres(book);

    return true;
}

bool BookManager::delete_book(const Book &book){
    ParametersRequest parameters = book.get_parametrs_request();

    delete_book_belonging_genres(book);
    delete_book_authorship(book);

    db->delete_book(parameters);

    return true;
}




bool BookManager::load_genres_book(Book &book){
    ParametersRequest parameters = book.get_parametrs_request();
    QSqlQuery responce = db->get_book_genres(parameters);

    BookGenres generes;

    while (responce.next()){
        QSqlRecord record = responce.record();
        Genres genere(
            record.value("id").toInt(),
            record.value("name").toString()
        );
        generes.add_ganre(genere);
    }
    book.set_genres(generes);
    return true;
}

bool BookManager::load_authors_book(Book &book){
    ParametersRequest parameters = book.get_parametrs_request();
    QSqlQuery responce = db->get_book_authors(parameters);

    BookAuthors authors;
    while (responce.next()){
        QSqlRecord record = responce.record();
        Authors author(
            record.value("surname").toString(),
            record.value("name").toString(),
            record.value("patronymic").toString(),
            record.value("id").toInt()
        );
        authors.add_author(author);
    }

    book.set_authors(authors);
    return true;
}





bool BookManager::add_genres(const BookGenres &genres){
    for (Genres genre : genres.get_genres()){
        if (not add_genres(genre)){
            return false;
        }
    }
    return true;
}

bool BookManager::add_genres(const Genres &genre){
    ParametersRequest parameters = genre.get_parametrs_request();
    QSqlQuery responce = db->add_genre(parameters);

    if (not responce.numRowsAffected()){
        return false;
    }
    return true;
}

bool BookManager::add_authors(const BookAuthors &authors){
    for (Authors author : authors.get_authors()){
        if (not add_authors(author)){
            return false;
        }
    }
    return true;
}

bool BookManager::add_authors(const Authors &author){
    ParametersRequest parameters = author.get_parametrs_request();
    QSqlQuery responce = db->add_author(parameters);

    if (not responce.numRowsAffected()){
        return false;
    }
    return true;
}



bool BookManager::add_order(const Users &user, const Book &book, const size_t &days_rent){
    ParametersRequest values = user.get_parametrs_request();
    values.insert(":user_id", values.take(":id"));

    values.unite(book.get_parametrs_request());
    values.insert(":book_id", values.take(":id"));
    values.insert(":days_rent", days_rent);

    QSqlQuery responce = db->add_order(values);

    qDebug() << "count insert order " << responce.numRowsAffected();
    if (responce.numRowsAffected() <= 0){
        return false;
    }
    return true;
}

bool BookManager::update_order(const Orders &order){
    ParametersRequest parameters = order.get_parametrs_request();
    QSqlQuery responce = db->update_order(parameters);

    if (responce.numRowsAffected() <= 0){
        return false;
    }
    return true;
}

QList<Orders> BookManager::get_all_orders(){
    QList<Orders> orders;
    QSqlQuery responce = db->get_all_orders();

    while (responce.next()){
        QSqlRecord record = responce.record();
        Orders order;

        order.set_accept(record.value("is_accept").toInt());
        order.set_days_rent(record.value("days_rent").toInt());
        order.set_date_receipt(record.value("date_receipt").toDate());
        order.set_book(this->get_book_by_id(record.value("book_id").toInt()));
        order.set_user(this->get_user_by_id(record.value("user_id").toInt()));
        order.set_id(record.value("id").toInt());

        orders.append(order);
    }

    return orders;
}


Orders BookManager::get_order_by_id(const size_t &id){
    ParametersRequest parameters;
    parameters.insert(":id", id);

    QSqlQuery responce = db->get_order_by_id(parameters);
    Orders order;

    if (responce.next()){
        QSqlRecord record = responce.record();

        order.set_accept(record.value("is_accept").toInt());
        order.set_days_rent(record.value("days_rent").toInt());
        order.set_date_receipt(record.value("date_receipt").toDate());
        order.set_book(this->get_book_by_id(record.value("book_id").toInt()));
        order.set_user(this->get_user_by_id(record.value("user_id").toInt()));
        order.set_id(record.value("id").toInt());
    }

    return order;
}


bool BookManager::delete_order(const Orders &order){
    ParametersRequest parameters = order.get_parametrs_request();
    QSqlQuery responce = db->delete_order(parameters);

    if (responce.numRowsAffected() <= 0){
        return false;
    }
    return true;
}






