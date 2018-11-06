#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QQuickItem>
#include <QVBoxLayout>
#include <QQuickView>
#include <QWidget>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    initbutton();
    this->ui->quickWidget->setSource(QUrl("qrc:/switch/switchUI.qml"));
   // this->ui->quickWidget->setClearColor(QColor(Qt::WA_TranslucentBackground));


   /*
                            QQuickView *view = new QQuickView();
        QWidget *container = QWidget::createWindowContainer(view, this);
        container->setMinimumSize(200, 200);
        container->setMaximumSize(200, 200);
        container->setFocusPolicy(Qt::TabFocus);
        view->setSource(QUrl("qrc:/switch/switchUI.qml"));
        ui->verticalLayout->addWidget(container);
    */
    QQuickItem *item = this->ui->quickWidget->rootObject();
     connect(item,SIGNAL(switch1open()),this,SLOT(on_pushButton_1on_clicked())); //QML连接qwidget槽函数
     connect(item,SIGNAL(switch1off()),this,SLOT(on_pushButton_1off_clicked())); //QML连接qwidget槽函数

     connect(item,SIGNAL(switch2open()),this,SLOT(on_pushButton_2on_clicked())); //QML连接qwidget槽函数
     connect(item,SIGNAL(switch2off()),this,SLOT(on_pushButton_2off_clicked())); //QML连接qwidget槽函数

     connect(item,SIGNAL(switch3open()),this,SLOT(on_pushButton_3on_clicked())); //QML连接qwidget槽函数
     connect(item,SIGNAL(switch3off()),this,SLOT(on_pushButton_3off_clicked())); //QML连接qwidget槽函数

     connect(item,SIGNAL(switch4open()),this,SLOT(on_pushButton_4on_clicked())); //QML连接qwidget槽函数
     connect(item,SIGNAL(switch4off()),this,SLOT(on_pushButton_4off_clicked())); //QML连接qwidget槽函数

     connect(item,SIGNAL(switchallOn()),this,SLOT(on_pushButton_AllOn_clicked())); //QML连接qwidget槽函数
     connect(item,SIGNAL(switchallOff()),this,SLOT(on_pushButton_AllOff_clicked())); //QML连接qwidget槽函数
    //查找可用的串口
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->PortBox->addItem(serial.portName());
            serial.close();
        }
    }
    //设置波特率下来菜单默认显示第0项
    ui->BaudBox->setCurrentIndex(0);

   // QObject::connect(serial,&QSerialPort::readyRead,this,&MainWindow::ReadData);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_OpenSerialButton_clicked()
{
    if(ui->OpenSerialButton->text()==tr("打开串口"))
    {
        serial = new QSerialPort;
        //设置串口名
        serial->setPortName(ui->PortBox->currentText());
        //打开串口
        serial->open(QIODevice::ReadWrite);
        //设置波特率
       // serial->setBaudRate(QSerialPort::Baud9600  );

        switch (ui->BaudBox->currentIndex())
        {
        case 1:
            serial->setBaudRate(QSerialPort::Baud9600);
            break;
        case 2:
            serial->setBaudRate(QSerialPort::Baud19200);
            break;
        case 3:
            serial->setBaudRate(QSerialPort::Baud38400);
            break;
        case 4:
            serial->setBaudRate(QSerialPort::Baud57600);
            break;
        case 5:
            serial->setBaudRate(QSerialPort::Baud115200);
            break;
        default:
            break;

        }
        //设置数据位数
        switch (ui->BitBox->currentIndex())
        {

        case 8:
            serial->setDataBits(QSerialPort::Data8);//设置数据位8
            break;

        default:
            break;
        }
        //设置校验位
        switch (ui->ParityBox->currentIndex())
        {
        case 0:
            serial->setParity(QSerialPort::NoParity);
            break;
        default:
            break;
        }
        //设置停止位
        switch (ui->BitBox->currentIndex())
        {
        case 1:
            serial->setStopBits(QSerialPort::OneStop);
            break;
        case 2:
            serial->setStopBits(QSerialPort::TwoStop);
            break;

        default:
            break;
        }
        //设置流控制
        serial->setFlowControl(QSerialPort::NoFlowControl);
        //关闭设置菜单是能
        ui->PortBox->setEnabled(false);
        ui->BaudBox->setEnabled(false);
        ui->BitBox->setEnabled(false);
        ui->ParityBox->setEnabled(false);
        ui->StopBox->setEnabled(false);
        ui->OpenSerialButton->setText(tr("关闭串口"));
        initbuttonopen();

        //连接槽函数
        QObject::connect(serial,&QSerialPort::readyRead,this,&MainWindow::ReadData);

        QObject::connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(on_SendButton_AT_clicked()));



    }

    else if(ui->OpenSerialButton->text()==tr("关闭串口"))
    {
        //关闭串口
        serial->clear();
        serial->close();
        serial->deleteLater();
        //恢复使能
        ui->PortBox->setEnabled(true);
        ui->BaudBox->setEnabled(true);
        ui->BitBox->setEnabled(true);
        ui->ParityBox->setEnabled(true);
        ui->StopBox->setEnabled(true);
        ui->OpenSerialButton->setText(tr("打开串口"));
        initbutton();
    }
}

