#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <unitree/robot/channel/channel_factory.hpp>
#include <unitree/robot/channel/channel_publisher.hpp>

using namespace unitree::robot;

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

        // Initialize DDS communication
        ChannelFactory::Instance()->Init(0); // Automatically select network interface
        publisher.reset(new ChannelPublisher<std::string>("robot_command_channel"));
        publisher->InitChannel();

        qDebug() << "DDS Publisher initialized for topic: robot_command_channel";
    }

private slots:
    void sendSitCommand() {
        sendCommand("sit");
    }

    void sendStandUpCommand() {
        sendCommand("stand_up");
    }

    void sendMoveForwardCommand() {
        sendCommand("move_forward");
    }

    void sendMoveBackwardCommand() {
        sendCommand("move_backward");
    }

private:
    void sendCommand(const std::string &command) {
        if (publisher->Write(command)) {
            qDebug() << "Command sent:" << QString::fromStdString(command);
        } else {
            qDebug() << "Failed to send command:" << QString::fromStdString(command);
        }
    }

    std::unique_ptr<ChannelPublisher<std::string>> publisher;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    RobotController controller;
    controller.show();

    return app.exec();
}

#include "qt_interface.moc"
