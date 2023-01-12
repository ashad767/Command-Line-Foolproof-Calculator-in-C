//clc_v3.c
//Ashad Ahmed
//December 1, 2021

#include <stdio.h> //libraries
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//global variables
float a=0,b=0,c=0,d=0,e=0;
float memory[1000];

//check if a number input is valid (e.g. not like abc123) and ask the user for another input if the previous one was not valid
float checkInput(void){ //function for checking if user inputs are numbers and not strings
  float n1=0;
  int x = 0, countDec=0;
  char line[100];

  while(x==0){
    scanf("%s",line); //get input
    int len = strlen(line)-1; //used for indexing to get each character and test it
    for(int i=len; i>=0; i--){
      if(line[i]=='.'){ //used to keep track of how many decimals there are in the number
        countDec++;
      }
      if((isdigit(line[i])==0 && line[i]!= '.' && line[i]!='-') || (line[i]=='.' && countDec>1) || (line[i]=='-' && i!=0)){//checking if the character is not a number and its not a decimal and negative sign or if the character is a decimal but there is more than one decimal or if the character is a negative sign but its not at the start of the number
        puts("Invalid value try again.");
        countDec=0;
        break; 
      }
      else if((line[i]=='.' && strlen(line)==1) || (line[i]=='-' && strlen(line)==1)){ //if the input is just a decimal or if the input is just a negative sign
        puts("Invalid value try again.");
        countDec=0;
        break; 
      }//this is the last iteration meaning the loop has checked all the characters and therefore it is valid
      else if(i==0){
        n1 = atof(line); //convert string to float
        x=1; //this is for exiting the while loop since the number testing is finished
        break; //break out of for loop
      }
    }
  }
  return n1; //return valid number
}

//checking for valid binary operations
int checkOperationB(void){
  char ln[100];
  puts("Enter operation: (+,-,*,/,%,^)");
  scanf("%s", ln);
  while(strcmp(ln, "+")!=0 && strcmp(ln, "-")!=0 && strcmp(ln, "/")!=0 && strcmp(ln, "*")!=0 && strcmp(ln, "^")!=0 && strcmp(ln, "%")!=0){ //if input is not a valid binary operation
    puts("Invalid input, please enter a valid operation:");
    scanf("%s", ln);
  }
  return ln[0];
}
//checking for valid unary operations
int CheckOperationU(void){
  char c[100];
  printf("Enter operation: S (for square root) , L (for logarithm) , E (for exponential) , C (for ceil) , F (for floor)\n");
  scanf("%s", c); //tell user to enter operation
  c[0] = tolower(c[0]);
  while(strcmp(c, "s")!=0 && strcmp(c, "l")!=0 && strcmp(c, "e")!=0 && strcmp(c, "c")!=0 && strcmp(c, "f")!=0){ //if input is not a valid unary operation
    puts("Invalid input, please enter a valid operation:");
    scanf("%s", c);
  }
  return c[0];
}
//checking input for variables
int checkInputV(void){
  char ch[100];
  puts("Please enter the name of the variable (A single character between 'a' to 'e'):");
  scanf("%s", ch);
  ch[0] = tolower(ch[0]); 
  while(strcmp(ch, "a")!=0 && strcmp(ch, "b")!=0 && strcmp(ch, "c")!=0 && strcmp(ch, "d")!=0 && strcmp(ch, "e")!=0 ){ //if input is not a valid variable (a-e)
    puts("Invalid input, please enter a valid variable name (a-e):");
    scanf("%s", ch);
  }
  return ch[0];
}

//checking if input is a number for advanced operations
int checkInputAdv(char line[100]){
  int countDec=0;
  int len = strlen(line)-1; //get length of the string for indexing and checking each character
  for(int i=len; i>=0; i--){
    if(line[i]=='.'){ //the number can only have one decimal, so if one is found, increase this by 1
      countDec++;
    }
    if((isdigit(line[i])==0 && line[i]!= '.' && line[i]!='-') || (line[i]=='.' && countDec>1) || (line[i]=='-' && i!=0)){ //if the character is not a number and it is not a decimal and negative sign or if the character is a decimal but there is more than one decimal or if the character is a negative that is not at the start of the number
      return false;
    }//if the user enters just a decimal or just a negative sign
    else if((line[i]=='.' && strlen(line)==1) || (line[i]=='-' && strlen(line)==1)){
      return false;
    }
  }
  return true;
}

