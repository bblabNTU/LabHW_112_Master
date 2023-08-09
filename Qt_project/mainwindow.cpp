#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "yolo.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

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

#define USE_CUDA false // use opencv-cuda
//#define RTSP_RGB "rtsp://admin:dh123456@140.112.84.2:8080/cam/realmonitor?channel=1&subtype=1"
using namespace std;
using namespace cv;
using namespace dnn;

string model_path = "D:/code/QtProject/Qt_yolo/yolo_test/yolov7.onnx";
Yolo test;
Net net;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(OpenImg()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OpenImg()
{
    QString OpenFile, OpenFilePath;
    QImage image;
    //打开文件夹中的图片文件
    OpenFile = QFileDialog::getOpenFileName(this,
                                            "Please choose an image file",
                                            "",
                                            "Image Files(*.jpg *.png *.bmp *.pgm *.pbm);;All(*.*)");
    if( OpenFile != "" )
    {
        //显示所示图片的路径
        QFileInfo OpenFileInfo;
        OpenFileInfo = QFileInfo(OpenFile);
        OpenFilePath = OpenFileInfo.filePath();
        ui->lineEdit->setText(OpenFilePath);

        string img_path = OpenFilePath.toStdString();
        cout<<"img_path:"<<img_path<<endl;

        // yolo Detect
        if (test.readModel(net, model_path, USE_CUDA))
        {
            cout << "read net ok!" << endl;
        }
        else
        {
            cout << "read onnx model failed!";
        }

        // 生成随机颜色
        vector<Scalar> color;
        srand(time(0));
        for (int i = 0; i < 80; i++)
        {
            int b = rand() % 256;
            int g = rand() % 256;
            int r = rand() % 256;
            color.push_back(Scalar(b, g, r));
        }
        vector<Output> result;
        Mat img = imread(img_path);

        if (test.Detect(img, net, result))
        {
            cout << "Detect OK!" << endl;
            test.drawPred(img, result, color);
        }
        else
        {
            cout << "Detect Failed!" << endl;
        }

        if( image.load("out.bmp") )
        {
            ui->label->setPixmap(QPixmap::fromImage(image));
        }
    }


}


