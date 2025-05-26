#include "bookstoredatabase.h"
#include "SQLrequests.h"
#include "database/fuzzycomparison.h"



BookStoreDataBase::BookStoreDataBase(QFileInfo file_name, QObject *parent) :
    DataBaseCore(file_name, parent)
{

    if (BookStoreDataBase::count_used == 1){
        create_tables();
        registerFunction(BookStoreDataBase::fuzzy_comparison, "levenshtein", 2);
    }



}


void BookStoreDataBase::initialization(){
}

void BookStoreDataBase::create_tables(){
    exec(SQLiterequests::CREATE_BOOKS_TABLE);

    exec(SQLiterequests::CREATE_USERS_TABLE);

    exec(SQLiterequests::CREATE_AUTHORS_TABLE);

    exec(SQLiterequests::CREATE_GENRES_TABLE);

    exec(SQLiterequests::CREATE_ORDERS_TABLE);

    exec(SQLiterequests::CREATE_AUTHORSHIPS_TABLE);

    exec(SQLiterequests::CREATE_BELONGING_GENRES_TABLE);
}


QSqlQuery BookStoreDataBase::get_user_by_phone(const ParametersRequest &parameters){
    return exec(SQLiterequests::GET_USER_BY_PHONE, parameters);
}

QSqlQuery BookStoreDataBase::get_user_by_id(const ParametersRequest &parameters){
    return exec(SQLiterequests::GET_USER_BY_ID, parameters);
}

QSqlQuery BookStoreDataBase::add_user(const ParametersRequest &parameters){
    return exec(SQLiterequests::ADD_USER, parameters);
}

QSqlQuery BookStoreDataBase::get_page_books(const ParametersRequest &parameters){
    return exec(SQLiterequests::GET_PAGE_BOOKS, parameters);
}

QSqlQuery BookStoreDataBase::get_book_by_id(const ParametersRequest &parameters){
    return exec(SQLiterequests::GET_BOOK_BY_ID, parameters);
}

QSqlQuery BookStoreDataBase::update_book(const ParametersRequest &parameters){
    return exec(SQLiterequests::UPDATE_BOOK, parameters);
}

QSqlQuery BookStoreDataBase::add_book(const ParametersRequest &parameters){
    return exec(SQLiterequests::ADD_BOOK, parameters);
}

QSqlQuery BookStoreDataBase::delete_book(const ParametersRequest &parameters){
    return exec(SQLiterequests::DELETE_BOOK_BY_ID, parameters);
}




QSqlQuery BookStoreDataBase::add_belonging_genres(const ParametersRequest &parameters){
    return exec(SQLiterequests::ADD_BELONGING_GENRES, parameters);
}

QSqlQuery BookStoreDataBase::delete_belonging_genres_by_book(const ParametersRequest &parameters){
    return exec(SQLiterequests::DELETE_BELONGING_GENRES_BY_BOOK_ID, parameters);
}


QSqlQuery BookStoreDataBase::add_authorship(const ParametersRequest &parameters){
    return exec(SQLiterequests::ADD_AUTHORSHIP, parameters);
}

QSqlQuery BookStoreDataBase::delete_authorship_by_book(const ParametersRequest &parameters){
    return exec(SQLiterequests::DELETE_AUTHORSHIP_BY_BOOK_ID, parameters);
}


QSqlQuery BookStoreDataBase::get_book_genres(const ParametersRequest &parameters){
    return exec(SQLiterequests::GET_BOOK_GENRES, parameters);
}

QSqlQuery BookStoreDataBase::get_all_genres(){
    return exec(SQLiterequests::GET_ALL_GENRES);
}

QSqlQuery BookStoreDataBase::add_genre(const ParametersRequest &parameters){
    return exec(SQLiterequests::ADD_GENRE, parameters);
}


QSqlQuery BookStoreDataBase::get_page_authors(const ParametersRequest &parameters){
    return exec(SQLiterequests::GET_PAGE_AUTHORS, parameters);
}

QSqlQuery BookStoreDataBase::get_author_by_id(const ParametersRequest &parameters){
    return exec(SQLiterequests::GET_AUTHOR_BY_ID, parameters);
}

QSqlQuery BookStoreDataBase::get_book_authors(const ParametersRequest &parameters){
    return exec(SQLiterequests::GET_BOOK_AUTHORS, parameters);
}

QSqlQuery BookStoreDataBase::add_author(const ParametersRequest &parameters){
    return exec(SQLiterequests::ADD_AUTHOR, parameters);
}



QSqlQuery BookStoreDataBase::add_order(const ParametersRequest &parameters){
    QSqlQuery check_query = exec(SQLiterequests::GET_ORDES_BY_USER_ID, parameters);
    bool isIn = false;

    while (check_query.next()){
        QSqlRecord record = check_query.record();
        isIn = (record.value("book_id").toInt() == parameters.find(":book_id").value().value<int>());
        if (isIn){
            break;
        }
    }

    QSqlQuery query;
    if (not isIn){
        query = exec(SQLiterequests::ADD_ORDERS, parameters);
    }
    return query;
}

QSqlQuery BookStoreDataBase::update_order(const ParametersRequest &parameters){
    return exec(SQLiterequests::UPDATE_ORDER_BY_ID, parameters);
}

QSqlQuery BookStoreDataBase::get_all_orders(){
    return exec(SQLiterequests::GET_ALL_ORDERS);
}

QSqlQuery BookStoreDataBase::get_order_by_id(const ParametersRequest &parameters){
    return exec(SQLiterequests::GET_ORDER_BY_ID, parameters);
}

QSqlQuery BookStoreDataBase::delete_order(const ParametersRequest &parameters){
    return exec(SQLiterequests::DELETE_ORDER_BY_ID, parameters);
}




void BookStoreDataBase::fuzzy_comparison(sqlite3_context* context, int argc, sqlite3_value** argv) {
    if (argc != 2){
        sqlite3_result_error(context, "Invalid quantity arguments, expected two arguments", -1);
        return;
    }
    else if (sqlite3_value_type(argv[0]) != SQLITE_TEXT || sqlite3_value_type(argv[1]) != SQLITE_TEXT) {
        sqlite3_result_error(context, "Invalid type arguments, expected SQLITE_TEXT", -1);
        return;
    }

    const char* s1 = (const char*)sqlite3_value_text(argv[0]);
    const char* s2 = (const char*)sqlite3_value_text(argv[1]);

    QString qs1 = QString::fromUtf8(s1);
    QString qs2 = QString::fromUtf8(s2);

    float result = FuzzyComparison::comparison_without_capitals(qs1, qs2);
    sqlite3_result_double(context, result);
}




