#include "mainwindow.h"
#include "ui_mainwindow.h"

/* Qt headers */
#include <QDebug>
#include <QDateTime>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QTimer>
#include <QEventLoop>
#include <QPointer>
#include <QNetworkReply>
#include <QFileDialog>

/* Windows headers */
#include <WinSock2.h>
#include <Windows.h>

#include <fstream>
#include <bits/stdc++.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_sourceFile("")
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushBtnLogin_clicked()
{
    login();
}

void MainWindow::on_pushBtnSelectFile_clicked()
{
    openBrowserFileDlg();
}

void MainWindow::on_pushBtnSendData_clicked()
{
    sendData();
}

bool MainWindow::init()
{
    setWindowTitle("Demo VTP");
    ui->labelUser->setImageSource(":/images/User.png");
    ui->labelPassword->setImageSource(":/images/Key.png");
    ui->labelSelectedFile->clear();
    ui->pushBtnLogin->setText("Đăng nhập");
    ui->pushBtnSelectFile->setText("Chọn tệp");
    ui->pushBtnSendData->setText("Gửi dữ liệu");
    return true;
}

bool MainWindow::login()
{
    return true;
}

bool MainWindow::openBrowserFileDlg()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("Excel (*.xls *.xlsx)"));
    dialog.setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();
    auto firstFile = fileNames.at(0);
    m_sourceFile = firstFile.toStdString();
    string str = "Selected file: ";
    str += m_sourceFile;
    ui->labelSelectedFile->setText(QString::fromStdString(m_sourceFile));
    writeLog("log.txt", str);
    return true;
}

bool MainWindow::sendData()
{
    string vtpServer = "";
    QNetworkAccessManager mgr;
    std::wstring szQStr = L"{\"email\": \"";
//    szQStr += emailAddress.toStdWString();
//    szQStr += L"\",\"check_code\": \"";
//    szQStr += crcCode.toStdWString();
//    szQStr += L"\"}";

    qDebug() << "Query string: " << QString::fromStdWString(szQStr);

    // the HTTP request
    QNetworkRequest request;
    request.setUrl(QUrl(QString::fromStdString(vtpServer)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain"); //text/plain //application/json

    const int  TIMEOUT_LOAD_WEB_PAGE    = 5000;//5 seconds for timeout
    QTimer              m_Timer;
    QEventLoop          m_EventLoop;
    QPointer<QNetworkReply> m_Reply;

    mgr.clearAccessCache();
    m_Reply = mgr.post(request, QString::fromStdWString(szQStr).toUtf8());

    // "quit()" the event-loop, when the network request "finished()"
    QObject::connect(m_Reply, SIGNAL(finished()), &m_EventLoop, SLOT(quit()));
    QObject::connect(m_Reply, SIGNAL(error(QNetworkReply::NetworkError)), &m_EventLoop, SLOT(quit()));

    m_Timer.setSingleShot(true);
    QObject::connect(&m_Timer, SIGNAL(timeout()), &m_EventLoop, SLOT(quit()));
    m_Timer.start(TIMEOUT_LOAD_WEB_PAGE);

    m_EventLoop.exec(); // blocks stack until "finished()" has been called

    if (m_Reply->error() == QNetworkReply::NoError)
    {
        auto content = (QString)m_Reply->readAll();
        // parse the response JSON from the web service
        writeLog("log.txt", "Content: ");
        writeLog("log.txt", content.toStdString());
        return false;
    }
    else
    {
        string str = "Error of replying ";
        str += std::to_string(static_cast<int>(m_Reply->error()));
        writeLog("log.txt", str);
        return false;
    }
    return true;
}

bool MainWindow::writeLog(const string &filePath, const string &strStr)
{
    ofstream ofs(filePath, ios::app);
    ofs << strStr;
    ofs << endl;
    ofs.close();
    return true;
}