//checking first number for advanced binary
float checkFirstNum(){
  bool check = false;
  char line[100];
  float num1=0;
  //Loop runs until a number or variable is found 
  while(!check){
    scanf("%s",line);
    check = checkInputAdv(line); //checks if it is a valid number
    if(check){ //if it is a number
      num1 = atof(line);
      break;
    } //if it is valid variable
    else if((line[0]=='a' || line[0]=='b' || line[0]=='c' || line[0]=='d' || line[0]=='e') && strlen(line)==1){
      break;
    }//otherwise the user has entered an invalid input
    else{
      puts("Invalid input");
    }
  }
  //If the user entered a valid variable for the first number, then it is assigned here
  if(line[0]=='a'){num1 = a;}
  if(line[0]=='b'){num1 = b;}
  if(line[0]=='c'){num1 = c;}
  if(line[0]=='d'){num1 = d;}
  if(line[0]=='e'){num1 = e;}

  return num1;
}

//checking second number for advanced binary
float checkSecondNum(float num1, char operation){
  float num2=0;
  bool check = false;
  char line[100];

  //Division restriction
  if(operation == '/'){
    while(!check){
      scanf("%s",line);
      check = checkInputAdv(line);
      num2 = atof(line);
      if(check && num2==0){ //if input is a number and denominator is zero
        puts("Denominator cannot be zero.");
        check = false;
      }
      else if(check && num2!=0){
        break;
      }
      else if(((line[0]=='a' && a==0) || (line[0]=='b' && b==0) || (line[0]=='c' && c==0) || (line[0]=='d' && d==0) || (line[0]=='e' && e==0)) && strlen(line)==1){ //check if input is a variable and if it is zero
        puts("Denominator cannot be zero.");
      }
      else if(((line[0]=='a' && a!=0) || (line[0]=='b' && b!=0) || (line[0]=='c' && c!=0) || (line[0]=='d' && d!=0) || (line[0]=='e' && e!=0)) && strlen(line)==1){ //check if input is a variable and its not zero
        break;
      } //if is not any of the above, then it is an invalid input
      else{
        puts("Invalid input. Please try again.");
      }
    }
  }
  //Modulo restriction
  if(operation == '%'){
    while(!check){
      scanf("%s",line);
      check = checkInputAdv(line);
      num2 = atof(line);
      if(check && num2==0){ //if input is a number and denominator is zero
        puts("Second number cannot be zero.");
        check = false;
      }
      else if(check && num2!=0){
        break;
      }
      else if(((line[0]=='a' && a==0) || (line[0]=='b' && b==0) || (line[0]=='c' && c==0) || (line[0]=='d' && d==0) || (line[0]=='e' && e==0)) && strlen(line)==1){ //if input is a variable and it is zero
        puts("Second number cannot be zero.");
      }
      else if(((line[0]=='a' && a!=0) || (line[0]=='b' && b!=0) || (line[0]=='c' && c!=0) || (line[0]=='d' && d!=0) || (line[0]=='e' && e!=0)) && strlen(line)==1){ //if input is a variable and it is not zero
        break;
      }
      else{ //otherwise it is an invalid input
        puts("Invalid input");
      }
    }
  }
  //Exponent restriction
  if(operation=='^'){
    while(!check){
      scanf("%s",line);
      check = checkInputAdv(line);
      num2 = atof(line);
      if(check && num1==0 && num2<=0){ //if input is a number and base (first number) is zero then check if second number (power) is non-negative
        puts("Power must be greater than zero.");
        check = false;
      }
      else if(check && num1!=0){ //if input is a number and base is not zero
        break;
      }
      else if(((line[0]=='a' && a<=0) || (line[0]=='b' && b<=0) || (line[0]=='c' && c<=0) || (line[0]=='d' && d<=0) || (line[0]=='e' && e<=0)) && strlen(line)==1 && num1==0){ //if it is a variable and it is not positive
        puts("Power must be greater than zero.");
      }
      else if(((line[0]=='a' && a>0) || (line[0]=='b' && b>0) || (line[0]=='c' && c>0) || (line[0]=='d' && d>0) || (line[0]=='e' && e>0)) && strlen(line)==1 && num1==0){ //if it is variable and it is positive and base is zero
        break;
      }
      else if((line[0]=='a' || line[0]=='b' || line[0]=='c' || line[0]=='d' || line[0]=='e') && strlen(line)==1 && num1!=0){
        break; //if it is a valid variable and base is not zero 
      }
      else{ //otherwise invalid input
        puts("Invalid input");
      }
    }
  }
  //All other binary operations 
  else if(operation=='*' || operation=='+' || operation=='-'){
    while(!check){
      scanf("%s",line);
      check = checkInputAdv(line);
      if(check){ //check if it is a number
        num2 = atof(line);
        break;
      }//check if it is a variable
      else if((line[0]=='a' || line[0]=='b' || line[0]=='c' || line[0]=='d' || line[0]=='e') && strlen(line)==1){
        break;
      }//if not, then it is an invalid input
      else{
        puts("Invalid input");
      }
    }
  }

  //If the user entered a valid variable for the second number, then it is assigned here
  if(line[0]=='a'){num2 = a;}
  if(line[0]=='b'){num2 = b;}
  if(line[0]=='c'){num2 = c;}
  if(line[0]=='d'){num2 = d;}
  if(line[0]=='e'){num2 = e;}

  return num2;
}

