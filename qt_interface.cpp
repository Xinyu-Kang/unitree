#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QTcpSocket>
#include <QVBoxLayout>

class RobotController : public QWidget {
    Q_OBJECT

public:
    RobotController(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);

        QPushButton *sitButton = new QPushButton("Sit", this);
        QPushButton *standUpButton = new QPushButton("Stand Up", this);
        QPushButton *forwardButton = new QPushButton("Move Forward", this);
        QPushButton *backwardButton = new QPushButton("Move Backward", this);

        layout->addWidget(sitButton);
        layout->addWidget(standUpButton);
        layout->addWidget(forwardButton);
        layout->addWidget(backwardButton);

        connect(sitButton, &QPushButton::clicked, this, &RobotController::sendSitCommand);
        connect(standUpButton, &QPushButton::clicked, this, &RobotController::sendStandUpCommand);
        connect(forwardButton, &QPushButton::clicked, this, &RobotController::sendMoveForwardCommand);
        connect(backwardButton, &QPushButton::clicked, this, &RobotController::sendMoveBackwardCommand);

        tcpSocket = new QTcpSocket(this);
        tcpSocket->connectToHost("192.168.123.161", 8888);  // 连接机械狗
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
