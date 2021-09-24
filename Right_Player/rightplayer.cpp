#include "rightplayer.h"
#include "ui_rightplayer.h"

RightPlayer::RightPlayer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RightPlayer)
{
    ui->setupUi(this);

    r_player = new QMediaPlayer();
    r_playlist = new QMediaPlaylist();
    r_player->setPlaylist(r_playlist);

    connect (ui->openfile, &QPushButton::clicked, this, &RightPlayer::browsefile);
    connect(ui->playlisttable, &QListWidget::doubleClicked,this, &RightPlayer::songselected);

}

RightPlayer::~RightPlayer()
{
    delete ui;
}

void RightPlayer::browsefile()
{
    QString r_fileway = QFileDialog::getOpenFileName(this, "Open folder", QDir::homePath(), "MP3 *.mp3");
    ui->playlisttable->addItem(r_fileway);
}
void RightPlayer::songselected()
{
    QString name_song = ui->playlisttable->currentItem()->text();
    ui->songname->setText(name_song);
    r_player->setMedia(QUrl::fromLocalFile(r_fileway + QDir::separator()+name_song));

}





