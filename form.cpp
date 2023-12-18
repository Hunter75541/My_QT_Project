#include "form.h"
#include <QLayout>
#include<QString>
#include <qwt_plot_grid.h>
#include <qwt_legend.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>


Form::Form(QWidget *parent)
    : QWidget(parent), sys(nullptr)
{
        labelMass = new QLabel("Mass of the Particle");
        labelPotention_Power = new QLabel("The degree of the Potention");
        labelConstant = new QLabel("Constant in the Potention's expression");
        labelInitialx0 = new QLabel("Initial coordinate on the x-axis");
        labelPricelny_Parametr = new QLabel("Impact parameter");
        labelv_x_0 = new QLabel("Initial speed on the x-axis");
        labelv_z_0 = new QLabel("Initial speed on the z-axis");


        doubleSpinBoxMass= new QDoubleSpinBox;
        doubleSpinBoxPotention_Power = new QDoubleSpinBox;
        doubleSpinBoxConstant = new QDoubleSpinBox;
        doubleSpinBoxInitialx0 = new QDoubleSpinBox;
        doubleSpinBoxPricelny_Parametr = new QDoubleSpinBox;
        doubleSpinBoxv_x_0 = new QDoubleSpinBox;
        doubleSpinBoxv_z_0 = new QDoubleSpinBox;

        //(9.1e-31, 2.0, 9e9*1.6e-19*1.6e-19, -1.0e-1, 1e-5, 1000.0, 0.0
        doubleSpinBoxMass->setMaximum(1e10);
        doubleSpinBoxMass->setMinimum(0.0);
        doubleSpinBoxPotention_Power->setMaximum(1e5);
        doubleSpinBoxPotention_Power->setMinimum(-1e5);
        doubleSpinBoxConstant->setMaximum(1e10);
        doubleSpinBoxConstant->setMinimum(-1e10);
        doubleSpinBoxInitialx0->setMaximum(1e10);
        doubleSpinBoxInitialx0->setMinimum(-1e10);
        doubleSpinBoxPricelny_Parametr->setMaximum(1e10);
        doubleSpinBoxPricelny_Parametr->setMinimum(-1e10);
        doubleSpinBoxv_x_0->setMaximum(1e10);
        doubleSpinBoxv_x_0->setMinimum(-1e10);
        doubleSpinBoxv_z_0->setMaximum(1e10);
        doubleSpinBoxv_z_0->setMinimum(-1e10);

        doubleSpinBoxMass->setSuffix(" kg");
        doubleSpinBoxInitialx0->setSuffix(" m");
        doubleSpinBoxPricelny_Parametr->setSuffix(" m");
        doubleSpinBoxv_x_0->setSuffix(" m/s");
        doubleSpinBoxv_z_0->setSuffix(" m/s");

        doubleSpinBoxMass->setValue(9.1);
        doubleSpinBoxPotention_Power->setValue(2.0);
        doubleSpinBoxConstant->setValue(23.296);
        doubleSpinBoxInitialx0->setValue(-1.0);
        doubleSpinBoxPricelny_Parametr->setValue(1);
        doubleSpinBoxv_x_0->setValue(1000.0);
        doubleSpinBoxv_z_0->setValue(0.0);

        pushButtonStart = new QPushButton("Start");
        pushButtonStop = new QPushButton("Stop");

        textEditLog = new QTextEdit;
        textEditLog->setReadOnly(true);

        //PLOT

        plot = new QwtPlot;
        plot->setTitle("Time plots");
        plot->setAxisTitle(QwtPlot::xBottom, "X (m)");
        plot->setAxisTitle(QwtPlot::yLeft, "Z (m)");
        plot->setCanvasBackground(QBrush(Qt::white));

       QwtPlotMagnifier *magnifier = new QwtPlotMagnifier(plot->canvas());
       magnifier->setMouseButton(Qt::MiddleButton);
       QwtPlotPanner *panner = new QwtPlotPanner(plot->canvas());
       panner->setMouseButton(Qt::LeftButton);

       QwtPlotGrid *grid = new QwtPlotGrid;
       grid->attach(plot);

        curveZ = new QwtPlotCurve;
        curveZ->setPen(Qt::blue, 4.0, Qt::DashLine);
        curveZ->setTitle("Trajectory of the particle motion");
        curveZ->attach(plot);


        QwtLegend *legend = new QwtLegend;
        plot->insertLegend(legend);

        QGridLayout * layoutParameters = new QGridLayout;
        layoutParameters->addWidget(labelMass, 0, 0);
        layoutParameters->addWidget(labelPotention_Power, 1, 0);
        layoutParameters->addWidget(labelConstant, 2, 0);
        layoutParameters->addWidget(labelInitialx0, 3, 0);
        layoutParameters->addWidget(labelPricelny_Parametr, 4, 0);
        layoutParameters->addWidget(labelv_x_0, 5, 0);
        layoutParameters->addWidget(labelv_z_0, 6, 0);

        layoutParameters->addWidget(doubleSpinBoxMass, 0, 1);
        layoutParameters->addWidget(doubleSpinBoxPotention_Power, 1, 1);
        layoutParameters->addWidget(doubleSpinBoxConstant, 2, 1);
        layoutParameters->addWidget(doubleSpinBoxInitialx0, 3, 1);
        layoutParameters->addWidget(doubleSpinBoxPricelny_Parametr, 4, 1);
        layoutParameters->addWidget(doubleSpinBoxv_x_0, 5, 1);
        layoutParameters->addWidget(doubleSpinBoxv_z_0, 6, 1);

        QHBoxLayout * layoutButtons = new QHBoxLayout;
        layoutButtons->addWidget(pushButtonStart);
        layoutButtons->addWidget(pushButtonStop);

        QVBoxLayout * layoutLeft = new QVBoxLayout;
        layoutLeft->addLayout(layoutParameters);
        layoutLeft->addLayout(layoutButtons);
        layoutLeft->addWidget(textEditLog);

        QVBoxLayout *layoutRight = new QVBoxLayout;
        layoutRight->addWidget(plot);

        QHBoxLayout * layoutMain = new QHBoxLayout;
        layoutMain->addLayout(layoutLeft);
        layoutMain->addLayout(layoutRight);

        this->setLayout(layoutMain);

        timer = new QTimer;
        timer->setInterval(0);

        this->setLayout(layoutMain);
        connect(pushButtonStart, SIGNAL(clicked()), this, SLOT(startCalculation()));
        connect(pushButtonStop, SIGNAL(clicked()), this, SLOT(stopCalculation()));
        connect(timer, SIGNAL(timeout()), this, SLOT(nextStep()));
}

