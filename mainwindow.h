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
    void addSongToQueue(QListWidgetItem *item);
    void playNextInQueue();
    void updateCurrentlyPlayingLabel();
    void handlePlaybackStateChanged(QMediaPlayer::PlaybackState state);
    void updateSongQueueTable();
    void handlePushButtonEditTrackInfo();
    void handleRemoveSongFromQueue();
    void clearQueue();
    void handleAllSongsCellChanged(QListWidgetItem *item);
    void on_actionSelect_File_mp3_triggered();
    void editList();

    void on_actionClear_History_triggered();

private:
    Ui::MainWindow *ui;
    bool is_muted = false;
    bool paused = true;
    bool playNextInQueueInProgress = false;
    bool stopButtonPressed = false; // New flag to indicate stop button pressed
    bool backButtonPressed = false; // New flag to indicate back button pressed
    qint64 Mduration;
    QString buttonStyle = "QPushButton::hover {"
                              "background-image: url(:/images/Sublime.jpg);}"
                          "QPushButton {"
                            "background-image: url(:/images/Vanusa.jpg);"
                            "border-radius: 35px;"
                            "background-color: white;"
                            "border: 2px solid rgb(190, 3, 252);}"
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
