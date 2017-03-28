#ifndef FENETRE_H
#define FENETRE_H

#include <QtWidgets>
#include <QtNetwork>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QFile>
#include <QSystemTrayIcon>

class fenetre : public QWidget
{
    Q_OBJECT
public:
    fenetre();
private:
    QByteArray *md5;
    QByteArray *last_md5;

    QNetworkAccessManager *md5Manager;
    QNetworkAccessManager *imageManager;
    QNetworkReply *reply;

    QFile *file;
    QTimer *timer;
    QLabel *label;

    QVBoxLayout *layout;

    QSystemTrayIcon *trayIcon;
    QAction *quit;
private slots:
    void DLTest();
    void onDownloadFileComplete(QNetworkReply *reply);
    void onDownloadMd5FileComplete(QNetworkReply *reply);
    void goDLSlot();
signals:
    void goDL();
};

#endif // FENETRE_H
