#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia>
#include <QtCore>
#include <QtWidgets>
#include <QStringList>

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
    void on_pushButtonVolume_clicked();

    void on_pushButtonBack_clicked();

    void on_pushButtonStop_clicked();

    void on_pushButtonForward_clicked();

    void on_verticalSliderVolume_valueChanged(int value);

    void on_pushButtonPlayPause_clicked();

    void on_horizontalSliderDuration_sliderMoved(int value);
    void on_horizontalSliderDuration_sliderReleased();
    void durationChanged(qint64 duration);
    void positionChanged(qint64 position);

private:
    Ui::MainWindow *ui;
    bool is_muted = false;
    bool paused = true;
    qint64 Mduration;
    QString buttonStyle = "QPushButton::hover {"
                              "background-color: rgba(0, 0, 0, 0.5);}"
                          "QPushButton {"
                            "border-radius: 35px;"
                            "background-color: white;"
                            "border: 2px solid black;}"
                          "QPushButton::pressed {"
                            "background-color: white}";
    QStringList headers;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    void listMp3Files(const QString &directoryPath);
    void playMp3File(const QString &filePath);
};
#endif // MAINWINDOW_H
