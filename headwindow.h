#ifndef HEADWINDOW_H
#define HEADWINDOW_H


#include "auth/authentications.h"
#include "detailedbookwindow.h"
#include "moduls/bookmanager.h"
#include "moduls/users.h"
#include "core/suppobject/selectedcombobox.h"

#include <QSvgRenderer>
#include <QMainWindow>



namespace Ui {
class HeadWindow;
}

class HeadWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HeadWindow(QWidget *parent = nullptr);
    ~HeadWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void sendBook(const Book &book);

private slots:
    void on_lineSerchBook_textChanged(const QString &search_string);

    void on_SelectButtun_clicked();

    void on_AddBook_clicked();

    void updateAuthUser();

    void loginUser();

    void logoutUser();

    void isSelected();

    void on_LookGetBook_clicked();

    void selectGanre(int index);

    void on_clearPushButton_clicked();

private:
    void load_genres();

    // SelectedComboBox *genresSelected;

    Authentications* auth;
    // Users user;

    Ui::HeadWindow *ui;

    DetailedBookWindow *detail_window;
    QSvgRenderer *svg_icon;
    BookManager *book_manager;

    int last_current_row;

};

#endif // HEADWINDOW_H
