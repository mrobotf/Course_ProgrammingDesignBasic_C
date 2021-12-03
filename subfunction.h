#ifndef SUBFUNCTION_H_INCLUDED
#define SUBFUNCTION_H_INCLUDED

extern void calcom(int Tag, int com[]);
extern void calhum(int Tag, int hum[]);
extern void printform(char (*board)[8]);
extern void PrintLetter(int op);
extern void CcountMinus(int op, int c[]);
extern void CcountPlus(int op, int c[]);
extern char Changeop(int op);

#endif // SUBFUNCTION_H_INCLUDED
