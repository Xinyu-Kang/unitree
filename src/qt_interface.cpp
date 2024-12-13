#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QTcpSocket>
#include <QVBoxLayout>
#include <QDebug>

class RobotController : public QWidget {
    Q_OBJECT

public:
    RobotController(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);

        QPushButton *sitButton = new QPushButton(tr("Sit"), this);
        QPushButton *standUpButton = new QPushButton(tr("Stand Up"), this);
        QPushButton *forwardButton = new QPushButton(tr("Move Forward"), this);
        QPushButton *backwardButton = new QPushButton(tr("Move Backward"), this);

        layout->addWidget(sitButton);
        layout->addWidget(standUpButton);
        layout->addWidget(forwardButton);
        layout->addWidget(backwardButton);

        connect(sitButton, &QPushButton::clicked, this, &RobotController::sendSitCommand);
        connect(standUpButton, &QPushButton::clicked, this, &RobotController::sendStandUpCommand);
        connect(forwardButton, &QPushButton::clicked, this, &RobotController::sendMoveForwardCommand);
        connect(backwardButton, &QPushButton::clicked, this, &RobotController::sendMoveBackwardCommand);

        tcpSocket = new QTcpSocket(this);

        // Connect to host
        tcpSocket->connectToHost("192.168.123.161", 8888);

        // Handle connection success or error
        connect(tcpSocket, &QTcpSocket::connected, []() {
            qDebug() << "Successfully connected to the server!";
        });
        connect(tcpSocket, &QTcpSocket::errorOccurred, [](QAbstractSocket::SocketError error) {
            qDebug() << "Connection failed with error:" << error;
        });
    }

private slots:
    void sendSitCommand() {
        tcpSocket->write("sit");
    }

    void sendStandUpCommand() {
        tcpSocket->write("stand_up");
    }

    void sendMoveForwardCommand() {
        tcpSocket->write("move_forward");
    }

    void sendMoveBackwardCommand() {
        tcpSocket->write("move_backward");
    }

private:
    QTcpSocket *tcpSocket;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    RobotController controller;
    controller.show();

    return app.exec();
}

#include "qt_interface.moc"
