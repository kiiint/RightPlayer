#ifndef RIGHTPLAYER_H
#define RIGHTPLAYER_H

#include <QMainWindow>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui { class RightPlayer; }
QT_END_NAMESPACE

class RightPlayer : public QMainWindow
{
    Q_OBJECT

public:
    RightPlayer(QWidget *parent = nullptr);
    ~RightPlayer();

private:
    Ui::RightPlayer *ui;
};

#endif // RIGHTPLAYER_H
