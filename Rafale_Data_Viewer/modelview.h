#ifndef MODELVIEW_H
#define MODELVIEW_H

#include <QObject>
#include <QWidget>

class ModelView
      : public QWidget
{
    Q_OBJECT

private:
    QWidget *container;

public:
    explicit ModelView(QWidget *parent = nullptr);

protected:
    // reimplementation needed to handle resize events
    // http://doc.qt.io/qt-5/qwidget.html#resizeEvent
    void
    resizeEvent ( QResizeEvent * event );

public slots:
    void
    resizeView(QSize size);
};

#endif // MODELVIEW_H
