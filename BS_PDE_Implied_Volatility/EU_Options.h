//EU_Option.h host 3 classes. one base class called Option and two derived classes Call and put.
//The base class Option is a pure abstract class that encapsules all the Data needed to compute the put's and call prices
//The put and call classes are created because they have 1 different argument that is the Observed _price in the market.(This price will be used to compute the Implied volatility of the underlying asset)


#ifndef EU_OPTIONS_H
#define EU_OPTIONS_H 
//Macros to define the tolerance error on Newton's method
#ifndef Tol_approx
#define Tol_approx pow(10,-9)
#endif
#ifndef Tol_consec
#define Tol_consec pow(10,-9)
#endif

#include<iostream> //Preprocessor directives
using namespace std;

class Option
{
protected:
	double Underlying_asset_price; // stock price for example
	double Dividend; // dividend if applicable
	double Strike_price; 
	double Sigma; // standard deviation of the stock
	double Risk_free_rate; 
	double t; //present time , often =0
	double T; //Maturity
	
	
	//private Member functions
	double d1()const;
	double d2()const;
	//Cum_Dist_Normal Poly based approximation of the Normal CDF function
	double Cum_Dist_Normal(double)const;
	//This functions help in computing the implied volatility
	virtual ~Option();
	double d1(double)const;
	double d2(double)const;
	//This is the derivative of BS Call with respect to volatility
	double Vega_IV(double)const;
	
public:
	//This class does not need a constructor or destructor because it is a pure abstract class 
	//Getter functions
	//Underlying
	double Get_Underlying_price()const{return Underlying_asset_price;};
	double Get_Dividend()const {return Dividend;};
	double Get_Strike()const{return Strike_price;};
	double Get_Sigma()const{return Sigma;};
	double Get_Risk_free_rate()const{return Risk_free_rate;};
	double Get_t()const{return t;};
	double Get_T()const{return T;};

	//Setter function
	void Set_Underlying_asset_price(double price){Underlying_asset_price=price;};
	void Set_Dividend(double dividend){Dividend=dividend;};
	void Set_Strike_price(double strike){Strike_price=strike;};
	void Set_Sigma(double sigma){Sigma=sigma;};
	void Set_risk_free_rate(double r){Risk_free_rate=r;};
	void Set_t(double a){t=a;};
	void Set_T(double maturity){T=maturity;};

	//Pure virtual function! it will be defined in the derived classes Put and Call
	virtual double OptionPrice()const =0; 
	
	//The vega of the Derivative put or call is the same vega
	double Vega ()const;
	

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Call a derived class from Option class
class Call:public Option
{
private:
	
	// Market price of the option we will use it to calculate the implied volatility later
	double Observed_price_of_Call_derivative;
	// This function is the function we need to solve for volatility BS_C-Obsercved price=0
	double BS_CIV(double)const;
	
public:
	//constructors
	Call();
	Call(double,double,double,double,double,double,double,double);
	//copy constructor call
	Call(const Call &C);
	//destructor
	~Call();
	
	//Getter for Observed Price
	double Get_Observed_price()const{return Observed_price_of_Call_derivative;};
	
	//setter for Observed price
	void Set_Observed_Price(double O) {Observed_price_of_Call_derivative=O;};
	
	//Modifier function: OptionPrice()
	virtual double OptionPrice()const;
	
	//function prototype for Newton method to compute implied volatility
	double I_Implied(double) const; 

	//Delta Function
	double Delta()const;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Put a Derived class from Option
class Put:public Option
{
private:
	// Market price of the option we will use it to calculate the implied volatility later
	double Observed_price_of_Put_derivative;
		// This function is the function we need to solve for volatility BS_P-Obsercved price=0
	double BS_PIV(double)const;
public:
	//Constructors
	Put();
	Put(double,double,double,double,double,double,double,double);
	//Copy constructor
	Put(const Put &P);
	//destructor
	~Put();
	//Getter for Observed Price
	double Get_Observed_price()const {return Observed_price_of_Put_derivative;};
	//setter for Observed price
	void Set_Observed_Price(double O) {Observed_price_of_Put_derivative=O;};
	
	//Modifiers
	virtual double OptionPrice()const;

	//function prototype for Newton method to compute implied volatility
	double I_Implied(double) const; 

	//Delta Function
	double Delta()const;
};




#endif