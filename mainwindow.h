#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "Chord.hpp"
#include <list>

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

    void on_btnNextChord_clicked();

    void on_btnPrevChord_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    std::list<Chord*> chordsFound;
};

#endif // MAINWINDOW_H
