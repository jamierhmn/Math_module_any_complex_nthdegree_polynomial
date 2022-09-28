

/*************************************************************
 * mathModule.cpp
 * Written by Jamie Rahman (BC Forward)
 * Description:Calculate Math expression for operator(+,-,*,/).
 * The code is designed to give high performance,so
 * no object oriented design approach is used.
 * The programming logic and algorithm used are stack 
 * Push,pop and calculation of code is done in single iteration
 * after validation to increase performance in result
 *************************************************************/
//#include <sys/time.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
#include<string>
char stack[1000];
char stackFn[1000];
double intStack[1000];
double intStackFn[1000];
void push(char element);
char pop();
void intPush(double element);
double intPop();
void pushFn(char element);
char popFn();
void intPushFn(double element);
double intPopFn();

int numElementStack();
void traverse();
int chech_precedence(char stack_top_element,char operation);
int is_empty();
int top_element();
int top ;
int intTop;
int topFn;
int intTopFn;
long double calculatePart(char *str); 
int validateStr(char str[]);
char* signReduction(char str[]);
char* removeSPace(char str[]);
int checkValidDecimals(char *strNbr);
short int mathCalculate(char *newarray,long double &result);

/***************************************************
* error code defined if input string is invalid or if 
* during processing of input mathematical expression if
* error found
****************************************************/

#define TWO_NON_NEGATIVE_OPERATOR_SIMULTANEOUSLY 10001;
#define MULTIPLE_OPERATOR_WITHOUT_VALUE_IN_BETWEEN 10002;
#define NEGATIVE_BRACE_NEGATIVE_CONTINOUSLY 10004;
#define RESULT_EXCEEDED_MAX_VALUE 10005;
#define INVALID_DECIMAL 10006;
#define BRACEMISSING 10007;
#define INPUT_STRING_GREATER_THAN_LIMIT 10008;
#define SPACE_BETWEEN_TWO_CONSECUTIVE_NUMBER 10009;
#define COMMA_BACK_TO_BACK 10010;
#define COMMA_AFTER_DOT 10011;
#define INVALID_COMMA_POSITION 10012;
#define BLANK_SPACE_AFTER_DOT 10013;
#define INSUFFUCIENT_NUMBER 10014;

int NUMBER=0,OPERATION=1,INVALID_INPUT=10015,OPENBRACE=4;
int CLOSEBRACE=5,BLANKSPACE=6,COMMA=7,DOT=8;

/*****************************************************
 * Get the type of each character required to form
 * floating point number and check if the input character 
 * is brace or operator(+,-,*,/)
 *****************************************************/
 
int get_type(char c) {
    if  (c >= '0' && c <= '9')
        return NUMBER;
    else if (c == '*' || c == '/' || c == '+' || 
	c == '-' )
	    return OPERATION;
    else if (c=='('||c==')')
	{
	if(c=='(')	
		return OPENBRACE;
	else if(c==')')
		return CLOSEBRACE;
	}
    else if (c==' ')
        return BLANKSPACE;
    else if (c== ',')
	return COMMA;
    else if (c=='.')
	return DOT;
     
	return 10009;
}

/**********************************************************
 * insert each number in input expression to intPush() and 
 * retrieve from intPop() .
 * input each operator(+,-,*,/) in input expression  and 
 *  brace in push() and pop() .
 *********************************************************/

void push(char value)
{   
   top++;
   stack[top] = value;
}
 
char pop()
{
   char element;
 
   if ( top == -1 )
      return top;
 
   element = stack[top];
   top--;
 
   return element;
}   

void intPush(double value)
{   
   intTop++;
   intStack[intTop] = value;
}
 
double intPop()
{
   double element;
 
   if ( intTop == -1 )
      return intTop;
 
   element = intStack[intTop];
   intTop--;
 
   return element;
}    
int numElementStack()
{
	return (top+1);
}

int is_empty()
{
   if ( top == - 1 )
      return 1;
   else
      return 0;
}
 
int top_element()
{
   return stack[top];
}

void pushFn(char value)
{   
   topFn++;
   stackFn[topFn] = value;
}
 
char popFn()
{
   char element;
 
   if ( topFn == -1 )
      return topFn;
 
   element = stackFn[topFn];
   topFn--;
 
   return element;
}   

void intPushFn(double value)
{   
   intTopFn++;
   intStackFn[intTopFn] = value;
}
 
