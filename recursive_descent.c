#include<stdio.h>
#include<stdbool.h>
/** 
 * this is the language grammar and now lets implement recursive descent parser
 * expression -> term ((+) term)*
 * term -> factor ((*) factor)*
 * factor -> [0-9]
 */

int expression();
int term();
int factor();
bool match(char token);
void moveCursor();
bool isDigit(char *token);
const char *input; 

int expression(){
  int value = term();
   while(match('+')){
    value += term();
   }
   return value;
}
int term(){
    int value = factor();
    while(match('*')){
      
       value *= factor();   
    }
    return value;
}
int factor(){
    if(isDigit(input)){
    int number = *input- '0';
    moveCursor();
    return number;
    }
    printf("Encountered unrecognized digit.\n");
    exit(0);
}
void moveCursor(){
    if(*input != '\0')
        input++;
}
bool match(char token){
    if(*input == token){
        moveCursor();
        return true;
    }
   return false;
}
bool isDigit(char *token){
    printf("digit: %d\n",*token);
    return *token >= 48 && *token <= 57;
}
int main(){
    input = "9+3*2";
    int result = expression();
    printf("Final value is: %d\n",result);
    return 0;
}