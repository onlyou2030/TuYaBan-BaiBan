#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>

class PaintArea : public QWidget
{
    Q_OBJECT
public:
    explicit PaintArea(QWidget *parent = 0);

    void setImageSize(int width,int height);    //设置画布尺寸
    void setImageColor(QColor color);      //设置画布背景颜色

    bool isModified() const;         //判断画布内容是否被更改
    bool saveImage(const QString &fileName,const char *fileFormat);  //保存图片
    bool openImage(const QString &fileName);                         //打开图片

    QSize getImageSize();

    void doPrint();

    void zoomIn();    //放大
    void zoomOut();   //缩小
    void zoom_l();    //还原
    void doRotate();  //旋转
    void doShear();   //拉伸
    void doClear();   //清空

    void setPenStyle(Qt::PenStyle style);   //设置画笔风格
    void setPenWidth(int width);            //设置画笔宽度
    void setPenColor(QColor color);         //设置画笔颜色
    void setBrushColor(QColor color);       //设置填充颜色

    enum ShapeType     //枚举变量，几个图形的选择
    {
        None,
        Line,
        Rectangle,
        Ellipse
    };

    void setShape(ShapeType shape);          //设置要绘制的图形

signals:

public slots:
protected:
    void paintEvent(QPaintEvent *);  //重绘事件

    void mousePressEvent(QMouseEvent *);  //鼠标按下事件
    void mouseMoveEvent(QMouseEvent *);   //鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *);//鼠标释放事件

    void paint(QImage &theImage);

private:
    QImage image;            //QImage类对象，用于在其上绘图
    QRgb backColor;          //存储image的背景颜色
    QPoint lastPoint,endPoint;   //定义两个坐标对象存放鼠标指针的前后两个坐标

    bool modified;           //标志画布是否被更改过

    qreal scale;             //缩放量
    int angle;               //角度
    qreal shear;             //拉伸量

    QColor penColor;         //画笔颜色
    QColor brushColor;       //填充颜色
    int penWidth;            //画笔宽度
    Qt::PenStyle penStyle;   //画笔风格
    ShapeType curShape;      //当前图形

    QImage tempImage;   //临时绘图区
    bool isDrawing;     //是否在绘制特殊 图形
};

#endif // PAINTAREA_H
