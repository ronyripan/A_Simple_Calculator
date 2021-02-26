#include<bits/stdc++.h>
#define PI 3.14159265
int iflag = 0;
int flag = 0;
using namespace std;
string InfixToPostfix(string expression);

int HasHigherPrecedence(char operator1, char operator2);
double performt(string a,double operand);
bool IsOperator(char C);
bool IsTrigonometric(char C);
bool IsOperand(char C);
double EvaluatePostfix(string expression);
double PerformOperation(char operation, double operand1, double operand2);
bool IsNumericDigit(char C);
int main()
{
    cout<<"#use parenthesis in trigonometric function such as sin(x)"<<endl;
	string expression;
	cout<<"Enter Postfix Expression \n";
	getline(cin,expression);
	double result = EvaluatePostfix(InfixToPostfix(expression));
	cout<<"Output = "<<result<<"\n";
}
string InfixToPostfix(string expression)
{
	// Declaring a Stack from Standard template library in C++.
	stack<char> S;
	string postfix = ""; // Initialize postfix as empty string.
	for(int i = 0;i< expression.length();i++) {

		// Scanning each character from left.
		// If character is a delimitter, move on.
		//cout<<expression[i]<<endl;
		if(expression[i] == ' ' || expression[i] == ',') continue;
		if(expression[i]=='s'||expression[i]=='c'||expression[i]=='t')
        {
            string a;
            if(expression[i]=='s') a = "sin";
            if(expression[i]=='c') a = "cos";
            if(expression[i]=='t') a = "tan";
            i+=4;
            double operand = 0.0, iflag = 0,n=10.0;
            while(expression[i]!=')')
            {
                if(expression[i]=='.')
                    iflag = 1;
                if(iflag==0)
				operand = (operand*10.0) + (expression[i] - '0');
				else if(iflag==1&&expression[i]!='.')
				{
				    operand = operand+(expression[i]-'0')/n;
				    n*=10.0;
				}
				i++;
            }

            //cout<<operand<<endl;
            double result = performt(a,operand);
            //cout<<result<<endl;
            int int_part,deci_part;
            int_part = int(result);
           // cout<<int_part<<endl;
            //cout<<(result - int_part)*100<<endl;
            if((result - int(result))!=0.0)
            deci_part = ((result - int(result))*100)+1;
            else
                deci_part = 0;
           // cout<<deci_part<<endl;
            stack<int>di;
            if(int_part == 0)
                postfix+=0+'0';
            else{
            while(int_part)
            {
                int digits = int_part%10;
                di.push(digits);
                int_part/=10;
            }
            while(!di.empty())
            {
                postfix+=(di.top()+'0');
                di.pop();
            }}
            if(deci_part){
            postfix +='.';
            while(deci_part)
            {
                int digits = deci_part%10;
                di.push(digits);
                deci_part/=10;
            }
            while(!di.empty())
            {
                postfix+=(di.top()+'0');
                di.pop();
            }}
           // postfix +=',';
            //cout<<postfix<<endl;
        }
		// If character is operator, pop two elements from stack, perform operation and push the result back.
		else if(IsOperator(expression[i]))
		{
		    postfix+=',';
			while(!S.empty() && S.top() != '(' && HasHigherPrecedence(S.top(),expression[i]))
			{
				postfix+= S.top();
				postfix+=',';
				S.pop();
			}
			S.push(expression[i]);
		}
		// Else if character is an operand
		else if(IsOperand(expression[i]))
		{
			postfix +=expression[i];
		}

		else if (expression[i] == '(')
		{
			S.push(expression[i]);
		}

		else if(expression[i] == ')')
		{
		    postfix +=',';
			while(!S.empty() && S.top() !=  '(') {
				postfix += S.top();
                postfix +=',';
				S.pop();
			}
			S.pop();
		}
	}
    postfix += ',';
	while(!S.empty()) {
		postfix += S.top();
		postfix += ',';
		S.pop();
	}
	cout<<postfix<<endl;
	return postfix;
}

