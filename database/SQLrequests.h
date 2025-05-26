#ifndef SQLREQUESTS_H
#define SQLREQUESTS_H

#include "moduls/book.h"

#include <QList>
#include <QString>


namespace InitialData{
BookGenres GENRES();
BookAuthors AUTHORS();

QList<Book> BOOK();
}



namespace SQLiterequests{

// -- Created tables --
static QString CREATE_BOOKS_TABLE =
    "CREATE TABLE IF NOT EXISTS Books ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "title TEXT NOT NULL, "
        "description TEXT NOT NULL, "
        "security_deposit INTEGER NOT NULL, "
        "rental_cost_day INTEGER NOT NULL, "
        "quantity INTEGER NOT NULL"
    ");"
    ;

static QString CREATE_USERS_TABLE =
    "CREATE TABLE IF NOT EXISTS Users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "surname TEXT NOT NULL, "
        "name TEXT NOT NULL, "
        "patronymic TEXT DEFAULT NULL, "
        "address TEXT NOT NULL, "
        "phone TEXT NOT NULL, "
        "hash_password NOT NULL, "
        "role TEXT DEFAULT Пользователь, "
        "points INTEGER DEFAULT 0"
    ");"
    ;

static QString CREATE_AUTHORS_TABLE =
    "CREATE TABLE IF NOT EXISTS Authors ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "surname TEXT NOT NULL, "
        "name TEXT NOT NULL, "
        "patronymic TEXT DEFAULT NULL"
    ");"
    ;

static QString CREATE_GENRES_TABLE =
    "CREATE TABLE IF NOT EXISTS Genres ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL"
    ");"
    ;

static QString CREATE_ORDERS_TABLE =
    "CREATE TABLE IF NOT EXISTS Orders ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "user_id INTEGER NOT NULL, "
        "book_id INTEGER NOT NULL, "
        "date_receipt DATE NOT NULL, "
        "days_rent INTEGER NOT NULL, "
        "is_accept BOOL NOT NULL, "
        "FOREIGN KEY (user_id) REFERENCES Users(id), "
        "FOREIGN KEY (book_id) REFERENCES Books(id)"
    ");"
    ;

static QString CREATE_AUTHORSHIPS_TABLE =
    "CREATE TABLE IF NOT EXISTS Authorship ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "book_id INTEGER NOT NULL, "
        "author_id INTEGER NOT NULL, "
        "FOREIGN KEY (book_id) REFERENCES Books(id), "
        "FOREIGN KEY (author_id) REFERENCES Authors(id)"
    ");"
    ;

static QString CREATE_BELONGING_GENRES_TABLE =
    "CREATE TABLE IF NOT EXISTS BelongingGenres ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "book_id INTEGER NOT NULL, "
        "genre_id INTEGER NOT NULL, "
        "FOREIGN KEY (book_id) REFERENCES Books(id), "
        "FOREIGN KEY (genre_id) REFERENCES Genres(id)"
    ");"
    ;





// -- CRUD with user --
static QString ADD_USER =
    "INSERT INTO Users "
        "(id, surname, name, patronymic, address, phone, hash_password, role, points) "
    "SELECT :id, :surname, :name, :patronymic, :address, :phone, :hash_password, :role, :points "
    "WHERE NOT EXISTS ( "
        "SELECT 1 "
        "FROM Users "
        "WHERE id = :id"
    ");"
    ;

static QString GET_USER_BY_ID =
    "SELECT * "
    "FROM Users "
    "WHERE id = :id"
    ;

static QString GET_USER_BY_PHONE =
    "SELECT * "
    "FROM Users "
    "WHERE phone = :phone"
    ;

static QString UPDATE_USER_BY_ID =
    ""
    ;

static QString UPDATE_USER_BY_PHONE =
    ""
    ;

static QString DELETE_USER_BY_ID =
    ""
    ;

static QString DELETE_USER_BY_PHONE =
    ""
    ;






// -- CRUD with book --
static QString ADD_BOOK =
    "INSERT INTO Books "
        "(id, title, description, security_deposit, rental_cost_day, quantity) "
    "SELECT :id, :title, :description, :security_deposit, :rental_cost_day, :quantity "
    "WHERE NOT EXISTS ("
        "SELECT 1 "
        "FROM Books "
        "WHERE id = :id"
    ");"
    ;

static QString GET_BOOK_BY_ID =
    "SELECT * FROM Books "
    "WHERE id = :id"
    ;

static QString GET_PAGE_BOOKS =
    "SELECT *, levenshtein(Books.title, :search_string) AS comparison "
    "FROM Books "
    "ORDER BY comparison DESC "
    "LIMIT :limit "
    "OFFSET :offset;"
    ;

static QString UPDATE_BOOK =
    "UPDATE Books "
    "SET "
        "title = :title, "
        "description = :description, "
        "security_deposit = :security_deposit, "
        "rental_cost_day = :rental_cost_day, "
        "quantity = :quantity "
    "WHERE id = :id;"
    ;

static QString DELETE_BOOK_BY_ID =
    "DELETE FROM Books "
    "WHERE id = :id;"
    ;





// -- CRUD with authors --
static QString ADD_AUTHOR =
    "INSERT INTO Authors "
        "(id, surname, name, patronymic) "
    "SELECT :id, :surname, :name, :patronymic "
    "WHERE NOT EXISTS ( "
        "SELECT 1 FROM Authors "
        "WHERE id = :id"
    ");"
    ;

static QString GET_AUTHOR_BY_ID =
    "SELECT * FROM Authors "
    "WHERE id = :id;"
    ;

static QString GET_PAGE_AUTHORS =
    "SELECT *, levenshtein(name || ' ' || surname || ' ' || IFNULL(patronymic, ''), :search_string) AS comparison "
    "FROM Authors "
    "ORDER BY comparison DESC "
    "LIMIT :limit "
    "OFFSET :offset;"
    ;

static QString GET_BOOK_AUTHORS =
    "SELECT Authors.* "
    "FROM Authors "
    "JOIN Authorship ON Authors.id = Authorship.author_id "
    "WHERE Authorship.book_id = :id;"
    ;

static QString UPDATE_AUTHOR_BY_ID =
    "UPDATE Authors "
    "SET "
        "surname = :surname, "
        "name = :name, "
        "patronymic = :patronymic "
    "WHERE id = :id;"
    ;

static QString DELETE_AUTHOR_BY_ID =
    "DELETE FROM Authors "
    "WHERE id = :id;"
    ;





// -- CRUD with genres --
static QString ADD_GENRE =
    "INSERT INTO Genres "
        "(id, name) "
    "SELECT :id, :name "
    "WHERE NOT EXISTS ( "
        "SELECT 1 FROM Genres WHERE id = :id"
    ");"
    ;

static QString GET_BOOK_GENRES =
    "SELECT Genres.* "
    "FROM Genres "
    "RIGHT JOIN BelongingGenres ON Genres.id = BelongingGenres.genre_id "
    "WHERE BelongingGenres.book_id = :id;"
    ;

static QString GET_ALL_GENRES =
    "SELECT * "
    "FROM Genres;"
    ;





// -- CRUD with authorship --
static QString ADD_AUTHORSHIP =
    "INSERT INTO Authorship "
        "(book_id, author_id) "
    "SELECT :book_id, :author_id "
    "WHERE NOT EXISTS ( "
        "SELECT 1 FROM Authorship WHERE book_id = :book_id AND author_id = :author_id"
    ");"
    ;

static QString DELETE_AUTHORSHIP_BY_ID =
    "DELETE FROM Authorship "
    "WHERE id = :id;"
    ;

static QString DELETE_AUTHORSHIP_BY_BOOK_ID =
    "DELETE FROM Authorship "
    "WHERE book_id = :book_id;"
    ;

static QString DELETE_AUTHORSHIP_BY_AUTHOR_ID =
    "DELETE FROM Authorship "
    "WHERE author_id = :author_id;"
    ;





// -- CRUD with belonging genres --
static QString ADD_BELONGING_GENRES =
    "INSERT INTO BelongingGenres "
        "(book_id, genre_id) "
    "SELECT :book_id, :genre_id "
    "WHERE NOT EXISTS ( "
        "SELECT 1 FROM BelongingGenres WHERE book_id = :book_id AND genre_id = :genre_id"
    ");"
    ;

static QString DELETE_BELONGING_GENRES_BY_ID =
    "DELETE FROM BelongingGenres "
    "WHERE id = :id;"
    ;

static QString DELETE_BELONGING_GENRES_BY_BOOK_ID =
    "DELETE FROM BelongingGenres "
    "WHERE book_id = :book_id;"
    ;

static QString DELETE_BELONGING_GENRES_BY_GENRE_ID =
    "DELETE FROM BelongingGenres "
    "WHERE genre_id = :genre_id;"
    ;





// -- CRUD with orders --
static QString ADD_ORDERS =
    "INSERT INTO Orders "
        "(user_id, book_id, date_receipt, days_rent, is_accept) "
    "SELECT :user_id, :book_id, date('now'), :days_rent, 0 "
    ;

static QString GET_ALL_ORDERS =
    "SELECT * "
    "FROM Orders;"
    ;

static QString GET_ORDER_BY_ID =
    "SELECT * "
    "FROM Orders "
    "WHERE id = :id;"
    ;

static QString GET_ORDES_BY_USER_ID =
    "SELECT * "
    "FROM Orders "
    "WHERE user_id = :user_id;"
    ;

static QString UPDATE_ORDER_BY_ID =
    "UPDATE Orders "
    "SET "
        "user_id = :user_id, "
        "book_id = :book_id, "
        "date_receipt = :date_receipt, "
        "days_rent = :days_rent, "
        "is_accept = :is_accept "
    "WHERE id = :id;"
    ;

static QString DELETE_ORDER_BY_ID =
    "DELETE FROM Orders "
    "WHERE id = :id;"
    ;




// -- helping function --
static QString LEVENSHTEIN_SEARCH =
    "CREATE FUNCTION levenshtein(s1 TEXT, s2 TEXT) RETURNS INTEGER AS $$ "
    "BEGIN "
        "IF s1 = '' THEN RETURN length(s2); END IF; "
        "IF s2 = '' THEN RETURN length(s1); END IF; "

