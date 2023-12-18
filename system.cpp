#include "system.h"
#include<iostream>
#include<cmath>
#include<stdio.h>
#include<vector>


System::System(double mass, double n, double c, double x0, double pricel_param, double v_x_0, double v_z_0):
    mass_(mass), n_(n), c_(c), V_x_(v_x_0), V_z_(v_z_0), X_(x0), Z_(pricel_param)
{
   // h_ = (t_max - t_min) / (num_points - 1);
}

System::System(const std::map<std::string, double> &data)
    : System (data.at("mass"),data.at("n"),data.at("c"),data.at("x0"),data.at("pricel_param"),data.at("v_x_0"),data.at("v_z_0"))
{}

double System::mass() const
{
    return mass_;
}
double System::Z()
{
    return Z_;
}
double System::X()
{
    return X_;
}

double System::n() const
{
    return n_;
}
double System::c() const
{
    return c_;
}
double System::V_x()
{
  return V_x_;
}

void System::step(double h)
{
    double  a_x_1,a_x_2,a_x_3,a_x_4,
            a_z_1,a_z_2,a_z_3,a_z_4,
            v_x_1,v_x_2,v_x_3,v_x_4,
            v_z_1,v_z_2,v_z_3,v_z_4;

                    a_x_1 = func_x1(X_,V_x_,Z_,mass_,n_,c_);
                    v_x_1 = func_x2(X_,V_x_,Z_,mass_,n_,c_);
                    a_z_1 = func_z1(X_,V_z_,Z_,mass_,n_,c_);
                    v_z_1 = func_z2(X_,V_z_,Z_,mass_,n_,c_);

                    a_x_2 = func_x1(X_+h/2*v_x_1	,V_x_+h/2*a_x_1		,Z_+h/2*v_z_1	, mass_,n_,c_);
                    v_x_2 = func_x2(X_+h/2*v_x_1	,V_x_+h/2*a_x_1		,Z_+h/2*v_z_1	, mass_,n_,c_);             //V_x add
                    a_z_2 = func_z1(X_+h/2*v_x_1	,V_z_+h/2*a_z_1		,Z_+h/2*v_z_1	, mass_,n_,c_);
                    v_z_2 = func_z2(X_+h/2*v_x_1	,V_z_+h/2*a_z_1		,Z_+h/2*v_z_1	, mass_,n_,c_);             //V_z add

                    a_x_3 = func_x1(X_+h/2*v_x_2	,V_x_+h/2*a_x_2		,Z_+h/2*v_z_2	, mass_,n_,c_);
                    v_x_3 = func_x2(X_+h/2*v_x_2	,V_x_+h/2*a_x_2		,Z_+h/2*v_z_2	, mass_,n_,c_);            //V_x add
                    a_z_3 = func_z1(X_+h/2*v_x_2	,V_z_+h/2*a_z_2		,Z_+h/2*v_z_2	,mass_,n_,c_);
                    v_z_3 = func_z2(X_+h/2*v_x_2	,V_z_+h/2*a_z_2		,Z_+h/2*v_z_2	, mass_,n_,c_);           //V_z add

                    a_x_4 = func_x1(X_+h*v_x_3		,V_x_+h*a_x_3		,Z_+h*v_z_3		, mass_,n_,c_);
                    v_x_4 = func_x2(X_+h*v_x_3		,V_x_+h*a_x_3		,Z_+h*v_z_3		, mass_,n_,c_);            //V_x add
                    a_z_4 = func_z1(X_+h*v_x_3		,V_z_+h*a_z_3		,Z_+h*v_z_3		, mass_,n_,c_);
                    v_z_4 = func_z2(X_+h*v_x_3		,V_z_+h*a_z_3		,Z_+h*v_z_3		, mass_,n_,c_);            //V_z add

                    V_x_ +=		h/6	*	(a_x_1 + 2*a_x_2 + 2*a_x_3 + a_x_4);
                    X_  += 		h/6	*	(v_x_1 + 2*v_x_2 + 2*v_x_3 + v_x_4);
                    V_z_ +=     h/6	*	(a_z_1 + 2*a_z_2 + 2*a_z_3 + a_z_4);
                    Z_  += 		h/6	*	(v_z_1 + 2*v_z_2 + 2*v_z_3 + v_z_4);

}
double System::func_x1(double x, double q, double z, double m, double n, double c )

{

    return (c_*n_*x)/(m*pow(x*x+z*z,(n_/2)+1));

}



double System::func_x2(double x, double q, double z, double m, double n, double c )

{

    return q;

}



double System::func_z1( double x, double v, double z, double m, double n, double c )

{

    return (c_*n_*z)/(m*pow(x*x+z*z,(n_/2)+1));

}



double System::func_z2(double x, double v, double z, double m, double n, double c )

{

    return v;

}

