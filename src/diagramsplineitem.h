#ifndef DIAGRAMSPLINEITEM_H
#define DIAGRAMSPLINEITEM_H

#include "diagramitem.h"

QT_BEGIN_NAMESPACE
class QMenu;
QT_END_NAMESPACE

class DiagramSplineItem : public QGraphicsPathItem
{
public:
    enum { Type = UserType + 7 };
    enum DiagramType { cubic,cubicStart,cubicEnd,cubicStartEnd,quad,quadStart,quadEnd,quadStartEnd };
    DiagramSplineItem(DiagramType diagramType, QMenu *contextMenu, QGraphicsItem *parent=nullptr);
    DiagramSplineItem(const QJsonObject &json, QMenu *contextMenu);
    DiagramSplineItem(const DiagramSplineItem& diagram);//copy constructor

    int type() const
        { return Type;}

    virtual void setDiagramType(DiagramType type)
        { myDiagramType=type; }

    void updateActive(const QPointF point, int currentActive=-1);
    void nextActive();

    QPointF getActivePoint(const int currentActive=-1);

    DiagramSplineItem* copy();
    void write(QJsonObject &json);

    QPixmap image() const;
    QPixmap icon();

protected:
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    void hoverEnterEvent(QGraphicsSceneHoverEvent *e);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *e);
    void mousePressEvent(QGraphicsSceneMouseEvent *e);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *e);

    void createPath();
    QPointF onGrid(QPointF pos);
    bool hasClickedOn(QPointF press_point, QPointF point) const;
    QPainterPath createArrow(QPointF p1, QPointF p2,qreal scale=1.) const;
    void drawArrows(QPainterPath  &path);

private:
    DiagramType myDiagramType;
    QPointF p0,p1,c0,c1;

    int mySelPoint,myHoverPoint;
    int myActivePoint;
    qreal myHandlerWidth;

    qreal len,breite;
};

#endif // DIAGRAMSPLINEITEM_H
