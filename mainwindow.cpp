#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , player(new QMediaPlayer(this))
    , audioOutput(new QAudioOutput(this))
    , stack()
    , queue()
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
    ui->pushButtonVolume->setStyleSheet("QPushButton::hover {"
                                        "background-color: rgba(0, 0, 0, 0.5);}"
                                        "QPushButton {"
                                        "border-radius: 20px;"
                                        "background-color: white;"
                                        "border: 2px solid black;}"
                                        "QPushButton::pressed {"
                                        "background-color: white};");

    ui->tableWidgetAllSongs->setColumnCount(2);
    ui->tableWidgetHistory->setColumnCount(2);
    ui->tableWidgetAllSongs->setHorizontalHeaderLabels(QStringList() << "Track" << "Artist");
    ui->tableWidgetHistory->setHorizontalHeaderLabels(QStringList() << "Track" << "Artist");
    int totalwidth = ui->tableWidgetAllSongs->width();
    ui->tableWidgetAllSongs->setColumnWidth(0, totalwidth * 0.5);
    ui->tableWidgetAllSongs->setColumnWidth(1, totalwidth * 0.5);

    ui->tableWidgetAllSongs->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetSongQueue->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetAllSongs->verticalHeader()->setVisible(false);

    ui->tableWidgetSongQueue->setColumnCount(2);
    headers << "Track" << "Artist";
    ui->tableWidgetSongQueue->setHorizontalHeaderLabels(headers);

    ui->tableWidgetSongQueue->setColumnWidth(0, totalwidth * 0.6);
    ui->tableWidgetSongQueue->setColumnWidth(1, totalwidth * 0.4);

    qDebug() << "Current working directory:" << QDir::currentPath();

    QString musicDirectory = "..\\..\\music";
    listMp3Files(musicDirectory);

    ui->verticalSliderVolume->setMinimum(1);
    ui->verticalSliderVolume->setMaximum(100);
    ui->verticalSliderVolume->setValue(50);

    connect(ui->pushButtonVolume, &QPushButton::clicked, this, &MainWindow::handleVolumeButton);
    connect(ui->pushButtonBack, &QPushButton::clicked, this, &MainWindow::handleBackButton);
    connect(ui->pushButtonStop, &QPushButton::clicked, this, &MainWindow::handleStopButton);
    connect(ui->pushButtonForward, &QPushButton::clicked, this, &MainWindow::handleForwardButton);
    connect(ui->pushButtonPlayPause, &QPushButton::clicked, this, &MainWindow::handlePlayPauseButton);
    connect(ui->verticalSliderVolume, &QSlider::valueChanged, this, &MainWindow::handleVolumeSliderChange);
    connect(ui->horizontalSliderDuration, &QSlider::sliderMoved, this, &MainWindow::handleDurationSliderMove);
    connect(ui->horizontalSliderDuration, &QSlider::sliderReleased, this, &MainWindow::handleDurationSliderRelease);
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);
    connect(ui->tableWidgetAllSongs, &QTableWidget::cellDoubleClicked, this, &MainWindow::addSongToQueue);
    connect(player, &QMediaPlayer::sourceChanged, this, &MainWindow::updateCurrentlyPlayingLabel);
    connect(player, &QMediaPlayer::playbackStateChanged, this, &MainWindow::handlePlaybackStateChanged);
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
            // Add song to tableWidgetAllSongs
            int row = ui->tableWidgetAllSongs->rowCount();
            ui->tableWidgetAllSongs->insertRow(row);
            ui->tableWidgetAllSongs->setItem(row, 0, new QTableWidgetItem(filename));
            ui->tableWidgetAllSongs->setItem(row, 1, new QTableWidgetItem("Unknown Artist"));
        }
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
}

void MainWindow::handlePlaybackStateChanged(QMediaPlayer::PlaybackState state)
{
    qDebug() << "Player state changed to:" << state;
    if (state == QMediaPlayer::StoppedState) {
        playNextInQueue();
    }
}

void MainWindow::handleVolumeButton()
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

void MainWindow::handleBackButton()
{
    if (!stack.isEmpty()) {
        TrackInfo previousTrack = stack.pop();
        QString filePath = QDir("..\\..\\music").absoluteFilePath(previousTrack.trackName);
        playMp3File(filePath);
        addSongToHistory(previousTrack);
    }
}

void MainWindow::handleStopButton()
{
    player->stop();
    ui->pushButtonPlayPause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    paused = true;
}

void MainWindow::handleForwardButton()
{
    qDebug() << "Forward button pressed";
    playNextInQueue();
}

