#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <include/pugixml/src/pugixml.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_lineEdit_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    pugi::xml_document doc;
};

#endif // MAINWINDOW_H