double intPopFn()
{
   double element;
 
   if ( intTopFn == -1 )
      return intTopFn;
 
   element = intStackFn[intTopFn];
   intTopFn--;
 
   return element;
}    

/************************************************************
 * chech_precedence() function allows only lower priority 
 * operator to sit on top of higher operator operator on 
 * stack
 ***********************************************************/

int chech_precedence(char stack_top_element,char operation)
{
  if(((stack_top_element=='*')|| (stack_top_element=='/'))&&
  ((operation=='+')||(operation=='-')))
  return 0;
  else if(((stack_top_element=='*')|| (stack_top_element=='/'))&&
  ((operation=='*')||(operation=='/')))
  return 0;
  else if (((stack_top_element=='+')|| (stack_top_element=='-'))&&
  ((operation=='+')||(operation=='-')))
  return 0;
  else if(((stack_top_element=='+')|| (stack_top_element=='-'))&&
  ((operation=='/')||(operation=='*')))
  return 1;
  else if(stack_top_element=='(') 
  return 1;
  return 0;
}

/***************************************************************
 * mathCalculate() method is responsible for all the stack
 * push   pop operation and calculation of mathematical 
 * expression starting from the beginning till the end .
 * It calculates two numbers at a time and push it in 
 * stack and advances till end of expression .it either 
 * looks for brace termination at the end or end of input 
 * string.In each calculation it takes two numbers from intPop() 
 * and one operator from pop() and result is push back to stack
 * using intPush().When all the numbers in the stack is calculated 
 * the final result is returned.
 ****************************************************************/



