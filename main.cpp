#include "mainwindow.h"

#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGroupBox>


QPushButton* createButton(const QString &iconPath, const QString &text)
{
    QPushButton *btn = new QPushButton;
    btn->setIcon(QIcon(iconPath));
    btn->setIconSize(QSize(32, 32));  // 图标大小
    btn->setText(text);
    btn->setCursor(Qt::PointingHandCursor); // 鼠标变成手指
    btn->setStyleSheet("background-color: red; color: white;");


    // 设置样式（圆角 + 灰色）
    btn->setStyleSheet(
        "QPushButton {"
        "  background-color: rgb(210, 210, 210);"
        "  border-radius: 8px;"
        "  padding: 6px 12px;"
        "  font: 12pt 'Microsoft YaHei';"
        "  text-align: left;"      // 文字靠左
        "}"
        "QPushButton:hover {"
        "  background-color: rgb(230, 230, 230);"
        "}"
        "QPushButton:pressed {"
        "  background-color: rgb(190, 190, 190);"
        "}"
    );
    return btn;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("棒管探伤检测系统");
//    QWidget *centralWidget = new QWidget(&w);

//    // 外层分组框
//    QGroupBox *group = new QGroupBox("操作");
//    QGridLayout *grid = new QGridLayout;

//    // 创建按钮
//    QPushButton *btnOpenImg   = createButton(":/images/icons/open_picture.png", "打开图片");
//    QPushButton *btnOpenDir   = createButton(":/images/icons/open_folder.png", "打开文件夹");
//    QPushButton *btnOpenVideo = createButton(":/images/icons/open_video.png", "打开视频");
//    QPushButton *btnOpenCam   = createButton(":/images/icons/open_camera.png", "打开摄像头");
//    QPushButton *btnSave      = createButton(":/images/icons/save_img.png", "保存");
//    QPushButton *btnExit      = createButton(":/images/icons/logout.png", "退出");

//    // 添加到网格布局（两列排布）
//    grid->addWidget(btnOpenImg,   0, 0);
//    grid->addWidget(btnOpenDir,   0, 1);
//    grid->addWidget(btnOpenVideo, 1, 0);
//    grid->addWidget(btnOpenCam,   1, 1);
//    grid->addWidget(btnSave,      2, 0);
//    grid->addWidget(btnExit,      2, 1);

//    group->setLayout(grid);

//    // 最外层布局
//    // ✅ 将 group 放入 centralWidget 的布局
//    QGridLayout *mainLayout = new QGridLayout(centralWidget);
//    mainLayout->addWidget(group, 0, 0);

//    // ✅ 最后将 centralWidget 设置为 MainWindow 的中心部件
//    w.setCentralWidget(centralWidget);



    w.show();
    return a.exec();
}
