#include "dialog.h"
#include "ui_dialog.h"

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
    setMaximumSize(313, 159);
    setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);

    //关机命令初始化
    cmd = "shutdown -s";

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
    dateFlag = false; //日期标记
    shutFlag = false; //关机成立标记
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
    QMessageBox::about(nullptr, nullptr, "已设置。。。");
    fTimer->start();
}

void Dialog::on_canBtn_clicked()
{
    fTimer->stop();
    QString cmd("shutdown -a");
    pro.start(cmd);
    QMessageBox::about(nullptr, nullptr, "已撤销。。。");
}

void Dialog::on_timer_timerout()
{
    curDateTime = QDateTime::currentDateTime();

    tmpDateStr = curDateTime.date().toString("yyyy-MM-dd");
    shutDateStr = ui->shutDateEdit->date().toString("yyyy-MM-dd");
    tmpTimStr = curDateTime.time().toString("hh:mm");
    shutTimStr = ui->shutTimEdit->time().toString("hh:mm");

    if (dateFlag)
    {
        if (tmpDateStr == shutDateStr)
        {
            if (tmpTimStr == shutTimStr)
            {
                if (!shutFlag)
                {
                    shutFlag = true;
                    QMessageBox::information(nullptr,nullptr, "即将关闭操作系统...",  nullptr, nullptr);
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
            QMessageBox::information(nullptr,nullptr, "即将关闭操作系统...",  nullptr, nullptr);
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
        dateFlag = true;
        ui->shutDateEdit->setDate(curDateTime.date());
    }
    else
    {
        dateFlag = false;
    }

}
