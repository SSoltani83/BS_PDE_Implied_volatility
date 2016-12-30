//EU_Options.cpp is an implementation file for EU_Option.h
//Updated: 12/29/2016
#ifndef _USE_MATH_DEFINES//Just to be able to use M_PI 3.14
#define _USE_MATH_DEFINES
#endif
#include<cmath>
#include<string>
#include<iostream>
#include"EU_Options.h"

using namespace std;

//Base Class EU_options

//Implementation for calculating d1=d+;
double Option::d1()const
{
	return (log(Underlying_asset_price/Strike_price)+(Risk_free_rate-Dividend+pow(Sigma,2)/2)*(T-t))/((Sigma*sqrt(T-t)));
}
//Implementation for calculating d2=d_
double Option::d2() const
{
	return d1()-(Sigma*sqrt(T-t));

}
//Implementation for calculating Vega derivative of BS with respect to volatility.(Will be used in computing Implied volatility
double Option::Vega()const
{
	double d=d1();
	return (Underlying_asset_price*exp(-Dividend*(T-t))*sqrt(T-t)/sqrt(2*M_PI))*exp(-d*d/2);
}

//approximation of the Normal distribution CDF using simpson rule
double Option::Cum_Dist_Normal(double x)const
{
	 double z=abs(x);
	 double y=1/(1+0.2316419*z);
	 double a1=0.319381530;
	 double a2=-0.356563782;
	 double a3=1.781477937;
	 double a4=-1.821255978;
	 double a5=1.330274429;
	 double m=1-exp(-pow(x,2)/2)*(a1*y+a2*pow(y,2)+a3*pow(y,3)+a4*pow(y,4)+a5*pow(y,5))/(sqrt(2*M_PI));

	 if (x>0){return m;}
	 else {return 1-m;}
}

//The three functions bellow will help in calculating implied volatility
//d1 with respect to volatility x;
double Option::d1(double x)const
{
	 return (log(Underlying_asset_price/Strike_price)+(Risk_free_rate-Dividend+pow(x,2)/2)*(T-t))/((x*sqrt(T-t)));
}
//d2 with respect to volatility x
double Option::d2(double x)const
{
	return d1(x)-(x*sqrt(T-t));
}
//The vega with respect to volatility
double Option::Vega_IV(double x)const
{
	double d=d1(x);
	return (Underlying_asset_price*exp(-Dividend*(T-t))*sqrt(T-t)/sqrt(2*M_PI))*exp(-d*d/2);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Derived call class
//Default Constructor
Call::Call()
{
	Underlying_asset_price=0;
	Dividend=0;
	Strike_price=0;
	Sigma=0;
	Risk_free_rate=0;
	t=0;
	T=0;
	Observed_price_of_Call_derivative=0;
	cout<<"A call object is being created!"<<endl;
}
//Constructor with initialization
Call::Call(double p,double d, double strike, double sig, double r, double present, double maturity,double O)
{
	Underlying_asset_price=p;
	Dividend=d;
	Strike_price=strike;
	Sigma=sig;
	Risk_free_rate=r;
	t=present;
	T=maturity;
	Observed_price_of_Call_derivative=O;
	cout<<"A call object is being created!"<<endl;
	
}

//Copy constructor
Call::Call(const Call &p)
{
	Underlying_asset_price=p.Underlying_asset_price;
	Dividend=p.Dividend;
	Strike_price=p.Strike_price;
	Sigma=p.Sigma;
	Risk_free_rate=p.Risk_free_rate;
	t=p.t;
	T=p.T;
	
	cout<<"A copy instance of a call object is being created!."<<endl;
}

//Destructor
Call::~Call()
{
	cout<<"A call object is being deleted!"<<endl;
}

//The BSformula Virtual function from the base class
 double Call::OptionPrice()const
 {
	//Returning the price of the call
	return (Underlying_asset_price*exp(-Dividend*(T-t))*Cum_Dist_Normal(d1())-Strike_price*exp(-Risk_free_rate*(T-t))*Cum_Dist_Normal(d2()));
 }

 
 //This function will help in calculating the implied volatility it makes the BS_call dependent on volatility only
 double Call::BS_CIV(double x)const
 {
	return (Underlying_asset_price*exp(-Dividend*(T-t))*Cum_Dist_Normal(d1(x))-Strike_price*exp(-Risk_free_rate*(T-t))*Cum_Dist_Normal(d2(x)))-Observed_price_of_Call_derivative;
 }

 //The I_Implied calculates the implied volatility using Newton's Method
 double Call::I_Implied(double firstguess)const
{
	
	double x_old;
	double x_new;
	
	x_new=firstguess;
	x_old=firstguess-1;
	
	
	while (abs(x_new-x_old) > Tol_consec || (abs(BS_CIV(x_new)) > Tol_approx))
	{
		
		x_old=x_new;
		x_new=x_old-(BS_CIV(x_old)/Vega_IV(x_old));
	}
	return x_new;

}

 //delta function
double Call::Delta()const
{
	return exp(-Dividend*(T-t))*Cum_Dist_Normal(d1());
}

 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 //Derived Put class
 //default constructor
 Put::Put()
 {
	Underlying_asset_price=0;
	Dividend=0;
	Strike_price=0;
	Sigma=0;
	Risk_free_rate=0;
	t=0;
	T=0;
	Observed_price_of_Put_derivative=0;
	cout<<"A put object is being created!"<<endl; 
	
}
 
 //Constructor that initializes the member data
 Put::Put(double p, double d, double strike, double sig, double r, double present, double maturity,double O)
{
	Underlying_asset_price=p;
	Dividend=d;
	Strike_price=strike;
	Sigma=sig;
	Risk_free_rate=r;
	t=present;
	T=maturity;
	Observed_price_of_Put_derivative=O;
	cout<<"A put object is being created!"<<endl;
 }

 //Copy constructor
 Put::Put(const Put &P)
 {
	 cout<<"A put Object is being deleted!"<<endl;
 }

 //Destructor
 Put::~Put()
 {
	 cout<<"A put object is being deleted!"<<endl;
 }

 //Getter for the Observed price of put

 //BS_formulae for calculating the price of the put
 double Put::OptionPrice()const
 {
	 return (Strike_price*exp(-Risk_free_rate*(T-t))*Cum_Dist_Normal(-d2())-Underlying_asset_price*exp(-Dividend*(T-t))*Cum_Dist_Normal(-d1()));

 }

  //This function will help in calculating the implied volatility it makes the BS_Put dependent on volatility only
 double Put::BS_PIV(double x)const
 {
	 return (Strike_price*exp(-Risk_free_rate*(T-t))*Cum_Dist_Normal(-d2(x))-Underlying_asset_price*exp(-Dividend*(T-t))*Cum_Dist_Normal(-d1(x)))-Observed_price_of_Put_derivative;
 }
 
 //The I_Implied calculates the implied volatility using Newton's Method
 double Put::I_Implied(double firstguess)const 
 {
	 double x_old;
	 double x_new;

	 x_new=firstguess;
	 x_old=firstguess-1;
	 while( (abs(x_new-x_old)> Tol_consec) || (abs(BS_PIV(x_new)) > Tol_approx))
	 {
		 x_old=x_new;
		 x_new=x_old-BS_PIV(x_old)/Vega_IV(x_old);
	 }
	 return x_new;
 }
 //delta function put
double Put::Delta()const
{
	return exp(-Dividend*(T-t))*((Cum_Dist_Normal(d1())-1)); //This is directly derived from the Put_call parity  C-P=S*e^-qt-Ke^-rt  ==> delta_c=e^-qt*N(d+)
}



