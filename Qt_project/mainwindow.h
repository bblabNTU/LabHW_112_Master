#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "yolo.h"
#include <iostream>
#include<opencv2//opencv.hpp>
#include<math.h>

#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <QFileDialog>
#include <QFileInfo>
#include <QPixmap>
#include <QDir>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QGraphicsPixmapItem>
#include <QGuiApplication>
#include <QLabel>
#include <QMessageBox>
#include <iostream>
#include <QThread>
#include <QImage>
#include <QObject>

#define USE_CUDA false //use opencv-cuda

using namespace std;
using namespace cv;
using namespace dnn;



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
    void OpenImg();
//    void on_open_file_clicked();

//    void on_pushButton_clicked();

//    void on_pushButton_2_clicked();

//    void on_choose_weight_clicked();

//    void on_rtsp_rgb_clicked();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
