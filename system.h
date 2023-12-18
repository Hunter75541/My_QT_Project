#ifndef SYSTEM_H
#define SYSTEM_H

#include<stdio.h>
#include<cmath>
#include<vector>
#include <string>
#include <map>

class System
{
public:
    System(double mass, double n, double c, double x0, double pricel_param, double v_x_0, double v_z_0);
    System(const std::map<std::string, double >& data);
    double mass() const;
    double n() const;
    double c() const;
    //double x0() const;
    //double pricel_param() const;
    /*double v_x_0() const;
    double v_z_0() const;
    int num_points() const;
    double t_min() const;
    double t_max() const;*/
    void step(double h);
    double func_x1(double x, double q, double z, double m, double n, double c );
    double func_x2(double x, double q, double z, double m, double n, double c );
    double func_z1( double x, double v, double z, double m, double n, double c );
    double func_z2(double x, double v, double z, double m, double n, double c );
    double X();
    double Z();
    double V_x();
    double V_z();

private:
    double mass_;
    double n_;
    double c_;
    double x0_;
    double pricel_param_;
    double v_x_0_;
    double v_z_0_;
    int num_points_;
    double t_min_;
    double t_max_;
    double V_x_,V_z_,X_,Z_;
    //double h_;
};
#endif // SYSTEM_H
