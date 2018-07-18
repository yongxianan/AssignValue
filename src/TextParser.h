#ifndef _TEXTPARSER_H
#define _TEXTPARSER_H

typedef struct VariableMapping VariableMapping;
struct VariableMapping {
  char *name;
  int *storage;
};
int StringCompare(char *Opcode,char **message);
char *extractWord(char **message);
int extractInteger(char **message);
int parseTextAndAssignValues(char *line, VariableMapping *varTableMapping);

#endif // _TEXTPARSER_H
