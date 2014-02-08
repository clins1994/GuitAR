#ifndef CONSULTCHORD_H
#define CONSULTCHORD_H

#include <QMainWindow>

namespace Ui {
class ConsultChord;
}

class ConsultChord : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ConsultChord(QWidget *parent = 0);
    ~ConsultChord();
    
private:
    Ui::ConsultChord *ui;
};

#endif // CONSULTCHORD_H
