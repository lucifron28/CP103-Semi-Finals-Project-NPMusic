#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia>
#include <QtCore>
#include <QtWidgets>
#include <QStringList>
#include "npqueue.h"
#include "npstack.h"
#include "trackinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleVolumeButton();
    void handleBackButton();
    void handleStopButton();
    void handleForwardButton();
    void handlePlayPauseButton();
    void handleVolumeSliderChange(int value);
    void handleDurationSliderMove(int value);
    void handleDurationSliderRelease();
    void durationChanged(qint64 duration);
    void positionChanged(qint64 position);
    void addSongToQueue(int row, int column);
    void playNextInQueue();
    void updateCurrentlyPlayingLabel();
    void handlePlaybackStateChanged(QMediaPlayer::PlaybackState state);
    void updateSongQueueTable();

    void on_actionSelect_File_mp3_triggered();

private:
    Ui::MainWindow *ui;
    bool is_muted = false;
    bool paused = true;
    bool playNextInQueueInProgress = false; // Add this flag
    qint64 Mduration;
    QString buttonStyle = "QPushButton::hover {"
                              "background-color: rgba(0, 0, 0, 0.5);}"
                          "QPushButton {"
                            "border-radius: 35px;"
                            "background-color: white;"
                            "border: 2px solid black;}"
                          "QPushButton::pressed {"
                            "background-color: white};";
    QStringList headers;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    void listMp3Files(const QString &directoryPath);
    void playMp3File(const QString &filePath);
    void addMp3FileToDirectory(const QString &filePath);
    void addSongToHistory(const TrackInfo &trackInfo);
    npstack stack;
    npqueue queue;
};

#endif // MAINWINDOW_H
