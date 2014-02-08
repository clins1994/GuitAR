#ifndef LISTMAKER_H
#define LISTMAKER_H

#include <QMainWindow>

namespace Ui {
class ListMaker;
}

class ListMaker : public QMainWindow
{
    Q_OBJECT

public:
    explicit ListMaker(QWidget *parent = 0);
    ~ListMaker();

private:
    Ui::ListMaker *ui;
};

#endif // LISTMAKER_H
