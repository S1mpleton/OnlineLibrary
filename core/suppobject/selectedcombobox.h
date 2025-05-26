#ifndef SELECTEDCOMBOBOX_H
#define SELECTEDCOMBOBOX_H

#include <QComboBox>

class SelectedComboBox : public QComboBox
{
    Q_OBJECT

public:
    explicit SelectedComboBox(QWidget *parent = nullptr);
    bool eventFilter(QObject *watched, QEvent *event) override;

    using QComboBox::QComboBox;

protected:
    void hidePopup() override;

};

#endif // SELECTEDCOMBOBOX_H
