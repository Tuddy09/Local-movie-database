#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_a89.h"

class a89 : public QMainWindow
{
    Q_OBJECT

public:
    a89(QWidget *parent = nullptr);
    ~a89();

private:
    Ui::a89Class ui;
};