//checking the first number for advanced unary mode
float checkNumAdvancedU(char operation){
  bool check = false;
  float num1=0;
  char line[100];
  //Square root restriction
  if(operation=='s'){
    while(!check){
      scanf("%s",line);
      check = checkInputAdv(line);
      num1 = atof(line);
      if(check && num1<0){ //if the the input is a number and it is negative
        puts("Enter a number greater than or equal to zero.");
        check = false;
      }
      else if(((line[0]=='a' && a<0) || (line[0]=='b' && b<0) || (line[0]=='c' && c<0) || (line[0]=='d' && d<0) || (line[0]=='e' && e<0)) && strlen(line)==1){ //if the input is a variable and it is negative
        puts("The number cannot be negative.");
      }
      else if(((line[0]=='a' && a>=0) || (line[0]=='b' && b>=0) || (line[0]=='c' && c>=0) || (line[0]=='d' && d>=0) || (line[0]=='e' && e>=0)) && strlen(line)==1){
        break; //if the input is a variable and it is positive or 0
      }
      else{//otherwise invalid input
        puts("Invalid input");
      }
    }
  }
  //Logarithm restriction
  else if(operation=='l'){
    while(!check){
      scanf("%s",line);
      check = checkInputAdv(line);
      num1 = atof(line);
      if(check && num1<=0){ //if the input is a number but it is not positive
        puts("The number must be positive.");
        check = false;
      }
      else if(((line[0]=='a' && a<=0) || (line[0]=='b' && b<=0) || (line[0]=='c' && c<=0) || (line[0]=='d' && d<=0) || (line[0]=='e' && e<=0)) && strlen(line)==1){ //if the input is a variable but it is not positive
        puts("The number must be positive.");
      }
      else if(((line[0]=='a' && a>0) || (line[0]=='b' && b>0) || (line[0]=='c' && c>0) || (line[0]=='d' && d>0) || (line[0]=='e' && e>0)) && strlen(line)==1){ //if the input is a variable and it is positive
        break;
      }//otherwise invalid input
      else{
        puts("Invalid input");
      }
    }
  }
  //All other unary operations (no restrictions on e^x, ceiling, or floor functions)
  else if(operation=='e' || operation=='c' || operation=='f'){
    while(!check){
      scanf("%s",line); 
      check = checkInputAdv(line); //check if input is a valid number
      if(check){ //if it is a valid number
        num1 = atof(line);  //convert the string into float
        break;
      }
      else if((line[0]=='a' || line[0]=='b' || line[0]=='c' || line[0]=='d' || line[0]=='e') && strlen(line)==1){ //if the input is a valid variable
        break;
      }//otherwise the input is invalid
      else{
        puts("Invalid input");
      }
    }
  }
  //If a variable was selected, assign the correct variable to num1 so it can be used in calculations
  if(line[0]=='a'){num1 = a;}
  if(line[0]=='b'){num1 = b;}
  if(line[0]=='c'){num1 = c;}
  if(line[0]=='d'){num1 = d;}
  if(line[0]=='e'){num1 = e;}

  return num1;
}

