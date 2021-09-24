#include "rightplayer.h"
#include "ui_rightplayer.h"

RightPlayer::RightPlayer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RightPlayer)
{
    ui->setupUi(this);

}

RightPlayer::~RightPlayer()
{
    delete ui;
}





