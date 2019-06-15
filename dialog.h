#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QProcess>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCloseEvent>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
private:
    QProcess pro;
    QTimer* fTimer;
    QDate m_date;
    QTime m_time;
    QDateTime curDateTime;
    QSystemTrayIcon* m_systemTray;
    QMenu* m_menu;
    QAction* m_action1;
    QAction* m_action2;
    bool shutFlag;
    bool dateTimeStrFlag;
    QString cmd;
    QString tmpDateStr;
    QString shutDateStr;
    QString tmpTimStr;
    QString shutTimStr;
    void showMenu();
    void showWindow();
    void toExit() __attribute__((noreturn));
public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_SettingBtn_clicked();
    void on_canBtn_clicked();
    void on_timer_timerout();
    void activeTray(QSystemTrayIcon::ActivationReason reason);
    void closeEvent(QCloseEvent * event);
    void on_setDatebtn_toggled(bool checked);

    void on_setDatebtn_clicked(bool checked);

    void on_isDelayShutChkBox_clicked(bool checked);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
