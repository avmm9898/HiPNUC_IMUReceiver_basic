#include "mainwindow.h"
#include "ui_mainwindow.h"

/*

C++ QT example.Here are 3 steps to follow,
 1. "imu_data_decode_init()" -> is for the RFreceiver and the node to initiate
 2. "kptl_decode(c)" -> to decode every character from serial port.
 3. Declare a "imu_data_t imu", and call the function "dump_rf_data(&imu)" or "dump_imu_data(&imu)";
    it will pass the data to your "imu"
 4. If you are using wireless receiver, you need to change "rf_slave_cnt" in imu_data_decode.cpp, or program will crash.
    the datatypes in imu_data_t: see "imu_data_decode.h", RF means RFceiver.

 C++ QT 範例:
 1. "imu_data_decode_init()" -> 初始化一次 RFreceiver 和 node
 2. "kptl_decode(c)" -> 接收到來自序列的單個字元並解析
 3. 宣告 "imu_data_t imu", 透過 "dump_rf_data(&imu)"(無線接收器)或 "dump_imu_data(&imu)"(USB節點);
    將數據存入"imu".
 4. 若使用無線接收器, 必須設定在 imu_data_decode.cpp 設定 "rf_slave_cnt" 的值為節點數量 ,
    節點 ID 必須依照順序從 0 開始設定 , 否則會閃退.

*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {

        //qDebug() << "Name : "<< com_info.portName();
        //qDebug() << "Description : "  << com_info.description();
        //qDebug() << "Serial Number: " << com_info.serialNumber();
        ui->Com_combo->addItem(info.portName()+" : "+info.description());
    }
    ui->imu_btn->setChecked(1);

    /********setting table**********/

    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);

    QString title1="Quaternion,W,X,Y,Z";
    QString title2="Euler Angle,Pitch,Roll,Yaw";
    QString title3="Acceleration,X,Y,Z";
    QString title4="Gyroscope,X,Y,Z";
    QString title5="Magnetic field,X,Y,Z";

    foreach(QString item,  title1.split(",")){
        static int i=0;
        QTableWidgetItem * protoitem = new QTableWidgetItem(item);
        protoitem->setFlags(protoitem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
        protoitem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(0,i,protoitem);
        i++;
    }
    foreach(QString item,  title2.split(",")){
        static int i=0;
        QTableWidgetItem * protoitem = new QTableWidgetItem(item);
        protoitem->setFlags(protoitem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
        protoitem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(2,i,protoitem);
        i++;
    }
    foreach(QString item,  title3.split(",")){
        static int i=0;
        QTableWidgetItem * protoitem = new QTableWidgetItem(item);
        protoitem->setFlags(protoitem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
        protoitem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(4,i,protoitem);
        i++;
    }
    foreach(QString item,  title4.split(",")){
        static int i=0;
        QTableWidgetItem * protoitem = new QTableWidgetItem(item);
        protoitem->setFlags(protoitem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
        protoitem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(6,i,protoitem);
        i++;
    }
    foreach(QString item,  title5.split(",")){
        static int i=0;
        QTableWidgetItem * protoitem = new QTableWidgetItem(item);
        protoitem->setFlags(protoitem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
        protoitem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(8,i,protoitem);
        i++;
    }
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_serial_init_clicked()
{

    QString m_PortName = ui->Com_combo->currentText().split(" : ").at(0);
    m_reader.setPortName(m_PortName);

    if(m_reader.open(QIODevice::ReadWrite))
    {

        m_reader.setBaudRate(QSerialPort::Baud115200);
        m_reader.setParity(QSerialPort::NoParity);
        m_reader.setDataBits(QSerialPort::Data8);
        m_reader.setStopBits(QSerialPort::OneStop);
        m_reader.setFlowControl(QSerialPort::NoFlowControl);
        m_reader.clearError();
        m_reader.clear();
        connect(&m_reader, SIGNAL(readyRead()), this, SLOT(read_serial()));

    }

    imu_data_decode_init();

    //set a timer to display data from port
    connect(&display_timer, SIGNAL(timeout()), this, SLOT(get_data()));
    display_timer.start(50);



}

void MainWindow::read_serial()
{
    //qDebug() << "read";
    auto NumberOfBytesToRead = m_reader.bytesAvailable();

    if(NumberOfBytesToRead > 0 && m_reader.isReadable())
    {
        QByteArray arr = m_reader.readAll();

        for (int i=0;i<NumberOfBytesToRead;i++) {
            uint8_t c=arr[i];
            packet_decode(c);
        }
    }

}

void MainWindow::get_data()
{


    if(receive_gwsol.tag != KItemGWSOL)
    {
        /* imu data packet */
        ShowOnTable(receive_imusol);
    }
    else
    {
        int slave_id=ui->rf_id_combobox->currentIndex();
        /* wireless data packet */

        for(int i = 0; i < receive_gwsol.n; i++)
        {
            if(QString::number(receive_gwsol.gw_id)!="")
                ui->imu_btn->setText("IMU(ID = "+QString::number(receive_gwsol.gw_id)+")");
            else
                ui->imu_btn->setText("IMU(ID = Nan)");
            ShowOnTable(receive_gwsol.receive_imusol[slave_id]);

        }
    }


}

void MainWindow::on_Com_Refresh_btn_clicked()
{
    ui->Com_combo->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        com_info = info;
        qDebug() << "Name : "<< com_info.portName();
        qDebug() << "Description : "  << com_info.description();
        qDebug() << "Serial Number: " << com_info.serialNumber();
        ui->Com_combo->addItem(com_info.portName()+" : "+com_info.description());
    }
}

void MainWindow::ShowOnTable(receive_imusol_packet_t imu)
{
    for(int i=0;i<4;i++){
        QString item= QString::number(imu.quat[i],'f',3);
        QTableWidgetItem * protoitem = new QTableWidgetItem(item);
        protoitem->setTextAlignment(Qt::AlignCenter);

        ui->tableWidget->setItem(1,i+1,protoitem);
    }

    for(int i=0;i<3;i++){
        QString item= QString::number(imu.eul[i],'f',3);
        QTableWidgetItem * protoitem = new QTableWidgetItem(item);
        protoitem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(3,i+1,protoitem);
        if(i==2){
            ui->tableWidget->setItem(3,4,new QTableWidgetItem("degree"));
        }
    }

    for(int i=0;i<3;i++){
        QString item= QString::number(imu.acc[i]);
        QTableWidgetItem * protoitem = new QTableWidgetItem(item);
        protoitem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(5,i+1,protoitem);
        if(i==2){
            ui->tableWidget->setItem(5,4,new QTableWidgetItem("0.001G"));
        }
    }

    for(int i=0;i<3;i++){
        QString item= QString::number(imu.gyr[i]);
        QTableWidgetItem * protoitem = new QTableWidgetItem(item);
        protoitem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(7,i+1,protoitem);
        if(i==2){
            ui->tableWidget->setItem(7,4,new QTableWidgetItem("0.1°/s"));
        }
    }

    for(int i=0;i<3;i++){
        QString item= QString::number(imu.mag[i]);
        QTableWidgetItem * protoitem = new QTableWidgetItem(item);
        protoitem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(9,i+1,protoitem);
        if(i==2){
            ui->tableWidget->setItem(9,4,new QTableWidgetItem("0.001Gauss"));
        }
    }
}

void MainWindow::on_rf_btn_clicked()
{
    for (int i=0;i<receive_gwsol.n;i++) {
        ui->rf_id_combobox->addItem(QString::number(i));
    }
}

void MainWindow::on_btn_serial_stop_clicked()
{
    m_reader.disconnect();
    display_timer.disconnect();
    m_reader.close();
}