short int mathCalculate(char *newarray,long double &result)
{

  char b[65533]= { NULL };
  char tempBuffer[100]= { NULL };
  char tempBuffer1[100]= { NULL };
  long double temp1=0,temp2=0;
  int j=0,k=0,inc;
  long double tempResult=0;
  int negative=0,PreserveNegative=0;
  int i=0;
  int braceIncrement=0,numInc=0;
  char a[65533],m=0,pop_element,c;
  int incBlank =0,incpost=0,replaceMinus=0,minusStartPoint=0;
  int validation=0,nextNumber=0;
  int numberinStack=0,storeNegativeStack=0,singleNegative=0;
  long double singleNumberValue;
  result=0;
  validation = validateStr(newarray);
  top=-1;
  intTop=-1;
  topFn=-1;
  intTopFn=-1;
/******************************************************
to test the validation please uncomment this section
* and compile it again
*******************************************************/
   if(validation!=0)
  {
	return validation;
  }

/*****************************************************
* reduces blank space after validation
*****************************************************/
  while (newarray[incBlank] != '\0')
   {
	
   
   // if(!(newarray[incBlank] == ','))
	 //  {
	     if (!(newarray[incBlank] == ' '))
		  {

		      b[incpost] = newarray[incBlank];
	          incpost++;
	        }
	   //}
	
	
	 incBlank++;
   }
  b[incpost] = '\0';
   incpost=0;
  
  incBlank=0;
  while (b[incBlank] != '\0')
   {
	  numInc++;
      if((b[incBlank]=='+') && (b[incBlank+1]=='-'))	
	  {
	    
		a[incpost] = '-';
	    incpost++;  
	    incBlank=incBlank+2;	
      }

     else if((b[incBlank]=='-') && (b[incBlank+1]=='+'))	
	 {
		 a[incpost] = '-';
	     incpost++;
	     incBlank=incBlank+2;	
     }
	 else if((b[incBlank]=='-') && (b[incBlank+1]=='-'))	
	 {
		 a[incpost] = '+';
	     incpost++;     
	     incBlank=incBlank+2;	
     }

	else 
	{
		a[incpost]=b[incBlank];
		incBlank++;
		incpost++;
    }
  }
 
  a[incpost]='\0';
  
   if((a[0]=='-')&&(a[1]=='('))
   {
	 negative=1;
	 i=1;
     
   }
    if(a[0]=='+')
   {
	 i=1; 
//	 plusAdd=1;

   }
   
   if((a[0]=='-')&&(get_type(a[1])==NUMBER))
   {
	 PreserveNegative=1;
	 
   }
   if((a[0]=='-')&&(a[1]=='.') \
	   &&(get_type(a[2])==NUMBER))
   {
	  
	   PreserveNegative=1;
   }
   
/***************************************************
* the main while loop.it do all the necessary logical
* steps to complete the calculation and find the result
***************************************************/  
   while(a[i])
  {

	 if((a[i]=='(') ||(OPERATION==get_type(a[i])))
	{
		if(a[i]=='('){
			braceIncrement++;
			push(a[i]); //insert open brace into stack
			}
	    
		else if((OPERATION==get_type(a[i]))&&
			((PreserveNegative==0)||(i!=0)))
		{
		  
		    nextNumber=0;
			if((a[i]=='-') &&(a[i-1]=='*'||a[i-1]=='/'))
		 {
			nextNumber=1;
		 }
		 
		  else if((a[i]=='-')&&(a[i-1]=='('))
		  {
			nextNumber=1;
		  }
		 
		 else if(!((a[i]=='-')&&(a[i-1]=='(')))
		 {
	   	 if(is_empty()==1)
		 {
		   push(a[i]); 	
		 }
		 else if((is_empty()==0)&&
			(chech_precedence(stack[top],a[i])==1))
		 {
			push(a[i]);
		 }
	     else if((numElementStack()>=1)&&
			(chech_precedence(stack[top],a[i])==0))
		{
		  b[j]=pop();
		  push(a[i]);  
		  temp1=intPop();
		  temp2=intPop();
		 //sprintf(tempBuffer,"%4.8f#%4.8f#%c",temp2,temp1,b[j]);
		  sprintf(tempBuffer,"%16.15f#%16.15f#%c",temp2,temp1,b[j]);
		  tempResult=calculatePart(tempBuffer);
		  c=pop();
		  if(temp2==0&&c=='-'&&b[j]=='-')
		  {
			  push(c);
			  if(tempResult<0)
			  tempResult=-tempResult;
		  }
		  else
			  push(c);
		  	  intPush(tempResult);
		  tempBuffer[100]='\0';
		  j++;
			 			  
		  }
		}
	}
	}

	else if(a[i]==')')
	{
		braceIncrement--;
		while(1){
		pop_element=pop();
	    if(pop_element=='(')
		{
		    if(braceIncrement==0)
			{
		
			if(negative==1&&numberinStack>1){
				temp1=-intPop();
				negative=0;
				intPush(temp1);
				}
			 
			}
			break;	
		}
		b[j]=pop_element;
		
		temp1=intPop();
		temp2=intPop();
		sprintf(tempBuffer1,"%16.15f#%16.15f#%c",temp2,temp1,b[j]);
		tempResult=calculatePart(tempBuffer1);	
	/*	c=pop();
		if(temp2==0&&c=='-'&&b[j]=='-')
		{
			  push(c);
			  if(tempResult<0)
			  tempResult=-tempResult;
		}
		else
		      push(c);*/
		tempBuffer1[100]='\0';
		if(braceIncrement==0)
		{
		  	if(negative==1)
			{
		      tempResult=-tempResult;
		      negative=0;
			}
		}
	 
		intPush(tempResult);
		j++;
		}
    }
	else if(get_type(a[i])==NUMBER ||a[i]=='.')
	{
		inc=0;
		char floatvalue[25];
		while((get_type(a[i])==NUMBER)||a[i]=='.'||a[i]==',')
		{
      	  
	      floatvalue[inc]=a[i]; 
		  inc++;
		  i++;
		}
		floatvalue[inc]='\0';
		i--;
	     
		int decimalCheck=checkValidDecimals(floatvalue);
		if(decimalCheck==10006)
		return INVALID_DECIMAL;
	    if(decimalCheck==10012)
		return INVALID_COMMA_POSITION;
		if(decimalCheck==10011)
		return COMMA_AFTER_DOT;
		inc=0;
		int k=0;
		while (floatvalue[inc] != '\0')
		 {
    
		   if(!(floatvalue[inc] == ','))
		   {
	          b[k] = floatvalue[inc];
	          k++;
		   }
		
		   inc++;
		}
		b[k] = '\0';
		long double inputNumber = atof(b);
	   	if(PreserveNegative==1)
		{
		  	inputNumber=-inputNumber;
		    PreserveNegative=0;
		}
		 
		singleNumberValue=inputNumber;
		if(nextNumber==1)
		{
			inputNumber=-inputNumber;
			singleNumberValue=inputNumber;
		}
        intPush(inputNumber);
		for(int fl=0;fl<31;fl++){
		    floatvalue[fl]='\0';
		}
		numberinStack++;
	}
   
	i++;
 }
    if(a[i+1] == '\0'||intTop!=-1)
	 {
		 if(numberinStack<2)
		 {
		    result=singleNumberValue;
			if(negative==1)
			{
			    
				result=-singleNumberValue;
			}
			 return 0;
		 }

 	 while(intTop!=-1)
	 {
        temp1=intPop();
	  	if(intTop==-1&&numberinStack<2)
		{
		    result=tempResult;
			break;
		}
			
		b[j]=pop();
		if(b[j]=='*'||b[j]=='/')
		{
			temp2=intPop();
			sprintf(tempBuffer1,"%16.15f#%16.15f#%c",temp2,temp1,b[j]);
			tempResult=calculatePart(tempBuffer1);
			temp1=tempResult;
			tempBuffer1[100]='\0';
			intPushFn(temp1);
		}
		else
		{
				push(b[j]);
				intPushFn(temp1);
		}
		
   } 
	 while(top!=-1)
	  {
		b[j]=pop();
		pushFn(b[j]);
	
      }
	 
	 while(topFn!=-1)
	  {
		b[j]=popFn();
		temp1=intPopFn();
		temp2=intPopFn();
		sprintf(tempBuffer1,"%16.15f#%16.15f#%c",temp1,temp2,b[j]);
		tempResult=calculatePart(tempBuffer1);
	  	intPushFn(tempResult);
		tempBuffer1[100]='\0';
	  }
	
	 }//finish while loop
  
 
 if(negative==1)
 {
	tempResult=-tempResult;
	
 }	

 if(tempResult>999999999999999.999999999)
 {
	 return RESULT_EXCEEDED_MAX_VALUE;
 }
 
 result=tempResult;
 return 0; 
}

