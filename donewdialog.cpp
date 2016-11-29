#include "donewdialog.h"
#include "ui_donewdialog.h"

#include <QColorDialog>

DoNewDialog::DoNewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DoNewDialog)
{
    ui->setupUi(this);
    backColor=Qt::white;       //画布背景色初始化为白色
}

DoNewDialog::~DoNewDialog()
{
    delete ui;
}


int DoNewDialog::getWidth()
{
    return ui->widthSpinBox->text().toInt();
}


int DoNewDialog::getHeight()
{
    return ui->heightSpinBox->text().toInt();
}

QColor DoNewDialog::getBackColor()
{
    return backColor;
}

void DoNewDialog::on_toolButton_clicked()
{
    QColor newColor=QColorDialog::getColor();   //从颜色框获得颜色
    if(newColor.isValid())    //如果得到的是可用的颜色
    {
        backColor=newColor;
        QPalette palette=ui->textBrowser->palette(); //palette对象获取了textBrowser的调色板
        palette.setColor(QPalette::Base,backColor);
        ui->textBrowser->setPalette(palette);
        update();
    }
}
