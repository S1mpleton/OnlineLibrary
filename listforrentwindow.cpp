#include "listforrentwindow.h"
#include "ui_listforrentwindow.h"

#include <QDate>
#include <QMessageBox>

ListForRentWindow::ListForRentWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ListForRentWindow)
{
    book_manager = new BookManager();
    ui->setupUi(this);


    ui->ordersTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->ordersTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->ordersTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->ordersTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->ordersTableWidget->setColumnHidden(4, true);
    ui->ordersTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    updateTable();
}

ListForRentWindow::~ListForRentWindow()
{
    delete book_manager;
    delete ui;
}


void ListForRentWindow::updateTable(){
    ui->ordersTableWidget->clearContents();
    ui->ordersTableWidget->setRowCount(0);

    QList<Orders> orders = book_manager->get_all_orders();

    for (Orders order : orders) {
        int index = ui->ordersTableWidget->rowCount();
        ui->ordersTableWidget->insertRow(index);

        QString days_rent = "Не получен";
        if (order.isAccept()){
            int days_of_client = order.get_date_receipt().daysTo(QDate::currentDate());

            if (days_of_client > (int)order.get_days_rent()){
                days_rent = "Просрочено: " + QString::number(days_of_client - (int)order.get_days_rent());
            }
            else{
                days_rent = "Осталось: " + QString::number((int)order.get_days_rent() - days_of_client);
            }
        }

        ui->ordersTableWidget->setItem(index, 0, new QTableWidgetItem(days_rent));
        ui->ordersTableWidget->setItem(index, 1, new QTableWidgetItem(order.get_user().get_phone()));
        ui->ordersTableWidget->setItem(index, 2, new QTableWidgetItem(order.get_book().get_title()));
        ui->ordersTableWidget->setItem(index, 3, new QTableWidgetItem(QString::number(order.get_book().get_security_deposit())));
        ui->ordersTableWidget->setItem(index, 4, new QTableWidgetItem(QString::number(order.get_id())));
    }

}



void ListForRentWindow::on_deletePushButton_clicked()
{
    if (ui->ordersTableWidget->selectedItems().empty()){
        return;
    }

    size_t order_id = ui->ordersTableWidget->item(ui->ordersTableWidget->currentRow(), 4)->text().toInt();
    Orders order = book_manager->get_order_by_id(order_id);

    QMessageBox::StandardButton but = QMessageBox::question(
        this,
        "Подтверждение",
        "Пользователь действительно возращает книгу?\n"
        "Перед возвратом залога, осмотрите книгу на повреждения"
    );

    if (but == QMessageBox::Yes){
        if (book_manager->delete_order(order)){
            QMessageBox::information(this, "Успешно", "Аренда была закрыта");
        }
        else{
            QMessageBox::warning(this, "Ошибка", "Ошибка закрытия аренды");
        }
    }
    updateTable();
}


void ListForRentWindow::on_toRentPushButton_clicked()
{
    if (ui->ordersTableWidget->selectedItems().empty()){
        return;
    }

    size_t order_id = ui->ordersTableWidget->item(ui->ordersTableWidget->currentRow(), 4)->text().toInt();
    Orders order = book_manager->get_order_by_id(order_id);

    if (not order.get_id()){
        QMessageBox::warning(this, "Ошибка", "Этот заказ уже не существует");
    }
    else if (order.isAccept()){
        QMessageBox::warning(this, "Ошибка", "Пользователь уже забрал эту книгу");
    }
    else{
        QMessageBox::StandardButton but = QMessageBox::question(
            this,
            "Подтверждение",
            "Вы действительно отдаете книгу в аренду?\n"
            "Возмите залоговую стоимость и зафиксируете состояние книги до того как отдадите ее клиенту"
        );

        if (but == QMessageBox::Yes){
            order.set_accept(true);
            book_manager->update_order(order);
            QMessageBox::information(this, "Начало аренды", "Книга была успешно арендована");
        }
    }
    updateTable();
}

