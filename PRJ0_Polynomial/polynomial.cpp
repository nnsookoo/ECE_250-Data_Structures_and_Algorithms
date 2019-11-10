// Polynomial_LinkedLists.cpp
// Implementation File for  polynomial using linked lists
// Author: Naveela Sookoo (September 2019)

#include <iostream>
#include <math.h>

using namespace std;

#include "polynomial.h"

// creating an empty polynomial
Polynomial::Polynomial(){
	head = NULL;
	size = 0;
}

Polynomial::Polynomial(const int size_p, const double coeff_p[]){
	
	size = size_p;                             //Allocate the size
	Term* head = new Term;                     //Create a new term for the beginning of the list
	Term* current;                             //Create a new object to keep track of the current
	
	current = head;                            //Allocate the location of the head to the location of the current
	
	for(int i = 0; i < size_p; i++){           //Define the coefficients of the linked list
		current->coefficient = coeff_p[i];
		current->exponent = i;
		
		current = current->next;
	}
}

// copy constructor
Polynomial::Polynomial(const Polynomial& polynomial_to_copy){
	
	if(head)
		destroy();
	
	Term *term_to_copy = polynomial_to_copy.head;
	
	int size = polynomial_to_copy.size_of();
	
	for(int i = 0; i < size; i++){
		this->InsertTerm(term_to_copy->exponent, term_to_copy->coefficient);
		term_to_copy = term_to_copy->next;
	}
}

// destructor
Polynomial::~Polynomial(){
	destroy();
}

void Polynomial::destroy(){
	
	Term* ptr = head;
	
	while(ptr != 0){
		Term *tmp = ptr;
		ptr = ptr->next;
		delete tmp;
	}
	
	head = NULL;
	
	size = 0;
}

void Polynomial::copy(const Polynomial& other){

	Term* term_to_copy = other.head;                    //Assign the head of the polynomial to copy to a node
	
	int size = other.size;                              //Assign the size of the polynomial to copy to an int
	
	for(int i = 0; i < size; i++){                      //Copy over all the coefficients
		double coeff = term_to_copy->coefficient;
		this->InsertTerm(i, coeff);
		term_to_copy = term_to_copy->next;
	}
	
}

// assignment operator
Polynomial& Polynomial::operator=(const Polynomial& other) {

	if(&other != this)
		this->copy(other);
	
	return *this;
}


bool Polynomial::operator==(const Polynomial& right){
	
	//First check for equal size. If it is not of equal size, then exit
	
	int size_right = right.size_of();
	int size_left = size_of();
	
	if(size_right != size_left)
		return 0;
	
	Term* current_term_right;
	Term* current_term_left;
	
	current_term_right = right.head;
	current_term_left = this->head;
	
	while(current_term_right != NULL && current_term_left != NULL){
		if((current_term_right->coefficient != current_term_left->coefficient))
			return 0;
		current_term_right = current_term_right->next;
		current_term_left = current_term_left->next;
	}
	
	return 1;
}

bool Polynomial::operator!=(const Polynomial& right){
	return !(*this == right);
}


int Polynomial::size_of() const{
	return this->size;
}


void Polynomial::InsertTerm(const int exp, const double coeff){
	
	Term *to_insert;
	Term *previous;
	Term *current;
	
	to_insert = new Term;
	
	to_insert->exponent = exp;
	to_insert->coefficient = coeff;
	
	size++;
	
	if(head == NULL){
		head = to_insert;
		to_insert->next = NULL;
	}
	else{
		current = head;
		
		//Start at the beginning of the list and go through until you find the end
		
		while(current != NULL){
			previous = current;
			current = current->next;
		}
		
		//Now that you have found the end of the list, you want to finally insert the new term
		
		if(current == head){
			to_insert->next = head;
			head = to_insert;
		}
		else{
			previous->next = to_insert;
			to_insert->next = current;
		}
	}
}

	
//Defines number of coefficients. Degree of polynomial is (m-1)