//getting option for  menu
char getOption(void){
  char option[100];
  printf("Please select one of the following items:\nB) - Binary Mathematical Operations such as addition and subtraction.\nU) - Unary Mathematical Operations, such as square root, and log.\nA) - Advances Mathematical Operations, using variables, arrays.\nV) - Define variables and assign them values.\nM) - View the memory.\nR) - Erase the memory.\nX) - Exit.\n");

  scanf("%s", option); //get the user's input for the type of operation (Binary, Unary... etc)
  option[0] = toupper(option[0]); //convert option to uppercase
  
  while(strcmp(option, "B")!=0 && strcmp(option, "U")!=0 && strcmp(option, "A")!=0 && strcmp(option, "V")!=0 && strcmp(option, "X")!=0 && strcmp(option, "M")!=0 && strcmp(option, "R")!=0){ //if the option is not on the menu, then it is invalid
    puts("Invalid option, please try again.");
    scanf("%s", option);
    option[0] = toupper(option[0]);
  }

  printf("You have selected option %s.\n", option); //print the user's selection
  return option[0];
}

//getting option for advanced menu
char getOption2(void){
  char option2[100];
  printf("Select one of the following items:\nB) - Binary Mathematical Operations, such as addition and subtraction.\nU) - Unary Mathematical Operations, such as square root, and log.\nX) - Exit and back to the main menu.\n");

  scanf("%s", option2); //get the user's input for the type of operation (Binary or Unary)
  option2[0] = toupper(option2[0]);
  //Invalid option entered
  while(strcmp(option2,"B")!=0 && strcmp(option2,"U")!=0 && strcmp(option2,"X")!=0){
    puts("Invalid option, please try again.");
    scanf("%s", option2);
    option2[0] = toupper(option2[0]);
  }
  return option2[0];
}

float checkInputB(float num1, char operation){
  float num2=0;
  //avoiding division by zero

  if(operation=='/' && num2==0){
    while(operation=='/' && num2==0){ 
      puts("Enter a non-zero number:");
      num2 = checkInput();
    }
  }
  //avoiding a power of 0 or negative when the base is 0
  else if((operation=='^' && num1==0 && num2<=0)){
    while((operation=='^' && num1==0 && num2<=0)){
      puts("Enter a number greater than zero:");
      num2 = checkInput();
    }
  }
  else if(operation=='^' && num1!=0){
    puts("Enter second number:");
    num2=checkInput();
  }
  //avoiding dividing by zero when user selects modulo
  else if(operation=='%'&& num2==0){
    while(operation=='%'&& num2==0){
      puts("Enter a non-zero number:");
      num2 = checkInput();
    }
  }
  else if(operation=='+' || operation=='-'|| operation=='*'){
    printf("Enter second number:\n"); //tell user to enter second number
    num2 = checkInput();
  }
  return num2;
}

//check input for unary number input 
float checkInputU(char operation){
  float num1=0;
  while(operation=='s'){
    puts("Please enter a number greater than or equal to zero:");
    num1 = checkInput();
    if(num1>=0){ //if number is positive or zero (required for square root)
      break;
    }
  }
  while(operation=='l'){
    puts("Please enter a number greater than zero:");
    num1 = checkInput();
    if(num1>0){ //if number is greater than zero (required for log)
      break;
    }
  }
  if(operation!='s' && operation!= 'l'){ //if the operation is not log or square root, then the numbers do not have any restrictions
    puts("Please enter a number:");
    num1 = checkInput();
  }
  return num1;
}

//calculate result for binary
float binaryOperation(float num1, char operation, float num2){
  float result=0;
  if(operation=='+'){
    result = num1+num2;
  }
  if(operation=='-'){
    result = num1-num2;
  }
  if(operation=='*'){
    result = num1*num2;
  }
  if(operation=='/'){
    result = num1/num2; 
  }
  if(operation=='%'){
    result = fmod(num1, num2);
  }
  if(operation=='^'){
    result = pow(num1, num2);
  }
  return result;
}