void MainWindow::handlePlayPauseButton()
{
    if (paused == true) {
        paused = false;
        player->play();
        ui->pushButtonPlayPause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    } else {
        paused = true;
        player->pause();
        ui->pushButtonPlayPause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
}

void MainWindow::handleVolumeSliderChange(int value)
{
    audioOutput->setVolume(value / 100.0);
}

void MainWindow::handleDurationSliderMove(int value)
{
    player->setPosition(value);
}

void MainWindow::handleDurationSliderRelease()
{
    player->setPosition(ui->horizontalSliderDuration->value());
}

void MainWindow::addSongToQueue(int row, int column)
{
    Q_UNUSED(column);
    QString track = ui->tableWidgetAllSongs->item(row, 0)->text();
    QString artist = ui->tableWidgetAllSongs->item(row, 1)->text();

    int queueRow = ui->tableWidgetSongQueue->rowCount();
    ui->tableWidgetSongQueue->insertRow(queueRow);
    ui->tableWidgetSongQueue->setItem(queueRow, 0, new QTableWidgetItem(track));
    ui->tableWidgetSongQueue->setItem(queueRow, 1, new QTableWidgetItem(artist));

    TrackInfo trackInfo = {track, artist};
    queue.enqueue(trackInfo);
}

void MainWindow::playNextInQueue()
{
    if (playNextInQueueInProgress) {
        qDebug() << "playNextInQueue already in progress, skipping...";
        return;
    }

    playNextInQueueInProgress = true;
    qDebug() << "playNextInQueue called";

    // Log the current queue items
    qDebug() << "Current queue items:";
    for (const TrackInfo &trackInfo : queue) {
        qDebug() << "Track:" << trackInfo.trackName << ", Artist:" << trackInfo.artistName;
    }

    QString currentTrackName = player->source().fileName();
    if (!currentTrackName.isEmpty()) {
        // Check if the current track is already the last track in the stack
        if (stack.isEmpty() || stack.top().trackName != currentTrackName) {
            TrackInfo currentTrack = { currentTrackName, "Unknown Artist" };
            stack.push(currentTrack);
            addSongToHistory(currentTrack);
        }
    }

    if (!queue.isEmpty()) {
        TrackInfo nextTrack = queue.dequeue();
        qDebug() << "Dequeued track:" << nextTrack.trackName << ", Artist:" << nextTrack.artistName;

        QString filePath = QDir("..\\..\\music").absoluteFilePath(nextTrack.trackName);
        playMp3File(filePath);
        updateSongQueueTable();
    } else {
        player->stop();
        ui->pushButtonPlayPause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }

    // Log the queue items after dequeue
    qDebug() << "Queue items after dequeue:";
    for (const TrackInfo &trackInfo : queue) {
        qDebug() << "Track:" << trackInfo.trackName << ", Artist:" << trackInfo.artistName;
    }

    playNextInQueueInProgress = false;
}

void MainWindow::updateCurrentlyPlayingLabel()
{
    QString currentTrack = player->source().fileName();
    ui->labelCurrentlyPlaying->setText(currentTrack);
}

void MainWindow::updateSongQueueTable()
{
    ui->tableWidgetSongQueue->setRowCount(0);
    int queueRow = 0;
    for (const TrackInfo &trackInfo : queue) {
        ui->tableWidgetSongQueue->insertRow(queueRow);
        ui->tableWidgetSongQueue->setItem(queueRow, 0, new QTableWidgetItem(trackInfo.trackName));
        ui->tableWidgetSongQueue->setItem(queueRow, 1, new QTableWidgetItem(trackInfo.artistName));
        queueRow++;
    }
}

void MainWindow::on_actionSelect_File_mp3_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select MP3 File"), "", tr("MP3 Files (*.mp3)"));
    if (!filePath.isEmpty()) {
        addMp3FileToDirectory(filePath);
    }
}

void MainWindow::addMp3FileToDirectory(const QString &filePath)
{
    QString fileName = QFileInfo(filePath).fileName();
    QString destinationPath = QDir("..\\..\\music").absoluteFilePath(fileName);

    if (QFile::copy(filePath, destinationPath)) {
        qDebug() << "File copied to:" << destinationPath;

        int row = ui->tableWidgetAllSongs->rowCount();
        ui->tableWidgetAllSongs->insertRow(row);
        ui->tableWidgetAllSongs->setItem(row, 0, new QTableWidgetItem(fileName));
        ui->tableWidgetAllSongs->setItem(row, 1, new QTableWidgetItem("Unknown Artist"));
    } else {
        qDebug() << "Failed to copy file to:" << destinationPath;
    }
}

void MainWindow::addSongToHistory(const TrackInfo &trackInfo)
{
    int row = ui->tableWidgetHistory->rowCount();
    ui->tableWidgetHistory->insertRow(row);
    ui->tableWidgetHistory->setItem(row, 0, new QTableWidgetItem(trackInfo.trackName));
    ui->tableWidgetHistory->setItem(row, 1, new QTableWidgetItem(trackInfo.artistName));
}

