#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , player(new QMediaPlayer(this))
    , audioOutput(new QAudioOutput(this))
{
    ui->setupUi(this);

    player->setAudioOutput(audioOutput);

    ui->pushButtonPlayPause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->pushButtonStop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->pushButtonBack->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->pushButtonForward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));

    ui->pushButtonPlayPause->setStyleSheet(buttonStyle);
    ui->pushButtonStop->setStyleSheet(buttonStyle);
    ui->pushButtonBack->setStyleSheet(buttonStyle);
    ui->pushButtonForward->setStyleSheet(buttonStyle);

    ui->pushButtonVolume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    ui->pushButtonVolume->setStyleSheet(buttonStyle);

    ui->tableWidgetSongQueue->setColumnCount(3);
    headers << "No." << "Track" << "Artist";
    ui->tableWidgetSongQueue->setHorizontalHeaderLabels(headers);

    ui->tableWidgetSongQueue->setColumnWidth(0, 30);
    ui->tableWidgetSongQueue->setColumnWidth(1, 235);

    qDebug() << "Current working directory:" << QDir::currentPath();

    QString musicDirectory = "..\\..\\music";
    listMp3Files(musicDirectory);

    ui->verticalSliderVolume->setMinimum(1);
    ui->verticalSliderVolume->setMaximum(100);
    ui->verticalSliderVolume->setValue(50); // Set initial volume to 50%

    // Connect the slider's valueChanged signal to the slot
    connect(ui->verticalSliderVolume, &QSlider::valueChanged, this, &MainWindow::on_verticalSliderVolume_valueChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);
    connect(ui->horizontalSliderDuration, &QSlider::sliderMoved, this, &::MainWindow::on_horizontalSliderDuration_sliderMoved);
    connect(ui->horizontalSliderDuration, &QSlider::sliderReleased, this, &MainWindow::on_horizontalSliderDuration_sliderReleased);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete player;
    delete audioOutput;
}

void MainWindow::durationChanged(qint64 duration)
{
    ui->horizontalSliderDuration->setMaximum(static_cast<int>(duration));
}

void MainWindow::positionChanged(qint64 position)
{
    ui->horizontalSliderDuration->setValue(static_cast<int>(position));
}

void MainWindow::listMp3Files(const QString &directoryPath) {
    QDir directory(directoryPath);

    if (!directory.exists()) {
        qDebug() << "Directory does not exist:" << directoryPath;
        return;
    }

    QStringList mp3Files = directory.entryList(QStringList() << "*.mp3", QDir::Files);

    if (mp3Files.isEmpty()) {
        qDebug() << "No .mp3 files found in directory:" << directoryPath;
    } else {
        foreach (QString filename, mp3Files) {
            qDebug() << filename;
        }
    }

    if (!mp3Files.isEmpty()) {
        QString filePath = directory.absoluteFilePath(mp3Files.first());
        qDebug() << "Playing file:" << filePath;
        playMp3File(filePath);
    }
}

void MainWindow::playMp3File(const QString &filePath) {
    QString absoluteFilePath = QFileInfo(filePath).absoluteFilePath();
    qDebug() << "Attempting to play file:" << absoluteFilePath;

    if (!QFile::exists(absoluteFilePath)) {
        qDebug() << "File does not exist:" << absoluteFilePath;
        return;
    }

    player->setSource(QUrl::fromLocalFile(absoluteFilePath));
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(ui->verticalSliderVolume->value() / 100.0);
    player->play();

    connect(player, &QMediaPlayer::playbackStateChanged, this, [](QMediaPlayer::PlaybackState state) {
        qDebug() << "Player state changed to:" << state;
    });

    connect(player, &QMediaPlayer::errorOccurred, this, [](QMediaPlayer::Error error, const QString &errorString) {
        qDebug() << "Player error:" << error << errorString;
    });
}

void MainWindow::on_pushButtonVolume_clicked()
{
    if (is_muted == false) {
        is_muted = true;
        ui->pushButtonVolume->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        audioOutput->setVolume(0.0);
    } else {
        is_muted = false;
        ui->pushButtonVolume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
        audioOutput->setVolume(ui->verticalSliderVolume->value() / 100.0);
    }
}

void MainWindow::on_pushButtonBack_clicked()
{

}

void MainWindow::on_pushButtonStop_clicked()
{
    player->stop();
    ui->pushButtonPlayPause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    paused = true;
}


void MainWindow::on_pushButtonForward_clicked()
{

}

void MainWindow::on_pushButtonPlayPause_clicked()
{
    if (paused == true) {
        paused = false;
        player->pause();
        ui->pushButtonPlayPause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    } else {
        paused = true;
        player->play();
        ui->pushButtonPlayPause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    }
}

void MainWindow::on_verticalSliderVolume_valueChanged(int value)
{
    audioOutput->setVolume(value / 100.0);
}

void MainWindow::on_horizontalSliderDuration_sliderMoved(int value)
{
    player->setPosition(value);
}

void MainWindow::on_horizontalSliderDuration_sliderReleased()
{
    player->setPosition(ui->horizontalSliderDuration->value());
}