void MainWindow::ReadData()
{
   QByteArray buf;
    buf=serial->readAll();
    if(!buf.isEmpty())
    {
        QString str=ui->textEdit->toPlainText();

        QString tp= buf.mid(26, 2);
        QString hm= buf.mid(39, 4);
qDebug()<<buf;
         qDebug()<<tp;
         qDebug()<<hm;
        str+=tr(buf);
        ui->textEdit->clear();
        ui->textEdit->append(str);
    }
    buf.clear();

}

void MainWindow::on_SendButton_clicked()
{
    serial->write(ui->textEdit_2->toPlainText().toLatin1());

}


void MainWindow::on_pushButton_clicked()
{
    ui->textEdit->clear();
    ui->textEdit_2->clear();
}



void MainWindow::on_pushButton_1on_clicked()
{
    qDebug()<<"U" ;
    QString one_on="U";
    serial->write(one_on.toLatin1());

}

void MainWindow::on_pushButton_1off_clicked()
{
     qDebug()<<"u" ;
    QString one_on="u";
    serial->write(one_on.toLatin1());

}

void MainWindow::on_pushButton_AllOn_clicked()
{
    QString one_on="!";
    serial->write(one_on.toLatin1());

}

void MainWindow::on_pushButton_AllOff_clicked()
{
    QString one_on="@";
    serial->write(one_on.toLatin1());

}

void MainWindow::on_pushButton_2on_clicked()
{
    QString one_on="V";
    serial->write(one_on.toLatin1());

}

void MainWindow::on_pushButton_2off_clicked()
{
    QString one_on="v";
    serial->write(one_on.toLatin1());

}

void MainWindow::on_pushButton_3on_clicked()
{
    QString one_on="W";
    serial->write(one_on.toLatin1());

}

void MainWindow::on_pushButton_3off_clicked()
{
    QString one_on="w";
    serial->write(one_on.toLatin1());

}

void MainWindow::on_pushButton_4on_clicked()
{
    QString one_on="X";
    serial->write(one_on.toLatin1());

}

void MainWindow::on_pushButton_4off_clicked()
{
    QString one_on="x";
    serial->write(one_on.toLatin1());

}

void MainWindow::onClicked()
{
    qDebug()<<"信号正常";
}

void MainWindow::initbutton()
{
    ui->pushButton_1on->setEnabled(false);
    ui->pushButton_1off->setEnabled(false);
    ui->pushButton_2on->setEnabled(false);
    ui->pushButton_2off->setEnabled(false);
    ui->pushButton_3on->setEnabled(false);
    ui->pushButton_3off->setEnabled(false);
    ui->pushButton_4on->setEnabled(false);
    ui->pushButton_4off->setEnabled(false);
    ui->pushButton_AllOff->setEnabled(false);
    ui->pushButton_AllOn->setEnabled(false);
    ui->SendButton->setEnabled(false);
    ui->quickWidget->setEnabled(false);
    ui->SendButton_AT->setEnabled(false);
}

void MainWindow::initbuttonopen()
{
    ui->pushButton_1on->setEnabled(true);
    ui->pushButton_1off->setEnabled(true);
    ui->pushButton_2on->setEnabled(true);
    ui->pushButton_2off->setEnabled(true);
    ui->pushButton_3on->setEnabled(true);
    ui->pushButton_3off->setEnabled(true);
    ui->pushButton_4on->setEnabled(true);
    ui->pushButton_4off->setEnabled(true);
    ui->pushButton_AllOff->setEnabled(true);
    ui->pushButton_AllOn->setEnabled(true);
    ui->SendButton_AT->setEnabled(true);
    ui->SendButton->setEnabled(true);
    this->ui->quickWidget->setEnabled(true);
}


void MainWindow::on_pushButton_scanTheSerioPort_clicked()
{
    ui->PortBox->clear();
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->PortBox->addItem(serial.portName());
            serial.close();
        }
    }
}

void MainWindow::on_SendButton_AT_clicked()
{
    QString str=ui->lineEdit->text();

    /*
    char*  ch;
    QByteArray ba = str.toLatin1(); // must
    ch=ba.data();
    serial->write(ch);
   //  serial->write(str.toUtf8());
     qDebug()<<str.toLatin1();
    qDebug()<<str.toUtf8();
    qDebug()<<ch;

    */
    QByteArray ba=ui->lineEdit->text().toLatin1();   //取出TextEdit的内容并转换为QByteArray

    serial->write(ba+"\r\n");
    qDebug()<<serial;
  }