//calculate result for unary
float unaryOperation(float num1, char operation){
  float result=0;
  if(operation=='s'){
    result = pow(num1, 0.5); 
  }
  if(operation=='l'){
    result = log10(num1);
  }
  if(operation=='e'){
    result = exp(num1);
  }
  if(operation=='c'){
    result = ceil(num1);
  }
  if(operation=='f'){
    result = floor(num1);
  }
  return result;
}

//assign variable the value inputted by user
float variableOperation(float x, char ch){
  if(ch=='a'){
    a = x;
  }
  if(ch=='b'){
    b = x;
  }
  if(ch=='c'){
    c = x;
  }
  if(ch=='d'){
    d = x;
  }
  if(ch=='e'){
    e = x;
  }
  printf("Variable %c is set to: %.2f\n", ch, x);
  return 0;
}

//calculate result for advanced binary
float advancedBinaryOperation(float num1, char operation, float num2){
  float result=0;
  if(operation=='+'){
    result = num1+num2;
  }
  if(operation=='-'){
    result = num1-num2;
  }
  if(operation=='*'){
    result = num1*num2;
  }
  if(operation=='/'){
    result = num1/num2;
  }
  if(operation=='%'){
    result = fmod(num1, num2);
  }
  if(operation=='^'){
    result = pow(num1, num2); 
  }
  return result;
}

//calculate result for advanced unary
float advancedUnaryOperation(float num1, char operation){
  float result=0;
  //print the correct output according to operations and numbers chosen
  if(operation=='s'){
    result = pow(num1, 0.5);
  }
  if(operation=='l'){
    result = log10(num1);
  }
  if(operation=='e'){
    result = exp(num1);
  }
  if(operation=='c'){
    result = ceil(num1);
  }
  if(operation=='f'){
    result = floor(num1);
  }
  return result;
}

int showMemory(int pos){
  char memoryOption[100];
  int x=0;
  bool decimal = false;

  if(pos==0){ //if the memory is empty, then tell the user that and return to main menu
    puts("Memory is empty.");
    return 0;
  }
  else{
    while(true){
      printf("Number of items currently stored in memory: %d\n", pos);
      printf("Enter a number between 1 and %d to view that item or enter 0 to see all items or enter x to exit to main menu\n", pos);
      scanf("%s", memoryOption);
      memoryOption[0] = toupper(memoryOption[0]);
      int len = strlen(memoryOption)-1;
      x = atof(memoryOption); //checks if user entered a number and not a character or string
      if(strcmp(memoryOption, "X")==0 && strlen(memoryOption)==1){ //if the checkInputMemory() returns -1, it means the user entered "X" therefore exiting out of memory menu
        break;
      }
      for(int i=len; i>=0; i--){
        if(memoryOption[i]=='.' && strlen(memoryOption)!=1){ //if the user enters something like 3.2 then it is invalid
          for(int n=i; n<len+1; n++){
            if(memoryOption[n]!='0' && memoryOption[n]!='.'){ //however this checks to make sure its not 1.0,1.0000, etc.
              puts("Invalid input, try again.");
              decimal = true;
              break;
            }
          }
        }
        if(decimal){ //if the number is a decimal, e.g. 1.5, then that is not valid input so break out of this for loop too
          decimal = false;
          break;
        }
        else if(memoryOption[i]=='.' && strlen(memoryOption)==1){ //if its just a decimal
          puts("Invalid input, try again.");
          break;
        }
        else if(isdigit(memoryOption[i])==0 && memoryOption[i]!='.'){ //invalid input (e.g. abc123)
          puts("Invalid input, try again.");
          break;
        }
        else if(x==0 && i==0){ //If i==0, then the input is not a decimal or something like abc123 and if x is 0 the user wishes to see all contents
          for(int i=0;i<pos;i++){
            printf("%d) %.2f\n", i+1, memory[i]);
          }
        break;
        }
        else if(x>=1 && x<=pos && x!=0 && i==0){ //if x is in between the 1 and the number of elements in memory
          printf("%d) %.2f\n", x, memory[x-1]);
          break;
        }
        else if(i==0){ //the user has entered something outside of the correct range 
          puts("Invalid input, try again.");
        } 
      }
    }
  }
  return 0;
}

