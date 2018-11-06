#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPortInfo>
#include <QtSerialPort>
#include <QIODevice>
#include <QString>
#include <QQuickWidget>
#include <QtQml>
#include <QQuickItem>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString msg;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void clicked();

public slots:
    void on_pushButton_1on_clicked();

    void on_pushButton_1off_clicked();

    void on_pushButton_AllOn_clicked();

    void on_pushButton_AllOff_clicked();

    void on_pushButton_2on_clicked();

    void on_pushButton_2off_clicked();

    void on_pushButton_3on_clicked();

    void on_pushButton_3off_clicked();

    void on_pushButton_4on_clicked();

    void on_pushButton_4off_clicked();


private slots:
    void on_OpenSerialButton_clicked();
    void ReadData();
    void on_SendButton_clicked();

    void on_pushButton_clicked();





    void onClicked();

    void on_pushButton_scanTheSerioPort_clicked();

    void on_SendButton_AT_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    void initbutton();
    void initbuttonopen();

 //  QQuickWidget *m_quickWidget;
};

#endif // MAINWINDOW_H
