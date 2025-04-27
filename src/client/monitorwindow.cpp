#include "monitorwindow.h"
#include <QVBoxLayout>
#include <QTimer>
#include <QColor>
#include <QHeaderView>
#include <QFont>

MonitorWindow::MonitorWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);

    table = new QTableWidget(0, 2);
    table->setHorizontalHeaderLabels({"Lab Computer", "Status"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Fancy header styling
    QFont headerFont = table->horizontalHeader()->font();
    headerFont.setBold(true);
    headerFont.setPointSize(12);
    table->horizontalHeader()->setFont(headerFont);
    table->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    layout->addWidget(table);
    setCentralWidget(central);

    // Define friendly computer names with their address/port
    labComputers = {
        {"PC-A", {"127.0.0.1", 12345}},
        {"PC-B", {"127.0.0.1", 12346}},
        {"PC-C", {"127.0.0.1", 12347}}
    };

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MonitorWindow::updateLabStatus);
    timer->start(3000); // Update every 3 seconds
}

void MonitorWindow::updateLabStatus() {
    table->setRowCount(labComputers.size());

    int row = 0;
    for (auto it = labComputers.begin(); it != labComputers.end(); ++it) {
        const QString &computerName = it.key();
        const auto &[address, port] = it.value();

        table->setItem(row, 0, new QTableWidgetItem(computerName));

        QTcpSocket socket;
        socket.connectToHost(address, port);

        QTableWidgetItem *statusItem = new QTableWidgetItem;

        if (socket.waitForConnected(300)) {
            socket.write("status");
            socket.waitForBytesWritten();
            socket.waitForReadyRead();
            QString status = socket.readAll();

            if (status == "Available") {
                statusItem->setText("Available");
                statusItem->setForeground(QColor(Qt::green));
            } else {
                statusItem->setText("Busy");
                statusItem->setForeground(QColor(Qt::red));
            }

        } else {
            statusItem->setText("Offline");
            statusItem->setForeground(QColor(Qt::gray));
        }

        table->setItem(row, 1, statusItem);
        row++;
    }
}