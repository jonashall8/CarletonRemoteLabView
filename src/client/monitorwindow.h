#ifndef MONITORWINDOW_H
#define MONITORWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QMap>
#include <QTcpSocket>

class MonitorWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MonitorWindow(QWidget *parent = nullptr);

private slots:
    void updateLabStatus();

private:
    QTableWidget *table;
    QMap<QString, QPair<QString, quint16>> labComputers; // Name -> (Address, Port)
};

#endif // MONITORWINDOW_H