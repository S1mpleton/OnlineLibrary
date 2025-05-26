#include "QMainWindow"
#include "headwindow.h"

#include "moduls/bookmanager.h"
#include "moduls/genres.h"
#include "moduls/users.h"
#include "database/bookstoredatabase.h"
#include "database/fuzzycomparison.h"

#include <QCoreApplication>
#include <QApplication>
#include <QVariant>
#include <QSqlDatabase>
#include <QMultiMap>

#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtCore/QVariant>
#include <QtCore/QDateTime>
#include <QtCore/QMetaType>
#include <QtCore/QDataStream>
#include <QtSql/QSqlDriver>

#include <QSqlDriver>
#include <QSqlField>
#include "QtSqlVersion"


// Q_DECLARE_OPAQUE_POINTER(sqlite3*)
// Q_DECLARE_METATYPE(sqlite3*);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HeadWindow w;
    w.show();

    return a.exec();
}
