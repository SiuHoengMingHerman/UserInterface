//    ______
//   /_  __/___  ____ ___  ___  ____
//    / / / __ \/ __ `__ \/ _ \/ __ \
//   / / / /_/ / / / / / /  __/ /_/ /
//  /_/  \____/_/ /_/ /_/\___/\____/
//              video for sports enthusiasts...
//
//

#include <iostream>
#include <QApplication>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlaylist>
#include <string>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileIconProvider>
#include <QDesktopServices>
#include <QImageReader>
#include <QStyle>
#include <QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include "the_player.h"
#include "the_button.h"

#include <QScrollArea>
#include <QPushButton>


// read in videos and thumbnails to this directory
std::vector<TheButtonInfo> getInfoIn (std::string loc) {

    std::vector<TheButtonInfo> out =  std::vector<TheButtonInfo>();
    QDir dir(QString::fromStdString(loc) );
    QDirIterator it(dir);

    while (it.hasNext()) { // for all files

        QString f = it.next();
            if (f.contains("."))

#if defined(_WIN32)
            if (f.contains(".wmv"))  { // windows
#else
            if (f.contains(".mp4") || f.contains("MOV"))  { // mac/linux
#endif

            QString thumb = f.left( f .length() - 4) +".png";
            if (QFile(thumb).exists()) { // if a png thumbnail exists
                /* Code added */
                QFileInfo info(f);
                /* end */
                QImageReader *imageReader = new QImageReader(thumb);
                    QImage sprite = imageReader->read(); // read the thumbnail
                    if (!sprite.isNull()) {
                        QIcon* ico = new QIcon(QPixmap::fromImage(sprite)); // voodoo to create an icon for the button
                        QUrl* url = new QUrl(QUrl::fromLocalFile( f )); // convert the file location to a generic url
                        //qDebug() << info.fileName();

                        out . push_back(TheButtonInfo( url , ico , info.size() , info.fileName()) ); // add to the output list
                    }
                    else
                        qDebug() << "warning: skipping video because I couldn't process thumbnail " << thumb << endl;
            }
            else
                qDebug() << "warning: skipping video because I couldn't find thumbnail " << thumb << endl;
        }
    }

    return out;
}


int main(int argc, char *argv[]) {

    // let's just check that Qt is operational first
    qDebug() << "Qt version: " << QT_VERSION_STR << endl;

    // create the Qt Application
    QApplication app(argc, argv);

    // collect all the videos in the folder
    std::vector<TheButtonInfo> videos;

    if (argc == 2)
        videos = getInfoIn( std::string(argv[1]) );

    if (videos.size() == 0) {

        const int result = QMessageBox::information(
                    NULL,
                    QString("Tomeo"),
                    QString("no videos found! Add command line argument to \"quoted\" file location."));
        exit(-1);
    }

    // the widget that will show the video
    QVideoWidget *videoWidget = new QVideoWidget;

    // the QMediaPlayer which controls the playback
    ThePlayer *player = new ThePlayer;
    player->setVideoOutput(videoWidget);

    // a row of buttons
    QWidget *buttonWidget = new QWidget();
    // a list of the buttons
    std::vector<TheButton*> buttons;
    // the buttons are arranged horizontally
    QVBoxLayout *layout = new QVBoxLayout();
    buttonWidget->setLayout(layout);

    /* Code added */
    QWidget *infoWidget = new QWidget();
    QWidget *nameWidget = new QWidget();


    //scrolling area
    QScrollArea *scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    QWidget *sidebar = new QWidget();
    scroll->setWidget(sidebar);
    scroll->widget()->setLayout(layout);
    scroll->setFixedWidth(250);


    QHBoxLayout *infoLayout = new QHBoxLayout(infoWidget);
    QHBoxLayout *nameLayout = new QHBoxLayout(nameWidget);
    //information for the video

    infoWidget->setLayout(infoLayout);
    nameWidget->setLayout(nameLayout);


    //name should put it on top
    QLabel *nameLabel = new QLabel("No Name", nameWidget);
    QLabel *addressLabel = new QLabel("No Address", infoWidget);
    QLabel *sizeLabel = new QLabel("No Size", infoWidget);

    std::vector<QLabel*> labels(3);
    labels[0] = nameLabel;
    labels[1] = addressLabel;
    labels[2] = sizeLabel;

    nameLayout->addWidget(nameLabel);

    infoLayout->addWidget(addressLabel);
    infoLayout->addWidget(sizeLabel);



    player->setLabels(labels);
    /* end */

    nameLabel->setAlignment(Qt:: AlignCenter);
    addressLabel->setAlignment(Qt:: AlignLeft);
    sizeLabel->setAlignment(Qt:: AlignRight);
    // create the four buttons
    for ( int i = 0; i < 7; i++ ) {
        TheButton *button = new TheButton(buttonWidget);
        button->connect(button, SIGNAL(jumpTo(TheButtonInfo*, std::vector<QLabel*>)), player, SLOT (jumpTo(TheButtonInfo*, std::vector<QLabel*>))); // when clicked, tell the player to play.
        buttons.push_back(button);
        layout->addWidget(button);
        button->init(&videos.at(i), labels);
    }

    // tell the player what buttons and videos are available
    player->setContent(&buttons, & videos);


    // create the main window and layout
    QWidget window;
    QHBoxLayout *top = new QHBoxLayout();
    window.setLayout(top);
    window.setWindowTitle("tomeo");
    window.setMinimumSize(800, 680);

    //
    QWidget *vidInfo = new QWidget();

    QVBoxLayout *infoVid = new QVBoxLayout();
//    QVBoxLayout *nameVid = new QVBoxLayout();
//    vidInfo->setLayout(nameVid);
    vidInfo->setLayout(infoVid);

//    QWidget * widget = new QWidget();
//    scroll->setWidget(widget);
//    scroll->widget()->setLayout(buttons);
    QBoxLayout *controls = new QHBoxLayout();
    QWidget *buttonControls= new QWidget();
    QAbstractButton *pausebutton = new QPushButton(buttonControls);
    QAbstractButton *playbutton = new QPushButton(buttonControls);
    QAbstractButton *stopbutton = new QPushButton(buttonControls);
    pausebutton->setText("||");
    pausebutton->setFixedSize(50, 50);
    pausebutton->setShortcut(Qt::Key_Space);
    playbutton->setText(" ▷ ");
    playbutton->setFixedSize(50, 50);
    stopbutton->setText("▣");
    stopbutton->setFixedSize(50, 50);

    playbutton->connect(playbutton, &QAbstractButton::clicked, player, &QMediaPlayer::play);
    pausebutton->connect(pausebutton, &QAbstractButton::clicked, player, &ThePlayer::mPause);
    stopbutton->connect(stopbutton, &QAbstractButton::clicked, player, &QMediaPlayer::stop);

    controls->addWidget(playbutton);
    controls->addWidget(pausebutton);
    controls->addWidget(stopbutton);

    // add the video and the buttons to the top level widget
    infoVid->addWidget(nameWidget);
    infoVid->addWidget(infoWidget);
    infoVid->addWidget(videoWidget);
    infoVid->addLayout(controls);

    top->addWidget(vidInfo);
    top->addWidget(buttonWidget);
    top->addWidget(scroll);

    // showtime!
    window.show();

    // wait for the app to terminate
    return app.exec();
}
