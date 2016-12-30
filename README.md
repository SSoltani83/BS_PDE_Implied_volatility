# BS_PDE_Implied_volatility
This C++ program calculates the prices of european options (put and calls) using the Black&Scholes Merton Formulae.
This program also estimates the implied volatility of the underlying assets using the observed market prices of the derivatives (puts or calls).
This program consists of three classes structured as following:

One absract virtual class called option. This class holds all the data members and helper functions such as the Normal CDF estimator or commonly shared function such as the vega.

Two derived classes: Put and Call that are likned to the base class Option.
To calculate the Implied volatility we rely on Newton's method. we try to find a solution to BS-P=0 where BS is the Black and scholes function and the P is the observed market price of the derivative.
All functionalities are tested in the Test.cpp file.