/***************************************************************
 * This method calculatePart() takes two parameters as numbers and
 * one parameters as operator to calculate and return the floating 
 *  point value in return
 **************************************************************/

long double calculatePart(char *str)
{

  char *pch='\0',*pch1='\0';
  long double  value1,value2;
  long double result;
  int inc=0;
  pch = strtok (str,"#");
  pch1=pch;
  value1=atof(pch1);
  while (pch != NULL)
  {
    if(inc==0)
	{
		pch = strtok (NULL, "#");
        pch1=pch;
		value2=atof(pch1); 
		    	
    }
	else if(inc==1)
	{
		pch1 = strtok (NULL, "#");
		if(!strcmp(pch1,"*")){
		result=value1*value2;
		break;
		}
		else if(!strcmp(pch1,"/")){
		if(value2==0.00000000){
		result=0.00000000;
		break;
		}
		result=value1/value2;
		break;
		}
		if(!strcmp(pch1,"+")){
          
		result=value1+value2;
       	break;
		}
		if(!strcmp(pch1,"-"))
		{
		result=value1-value2;
		break;
		}
	
	}
    inc++;
  }
 return result;
 
}


/********************************************************
* validateStr() function takes whole string as input and 
* return error code if invalid input as mathematical expression
* is passed to Math Module
*********************************************************/ 
int validateStr(char str[])
{
    int i = 0;
    int openBraceCount=0,closeBraceCount=0;
//	int length=strlen(str);

	while (str[i]!='\0')
    {
     	
	  switch(str[i])
        {
       
            
            case '+':
            
                  
           if( (str[i+1] == '*' || str[i+1] == '/'
			   || str[i+1] == '+'))
           {
                            
            return MULTIPLE_OPERATOR_WITHOUT_VALUE_IN_BETWEEN;               
                
           }    
          else if(( str[i+1]==' ') &&(str[i+2] == '*' || str[i+2] == '/'
			   || str[i+2] == '+'))
           {
                            
            return MULTIPLE_OPERATOR_WITHOUT_VALUE_IN_BETWEEN;               
                
           }  
          
            break;
            case '-':
            
           if (str[i+1] == '*' || str[i+1] == '/')
           {
             
           return MULTIPLE_OPERATOR_WITHOUT_VALUE_IN_BETWEEN;               
              
           } 
		   else  if ((str[i+1]==' ' )&&
		   (str[i+2] == '*' || str[i+2] == '/'))
           {
             
           return MULTIPLE_OPERATOR_WITHOUT_VALUE_IN_BETWEEN;               
              
           } 
         
	         
            break;
            
            case '*':

           
            if (str[i+1] == '*' || str[i+1] == '/' || 
				str[i+1] == '+')
            {
              
             return TWO_NON_NEGATIVE_OPERATOR_SIMULTANEOUSLY;               
              
            }
           else if((str[i+1]==' ')&&(str[i+2] == '*' ||
			   str[i+2] == '/' || str[i+2] == '+' ))
            {
              
             return TWO_NON_NEGATIVE_OPERATOR_SIMULTANEOUSLY;               
              
            }
            break;
            
            case '/':
            
            
           if( (str[i+1] == '*' || str[i+1] == '/' || 
			   str[i+1] == '+' ))
            {
             
             return TWO_NON_NEGATIVE_OPERATOR_SIMULTANEOUSLY;               
               
            }
            
            else if((str[i+1]==' ')&&(str[i+2] == '*' ||
				str[i+2] == '/' || 	str[i+2] == '+'))
            {
              
             return TWO_NON_NEGATIVE_OPERATOR_SIMULTANEOUSLY;               
              
            }
			break;
                        
            default:
           
        
			break;
	   }
        
     i++;
    }
    if(OPENBRACE==get_type(str[i]))
		 {
		
			openBraceCount++;
		 }	
	if(CLOSEBRACE==get_type(str[i]))
		{
		
			closeBraceCount++;
		}	
	  	 
	if(INVALID_INPUT==get_type(str[i]))
		{
		
			 return INVALID_INPUT;
		}
		if((NUMBER==get_type(str[i]))&&(' '==str[i+1])
			&&(NUMBER==get_type(str[i+2])))
		{
			return SPACE_BETWEEN_TWO_CONSECUTIVE_NUMBER;
		}
		
			if((NUMBER==get_type(str[i]))&&(' '==str[i+1])
			&&(' '==str[i+2])&&(NUMBER==get_type(str[i+3])))
		{
			return SPACE_BETWEEN_TWO_CONSECUTIVE_NUMBER;
		}
		if((str[i] == ',')&&(str[i+1] == ','))
		{
		   return COMMA_BACK_TO_BACK;
		}
		if((str[i] == '.')&&(str[i+1] == ' '))
		{
		   return BLANK_SPACE_AFTER_DOT;
		}

		if((str[i] == '.')&&(str[i+1] == ' ')&&(str[i+2]==' '))
		{
		   return BLANK_SPACE_AFTER_DOT;
		}
	if(openBraceCount!=closeBraceCount)
	return BRACEMISSING;
    return 0;
}

