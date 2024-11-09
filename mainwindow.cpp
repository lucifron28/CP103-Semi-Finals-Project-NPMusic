#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButtonPause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->pushButtonPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButtonStop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->pushButtonBack->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->pushButtonForward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));

    ui->pushButtonPause->setStyleSheet(buttonStyle);
    ui->pushButtonPlay->setStyleSheet(buttonStyle);
    ui->pushButtonStop->setStyleSheet(buttonStyle);
    ui->pushButtonBack->setStyleSheet(buttonStyle);
    ui->pushButtonForward->setStyleSheet(buttonStyle);

    ui->pushButtonVolume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    ui->pushButtonVolume->setStyleSheet(buttonStyle);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonVolume_clicked()
{
    if (is_muted == false) {
        is_muted = true;
        ui->pushButtonVolume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    } else {
        is_muted = false;
            ui->pushButtonVolume->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
    }
}