        "DECLARE m INTEGER[length(s1)+1][length(s2)+1]; "
        "DECLARE i INTEGER; "
        "DECLARE j INTEGER; "

        "FOR i IN 0..length(s1) LOOP "
            "m[i][0] := i; "
        "END LOOP; "

        "FOR j IN 0..length(s2) LOOP "
            "m[0][j] := j; "
        "END LOOP; "

        "FOR i IN 1..length(s1) LOOP "
            "FOR j IN 1..length(s2) LOOP "
                "IF substring(s1 FROM i FOR 1) = substring(s2 FROM j FOR 1) THEN "
                    "m[i][j] := m[i-1][j-1]; "
                "ELSE"
                    "m[i][j] := least( "
                        "m[i-1][j] + 1, "
                        "m[i][j-1] + 1, "
                        "m[i-1][j-1] + 1 "
                    "); "
                "END IF; "
            "END LOOP; "
        "END LOOP; "
        "RETURN m[length(s1)][length(s2)]; "
    "END;"
    ;

static QString LEVENSHTEIN_SIMILARITY =
    "CREATE OR REPLACE FUNCTION levenshtein_similarity(s1 TEXT, s2 TEXT) RETURNS INTEGER AS $$ "
    "DECLARE "
        "distance INTEGER; "
        "max_len INTEGER; "
        "similarity FLOAT; "
    "BEGIN "
        "distance := levenshtein(s1, s2); "
        "max_len := GREATEST(length(s1), length(s2)); "
        "similarity := ((max_len - distance::FLOAT) / max_len::FLOAT) * 100; "
        "RETURN ROUND(similarity)::INTEGER; "
    "END;"
    ;


static QString test =
    "CREATE FUNCTION levenshtein_similarity(s1 TEXT, s2 TEXT) RETURNS INTEGER "
    "BEGIN "
    "DECLARE s INTEGER "
    "END;"
    ;
}







#endif // SQLREQUESTS_H
