//Test.cpp is test file for Option, Put and Call classes.
// To Create a put or call objects the arguments must entered in the following order. Call Google (stock_price,dividend,strike,volatility,risk_free_rate,present time, maturity) The same goes for puts.
#include"EU_Options.h"
#include <iostream>
#include<iomanip>
#include<string>
using namespace std;
int main()
{
	double S,d,K,sig,r,t,T,Observed_c,Observed_p,Newton_first_guess;
	string choice = "Y";// User's choice to make another estimation
	
	cout<<"\n\n                       THIS C++ PROGRAM COMPUTES THE PRICES OF PUTS AND CALLS USING THE BLACK AND SCHOLES FORMULAE. IT ALSO CALCULATES THE IMPLIED VOLATILITY GIVEN OBSERVED MARKET PRICES OF PUT AND CALLS"<<endl;
	while ( choice == "Y")
	{
		string choice_put_or_call;// choice between put or call
		
		cout<<"\n\nWould you like to price a put or a call? Enter 'C' for call and 'P' for put: ";
		//Safety mechanism to make sure the users enters the right input 
		do
		{
			cin>>choice_put_or_call;
			if(choice_put_or_call!="P" && choice_put_or_call!="C")
			{
			cout<<"You entered a wrong input\a, Please enter 'P' for put and 'C'for call: ";
			}
		}while (choice_put_or_call!="P" && choice_put_or_call!="C");

		if (choice_put_or_call == "C")
		{
		//Asking user to enter data
		cout<<"Enter Underlying asset price: ";
		cin>>S;
		cout<<"Enter contunious dividend rate: ";
		cin>>d;
		cout<<"Enter the strike price: ";
		cin>>K;
		cout<<"Enter the volatility parameter: ";
		cin>>sig;
		cout<<"Enter continuous risk free rate: ";
		cin>>r;
		cout<<"Enter present time t: ";
		cin>>t;
		cout<<"Enter maturity time T: ";
		cin>>T;
		cout<<"Enter Observed price in the market for call:";
		cin>>Observed_c;
		
		//Creating the instances of a call class
		Call call_test(S,d,K,sig,r,t,T,Observed_c);
		
		//Print the output
		cout<<"The price of the european call is : "<<call_test.OptionPrice()<<" it has a delta of "<<call_test.Delta()<<" and a vega of "<<call_test.Vega()<<endl;

		cout<<"\n\n\n                                      CUMPUTING IMPLIED VOLATILITY USING NEWTON'S METHOD"<<endl;

		cout<<"\n\nPlease enter first guess for Newton's method: ";
		cin>>Newton_first_guess;
		//Printing the output for implied volatility
		cout<<"\nThe implied Volatility of Underlying assetusing a call is : "<<call_test.I_Implied(Newton_first_guess)<<endl;
		
		}
		
		else if (choice_put_or_call=="P")
		{
		//Asking user to enter data
		cout<<"Enter Underlying asset price: ";
		cin>>S;
		cout<<"Enter contunious dividend rate: ";
		cin>>d;
		cout<<"Enter the strike price: ";
		cin>>K;
		cout<<"Enter the volatility parameter: ";
		cin>>sig;
		cout<<"Enter continuous risk free rate: ";
		cin>>r;
		cout<<"Enter present time t: ";
		cin>>t;
		cout<<"Enter maturity time T: ";
		cin>>T;
		cout<<"Enter Observed price in the market for put:";
		cin>>Observed_p;
		
		//creating an instance of a put class
		Put put_test (S,d,K,sig,r,t,T,Observed_p);

		cout<<"\nThe price of the european put is : "<<put_test.OptionPrice()<<" it has a delta of "<<put_test.Delta()<<" and a vega of "<<put_test.Vega()<<endl;

		cout<<"\n\n\n                                      CUMPUTING IMPLIED VOLATILITY USING NEWTON'S METHOD"<<endl;

		cout<<"\n\nPlease enter first guess for Newton's method: ";
		cin>>Newton_first_guess;
		//Printing the output for implied volatility
		cout<<"\nThe implied volatility of the underlying asset using a put is:"<<put_test.I_Implied(Newton_first_guess)<<endl;
		}

		
		cout<<"\n\n\n\aWould you like to make another estimate using this program? Type 'Y' for yes, and 'N 'for no: ";
		//safety mechanism to make sure the user enters the right input.
		do
		{
			cin>>choice;
			if (choice !="Y" && choice !="N")
			{
				cout<<"You entered a wrong input\a, Please enter 'Y' for yes and 'N'for no: ";
			}
			if(choice=="N")
			{   
				cout<<"\n\n                                                                     THANK YOU FOR USING THIS PROGRAM !"<<endl;//bye bye:)
			}
		}while (choice !="Y" && choice !="N");
	}

	
return 0;
}