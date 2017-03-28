#include "fenetre.h"

fenetre::fenetre()
{
    setWindowIcon(QIcon(":/image/icone.png"));
    imageManager = new QNetworkAccessManager(this);
    layout = new QVBoxLayout;
    label = new QLabel;
    layout->addWidget(label);
    this->setLayout(layout);

    last_md5 = new QByteArray;
    md5 = new QByteArray;
    md5Manager = new QNetworkAccessManager(this);

    timer = new QTimer;
    timer->start(60000);
    move(QPoint(100, 100));
    QTimer::singleShot(200, this, SLOT(DLTest()));
    QTimer::singleShot(300, this, SLOT(goDLSlot()));

    trayIcon = new QSystemTrayIcon;
    trayIcon->setIcon(QIcon(":/image/icone.png"));
    trayIcon->show();
    trayIcon->setToolTip("Emploi du temps !");

    connect(imageManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onDownloadFileComplete(QNetworkReply *)));
    connect(timer, SIGNAL(timeout()), this, SLOT(DLTest()));
    connect(this, SIGNAL(goDL()), this, SLOT(goDLSlot()));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(close()));
}

void fenetre::onDownloadFileComplete(QNetworkReply *reply)
{
    QFile file("wSySwC9C.png");
    file.open(QIODevice::WriteOnly);
    file.write(reply->readAll());
    file.close();
}

void fenetre::goDLSlot()
{
    imageManager->get(QNetworkRequest(QUrl("http://88.123.43.158//aze/PROJET_EDT/image1.png")));
    label->setPixmap(QPixmap("wSySwC9C.png"));

}

void fenetre::DLTest()
{
    connect(md5Manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onDownloadMd5FileComplete(QNetworkReply *)));
    md5Manager->get(QNetworkRequest(QUrl("http://88.123.43.158//aze/PROJET_EDT/md5.txt")));

}

void fenetre::onDownloadMd5FileComplete(QNetworkReply *reply)
{
    QByteArray *result = new QByteArray;
    *result = reply->readAll();
    *md5 = *result;

    bool yep = QFile::exists("md5.txt");
    if(yep)
    {
        QFile file("md5.txt");
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        *last_md5 = file.readAll();
        file.close();
        file.open(QIODevice::WriteOnly);
        file.write(*md5);
        if(*md5 != *last_md5)
        {
            emit goDL();
        }
        file.close();
    }
    else
    {
        QFile file("md5.txt");
        file.open(QIODevice::WriteOnly);
        file.write(*md5);
        file.close();
        emit goDL();
    }
}
