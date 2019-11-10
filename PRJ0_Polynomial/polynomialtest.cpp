// PolynomialTest_LinkedLists.cpp
// Test File for  polynomial using linked lists
// Author: Naveela Sookoo (September 2019)

#include <iostream>
#include <cstring>
#include <string>
#include <math.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

const int MAXLINE = 256;

#include "polynomial.h" // Class to represent polynomials

int main(){

/*****Getting commands from the test.in file*****/

	Polynomial p1_current_polynomial;
	Polynomial p2_second_polynomial;
	Polynomial p3_expected_polynomial;
	
	Polynomial temp;
	
	Polynomial p4; //stores the current_polynomial after initialization
	Polynomial p5; //stores the second_polynomial after initialization
	Polynomial p6; //stores the expected_polynomial after initialization
	
	Polynomial sum; //contains the contents of add
	Polynomial p7; // initialized polynomial to the size
	Polynomial p8; //to compare with add result
	
	Polynomial product; //contains the contents of mult
	Polynomial p9; // initialized polynomial to the size
	Polynomial p10; //to compare with mult result
	
	char oneline[MAXLINE];
	int previous_length_of_command;
	
	while(!cin.eof()){
		
		cin.getline(oneline, MAXLINE);
		
		int length_of_line = (strlen(oneline)); 
		
		char copy_1[length_of_line];
		
		for(int i = 0; i < length_of_line; i++){
			copy_1[i] = oneline[i];
		}
		
		char delim[] = " ";
		
		char* token = strtok(copy_1, delim);
		
		// oneline contains the original line
		// token_1 and copy_1 contains the command
		
		int length_of_command = (strlen(copy_1)) + 1; //Add one to account for space after command
		
		char prev_token[length_of_command]; 
		
		
		int num_of_numbers = length_of_line - length_of_command;
		
		char input[num_of_numbers];
		
		for(int i = length_of_command; i < length_of_line && oneline[i] != '\n'; i++){
			int space = i - length_of_command;
			input[space] = oneline[i];
		}
		
		
/*******INIT FUNCTION************************************************************************************************************************************************************/

		if(0 == strcmp(token, "init")){
			
			//cout << "INIT ";
			
			int k = 0;
			int integer = 0;
			
			while(k < num_of_numbers){
				if(input[k] == ' ')
					break;
				else if((input[k] >= '0') && (input[k] <= '9')){
					integer = integer*10 + (input[k] - '0');
				}
				k++;
			}
			
			if(temp.init(integer)){
				cout << "success" << endl;
			}
			else
				cout << "failure" << endl;
		
		}

/********************************************************************************************************************************************************************************/

		else if((0 == strcmp(token, "coeff_p1"))||(0 == strcmp(token, "coeff_p2"))||(0 == strcmp(token, "add"))||(0 == strcmp(token, "mult"))||(0 == strcmp(token, "get"))){
						
			/****************************************          The following block of code is taken and adapted from:                 ******************************************/
			/************************************ https://stackoverflow.com/questions/1894886/parsing-a-comma-delimited-stdstring **********************************************/
			
			/***********************************************************************START***************************************************************************************/
			
			int num_of_semis = 0;
			
			for(int i = 0; i < num_of_numbers; i++){
				if(input[i] == ';'){
					num_of_semis++;
				}
			}
			
			int num_of_coeff = num_of_semis + 1;
			
			vector<double> vect;

			stringstream ss(input);

			for (double i; ss >> i;) {
				vect.push_back(i);    
				if ((ss.peek() == ' ') || (ss.peek() == ';'))
					ss.ignore();
			}
			
			/************************************************************************END****************************************************************************************/
			
			//Copy vector to array
			
			double* input_2 = vect.data();
			
			double terms[num_of_coeff];
			
			int size_of_vector = num_of_coeff*2;
			
			int sz = 0;
			
			for(int i = 0; i < size_of_vector; i++){
				if((i%2)==1){
					terms[sz] = input_2[i];
					sz++;
				}
			}

/***********COEFF_P1 FUNCTION***************************************************************************************************************************************************/
			
			if((0 == strcmp(token, "coeff_p1"))){
				
				p4.destroy();
				
				//cout << "COEFF_P1 ";
				
				if(sz != temp.size_of())
					cout << "failure" << endl;
				else{
					p1_current_polynomial.init(temp.size_of());
					
					p4 = p1_current_polynomial.coeffp1(terms);
					
					//p4.print();
					
					cout << "success" << endl;
				}
					
			}
			
/***********COEFF_P2 FUNCTION***************************************************************************************************************************************************/

			else if(0 == strcmp(token, "coeff_p2")){
				
				p5.destroy();
				
				//cout << "COEFF_P2 ";
				
				if(sz != temp.size_of())
					cout << "failure" << endl;
				else{
					p2_second_polynomial.init(temp.size_of());
					
					p5 = p2_second_polynomial.coeffp2(terms);
					
					cout << "success" << endl;
				}
			}
			else if(0 == strcmp(token, "get")){
				
				p6.destroy();
				
				//cout << "GET ";
				
				p3_expected_polynomial.init(sz);
				
				p6 = p3_expected_polynomial.expected(terms);
				
				if(p4.get(p6))
					cout << "success" << endl;
				else
					cout << "failure" << endl;
			}
			else if(0 == strcmp(token, "add")){
				
				sum.destroy();
				
				//cout << "ADD ";
				
				sum = p4.add(p5);
				
				//sum.print();
				
				p7.init(sz);
				
				p8 = p7.expected(terms);
				
				//p8.print();
				
				if(sum.get(p8))
					cout << "success" << endl;
				else
					cout << "failure" << endl;
				
			}
			else if(0 == strcmp(token, "mult")){
				
				product.destroy();
				
				//cout << "MULT ";
				
				product = p4.mult(p5);
				
				//product.print();
				
				p9.init(sz);
				
				p10 = p9.expected(terms);
				
				//p10.print();
				
				if(product.get(p10))
					cout << "success" << endl;
				else 
					cout << "failure" << endl;
			
			}
		}

/*******EVAL FUNCTION ***********************************************************************************************************************************************************/

		else if(0 == strcmp(token, "eval")){
			
			enum State{ START, GOT_EVAL_DIGIT, GOT_EVAL_POINT, GOT_EVAL_DECIMAL, GOT_SPACE, GOT_EXP_DIGIT, GOT_EXP_POINT, GOT_EXP_DECIMAL, DONE };
	
			State s = START;
			
			int i = 0; 
			
			int eval_decimal_count = 0;
			double eval_integer = 0.0;
			double eval_decimal = 0.0;
			
			int exp_decimal_count = 0;
			double exp_integer = 0.0;
			double exp_decimal = 0.0;
			
			while((s != DONE) && (i < num_of_numbers)){
			
				switch(s){
				
				case START:
					if(input[i] == '.')
						s = GOT_EVAL_POINT;
					else if((input[i] >= '0') && (input[i] <= '9')){
						eval_integer = eval_integer*10 + (input[i] - '0');
						s = GOT_EVAL_DIGIT;
					}
					break;
				
				case GOT_EVAL_DIGIT:
					if((input[i] >= '0') && (input[i] <= '9')){
						eval_integer = eval_integer*10 + (input[i] - '0');
						s = GOT_EVAL_DIGIT;
					}
					else if(input[i] == '.')
						s = GOT_EVAL_POINT;
					else if(input[i] == 0)
						s = DONE;
					break;
				
				case GOT_EVAL_POINT:
					if((input[i] >= '0') && (input[i] <= '9')){
						eval_decimal_count++;
						eval_decimal = eval_decimal*10 + (input[i] - '0');
						s = GOT_EVAL_DECIMAL;
					}
					break;
					
				case GOT_EVAL_DECIMAL:
					if((input[i] >= '0') && (input[i] <= '9')){
						eval_decimal_count++;
						eval_decimal = eval_decimal*10 + (input[i] - '0');
						s = GOT_EVAL_DECIMAL;
					}
					else if(input[i] == ' ')
						s = GOT_SPACE;
					break;
				
				case GOT_SPACE:
					if((input[i] >= '0') && (input[i] <= '9')){
						exp_integer = exp_integer*10 + (input[i] - '0');
						s = GOT_EXP_DIGIT;
					}
					else if(input[i] == ' ')
						s = GOT_SPACE;
					break;
				
				case GOT_EXP_DIGIT:
					if((input[i] >= '0') && (input[i] <= '9')){
						exp_integer = exp_integer*10 + (input[i] - '0');
						s = GOT_EXP_DIGIT;
					}
					else if(input[i] == '.')
						s = GOT_EXP_POINT;
					else if(input[i] == 0)
						s = DONE;
					break;
				
				case GOT_EXP_POINT:
					if((input[i] >= '0') && (input[i] <= '9')){
						exp_decimal_count++;
						exp_decimal = exp_decimal*10 + (input[i] - '0');
						s = GOT_EXP_DECIMAL;
					}
					break;
					
				case GOT_EXP_DECIMAL:
					if((input[i] >= '0') && (input[i] <= '9')){
						exp_decimal_count++;
						exp_decimal = exp_decimal*10 + (input[i] - '0');
						s = GOT_EXP_DECIMAL;
					}
					else if(input[i] == ' ')
						s = DONE;
					break;
					
				case DONE:
					return 0;
					break;
				
				}
			i++;
			}
		
			double eval_whole = eval_integer;
			double eval_frac = (double)eval_decimal/pow(10, (double)eval_decimal_count);
			
			double eval_number = eval_whole + eval_frac;
			
			double exp_whole = exp_integer;
			double exp_frac = (double)exp_decimal/pow(10, (double)exp_decimal_count);
			
			double exp_number = exp_whole + exp_frac;
			
			//cout << "EVALUATE ";
			
					if(p4.evaluate(eval_number, exp_number))
						cout << "success" << endl;
					else
						cout << "failure" << endl;
				
			
			
		}

/********************************************************************************************************************************************************************************/
	}
	
	return 0;
}
	