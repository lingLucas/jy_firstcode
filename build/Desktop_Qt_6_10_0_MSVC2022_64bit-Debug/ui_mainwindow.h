/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionStart;
    QAction *actionStop;
    QWidget *centralwidget;
    QLabel *imageLabel;
    QFrame *frame;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *run_status;
    QGroupBox *groupBox;
    QPlainTextEdit *log_output;
    QGroupBox *groupAction;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_save;
    QPushButton *pushButton_exit;
    QPushButton *pushButton_openvideo;
    QPushButton *pushButton_opendir;
    QPushButton *pushButton_openimg;
    QPushButton *pushButton_opencam;
    QMenuBar *menubar;
    QMenu *menucamera;
    QMenu *menuInfo;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(958, 788);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamilies({QString::fromUtf8("Corbel")});
        font.setPointSize(11);
        MainWindow->setFont(font);
        MainWindow->setToolTipDuration(0);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName("actionConnect");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/icons/connect.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionConnect->setIcon(icon);
        QFont font1;
        actionConnect->setFont(font1);
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName("actionDisconnect");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/icons/disconnect.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionDisconnect->setIcon(icon1);
        actionStart = new QAction(MainWindow);
        actionStart->setObjectName("actionStart");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/icons/start.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionStart->setIcon(icon2);
        actionStop = new QAction(MainWindow);
        actionStop->setObjectName("actionStop");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/icons/stop.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionStop->setIcon(icon3);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        imageLabel = new QLabel(centralwidget);
        imageLabel->setObjectName("imageLabel");
        imageLabel->setGeometry(QRect(10, 10, 641, 501));
        sizePolicy.setHeightForWidth(imageLabel->sizePolicy().hasHeightForWidth());
        imageLabel->setSizePolicy(sizePolicy);
        imageLabel->setAutoFillBackground(false);
        imageLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        imageLabel->setFrameShape(QFrame::Shape::Box);
        imageLabel->setFrameShadow(QFrame::Shadow::Raised);
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(660, 30, 281, 101));
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(199, 255, 251);"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 10, 91, 21));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Microsoft YaHei UI")});
        font2.setPointSize(10);
        label_4->setFont(font2);
        label_4->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(100, 10, 71, 21));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setFont(font2);
        label_5->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 163, 167);\n"
"color: rgb(255, 255, 255);"));
        label_5->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 40, 91, 21));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);
        QFont font3;
        font3.setPointSize(10);
        label_6->setFont(font3);
        label_6->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_7 = new QLabel(frame);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(100, 40, 71, 21));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_7->setFont(font3);
        label_7->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 163, 167);\n"
"color: rgb(255, 255, 255);"));
        label_7->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_8 = new QLabel(frame);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 70, 91, 21));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);
        label_8->setFont(font3);
        label_8->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label_8->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_8->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        label_9 = new QLabel(frame);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(100, 70, 71, 21));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);
        label_9->setFont(font3);
        label_9->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 163, 167);\n"
