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

    ui->volumesong->setRange(0, 100);
    ui->volumesong->setValue(50);
    r_player->setVolume(50);

    connect (ui->openfile, &QPushButton::clicked, this, &RightPlayer::browsefile);
    connect (ui->stop_play, &QPushButton::clicked, this, &RightPlayer::playsong);
    connect (ui->volumesong, &QSlider::valueChanged, r_player, &QMediaPlayer::setVolume);
    connect(r_player, &QMediaPlayer::currentMediaChanged, this, &RightPlayer::curschange);
    connect(r_player, &QMediaPlayer::stateChanged, this, &RightPlayer::statechange);
    connect(r_player, &QMediaPlayer::positionChanged, this, &RightPlayer::positionchange);
    connect(r_player, &QMediaPlayer::durationChanged, this, &RightPlayer::durationchange);
    connect(r_playlist, &QMediaPlaylist::currentIndexChanged, this, &RightPlayer::playlistchange);

    ui->playlisttable->clear();

}

RightPlayer::~RightPlayer()
{
    delete ui;
}

void RightPlayer::browsefile()
{
    QStringList r_fileway = QFileDialog::getOpenFileNames(this,"Open folder", QDir::homePath());
    if (r_fileway.count()<1)
        return;

    for (int i=0; i<r_fileway.count();i++){
        QString pathfile=r_fileway.at(i);
        r_playlist->addMedia(QUrl::fromLocalFile(pathfile));
        QFileInfo fileInfo(pathfile);
        ui->playlisttable->addItem(fileInfo.fileName());
    }

    if (r_player->state() != QMediaPlayer::PlayingState){
        r_playlist->setCurrentIndex(0);
    }
    r_player->play();
}

void RightPlayer::playsong()
{
    if (r_player->state() == QMediaPlayer::PlayingState){
        r_player->pause();
        ui->stop_play->setText(">");
    }else{
        r_player->play();
    }
}

void RightPlayer::curschange(QMediaContent media)
{
    QString songway = media.canonicalUrl().toString();
    ui->songname->setText(songway.remove(0, songway.lastIndexOf("/") + 1));
}

void RightPlayer::statechange(int state)
{
    switch(state) {
        case QMediaPlayer::StoppedState: ui->stop_play->setText(">"); break;
        case QMediaPlayer::PlayingState: ui->stop_play->setText("||"); break;
    }
}

void RightPlayer::playlistchange(int position)
{
    ui->playlisttable->setCurrentRow(position);
}

void RightPlayer::on_playlisttable_doubleClicked(const QModelIndex &index)
{
    int clickedrow=index.row();
    r_playlist->setCurrentIndex(clickedrow);
    r_player->play();
}

void RightPlayer::on_nextsong_clicked()
{
    r_playlist->next();
}

void RightPlayer::on_previous_clicked()
{
    r_playlist->previous();
}

void RightPlayer::on_mute_clicked()
{
    if(ui->mute->text() == "Mute"){
        r_player->setMuted(true);
        ui->mute->setText("Unmute");
    }else{
        r_player->setMuted(false);
        ui->mute->setText("Mute");
    }
}

void RightPlayer::on_slidertime_sliderMoved(int position)
{
    r_player->setPosition(position);
}

void RightPlayer::durationchange(qint64 position)
{
    ui->slidertime->setMaximum(position);
}

void RightPlayer::positionchange(qint64 position)
{
    int fullsong = r_player->duration();
    ui->slidertime->setValue(position);
    QTime time = QTime::fromMSecsSinceStartOfDay(position);
    QTime fulltime = QTime::fromMSecsSinceStartOfDay(fullsong);

    ui->timesong->setText(time.toString("mm:ss") + "/" + fulltime.toString("mm:ss"));
}

void RightPlayer::on_deletesong_clicked()
{
    int songposition=ui->playlisttable->currentRow();
    QListWidgetItem *item=ui->playlisttable->takeItem(songposition);
    delete item;

    if (r_playlist->currentIndex() == songposition){
        int nextPos=0;
        if (songposition >= 1)
            nextPos = songposition - 1;

        r_playlist->removeMedia(songposition);

        if (ui->playlisttable->count()>0){
            r_playlist->setCurrentIndex(nextPos);
            playlistchange(nextPos);
        }else{
            r_player->stop();
        }
    }else{
        r_playlist->removeMedia(songposition);
    }

}

void RightPlayer::on_clearplaylist_clicked()
{
    r_playlist->clear();
    ui->playlisttable->clear();
    r_player->stop();

}

void RightPlayer::on_saveplaylist_clicked()
{
    QString pathplaylist = QFileDialog::getSaveFileName(this, "Save file", QDir::homePath(), "Text format (*.txt);;Another files (*)");


    r_playlist->save(QUrl::fromLocalFile(pathplaylist),"m3u");
}

void RightPlayer::on_loadplaylist_clicked()
{
    QString r_fileway = QFileDialog::getOpenFileName(this,"Open folder", QDir::homePath(),"TXT *.txt");
    if (r_fileway.isEmpty())
        return;
    QFile readFile(r_fileway);

    if (readFile.open(QIODevice::ReadOnly)) {
        QTextStream stream(&readFile);
        while (!stream.atEnd()) {
            QString s = stream.readLine();
            QString d = (s.trimmed()).remove(0, s.trimmed().indexOf("/") + 3);
            r_playlist->addMedia(QUrl::fromLocalFile(d));
            QFileInfo fileInfo(d);
            ui->playlisttable->addItem(fileInfo.fileName());
        }
        readFile.close();
    }

    if (r_player->state() != QMediaPlayer::PlayingState){
        r_playlist->setCurrentIndex(0);
    }
    r_player->play();

}