bool Polynomial::init(const double &m){
	
	this->size = m;
	this->head = NULL;
	
	return true;
}
		
//Defines the coefficients of a polynomial functions
Polynomial Polynomial::coeffp1(const double coeff[]){

	Polynomial output;
	
	Term* current_term;
	
	current_term = this->head;
	int size_p = this->size_of();
	
	for(int i = 0; i < size_p; i++){
		output.InsertTerm(i, coeff[i]);
	}
	
	//output.print();
	
	return output;
	
}


//Defines the second polynomial for an addition or a multiplication operation
Polynomial Polynomial::coeffp2(const double coeff[]){
	
	Polynomial output;
	
	Term* current_term;
	
	current_term = this->head;
	int size_p = this->size_of();
	
	//output.destroy();
	
	for(int i = 0; i < size_p; i++){
		output.InsertTerm(i, coeff[i]);
	}
	
	//output.print();
	
	return output;
	
}

Polynomial Polynomial::expected(const double coeff[]){
	
	Polynomial output;
	
	Term* current_term;
	
	current_term = this->head;
	int size_p = this->size_of();
	
	for(int i = 0; i < size_p; i++){
		output.InsertTerm(i, coeff[i]);
	}
	
	return output;
}

//Compares the current_polynomial with the expected_polynomial
bool Polynomial::get(const Polynomial& expected_polynomial){ 

	int exp_poly_size = expected_polynomial.size_of();
	int cur_poly_size = this->size_of();
	
	if(exp_poly_size != cur_poly_size){
		return false;
	}
	
	else if(exp_poly_size == cur_poly_size){
		bool same = 1;
		Term* current_node = this->head;
		Term* expected_node = expected_polynomial.head;
		
		for(int i = exp_poly_size; i >= 0; i--){
		
			while(current_node != NULL){ // ALWAYS CHECK FOR THIS
				
				int current_coefficient = current_node->coefficient;
				int expected_coefficient = expected_node->coefficient;
				
				if(current_coefficient == expected_coefficient){
					same = same && 1;
				}
				else{
					same = same && 0;
				}
				
				current_node = current_node->next;
				expected_node = expected_node->next;
			}
			
		}
		
		
		if(same == 1)
			return true;
		else
			return false;
		
	}

}

//Calculates the value of current_polynomial at x and then compares it with the expected_value
bool Polynomial::evaluate(const double &x, const double &expected_value){
	
	//cout << "EVALUATE AT: " << x << endl;
	//cout << "EXPECTED VALUE: " << expected_value << endl;
	
	Term *current_term = new Term;
	
	current_term = this->head;
	
	int size = this->size_of();
	
	double calculated_value = 0.0;
	
	while(current_term != NULL){
		for(int i = 0; i < size; i++){
			double current_coeff = current_term->coefficient;
			calculated_value = ((pow(x,i))*(current_coeff)) + calculated_value;
			
			current_term = current_term->next;
		}
	}
	
	//cout << "CALCULATED VALUE: " << cal_value << endl;
	
	if(calculated_value == expected_value)
		return true;
	else
		return false;
				
}