Form::~Form()
{

}

void Form::startCalculation()
{
    textEditLog->clear();
    delete sys;
    dataZ.clear();
    dataX.clear();
    /*sys =  new System(9.1e-31, 2.0, 9e9*1.6e-19*1.6e-19, -1.0e-1, 1e-5, 1000.0, 0.0); */
    sys = new System({
        {"mass", doubleSpinBoxMass->value()*1.0e-31},
        {"n", doubleSpinBoxPotention_Power->value()},
        {"c", doubleSpinBoxConstant->value()*1.0e-29},
        {"x0", doubleSpinBoxInitialx0->value()*1.0e3},
        {"pricel_param", doubleSpinBoxPricelny_Parametr->value()*1.0e-5},
        {"v_x_0", doubleSpinBoxv_x_0->value()},
        {"v_z_0", doubleSpinBoxv_z_0->value()}
    });


    textEditLog->append(QString::number(sys->Z())+'\t'+
                        QString::number(sys->X()));

    dataZ.push_back(QPointF(sys->X(), sys->Z()));
    curveZ->setSamples(dataZ);
    plot->replot();
    timer->start();
}

void Form::stopCalculation()
{
    timer->stop();
}

void Form::nextStep()
{
    double h = 0.0001;
    sys->step(h);
    textEditLog->append(QString::number(sys->Z())+'\t'+
                            QString::number(sys->X()));
   dataZ.push_back(QPointF(sys->X(), sys->Z()));
   curveZ->setSamples(dataZ);
   plot->replot();
}