"color: rgb(255, 255, 255);"));
        label_9->setAlignment(Qt::AlignmentFlag::AlignCenter);
        run_status = new QLabel(centralwidget);
        run_status->setObjectName("run_status");
        run_status->setGeometry(QRect(660, 10, 71, 16));
        sizePolicy.setHeightForWidth(run_status->sizePolicy().hasHeightForWidth());
        run_status->setSizePolicy(sizePolicy);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 520, 641, 171));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        log_output = new QPlainTextEdit(groupBox);
        log_output->setObjectName("log_output");
        log_output->setGeometry(QRect(0, 20, 641, 151));
        groupAction = new QGroupBox(centralwidget);
        groupAction->setObjectName("groupAction");
        groupAction->setGeometry(QRect(660, 150, 281, 411));
        sizePolicy.setHeightForWidth(groupAction->sizePolicy().hasHeightForWidth());
        groupAction->setSizePolicy(sizePolicy);
        gridLayoutWidget = new QWidget(groupAction);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(10, 30, 261, 181));
        gridLayout_2 = new QGridLayout(gridLayoutWidget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setHorizontalSpacing(6);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton_save = new QPushButton(gridLayoutWidget);
        pushButton_save->setObjectName("pushButton_save");
        sizePolicy.setHeightForWidth(pushButton_save->sizePolicy().hasHeightForWidth());
        pushButton_save->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(pushButton_save, 5, 0, 1, 1);

        pushButton_exit = new QPushButton(gridLayoutWidget);
        pushButton_exit->setObjectName("pushButton_exit");
        sizePolicy.setHeightForWidth(pushButton_exit->sizePolicy().hasHeightForWidth());
        pushButton_exit->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(pushButton_exit, 5, 1, 1, 1);

        pushButton_openvideo = new QPushButton(gridLayoutWidget);
        pushButton_openvideo->setObjectName("pushButton_openvideo");
        sizePolicy.setHeightForWidth(pushButton_openvideo->sizePolicy().hasHeightForWidth());
        pushButton_openvideo->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(pushButton_openvideo, 0, 1, 1, 1);

        pushButton_opendir = new QPushButton(gridLayoutWidget);
        pushButton_opendir->setObjectName("pushButton_opendir");
        sizePolicy.setHeightForWidth(pushButton_opendir->sizePolicy().hasHeightForWidth());
        pushButton_opendir->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(pushButton_opendir, 3, 0, 1, 1);

        pushButton_openimg = new QPushButton(gridLayoutWidget);
        pushButton_openimg->setObjectName("pushButton_openimg");
        sizePolicy.setHeightForWidth(pushButton_openimg->sizePolicy().hasHeightForWidth());
        pushButton_openimg->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(pushButton_openimg, 3, 1, 1, 1);

        pushButton_opencam = new QPushButton(gridLayoutWidget);
        pushButton_opencam->setObjectName("pushButton_opencam");
        sizePolicy.setHeightForWidth(pushButton_opencam->sizePolicy().hasHeightForWidth());
        pushButton_opencam->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(pushButton_opencam, 0, 0, 2, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 958, 24));
        menucamera = new QMenu(menubar);
        menucamera->setObjectName("menucamera");
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Corbel")});
        font4.setPointSize(6);
        menucamera->setFont(font4);
        menuInfo = new QMenu(menubar);
        menuInfo->setObjectName("menuInfo");
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        sizePolicy.setHeightForWidth(toolBar->sizePolicy().hasHeightForWidth());
        toolBar->setSizePolicy(sizePolicy);
        toolBar->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        menubar->addAction(menucamera->menuAction());
        menubar->addAction(menuInfo->menuAction());
        toolBar->addAction(actionConnect);
        toolBar->addAction(actionDisconnect);
        toolBar->addAction(actionStart);
        toolBar->addAction(actionStop);
        toolBar->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionConnect->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245", nullptr));
#if QT_CONFIG(tooltip)
        actionConnect->setToolTip(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDisconnect->setText(QCoreApplication::translate("MainWindow", "\346\226\255\350\277\236", nullptr));
#if QT_CONFIG(tooltip)
        actionDisconnect->setToolTip(QCoreApplication::translate("MainWindow", "\346\226\255\350\277\236", nullptr));
#endif // QT_CONFIG(tooltip)
        actionStart->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
#if QT_CONFIG(tooltip)
        actionStart->setToolTip(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
#endif // QT_CONFIG(tooltip)
        actionStop->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255", nullptr));
#if QT_CONFIG(tooltip)
        actionStop->setToolTip(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255", nullptr));
#endif // QT_CONFIG(tooltip)
        imageLabel->setText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "\347\263\273\347\273\237\350\277\220\350\241\214\347\212\266\346\200\201\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\350\277\220\350\241\214", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\350\277\220\350\241\214\346\227\266\351\227\264\357\274\232", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "19h30m", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\345\267\262\346\243\200\346\265\213\346\243\222\347\256\241\346\225\260\351\207\217\357\274\232", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        run_status->setText(QCoreApplication::translate("MainWindow", "\350\277\220\350\241\214\347\212\266\346\200\201", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\346\227\245\345\277\227", nullptr));
        groupAction->setTitle(QCoreApplication::translate("MainWindow", "\346\223\215\344\275\234", nullptr));
        pushButton_save->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
        pushButton_exit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        pushButton_openvideo->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\350\247\206\351\242\221", nullptr));
        pushButton_opendir->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266\345\244\271", nullptr));
        pushButton_openimg->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\345\233\276\347\211\207", nullptr));
        pushButton_opencam->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\221\204\345\203\217\345\244\264", nullptr));
        menucamera->setTitle(QCoreApplication::translate("MainWindow", "Camera", nullptr));
        menuInfo->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
