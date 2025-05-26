#ifndef LISTFORRENTWINDOW_H
#define LISTFORRENTWINDOW_H

#include "moduls/bookmanager.h"
#include <QDialog>

namespace Ui {
class ListForRentWindow;
}

class ListForRentWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ListForRentWindow(QWidget *parent = nullptr);
    ~ListForRentWindow();

private slots:
    void updateTable();

    void on_deletePushButton_clicked();

    void on_toRentPushButton_clicked();

private:
    BookManager *book_manager;
    Ui::ListForRentWindow *ui;
};

#endif // LISTFORRENTWINDOW_H
