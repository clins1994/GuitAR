#include "consultchord.h"
#include "ui_consultchord.h"

ConsultChord::ConsultChord(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConsultChord)
{
    ui->setupUi(this);
}

ConsultChord::~ConsultChord()
{
    delete ui;
}
