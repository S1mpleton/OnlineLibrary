#include "selectedcombobox.h"

#include <QMouseEvent>
#include <QApplication>



SelectedComboBox::SelectedComboBox(QWidget *parent) : QComboBox(parent)
{
    if (parent) {
        parent->installEventFilter(this);
    }
}

bool SelectedComboBox::eventFilter(QObject *watched, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        qDebug() << mouseEvent->position().toPoint();
        if (!this->rect().contains(this->mapFromGlobal(mouseEvent->globalPosition().toPoint()))) {
            hidePopup();
        }
    }
    return QComboBox::eventFilter(watched, event);
}


void SelectedComboBox::hidePopup() {
    qDebug() << "CLOSE MY Q BOX ";
    QComboBox::hidePopup();
}
