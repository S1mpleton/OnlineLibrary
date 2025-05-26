#ifndef DATABASECORE_H
#define DATABASECORE_H


#include <QtSql>
#include <sqlite3.h>

#include <QSqlDatabase>

#include <QSqlQuery>
#include <QSqlRecord>

#include <QFileInfo>
#include <QObject>

#include <QDebug>
#include <QMultiMap>




using ParametersRequest = QMultiMap<QString, QVariant>;


class DataBaseCore : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseCore(QFileInfo databasename, QObject *parent = nullptr);
    ~DataBaseCore();

    bool registerFunction(void (&func)(sqlite3_context*, int, sqlite3_value**), QString name_function, int argc);

protected:
    QSqlQuery exec(QString request, ParametersRequest values = {});

    void closeDB();

    int static count_used;
    QString name_db;

};



class OpenDBException: public std::exception {
public:
    OpenDBException(const char* dbName) : m_dbname(dbName) {}
private:
    virtual const char* what() const throw() {
        return m_dbname;
    }
    const char* m_dbname;
};


class ExecException: public std::exception {
public:
    ExecException(const char* request) : m_request(request) {}
private:
    virtual const char* what() const throw() {
        return m_request;
    }
    const char* m_request;
};

#endif // DATABASECORE_H
