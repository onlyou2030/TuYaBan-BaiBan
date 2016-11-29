#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "donewdialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPainter>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(900,700);   //主窗口大小设置为700*500
    area=new PaintArea;
    scrollArea=new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);  //将scrollArea对象的背景色设为Dark
    scrollArea->setWidget(area);     //非常关键：将画布添加到scrollArea中
    scrollArea->widget()->setMinimumSize(800,600);  //scrollArea初始化大小设为800*600
    setCentralWidget(scrollArea);     //将scrollArea加入到主窗口的中心区

    isSaved=false;
    curFile="NoName.png";

    creatColorComboBox(ui->penColorComboBox);   //画笔颜色组合框
    creatColorComboBox(ui->brushColorComboBox);   //填充颜色组合框
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_N_triggered()
{
    doNew();
}


void MainWindow::doOpen()
{
    if(maybeSave())
    {
        QString fileName=QFileDialog::getOpenFileName(this,"打开文件",QDir::currentPath());
        if(!fileName.isEmpty())
        {
            area->openImage(fileName);
            scrollArea->widget()->resize(area->getImageSize());  //获得图片的大小，然后更改scrollArea的大小
            isSaved=true;
            curFile=fileName;
        }
    }
}

void MainWindow::doNew()
{
    if(maybeSave())
    {
        DoNewDialog dlg;
        if(dlg.exec()==QDialog::Accepted)
        {
            int width=dlg.getWidth();
            int height=dlg.getHeight();
            area->setImageSize(width,height);
            scrollArea->widget()->resize(width,height);
            area->setImageColor((dlg.getBackColor()));
            isSaved=false;
        }
    }
}



bool MainWindow::maybeSave()
{
    if(area->isModified())
    {
        QMessageBox::StandardButton box;
        box = QMessageBox::warning(this,"保存文件","图片已经改变，是否保存？",
                                   QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if(box == QMessageBox::Yes)
        {
            return doFileSave();
        }
        else if(box == QMessageBox::Cancel)
        {
            return false;
        }
    }
    return true;
}



bool MainWindow::doFileSave()
{
    if(isSaved)
    {
        return saveFile(curFile);
    }
    else  return doFileSaveAs();
}



bool MainWindow::saveFile(QString fileName)
{
    if(area->saveImage(fileName,"png"))
    {
        isSaved = true;
        return true;
    }
    else return false;
}



bool MainWindow::doFileSaveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,"另存为 ",curFile);
    if(fileName.isEmpty())
    {
        return false;
    }
    else return saveFile(fileName);
}

void MainWindow::on_action_O_triggered()
{
    doOpen();
}

void MainWindow::on_action_S_triggered()
{
    doFileSave();
}

void MainWindow::on_action_A_triggered()
{
    doFileSaveAs();
}

void MainWindow::on_action_X_triggered()
{
    if(maybeSave())
    {
        qApp->quit();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(maybeSave())
    {
        qApp->quit();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::on_action_P_triggered()
{
    area->doPrint();
}

void MainWindow::on_action_3_triggered()
{
    area->zoomIn();
    //获得图片的大小，然后更改scrollArea的大小
    scrollArea->widget()->resize(area->getImageSize());
}

void MainWindow::on_action_4_triggered()
{
    area->zoomOut();
}

void MainWindow::on_action_5_triggered()
{
    area->zoom_l();
}

void MainWindow::on_action_6_triggered()
{
    area->doRotate();
}

void MainWindow::on_action_7_triggered()
{
    area->doShear();
}

void MainWindow::on_action_9_triggered()
{
    area->doClear();
}

void MainWindow::on_action_10_triggered()
{
    ui->dockWidget->show();
}



//对颜色组合框添加条目
void MainWindow::creatColorComboBox(QComboBox *comboBox)
{
    QPixmap pix(16,16);
    QPainter painter(&pix);
    painter.fillRect(0,0,16,16,Qt::black);  //先绘制一个16*16的小图片，然后涂色
    //QVariant v = QColor(Qt::black);
    comboBox->addItem(QIcon(pix),"黑色",QColor(Qt::black));  //再用该图片作为组合框条目的图标
    painter.fillRect(0,0,16,16,Qt::white);
    comboBox->addItem(QIcon(pix),"白色",QColor(Qt::white));
    painter.fillRect(0,0,16,16,Qt::red);
    comboBox->addItem(QIcon(pix),"红色",QColor(Qt::red));
    painter.fillRect(0,0,16,16,Qt::green);
    comboBox->addItem(QIcon(pix),"绿色",QColor(Qt::green));
    painter.fillRect(0,0,16,16,Qt::blue);
    comboBox->addItem(QIcon(pix),"蓝色",QColor(Qt::blue));
    painter.fillRect(0,0,16,16,Qt::yellow);
    comboBox->addItem(QIcon(pix),"黄色",QColor(Qt::yellow));
    comboBox->addItem("没有颜色",QColor(Qt::transparent));  //即透明
}

void MainWindow::on_shapeComboBox_currentIndexChanged(const QString &shape)
{
    if(shape=="矩形")
        area->setShape(PaintArea::Rectangle);
    else if(shape=="直线")
        area->setShape(PaintArea::Line);
    else if(shape=="椭圆")
        area->setShape(PaintArea::Ellipse);
    else
        area->setShape(PaintArea::None);   //利用PaintArea类中的枚举变量
}

void MainWindow::on_penStyleComboBox_currentIndexChanged(const QString &arg1)
{
    if(arg1=="实线")
        area->setPenStyle(Qt::SolidLine);
    else if(arg1=="点线")
        area->setPenStyle(Qt::DotLine);
}

void MainWindow::on_penColorComboBox_currentIndexChanged(int index)
{
    QColor color = ui->penColorComboBox->itemData(index,Qt::UserRole).value<QColor>();
        area->setPenColor(color);
}

void MainWindow::on_penWidthSpinBox_valueChanged(int arg1)
{
    area->setPenWidth(arg1);
}

void MainWindow::on_brushColorComboBox_currentIndexChanged(int index)
{
    QColor color = ui->brushColorComboBox->itemData(index,Qt::UserRole).value<QColor>();
        area->setBrushColor(color);
}

void MainWindow::on_action_11_triggered()
{
    QMessageBox::information(this,"版本","By JoyTian!");
}
