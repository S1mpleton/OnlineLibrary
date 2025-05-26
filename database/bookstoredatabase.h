#ifndef BOOKSTOREDATABASE_H
#define BOOKSTOREDATABASE_H

#include "databasecore.h"


class BookStoreDataBase : public DataBaseCore
{
    Q_OBJECT
public:
    explicit BookStoreDataBase(
        QFileInfo file_name = QFileInfo("database/data.db"),
        QObject *parent = nullptr
    );
    void initialization();
    void create_tables();
    void create_levenshtein_search_function();

    QSqlQuery get_user_by_phone(const ParametersRequest &parameters);
    QSqlQuery get_user_by_id(const ParametersRequest &parameters);
    QSqlQuery add_user(const ParametersRequest &parameters);


    QSqlQuery get_book_genres(const ParametersRequest &parameters);
    QSqlQuery get_all_genres();
    QSqlQuery add_genre(const ParametersRequest &parameters);


    QSqlQuery get_page_authors(const ParametersRequest &parameters);
    QSqlQuery get_author_by_id(const ParametersRequest &parameters);
    QSqlQuery get_book_authors(const ParametersRequest &parameters);
    QSqlQuery add_author(const ParametersRequest &parameters);


    QSqlQuery get_page_books(const ParametersRequest &parameters);
    QSqlQuery get_book_by_id(const ParametersRequest &parameters);
    QSqlQuery update_book(const ParametersRequest &parameters);
    QSqlQuery add_book(const ParametersRequest &parameters);
    QSqlQuery delete_book(const ParametersRequest &parameters);


    QSqlQuery add_belonging_genres(const ParametersRequest &parameters);
    QSqlQuery delete_belonging_genres_by_book(const ParametersRequest &parameters);


    QSqlQuery add_authorship(const ParametersRequest &parameters);
    QSqlQuery delete_authorship_by_book(const ParametersRequest &parameters);


    QSqlQuery add_order(const ParametersRequest &parameters);
    QSqlQuery update_order(const ParametersRequest &parameters);
    QSqlQuery get_all_orders();
    QSqlQuery get_order_by_id(const ParametersRequest &parameters);
    QSqlQuery delete_order(const ParametersRequest &parameters);



    static void fuzzy_comparison(sqlite3_context* context, int argc, sqlite3_value** argv);

};


#endif // BOOKSTOREDATABASE_H
