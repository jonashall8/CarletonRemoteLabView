#include <QTcpServer>
#include <QTcpSocket>
#include <QCoreApplication>
#include <QTimer>
#include <QRandomGenerator>

class LabServer : public QTcpServer {
    Q_OBJECT
public:
    LabServer(quint16 port, QObject *parent = nullptr) : QTcpServer(parent) {
        listen(QHostAddress::Any, port);
        qInfo() << "Server started, listening on port" << port;
    }

protected:
    void incomingConnection(qintptr socketDescriptor) override {
        QTcpSocket *socket = new QTcpSocket(this);
        socket->setSocketDescriptor(socketDescriptor);

        connect(socket, &QTcpSocket::readyRead, [socket]() {
            QByteArray request = socket->readAll();
            if (request == "status") {
                QString status = (QRandomGenerator::global()->bounded(2) == 0) ? "Available" : "Busy";
                socket->write(status.toUtf8());
                socket->flush();
            }
        });

        connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    }
};

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    if (argc < 2) {
        qFatal("Usage: server <port>");
        return 1;
    }

    quint16 port = QString(argv[1]).toUShort();
    LabServer server(port);
    return app.exec();
}

#include "server.moc"