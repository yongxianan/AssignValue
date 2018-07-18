#include "TextParser.h"
#include "Exception.h"
#include "CException.h"
#include "Error.h"
#include <stdlib.h>
//#include <math.h>
/*
int FindStrLength (char *str){
  int i=0;
  while(str[i]!= '\0'){
    i++;
  }
  return i;	//the length is from 0-8 in an array but will output 9 character
}

char *convertToLowerCase(char *str){
  char *result=(char *)malloc(FindStrLength (str)+1);
  int i=0;
  
  strcpy(result,str);
  
  while(str[i] != '\0'){
    result[i] = tolower (result[i]);
    //printf("str1=%d\n",str1[k]);
    i++;
  }
  result[i]='\0';
  return result;
}
*/

int StringCompare(char *Opcode,char **message){
  int i=0;
  if(*message ==NULL){
    return 0;
  }
  while(*Opcode ==' '){
    Opcode++;
  }
  while(**message ==' '){
    (*message)++;
  }
  /*
  if(**message =='\0'){
    return 0;
  }
  */
  while((**message)==(*Opcode)){
    (*message)++;
    i++;
    Opcode++;
    if(*Opcode=='\0' || *Opcode==' '){
      return 1;
    }
  }
  while(i!=0){
    (*message)--;
    i--;
  }
  
  return 0;
}
//  if it can't find the name from varTableMapping,
//  i thought it will need to auto create a new name in varTableMapping
//  and assign storage value
char *extractWord(char **message){
  char *extractMessage = malloc(100);
  int i=0;
  while(**message==' '){
    (*message)++;
  }
  while((**message >= 'A' &&  **message <= 'Z') || (**message >= 'a' &&  **message <= 'z')){
    extractMessage[i] = (**message);
    (*message)++;
    i++;
  }
  extractMessage[i]='\0';
  
  return extractMessage;
}

int extractInteger(char **message){
  int extractNumber=0;
  while(**message==' '){
    (*message)++;
  }
 
  while(**message >= '0' &&  **message <= '9'){
    extractNumber=(extractNumber*10);
    extractNumber=(extractNumber+((**message)-'0'));
    (*message)++;
  }
  return extractNumber;
}
  
int checkWhetherIsInteger(char **message){
  while(**message==' '){
    (*message)++;
  }
  if(**message >= '0' &&  **message <= '9'){
    return 1;
  }
  else{
    return 0;
  }
}


int parseTextAndAssignValues(char *line, VariableMapping *varTableMapping) {
  int i=0;
  int detectNameFromTableMapping=0;
  int storageNumber=0;
  if(StringCompare("assign",&line)==1){
    while(*line!='\0'){
      if(varTableMapping==NULL){
        throwSimpleError(ERR_TABLE_IS_MISSING,"ERR_TABLE_IS_MISSING");
      }
      while(varTableMapping->name != NULL){
        if(StringCompare(varTableMapping->name,&line)==1){
          detectNameFromTableMapping=1;
          if(StringCompare("=",&line)==1){
            if(checkWhetherIsInteger(&line)==1){
              storageNumber=(extractInteger(&line));
              *(varTableMapping->storage)=storageNumber;
            }
            else{
              throwSimpleError(ERR_NOT_A_NUMBER,"ERR_NOT_A_NUMBER");
            }
          }
          else{
            throwSimpleError(ERR_MALFORM_ASSIGN,"= sign missing in the line ");
          }
        }
        varTableMapping++;
        i++;
      }
      while(i!=0){
        varTableMapping--;
        i--;
      }
      if(detectNameFromTableMapping==0){
        throwSimpleError(ERR_UNKNOWN_VARIABLE,"ERR_UNKNOWN_VARIABLE");
      }
      else{
        detectNameFromTableMapping=0;
        while(*line==' '){
          line++;
        }
      }
        
      
    }
  }
  else if(line==NULL){
    return 0;
  }
  else if(StringCompare("\0",&line)==1){
    return 0;
  }
  else{
    throwSimpleError(ERR_UNKNOWN_COMMAND,"ERR_UNKNOWN_COMMAND");
  }
}
























