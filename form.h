#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QTextEdit>
#include <QTimer>
#include "system.h"
#include <qwt_plot.h>
#include <qwt_plot_curve.h>

class Form : public QWidget
{
    Q_OBJECT

public:
    Form(QWidget *parent = nullptr);
    ~Form();
private:
    QLabel * labelMass;
    QLabel * labelPotention_Power;
    QLabel * labelConstant;
    QLabel * labelInitialx0;
    QLabel * labelPricelny_Parametr;
    QLabel * labelv_x_0;
    QLabel * labelv_z_0;

    QDoubleSpinBox * doubleSpinBoxMass;
    QDoubleSpinBox * doubleSpinBoxPotention_Power;
    QDoubleSpinBox * doubleSpinBoxConstant;
    QDoubleSpinBox * doubleSpinBoxInitialx0;
    QDoubleSpinBox * doubleSpinBoxPricelny_Parametr;
    QDoubleSpinBox * doubleSpinBoxv_x_0;
    QDoubleSpinBox * doubleSpinBoxv_z_0;


    QPushButton * pushButtonStart;
    QPushButton * pushButtonStop;

    QTextEdit * textEditLog;
    System * sys;
    QTimer *timer;

    QwtPlot * plot;
    QwtPlotCurve *curveZ;
    QVector<QPointF> dataZ, dataX, dataV_x, dataV_z;

public slots:
    void startCalculation();
    void stopCalculation();
    void nextStep();
};

#endif // FORM_H
