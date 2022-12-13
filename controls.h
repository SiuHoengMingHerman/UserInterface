#ifndef CONTROLS_H
#define CONTROLS_H

#include <QMediaPlayer>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QAbstractButton;
class QAbstractSlider;
class QComboBox;
QT_END_NAMESPACE

class controls : public QWidget
{
public:
    explicit controls(QWidget *parent = nullptr);
    QMediaPlayer::State mediaStatus() const;

public slots:
    void setState(QMediaPlayer::State state);

signals:
    void play();
    void pause();
    void stop();

private slots:
    void playClicked();
private:
    QMediaPlayer::State status = QMediaPlayer::StoppedState;
    QAbstractButton *playbutton = nullptr;
    QAbstractButton *stopbutton = nullptr;
};

#endif // CONTROLS_H
