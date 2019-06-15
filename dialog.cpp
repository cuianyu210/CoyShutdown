#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
void Dialog::showMenu()
{
    m_menu->show();
}

void Dialog::showWindow()
{
    this->show();
}

void Dialog::toExit()
{
    exit(0);
}

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setMaximumSize(389, 113);
    setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);

    //创建托盘
    m_systemTray = new QSystemTrayIcon(this);
    m_systemTray->setIcon(QIcon(":/ico/CoyShutDown.ico"));
    m_systemTray->setToolTip("Coy Shutdown");
    m_systemTray->show();
    connect(m_systemTray, &QSystemTrayIcon::activated,
            this, &Dialog::activeTray);

    //托盘菜单
    m_menu = new QMenu(this);

    //设置托盘菜单子项
    m_action1 = new QAction(m_menu);
    m_action2 = new QAction(m_menu);

    //设置托盘子项文本
    m_action1->setText("打开主界面");
    m_action2->setText("退出");

    //将子项添加到托盘菜单中
    m_menu->addAction(m_action1);
    m_menu->addAction(m_action2);

    //子项对应的槽函数
    connect(m_action1, &QAction::triggered,
            this, &Dialog::showWindow);
    connect(m_action2, &QAction::triggered,
            this, &Dialog::toExit);
    m_systemTray->setContextMenu(m_menu);

    curDateTime = QDateTime::currentDateTime(); //读取当前日期时间
    shutFlag = false; //关机成立标记
    dateTimeStrFlag = false; //日期字符串设置标记
    ui->shutTimEdit->setTime(curDateTime.time());

    fTimer = new QTimer(this);
    fTimer->stop();
    fTimer->setInterval(1000);
    connect(fTimer, SIGNAL(timeout()),
            this, SLOT(on_timer_timerout()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_SettingBtn_clicked()
{
    QMessageBox::information(nullptr, nullptr, "已设置！");
    this->hide();
    fTimer->start();
    if (ui->setDatebtn->isChecked()) //日期窗口禁用
        ui->shutDateEdit->setEnabled(false);
    if (ui->isDelayShutChkBox->isChecked()) //关机延时窗口禁用
        ui->shutDelayBox->setEnabled(false);
    ui->shutTimEdit->setEnabled(false); //时间窗口禁用
}

void Dialog::on_canBtn_clicked()
{
    fTimer->stop();
    QString cmd("shutdown -a");
    pro.start(cmd);


    if (ui->setDatebtn->isChecked()) //设置日期窗口重新激活
        ui->shutDateEdit->setEnabled(true);
    if (ui->isDelayShutChkBox->isChecked()) //关机延时重新窗口激活
        ui->shutDelayBox->setEnabled(true);
    ui->shutTimEdit->setEnabled(true); //时间窗口重新激活

    shutFlag = false;
    QMessageBox::information(nullptr, nullptr, "已撤销！");
}

void Dialog::on_timer_timerout()
{
    curDateTime = QDateTime::currentDateTime();
    tmpDateStr = curDateTime.date().toString("yyyy-MM-dd");
    shutDateStr = ui->shutDateEdit->date().toString("yyyy-MM-dd");
    tmpTimStr = curDateTime.time().toString("hh:mm");
    shutTimStr = ui->shutTimEdit->time().toString("hh:mm");

    //关机命令初始化
    if (ui->isDelayShutChkBox->isChecked())
    {
        cmd = cmd.asprintf("shutdown /s /t %d", ui->shutDelayBox->value() * 60);
        qDebug("cmd的命令为:%s\n", cmd.toStdString().data());
    }
    else
    {
        cmd = "shutdown /s";
        qDebug("cmd的命令为:%s\n", cmd.toStdString().data());
    }

    if (ui->setDatebtn->isChecked())
    {
        if (tmpDateStr == shutDateStr)
        {
            if (tmpTimStr == shutTimStr)
            {
                if (!shutFlag)
                {
                    shutFlag = true;
                    pro.start(cmd);
                }
            }
        }
    }
    else if (tmpTimStr == shutTimStr)
    {
        if (!shutFlag)
        {
            shutFlag = true;
            pro.start(cmd);
        }
    }
}

//托盘相关槽函数
void Dialog::activeTray(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::DoubleClick: //双击事件
        showWindow();
        break;
    default:
        break;
    }
}

//点击关闭隐藏的系统托盘
void Dialog::closeEvent(QCloseEvent *event)
{
    if (ui->HideToSysTray->isChecked())
    {
        event->ignore();
        this->hide();
    }
}

void Dialog::on_setDatebtn_toggled(bool checked)
{
    if (checked)
        ui->shutDateEdit->setEnabled(true);
    else
        ui->shutDateEdit->setEnabled(false);
}

void Dialog::on_setDatebtn_clicked(bool checked)
{
    if (checked)
    {
        ui->shutDateEdit->setDate(curDateTime.date());
    }
    else
    {
        ui->shutDateEdit->setEnabled(false);
    }
}

void Dialog::on_isDelayShutChkBox_clicked(bool checked)
{
    //设置关机是否延时
    if (checked)
    {
        ui->shutDelayBox->setEnabled(true);
    }
    else
        ui->shutDelayBox->setEnabled(false);
}
