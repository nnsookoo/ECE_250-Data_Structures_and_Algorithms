// Polynomial_LinkedLists.h
// Class interface/header file for  polynomial using linked lists
// Author: Naveela Sookoo (September 2019)

#include <iostream>
using namespace std;

// Polynomial for single variable x
// Structure of Polynomial : c0 +  c1x + c2x^2 + ...

class Polynomial {
	private:
		struct Term{
			double coefficient;
			int exponent;
			Term *next;
		};
		Term *head; // Beginning of the list
		int size; //number of coefficients

	// class functions
	public:
		// creating an empty polynomial
		Polynomial();
		
		// creating a defined polynomial
		Polynomial(const int size, const double coeff[]);
		
		// copy constructor
		Polynomial(const Polynomial& polynomial_to_copy);
		
		// destructor
		~Polynomial();
		void destroy();
		
		// assignment constructor
		void copy(const Polynomial &other);
		Polynomial& operator=(const Polynomial& other);
		
		// equivalence operators
		bool operator==(const Polynomial& right);
		bool operator!=(const Polynomial& right);
		
		//Returning the size of polynomial
		int size_of() const;
		
		//Inserting a node
		void InsertTerm(const int exp, const double coeff);
		
		//Defines number of coefficients. Degree of polynomial is (m-1)
		bool init(const double &m);
		
		//Defines the coefficients of the current polynomial
		Polynomial coeffp1(const double coeff[]);
		
		//Defines the second polynomial for an addition or a multiplication operation
		Polynomial coeffp2(const double coeff[]);
		
		//Defines the expected polynomial
		Polynomial expected(const double coeff[]);
		
		//Compares the current_polynomial with the expected_polynomial
		bool get(const Polynomial& expected_polynomial); //in other words, equivalent operator (==)
		
		//Calculates the value of current_polynomial at x and then compares it with the expected_value
		bool evaluate(const double &x, const double &expected_value);
		
		//Adds the parameters of coeff_p1 to the parameters of the coeff_p2, then compares result with expected_polynomial
		Polynomial add(const Polynomial& p2);
		Polynomial operator+(const Polynomial& right);
		
		//Multiplies the parameters of the coeff_p1 with the parameters of coeff_p2, then compares result with expected_polynomial
		Polynomial mult(const Polynomial& p2);
		Polynomial operator*(const Polynomial& right);
		
		// print the polynomial
		// for debugging purposes
		//void print();
};
