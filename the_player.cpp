//
// Created by twak on 11/11/2019.
//

#include "the_player.h"

// all buttons have been setup, store pointers here
void ThePlayer::setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i) {
    buttons = b;
    infos = i;
    jumpTo(buttons -> at(0) -> info, labels);
}

/* code added */
void ThePlayer::setLabels(std::vector<QLabel *> l){
    labels = l;
}
/* end */

//void ThePlayer::playStateChanged (QMediaPlayer::State ms) {
//    switch (ms) {
//        case QMediaPlayer::State::StoppedState:
//            play(); // starting playing again...
//            break;
//        case QMediaPlayer::State::PausedState:
//            stop();
//            break;
//    default:
//        break;
//    }
//}

void ThePlayer::jumpTo (TheButtonInfo* button, std::vector<QLabel*> labels) {
    setMedia( * button -> url);
    labels[0]->setText(button->name);
    labels[1]->setText(button->url->toString());
    std::stringstream ss;
    ss << button->size;
    char string[50] = "";
    ss >> string;
    labels[2]->setText(string);
    play();
}

void ThePlayer::mPause(){
    pause();
}

void ThePlayer::mPlay(){
    play();
}

void ThePlayer::seek(int seconds)
{
    this->setPosition(seconds * 1000);
}

qint64 ThePlayer::mduration()
{
    return duration();
}

void ThePlayer::mdurationChanged(qint64 duration, QSlider *slider)
{
    m_duration = duration / 500;
    slider->setMaximum(m_duration);
}

void ThePlayer::mfullScreen(QVideoWidget *thing)
{
    if(thing->isFullScreen() == false)
    {
        thing->setFullScreen(true);
    }
    else{
        thing->setFullScreen(false);
    }
}

void ThePlayer::showDuration(QSlider *time, qint64 progress)
{
   time->setValue(progress/1000);
}
//void ThePlayer::dropInfo(QMessageBox *yes)
//{
//    yes->open();s
//}
void ThePlayer::positionChanged(qint64 progress)
{
        m_slider->setValue(progress / 1000);
}

void ThePlayer::showInfo(QLabel *name, QLabel *address, QLabel *size)
{
    if(!infoBox)
    {
        QBoxLayout *infolayout = new QVBoxLayout;
        QPushButton *button = new QPushButton(tr("Close"));
        infolayout->addWidget(name);
        infolayout->addWidget(address);
        infolayout->addWidget(size);
        infolayout->addWidget(button);

        infoBox = new QDialog();
        infoBox->setWindowTitle(tr("Video Information"));
        infoBox->setLayout(infolayout);

        connect(button, &QPushButton::clicked, infoBox, &QDialog::close);
    }
    infoBox->show();
}
void ThePlayer::showColorDialog(QVideoWidget *m_videoWidget)
{
    if (!dialogBox) {
        QSlider *brightnessSlider = new QSlider(Qt::Horizontal);
        brightnessSlider->setRange(-100, 100);
        brightnessSlider->setValue(m_videoWidget->brightness());
        connect(brightnessSlider, &QSlider::sliderMoved, m_videoWidget, &QVideoWidget::setBrightness);
        connect(m_videoWidget, &QVideoWidget::brightnessChanged, brightnessSlider, &QSlider::setValue);

        QSlider *contrastSlider = new QSlider(Qt::Horizontal);
        contrastSlider->setRange(-100, 100);
        contrastSlider->setValue(m_videoWidget->contrast());
        connect(contrastSlider, &QSlider::sliderMoved, m_videoWidget, &QVideoWidget::setContrast);
        connect(m_videoWidget, &QVideoWidget::contrastChanged, contrastSlider, &QSlider::setValue);

        QSlider *hueSlider = new QSlider(Qt::Horizontal);
        hueSlider->setRange(-100, 100);
        hueSlider->setValue(m_videoWidget->hue());
        connect(hueSlider, &QSlider::sliderMoved, m_videoWidget, &QVideoWidget::setHue);
        connect(m_videoWidget, &QVideoWidget::hueChanged, hueSlider, &QSlider::setValue);

        QSlider *saturationSlider = new QSlider(Qt::Horizontal);
        saturationSlider->setRange(-100, 100);
        saturationSlider->setValue(m_videoWidget->saturation());
        connect(saturationSlider, &QSlider::sliderMoved, m_videoWidget, &QVideoWidget::setSaturation);
        connect(m_videoWidget, &QVideoWidget::saturationChanged, saturationSlider, &QSlider::setValue);

        QFormLayout *layout = new QFormLayout;
        layout->addRow(tr("Brightness"), brightnessSlider);
        layout->addRow(tr("Contrast"), contrastSlider);
        layout->addRow(tr("Hue"), hueSlider);
        layout->addRow(tr("Saturation"), saturationSlider);

        QPushButton *button = new QPushButton(tr("Close"));
        layout->addRow(button);

        dialogBox = new QDialog();
        dialogBox->setWindowTitle(tr("Color Options"));
        dialogBox->setLayout(layout);

        connect(button, &QPushButton::clicked, dialogBox, &QDialog::close);
    }
    dialogBox->show();
}
