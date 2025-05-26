#include "databasecore.h"

#include <QSqlDriver>

int DataBaseCore::count_used = 0;


DataBaseCore::DataBaseCore(QFileInfo databasename, QObject *parent)
    : QObject{parent}, name_db{databasename.filePath()}
{
    DataBaseCore::count_used++;

    if (QSqlDatabase::contains(name_db)) {
        qDebug() << "Подключение существует.";
    }
    else{
        qDebug() << "Полный путь к базе данных: " << databasename.absoluteFilePath();

        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", name_db);
        db.setDatabaseName(name_db);

        if (not db.open()){
            qDebug() << "Ошибка. База данных не открыта";
            throw OpenDBException(name_db.toLatin1());
        }

        sqlite3_initialize();

        qDebug() << "База данных успешно открыта";
    }

    qDebug() << "Обращений к БД в коде: " << count_used << "\n";
}


DataBaseCore::~DataBaseCore(){
    DataBaseCore::count_used--;

    qDebug() << "Уничтожение обращения.";
    if (DataBaseCore::count_used <= 0){
        closeDB();
        QSqlDatabase::removeDatabase(name_db);

        qDebug() << "За ненадобностью, соеденение было закрыто.";
    }
    qDebug() << "Обращений к БД в коде: " << count_used << '\n';
}


void DataBaseCore::closeDB(){
    QSqlDatabase db = QSqlDatabase::database(name_db, false);
    db.close();
}


QSqlQuery DataBaseCore::exec(QString request, ParametersRequest values){
    QSqlDatabase db = QSqlDatabase::database(name_db, true);
    QSqlQuery query(db);
    query.prepare(request);

    for (auto iter = values.begin(); iter != values.end(); ++iter){
        query.bindValue(iter.key(), iter.value());
    }

    if (not query.exec()){
        qDebug() << "Ошибка. Ошибка выполнения запроса";
        throw ExecException(request.toLatin1());
    }
    return query;
}


bool DataBaseCore::registerFunction(void (&func)(sqlite3_context*, int, sqlite3_value**), QString name_function, int argc) {
    QSqlDatabase db = QSqlDatabase::database(name_db, true);
    if (!db.isOpen()) {
        qDebug() << "Ошибка: База данных не открыта!";
        return false;
    }

    QVariant v = db.driver()->handle();

    if (!v.isValid()) {
        qDebug() << "Ошибка: Handle не валиден!";
        return false;
    }

    if (qstrcmp(v.typeName(), "sqlite3*") != 0) {
        qDebug() << "Ошибка: Handle не является sqlite3*. Фактический тип:" << v.typeName();
        return false;
    }

    if (db.driverName() != "QSQLITE") {
        qDebug() << "Ошибка: Драйвер должен быть QSQLITE. " << "Текущий драйвер: " << db.driverName();
        return false;
    }

    sqlite3 *handle = nullptr;
    handle = *static_cast<sqlite3* const*>(v.data());

    if (!handle) {
        qDebug() << "Ошибка: SQLite handle равен nullptr";
        return false;
    }

    auto rc = sqlite3_create_function(
        handle,
        name_function.toUtf8(),
        argc,
        SQLITE_UTF8,
        nullptr,
        func,
        nullptr,
        nullptr
    );

    if (rc != SQLITE_OK){
        qDebug() << "Ошибка: не удалось зарегестрировать функцию " << name_function;
        return false;
    }

    qDebug() << "Функция " << name_function << " зарегистрирована.";
    return true;
}














