#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
/** 
 * this is the language grammar and now lets implement recursive descent parser
 * expression -> term ((+) term)*
 * term -> factor ((*) factor)*
 * factor -> [0-9] | '(' expression ')'
 */

int expression();
int term();
int factor();
bool match(char token);
void moveCursor();
bool isDigit(char *token);
void error(const char *message);
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
     if (match('(')) {
        int value = expression(); 
        if (!match(')')) {
            error("Expected closing parenthesis.");
        }
        return value;
    } else if (isDigit(input)) {
        int value = *input - '0'; 
        moveCursor();
        return value;
    } else {
        error("Unexpected token. Expected a digit or '('.");
        return -1; 
    }
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

void error(const char *message) {
    printf("Error: %s\n", message);
    exit(1); 
}

int main(){
    input = "(9+3)*2";
    int result = expression();
    printf("Final value is: %d\n",result);
    return 0;
}