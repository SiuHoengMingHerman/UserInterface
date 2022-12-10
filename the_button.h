//
// Created by twak on 11/11/2019.
//

#ifndef CW2_THE_BUTTON_H
#define CW2_THE_BUTTON_H

#include <QPushButton>
#include <QUrl>

/* header added */
#include <QtWidgets/QLabel>
#include <vector>
/* end */

class TheButtonInfo {

public:
    QUrl* url; // video file to play
    QIcon* icon; // icon to display

    /* fields added */
    qint64 size; // the size of video
    QString name; // the name of video
    /* end */

    TheButtonInfo ( QUrl* url, QIcon* icon, qint64 size, QString name) : url (url), icon (icon), size(size), name(name) {}
};

class TheButton : public QPushButton {
    Q_OBJECT

public:
    TheButtonInfo* info;
    std::vector<QLabel*> labels;
    
     TheButton(QWidget *parent) :  QPushButton(parent) {
         setIconSize(QSize(200,110));
         connect(this, SIGNAL(released()), this, SLOT (clicked() )); // if QPushButton clicked...then run clicked() below
    }

    void init(TheButtonInfo* i, std::vector<QLabel*> l);

private slots:
    void clicked();

signals:
    void jumpTo(TheButtonInfo*, std::vector<QLabel*>);

};

#endif //CW2_THE_BUTTON_H
