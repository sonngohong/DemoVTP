#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>

// Add a new comment

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushBtnLogin_clicked();

    void on_pushBtnSelectFile_clicked();

    void on_pushBtnSendData_clicked();

private:
    Ui::MainWindow *ui;

    bool init();

    bool login();

    bool openBrowserFileDlg();

    bool sendData();

    bool writeLog(const string& filePath, const string& strStr);

    string m_sourceFile;
};
#endif // MAINWINDOW_H
