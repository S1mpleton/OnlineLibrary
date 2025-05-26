QT += sql \
    core gui \
    svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    auth/authentications.cpp \
    authwindow.cpp \
    changebook.cpp \
    core/pagination.cpp \
    core/suppobject/selectedcombobox.cpp \
    database/SQLrequests.cpp \
    database/bookstoredatabase.cpp \
    database/databasecore.cpp \
    database/fuzzycomparison.cpp \
    detailedbookwindow.cpp \
    headwindow.cpp \
    listforrentwindow.cpp \
    main.cpp \
    moduls/authors.cpp \
    moduls/book.cpp \
    moduls/bookmanager.cpp \
    moduls/genres.cpp \
    moduls/orders.cpp \
    moduls/persons.cpp \
    moduls/users.cpp \
    selectauthorsdialog.cpp

HEADERS += \
    auth/authentications.h \
    authwindow.h \
    changebook.h \
    core/pagination.h \
    core/suppobject/selectedcombobox.h \
    database/SQLrequests.h \
    database/bookstoredatabase.h \
    database/databasecore.h \
    database/fuzzycomparison.h \
    detailedbookwindow.h \
    headwindow.h \
    listforrentwindow.h \
    moduls/authors.h \
    moduls/book.h \
    moduls/bookmanager.h \
    moduls/genres.h \
    moduls/orders.h \
    moduls/persons.h \
    moduls/users.h \
    selectauthorsdialog.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    authwindow.ui \
    changebook.ui \
    detailedbookwindow.ui \
    headwindow.ui \
    listforrentwindow.ui \
    selectauthorsdialog.ui

RESOURCES += \
    resources.qrc







# INCLUDEPATH += $$PWD/libs/SQLite-ver-3-35-5
# LIBS += -L$$PWD/libs/SQLite-ver-3-35-5 -lsqlite3

INCLUDEPATH += $$PWD/libs/SQLite-ver-4-49-1
LIBS += -L$$PWD/libs/SQLite-ver-4-49-1 -lsqlite3

# INCLUDEPATH += $$PWD/libs/SQLite-ver-4-49-1-with-params
# LIBS += -L$$PWD/libs/SQLite-ver-4-49-1-with-params -lsqlite3

# DEFINES += QT_NO_SQLITE_STATIC