int eraseMemory(){
  memset(memory, 0, 100);
  puts("Memory has succesfully been erased.");
  return 0;
}

int main(void) {
  float num1=0, num2=0, result=0;//declaring variables to use later
  char operation;
  char option[100], option2[100];
  int pos=0;

  //welcome message
  printf("Welcome to my Command-Line Calculator (CLC)\nDeveloper: Ashad Ahmed\nVersion: 3\nDate: December 1, 2021\n-----------------------------------------------------------\n");

  while(option[0]!= 'X'){ //loop for displaying menu, allowing user to choose type of operation and numbers until they wish to exit by entering "X" for their option
    //print selection menu for calculator
    
    option[0] = getOption();
    
    //BINARY MATHEMATICAL OPERATIONS
    if(option[0]=='B'){ //If the user selects binary operations
      printf("Enter first number:\n"); //tell user to enter first number
      num1 = checkInput(); //get first number and see if its valid
      operation = checkOperationB(); //get operation and see if the operation entered is valid
      num2=checkInputB(num1, operation); //check input for second number, including restrictions such as division by zero
      result = binaryOperation(num1, operation, num2); //calculate the result and store it
      printf("The result is: %.2f\n", result);
      memory[pos] = result; //store in memory
      pos++;
    }
    
    //UNARY MATHEMATICAL OPERATIONS
    if(option[0] == 'U'){
      operation = CheckOperationU(); //check if the operation is valid for unary operations
      num1 = checkInputU(operation); //get valid input for num1
      result = unaryOperation(num1, operation);
      printf("The result is: %.2f\n", result);
      memory[pos] = result; //store in memory
      pos++;  
    }

    //ADVANCED MATHEMATICAL OPERATIONS
    if(option[0]=='A'){
      while(option2[0]!='X'){
        option2[0] = getOption2();
        //EXIT TO MAIN MENU
        if(option2[0]=='X'){
          break;
        }
        //BINARY OPERATIONS WITH ADVANCED MODE
        if(option2[0]=='B'){
          printf("Enter first number or variable:\n");
          num1 = checkFirstNum(); //checks if the user inputted a valid number of variable (e.g., not zero for log)
          operation = checkOperationB();
          printf("Enter second number or variable:\n");
          num2 = checkSecondNum(num1, operation);
          result = advancedBinaryOperation(num1, operation, num2);
          printf("The result is: %.2f\n", result);
          memory[pos] = result; //store in memory
          pos++;  
        }
        //UNARY OPERATIONS IN ADVANCED MODE
        if(option2[0]=='U'){
          operation = CheckOperationU();
          puts("Enter number or variable:");
          num1 = checkNumAdvancedU(operation);
          result = advancedUnaryOperation(num1, operation);
          printf("The result is: %.2f\n", result);
          memory[pos] = result;
          pos++; 
        }
        operation = ' ';
        num1 = 0;
        num2 = 0;
      }
    }

    //DEFINE VARIABLES AND ASSIGN THEM
    if(option[0]=='V'){ //if the user selects V from the main menu
      float x;
      char ch;
      ch = checkInputV(); //checking if the input is a valid variable option (a-e)
      puts("Please enter a value to assign to the variable:");
      x = checkInput(); //checking if input is a valid number
      variableOperation(x, ch); //assigning the value to the correct variable
    }

    //VIEW MEMORY
    if(option[0]=='M'){
      showMemory(pos);
    }
    
    //ERASE MEMORY
    if(option[0]=='R'){
      if(pos>0){
        pos = eraseMemory(); //=empty array means the array starts at index 0 therefore I have to set  pos to zero
      }
      else{
        puts("Memory is already empty.");
      }
    }

    //EXIT
    if(option[0]=='X'){ //if user selects X from the main menu
      puts("Thank you for using CLC, goodbye!");
      break;
    }

    //resetting variables
    num1=0, num2=0;
    operation = ' ';
    memset(option, 0, 100);
    memset(option2, 0, 100);
  }
}