// Function to verify whether a character is english letter or numeric digit.
// We are assuming in this solution that operand will be a single character
bool IsOperand(char C)
{
	if(C >= '0' && C <= '9') return true;
	if(C =='.') return true;
	return false;
}
// Function to verify whether an operator is right associative or not.
int IsRightAssociative(char op)
{
	if(op == '^') return true;
	return false;
}

// Function to get weight of an operator. An operator with higher weight will have higher precedence.
int GetOperatorWeight(char op)
{
	int weight=-1;
    if(op=='+' || op=='-')
    {
        weight=1;
    }
    else if(op=='*' || op=='/')
    {
        weight=2;
    }
    else if(op=='^')
    {
        weight=3;
    }
    return weight;
}

// Function to perform an operation and return output.
int HasHigherPrecedence(char op1, char op2)
{
	int op1Weight = GetOperatorWeight(op1);
	int op2Weight = GetOperatorWeight(op2);

	// If operators have equal precedence, return true if they are left associative.
	// return false, if right associative.
	// if operator is left-associative, left one should be given priority.
	if(op1Weight == op2Weight)
	{
		if(IsRightAssociative(op1)) return false;
		else return true;
	}
	return op1Weight > op2Weight ?  true: false;
}
double performt(string a,double operand)
{
    //cout<<operand<<endl;
    if(a=="sin")
    {
        return sin((operand*PI)/180);
    }
    else if(a=="cos")
    {
        return cos(operand*PI/180);
    }
    else if(a=="tan")
    {
        if(operand==90.0)
        {
            cout<<"MATH ERROR"<<endl;
            exit(0);
        }
        return tan(operand*PI/180);
    }
}
// Function to evaluate Postfix expression and return output
double EvaluatePostfix(string expression)
{
	// Declaring a Stack from Standard template library in C++.
	stack<double> S;

	for(int i = 0;i< expression.length();i++) {

		// Scanning each character from left.
		// If character is a delimitter, move on.
		if(expression[i] == ' ' || expression[i] == ',') continue;

		// If character is operator, pop two elements from stack, perform operation and push the result back.
		else if(IsOperator(expression[i])) {
			// Pop two operands.
			double operand2 = S.top(); S.pop();
			double operand1 = S.top(); S.pop();
			// Perform operation
			double result = PerformOperation(expression[i], operand1, operand2);
			//Push back result of operation on stack.
			S.push(result);
		}
		else if(IsNumericDigit(expression[i])){
			// Extract the numeric operand from the string
			// Keep incrementing i as long as you are getting a numeric digit.
			double operand = 0.0,n=10.0;
			flag = 0;
			while(i<expression.length() && IsNumericDigit(expression[i])) {
				// For a number with more than one digits, as we are scanning from left to right.
				// Everytime , we get a digit towards right, we can multiply current total in operand by 10
				// and add the new digit.
				if(flag==0)
				operand = (operand*10.0) + (expression[i] - '0');
				else if(flag==1&&expression[i]!='.')
				{
				    operand = operand+(expression[i]-'0')/n;
				    n*=10.0;
				}
				i++;
			}
			// Finally, you will come out of while loop with i set to a non-numeric character or end of string
			// decrement i because it will be incremented in increment section of loop once again.
			// We do not want to skip the non-numeric character by incrementing i twice.
			i--;
			//cout<<operand<<endl;

                // Push operand on stack.
			S.push(operand);
		}
	}
	// If expression is in correct format, Stack will finally have one element. This will be the output.
	return S.top();
}

// Function to verify whether a character is numeric digit.
bool IsNumericDigit(char C)
{
	if(C >= '0' && C <= '9') return true;
	if(C=='.') {flag = 1;return true;}
	return false;
}

// Function to verify whether a character is operator symbol or not.
bool IsOperator(char C)
{
	if(C == '+' || C == '-' || C == '*' || C == '/')
		return true;

	return false;
}

// Function to perform an operation and return output.
double PerformOperation(char operation, double operand1, double operand2)
{
	if(operation == '+') return operand1 +operand2;
	else if(operation == '-') return operand1 - operand2;
	else if(operation == '*') return operand1 * operand2;
	else if(operation == '/') return operand1 / operand2;

	else cout<<"Unexpected Error \n";
	return -1;
}