/*********************************************
*checkValidDecimals() function checks for valid 
* decimal.It check for one decimal point per number 
* of input at maximum 
**********************************************/

int checkValidDecimals(char *strVal)
{

  int totDec = 0,dotFound=0,k=0;
  int position[10],commaPos=1;
  int length=strlen(strVal);
 
  for (int i = 0; strVal[i] != '\0'; i++) 
  {
		if (strVal[i] == '.')
		{
		  dotFound=i; 	  	 
		  totDec++;
		}
		if (totDec > 1)
		{
		  return INVALID_DECIMAL;
		}
		if((strVal[i] == '.') &&(get_type(strVal[i+1])!= NUMBER))
		
		{
		  return INVALID_DECIMAL;
		}
 }
  
  if(totDec==1)
  {
    for(int j=dotFound+1;j<length;j++)
    {
		if(strVal[j]==',')
		{
			return COMMA_AFTER_DOT;
		
		}
	}
    for(int j=dotFound-1;j>=0;j--)
    {
	   if(strVal[j]==',')
	  {
		   position[k]= commaPos;
		   k++;
		   
	   }
	   commaPos++;
    }
    for(int l=0;l<k;l++)
    {
	  if(position[l]%4!=0)
		  {
			  return INVALID_COMMA_POSITION;	
		  }
	}
	
  }	 
  k=0;
  commaPos=1;
  if(totDec==0)
  {
   for(int i=length-1;i>=0;i--)
    {
	   
 	   if(strVal[i]==',')
	   {
		   position[k]= commaPos;
		   k++;
	   }
	   commaPos++;
    }
    for(int l=0;l<k;l++)
    {
	  if(position[l]%4!=0)
		  {
			  return INVALID_COMMA_POSITION;	
		  }
    }
	
  }
 
  return 0;
}