//Adds the parameters of coeff_p1 to the parameters of the coeff_p2, then compares result with expected_polynomial
Polynomial Polynomial::add(const Polynomial& p2){
	
	Polynomial result;
	
	result.destroy();
	
	//What if p1 or p2 is an empty polynomial?
	
	Term *p1current_term, *p2current_term, *resultcurrent_term;
	
	int p1size = this->size_of();
	int p2size = p2.size_of();
	
	p1current_term = this->head;
	p2current_term = p2.head;
	resultcurrent_term = result.head;
	
	int min_size = 0;

	if(p1size == p2size){
		
		while((p1current_term != NULL) && (p2current_term != NULL)){
			
			for(int i = 0; i < p1size; i++){
				result.InsertTerm(i, (p1current_term->coefficient + p2current_term->coefficient));
			
				p1current_term = p1current_term->next;
				p2current_term = p2current_term->next;
			}
		}
	}
	
	else if(p1size < p2size){

		min_size = p1size;
			
		for(int i = 0; i < min_size; i++){
			while((p1current_term != NULL)&&(p2current_term != NULL)){
				result.InsertTerm(i, (p1current_term->coefficient + p2current_term->coefficient));
				
				p1current_term = p1current_term->next;
				p2current_term = p2current_term->next;
				
				
			}
		}
		
		for(int i = min_size ; i < p2size ; i++){
			while(p2current_term != NULL){
				result.InsertTerm(i, p2current_term->coefficient);
				
				p2current_term = p2current_term->next;
			}
		}
	}
	
	else if(p1size > p2size){
		
		min_size = p2size;
		
		for(int i = 0; i < min_size; i++){
			while((p1current_term != NULL)&&(p2current_term != NULL)){
	    		result.InsertTerm(i, (p1current_term->coefficient + p2current_term->coefficient));
				
				p1current_term = p1current_term->next;
				p2current_term = p2current_term->next;
			}
		}

		for(int i = min_size ; i < p1size ; i++){
			while(p1current_term != NULL){
				result.InsertTerm(i, p1current_term->coefficient);
				
				p1current_term = p1current_term->next;
			}
		}
	}
	
	return result;

}

Polynomial Polynomial::operator+(const Polynomial& right){
	
	return add(right);

}

//Multiplies the parameters of the coeff_p1 with the parameters of coeff_p2, then compares result with expected_polynomial
Polynomial Polynomial::mult(const Polynomial& p2){
	
	Polynomial result;
	
	Term* current_term_p1;
	Term* current_term_p2;
	
	int current_exp_p1;
	int current_exp_p2;
	double current_coeff_p1;
	double current_coeff_p2;
	
	current_term_p1 = this->head;
	
	int k = 0;
	Polynomial previous;
	
	while(current_term_p1 != NULL){
		
		result.destroy();
		
		current_exp_p1 = current_term_p1->exponent;
		current_coeff_p1 = current_term_p1->coefficient;
		
		current_term_p2 = p2.head;
		
		Polynomial temp;
		
		int i = 0;
		k++;
		
		while(current_term_p2 != NULL){
			
			current_exp_p2 = current_term_p2->exponent;
			current_coeff_p2 = current_term_p2->coefficient;
			
			//cout << "Multiply " << current_coeff_p2 << " by " << current_coeff_p1 << endl;
			//cout << "The result is: " << current_coeff_p1*current_coeff_p2 << endl;
			
			double coeff_to_insert = current_coeff_p2*current_coeff_p1;
			int new_exp = current_exp_p2+current_exp_p1;
			
			//cout << new_exp << endl;
			
			i++;
			
			if((i == 1)&&(new_exp != 0)){
				for(int j = 0; j < new_exp; j++){
					temp.InsertTerm(j, 0);
				}
				
			}
			
			temp.InsertTerm(new_exp, coeff_to_insert);
			
			current_term_p2 = current_term_p2->next;
			
		}
		
		//cout << "POLYNOMIAL: ";
		//temp.print();
		
		if(k==0){
			result = temp;
			previous.copy(result);
		}
		else{
			result = previous.add(temp);
			previous.copy(result); //should it be result? changed from temp
		}
		
		//cout << "UPDATED RESULT: ";
		//result.print();
		
		current_term_p1 = current_term_p1->next;
	}
	
	return result;
			
}

Polynomial Polynomial::operator*(const Polynomial& right){
	
	return mult(right);

}

/*
void Polynomial::print(){
	
	Term* current;
	
	current = this->head;
	
    for(int i = 0; i < this->size_of(); i++){
    	cout << current->coefficient << " ";
		
		current = current->next;
	}

	cout << endl ;
}
*/