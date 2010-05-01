#include <iostream>
#include <stack>
#include <wchar.h>
#include <complex>
#include "symbolTable.h"
#include <tr1/unordered_map>

using namespace std;
using namespace std::tr1;

/*

codigo para tipos
0 int
1 float
2 string
3 boolean
4 complex
5 error
6 void
7 program

*/

COMPILER matematrix

symbolTable st;
constTable ct;
Memoria MemGlobal;
Memoria MemTemp;
Memoria MemConst;
Memoria MemLoc;

int // types
	  floats, integer, boolean, complexi, stringg;

int // operators
	  plus, minus, times, slash, diff, gtr, lss, gtreq, lsseq, eqeq, andop, orop, equ;

int // object kinds
	  var, def;


int // opcodes
	  ADD,  SUB,   MUL,   DIV,   EQU,  LSS, GTR, DIFF,
	  GTREQ, LSSEQ, EQEQ, ANDOP, OROP, RET, PRINT, RETURN,
	  GOTO, GOTOF, GOTOV, GOSUB, READ, ERA, PARAM;

int numproc, tipoactual,tipo_proc, cont_cuadruple, diract,asact, aux,k,arg,tipoarg;  //Variables utilizadas para generar cuadruplos.

stack<int> PTipos;
stack<int> POperadores;
stack<int> POperandos;
stack<int> PSaltos;

typedef struct {
	int op;
	int opdo1;
	int opdo2;
	int res;
} cuadruplos;

unordered_map<int, cuadruplos> hasht;

int semantico(int a, int b , int c) {

int t;
			//	 +  -  *  /  <> >  < >= <= == and or =
int semanticCube[5][5][13] = {{ {0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 5, 5, 0},
                                {1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 5, 5, 5},
   /*int*/                      {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
                                {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
                                {4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5} },
                              { {1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 5, 5, 5},
   /*float*/                    {1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 5, 5, 1},
                                {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
                                {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
                                {4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5} },
                              { {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
  /*string*/                    {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
                                {5, 5, 5, 5, 3, 5, 5, 5, 3, 5, 5, 5, 2},
                                {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
                                {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5} },
                              { {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
                                {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
  /*bool*/                      {5, 5, 5, 5, 3, 5, 5, 5, 3, 5, 5, 5, 3},
                                {5, 5, 5, 5, 5, 5, 5, 5, 3, 3, 5, 5, 3},
                                {5, 5, 5, 5, 5, 5, 5, 5, 3, 3, 5, 5, 5} },
                              { {4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 5, 5, 5},
  /*complejo*/                  {4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 5, 5, 5},
                                {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
                                {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
                                {4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 5, 5, 4} }};


t = semanticCube[a][b][c];
return t;
}


int rellenar(int a, int b) {
	if(hasht.find(a) != hasht.end()) {
		hasht[a].res = b;
	}
	
}

int buildCruadruple(int op){
	int uno, dos, id1, id2, res, temp;
	dos = PTipos.top();
	PTipos.pop();
	uno = PTipos.top();
	PTipos.pop();

/*
while (!POperandos.empty()) {
cout << "Pila operandos en cuadruplo" << POperandos.top() << endl;
POperandos.pop();
}
*/
		
if(semantico(uno, dos, op) != 5 ) {	
	
	id2 = POperandos.top();
	POperandos.pop();
	id1 = POperandos.top();
	POperandos.pop();
	
	res = semantico(uno, dos, op);
		switch(res) {
			case 0:
				temp = MemTemp.mint;
				MemTemp.mint = MemTemp.insertaInt(MemTemp.mint, 6000, res);
			break;
			case 1:
				temp = MemTemp.mfloat;
				MemTemp.mfloat = MemTemp.insertaFloat(MemTemp.mfloat, 7000, res);
			break;
			case 2:
				temp = MemTemp.mstring;
				MemTemp.mstring = MemTemp.insertaString(MemTemp.mstring, 8000, res);
			break;
			case 3:
				temp = MemTemp.mboolean;
				MemTemp.mboolean = MemTemp.insertaBoolean(MemTemp.mboolean, 9000, res);
			break;
			case 4:
				temp = MemTemp.mcomplex;
				MemTemp.mcomplex = MemTemp.insertaComplex(MemTemp.mcomplex, 10000, res);
			break;
			default:
				cout << "Type mismatch" << endl;
		}
	cuadruplos x;
	x.op = op;
	x.opdo1 = id1;
	x.opdo2 = id2;
	x.res = temp;
	hasht[cont_cuadruple] = x;
	cont_cuadruple++;
	POperandos.push(temp);
	PTipos.push(res);
	POperadores.pop();
cout << "pila tipos top " << PTipos.top() << endl;
	} else {
		cout << "Semantic error: Type mismatch" << endl;

	}
return 0;
}


int buildCruadruple2(int op){
	int uno, dos, id1, id2, res;
	dos = PTipos.top();
	PTipos.pop();
	uno = PTipos.top();
	PTipos.pop();

	if( semantico(uno, dos, op) != 5 ) {
		id2 = POperandos.top();
		POperandos.pop();
		id1 = -1;
		res = POperandos.top();
		POperandos.pop();
		cuadruplos x;
		x.op = op;
		x.opdo1 = id1;
		x.opdo2 = id2;
		x.res = res;
		hasht[cont_cuadruple] = x;
		cont_cuadruple++;
		POperadores.pop();
	} else {
		cout << "Semantic error: Type mismatch" << endl;

	}
return 0;
}
int buildCuadruple3(){
int res, aux;	
aux = PTipos.top();
PTipos.pop();
cout << "El valor de aux es: " << aux << endl;
	if(aux == 3 ) {
		res = POperandos.top();
		POperandos.pop();
cout << "1er cuadruplo" << cont_cuadruple << endl;
		cuadruplos x;
		x.op = GOTOF;
		x.opdo1 = res;
		x.opdo2 = -1;
		x.res = -1;
		hasht[cont_cuadruple] = x;
		cont_cuadruple++;
		PSaltos.push((cont_cuadruple-1));
	} else {
		cout << "Semantic error: Type mismatch" << endl;

	}
return 0;
}

int buildCuadrupleWhile(){
	int falso = PSaltos.top();
	PSaltos.pop();
	int retorno = PSaltos.top();
	PSaltos.pop();
cout << "2ndo cuadruplo" << cont_cuadruple << endl;
	cuadruplos x;
	x.op = GOTO;
	x.opdo1 = -1;
	x.opdo2 = -1;
	x.res = retorno;
	hasht[cont_cuadruple] = x;
	cont_cuadruple++;
	rellenar(falso,cont_cuadruple);
return 0;
}
int buildCuadruple4(int a){
	int id2, res;
		id2 = -1;
		POperandos.pop();
		cuadruplos x;
		x.op = GOTOF;
		x.opdo1 = a;
		x.opdo2 = id2;
		x.res = -1;
		hasht[cont_cuadruple] = x;
		cont_cuadruple++;
return 0;
}
void buildCuadruple5(int uno, int dos, int tres){
	cuadruplos x;
	x.op = uno;
	x.opdo1 = dos;
	x.opdo2 = tres;
	x.res = -1;
	hasht[cont_cuadruple] = x;
	cont_cuadruple++;
}

void buildCuadrupleM(int a, int b, int c, int d){
	cuadruplos x;
	x.op = a;
	x.opdo1 = b;
	x.opdo2 = c;
	x.res = d;
	hasht[cont_cuadruple] = x;
	cont_cuadruple++;

}
void buildCuadrupleFOR(){
	int temp, temp2;
	int tipo = PTipos.top();
	PTipos.pop();
	cout << "entro al for" << endl;
		switch(tipo) {
			case 0:
				temp = MemTemp.mint;
				MemTemp.mint = MemTemp.insertaInt(MemTemp.mint, 6000, tipo);
				temp2 = MemTemp.mint;
				MemTemp.mint = MemTemp.insertaInt(MemTemp.mint, 6000, tipo);
			break;
			case 1:
				temp = MemTemp.mfloat;
				MemTemp.mfloat = MemTemp.insertaFloat(MemTemp.mfloat, 7000, tipo);
				temp2 = MemTemp.mfloat;
				MemTemp.mfloat = MemTemp.insertaFloat(MemTemp.mfloat, 7000, tipo);
			break;
			case 2:
				temp = MemTemp.mstring;
				MemTemp.mstring = MemTemp.insertaString(MemTemp.mstring, 8000, tipo);
				temp2 = MemTemp.mstring;
				MemTemp.mstring = MemTemp.insertaString(MemTemp.mstring, 8000, tipo);				
			break;
			case 3:
				temp = MemTemp.mboolean;
				MemTemp.mboolean = MemTemp.insertaBoolean(MemTemp.mboolean, 9000, tipo);
				temp2 = MemTemp.mboolean;
				MemTemp.mboolean = MemTemp.insertaBoolean(MemTemp.mboolean, 9000, tipo);
			break;
			case 4:
				temp = MemTemp.mcomplex;
				MemTemp.mcomplex = MemTemp.insertaComplex(MemTemp.mcomplex, 10000, tipo);
				temp2 = MemTemp.mcomplex;
				MemTemp.mcomplex = MemTemp.insertaComplex(MemTemp.mcomplex, 10000, tipo);
			break;
			default:
				cout << "Type mismatch FOR.." << endl;
		}
cout << "genero temporales" << endl;
	int exp2 = POperandos.top();
	POperandos.pop();
cout << "saco de operandos exp2: " << exp2 << endl;
	cuadruplos x,y,z;

	x.op = 12;
	x.opdo1 = exp2;
	x.opdo2 = -1;
	x.res = temp;

	y.op = 8;
	y.opdo1 = asact;
	y.opdo2 = temp;
	y.res = temp2;

	z.op = GOTOF;
	z.opdo1 = temp2;
	z.opdo2 = -1;
	z.res = -1;

	hasht[cont_cuadruple] = x;
	cont_cuadruple++;

	hasht[cont_cuadruple] = y;
	cont_cuadruple++;

	hasht[cont_cuadruple] = z;
	cont_cuadruple++;
cout << "genero cuadruplos" << endl;
	//Libera temp
	PSaltos.push((cont_cuadruple-2));
}

void printCuadruplos() {

	for(unordered_map<int, cuadruplos>::iterator it = hasht.begin(); it != hasht.end(); it ++){
	cout << (*it).first << " " << (*it).second.op << " " << (*it).second.opdo1 << " " << (*it).second.opdo2 << " " << (*it).second.res << endl;
	}
}


void Err(wchar_t* msg) {
		errors->Error(la->line, la->col, msg);
}

void InitDeclarations() { // it must exist
	floats=1; integer=0; boolean=3; complexi=4; stringg = 2;  // types
	plus=0; minus=1; times=2; slash=3; diff=4; gtr=5; lss=6; gtreq=7; lsseq=8; eqeq=9; andop=10; orop=11; equ=12; // operators
	var = 0; def = 1; // object kinds

	cont_cuadruple=1;	
	
	// opcodes
	ADD  =  0; SUB   =  1; MUL   =  2; DIV   =  3; DIFF   =  4; GTR = 5; LSS = 6;
	GTREQ = 7; LSSEQ =8; EQEQ =9; ANDOP =10; OROP = 11; EQU = 12; RET = 13; GOTO = 14;
	GOTOF = 15; GOTO = 16; PARAM= 17; PRINT = 18; RETURN =19; ERA = 20; GOSUB = 21; READ = 22; 
	
	numproc=0;
	MemGlobal.mint = 1000;
	MemGlobal.mfloat = 2000;
	MemGlobal.mstring = 3000;
	MemGlobal.mboolean = 4000;
	MemGlobal.mcomplex = 5000;

	MemTemp.mint = 6000;
	MemTemp.mfloat = 7000;
	MemTemp.mstring = 8000;
	MemTemp.mboolean = 9000;
	MemTemp.mcomplex = 10000;

	MemConst.mint = 11000;
	MemConst.mfloat = 12000;
	MemConst.mstring = 13000;
	MemConst.mboolean = 14000;
	MemConst.mcomplex = 15000;
	
	MemLoc.mint = 20000;
	MemLoc.mfloat = 21000;
	MemLoc.mstring = 22000;
	MemLoc.mboolean = 23000;
	MemLoc.mcomplex = 25000;

}

CHARACTERS
	under = '_'.
	letter = 'A'..'Z' + 'a'..'z'.
	digit = '0'..'9'.
	cr  = '\r'.
	lf  = '\n'.
	tab = '\t'.
	quote = '"'.
	blash = '\\'.
	anyButQuote = ANY - quote.
	chars = ANY - digit - cr - lf - tab - blash - quote.
TOKENS
	ident = (letter | under) {letter | digit | under}.
	number = digit {digit}.
	flotante = digit {digit} '.' {digit} ['E' ['+'|'-'] digit {digit}].
	imaginario =  ( digit {digit} '.' {digit} ['E' ['+'|'-'] digit {digit}] | digit {digit} ) ("i" | "I").
	string =  quote { ( chars | digit) } quote.

COMMENTS FROM "/*" TO "*/" NESTED
COMMENTS FROM "//" TO cr lf

IGNORE cr + lf + tab
PRODUCTIONS      

Ident<wchar_t* &name>= ident (. name = coco_string_create(t->val); .).

matematrix = (. wchar_t* name; InitDeclarations(); .) "program" Ident<name>  (. 
	st.insertaDirProc(numproc,0, name, MemGlobal.mint); 
.) ';'(.
	PSaltos.push(cont_cuadruple);
	buildCuadrupleM(GOTO,-1,-1,-1);
.) [variables] (.
	numproc = numproc+1;
.) [funcion{funcion}] "main" (.
	int goo;
	goo = PSaltos.top();
	PSaltos.pop();
	rellenar(goo,cont_cuadruple);

.) bloque (.
	st.printLista();
	printCuadruplos();
.).


//funcion = (funcU | funcE).
//funcU = (funcV| funcT).


tipo<int &type> 
= 
("int" (. type = integer; .) | 
"float" (. type = floats; .) | 
"bool" (. type = boolean; .) | 
"string" (. type = stringg; .) | 
"complex" (. type = complexi; .) ).

var_cte (.int n1;float m1;bool b1;wchar_t *s1;.) = ( number (. 
	swscanf(t->val, L"%d", &n1);
	//cout << n1 << " es dirV " << MemConst.mint << endl; 
	MemConst.mint = ct.insertaInt(MemConst.mint,11000,n1);
.)  | flotante (. 
	swscanf(t->val, L"%f", &m1); 
	MemConst.mfloat = ct.insertaBoolean(MemConst.mfloat,12000, m1);
.) | "true" (. 
	b1 = true;
	MemConst.mboolean = ct.insertaBoolean(MemConst.mboolean,14000, b1);
.) | "false" (. 
	b1 = false; 
	MemConst.mboolean = ct.insertaBoolean(MemConst.mboolean,14000, b1);
.) | string (. 
	s1 = coco_string_create(t->val); 
	MemConst.mstring = ct.insertaBoolean(MemConst.mstring,13000, s1);
.)  | imaginario ).

bloque = '{' [ estatuto { estatuto } ] '}'.
index = '[' exp ']' {  '[' exp ']'  }.
estatuto = ( condicion | escritura | lectura | ciclo | funciones | variables | asignacion ).
//llamadas = '(' (  funciones  | otras ) ')' .
//otras = Ident<name> [index] ( asignacion | aesp ).
//aesp = ("++" | "--" | "+=" expresion | "-=" expresion ).
//llamadaFuncU = (. wchar_t* name; .)  Ident<name> '(' exp { ',' exp } ')' ';'.	
funciones = '(' ( funcN | funcE ) ')' ';'.

funcN = (. wchar_t* name; .)  Ident<name> (.
 		if ( st.checaDirProc2(name)) {
 			st.tempnumproc = st.checaDirProc3(name);
 		}
 .)'(' (.
 		buildCuadrupleM(ERA,-1,-1,-1);
 		k=1;
 .) expresion (.
 		arg = POperandos.top();
 		POperandos.pop();
 		tipoarg = PTipos.top();
 		PTipos.pop();
 		st.temptipop = st.verificaParametro(st.tempnumproc,k);
 		if( st.temptipop == tipoarg && st.temptipop != -1 ) {
 			buildCuadrupleM(PARAM,arg,-1,k);
 		}
 .) { ',' (.k=k+1;.) expresion (.
 		arg = POperandos.top();
 		POperandos.pop();
 		tipoarg = PTipos.top();
 		PTipos.pop();
 		st.temptipop = st.verificaParametro(st.tempnumproc, k);
 		if( st.temptipop == tipoarg && st.temptipop != -1 ) {
 			buildCuadrupleM(PARAM,arg,-1,k);
 		}
 .) } ')' (.
 			buildCuadrupleM(GOSUB,arg,-1,-1);
.).

funcE = ( fAlgebra | fMatrix | fGraph | fVector | fTrigonom | log ).
llamadaFuncE = (fTrigonom | log).
variables = "var" ( vares | varns ) { ( vares | varns ) } "end" (.
	if (numproc != 0) {
		st.insertaContDirProc(numproc, cont_cuadruple);
	}
.).
vares = ( vector | matriz ).
matriz = (. wchar_t* name;int type; .)  "matrix" tipo<type> Ident<name> '['expresion ',' expresion ']' (.
/*
switch(numproc){
	case 0:
	if( st.checaTablaVars(numproc, type, name) ){
		switch(type) {
			case 0:
				MemGlobal.mint = st.newTablaVarArr(numproc, type, name, MemGlobal.mint);
			break;
			case 1:
				MemGlobal.mfloat = st.newTablaVarArr(numproc, type, name, MemGlobal.mfloat);
			break;
			case 2:
				MemGlobal.mstring = st.newTablaVarArr(numproc, type, name, MemGlobal.mstring);
			break;
			case 3:
				MemGlobal.mboolean = st.newTablaVarArr(numproc, type, name, MemGlobal.mboolean);
			break;
			case 4:
				MemGlobal.mcomplex = st.newTablaVarArr(numproc, type, name, MemGlobal.mcomplex);
			break;
			default:
				MemGlobal.mint = st.newTablaVarArr(numproc, type, name, MemGlobal.mint);
		}
	}
	break;
	default:

	if( st.checaTablaVars(numproc, type, name) ){
		switch(type) {
			case 0:
				MemLoc.mint = st.newTablaVarArr(numproc, type, name, MemLoc.mint);
			break;
			case 1:
				MemLoc.mfloat = st.newTablaVarArr(numproc, type, name, MemLoc.mfloat);
			break;
			case 2:
				MemLoc.mstring = st.newTablaVarArr(numproc, type, name, MemLoc.mstring);
			break;
			case 3:
				MemLoc.mboolean = st.newTablaVarArr(numproc, type, name, MemLoc.mboolean);
			break;
			case 4:
				MemLoc.mcomplex = st.newTablaVarArr(numproc, type, name, MemLoc.mcomplex);
			break;
			default:
				MemLoc.mint = st.newTablaVarArr(numproc, type, name, MemLoc.mint);
		}
	}

	}



*/
.) '=' '(' '[' expresion { ',' expresion } ']' { ',' '[' expresion { ',' expresion } ']' } ')' ';'.

vector = (. wchar_t* name;int type; .)  "vector" tipo<type> Ident<name> '=' '{' expresion ',' expresion ',' expresion '}' ';'.
varns = (. wchar_t* name;int type; .)  tipo<type> Ident<name> (. 

	switch(numproc){
	case 0:
	if( st.checaTablaVars(numproc, type, name) ){
		switch(type) {
			case 0:
				MemGlobal.mint = st.newTablaVar(numproc, type, name, MemGlobal.mint);
			break;
			case 1:
				MemGlobal.mfloat = st.newTablaVar(numproc, type, name, MemGlobal.mfloat);
			break;
			case 2:
				MemGlobal.mstring = st.newTablaVar(numproc, type, name, MemGlobal.mstring);
			break;
			case 3:
				MemGlobal.mboolean = st.newTablaVar(numproc, type, name, MemGlobal.mboolean);
			break;
			case 4:
				MemGlobal.mcomplex = st.newTablaVar(numproc, type, name, MemGlobal.mcomplex);
			break;
			default:
				MemGlobal.mint = st.newTablaVar(numproc, type, name, MemGlobal.mint);
		}
	}
	break;
	default:

	if( st.checaTablaVars(numproc, type, name) ){
		switch(type) {
			case 0:
				MemLoc.mint = st.newTablaVar(numproc, type, name, MemLoc.mint);
			break;
			case 1:
				MemLoc.mfloat = st.newTablaVar(numproc, type, name, MemLoc.mfloat);
			break;
			case 2:
				MemLoc.mstring = st.newTablaVar(numproc, type, name, MemLoc.mstring);
			break;
			case 3:
				MemLoc.mboolean = st.newTablaVar(numproc, type, name, MemLoc.mboolean);
			break;
			case 4:
				MemLoc.mcomplex = st.newTablaVar(numproc, type, name, MemLoc.mcomplex);
			break;
			default:
				MemLoc.mint = st.newTablaVar(numproc, type, name, MemLoc.mint);
		}
	}

	}
.)  ['=' exp1] ';'. //[index] ( [asignacion] | ';'). 


eqOp<int &op> = (. op = -1; .) '=' (. op = equ;.) .

asignacion = (.int op; wchar_t* name; .)  Ident<name> (.
	asact = st.buscaVariable(numproc, name);
	cout << " tu as dir es " << asact <<endl;
	POperandos.push(asact);
	PTipos.push(st.temptipo);

.) [ index ] eqOp<op> (.
	POperadores.push(op);
.) expresion (.
	if ( !POperadores.empty() ) {
		if ( POperadores.top() == equ){
			buildCruadruple2(POperadores.top());
		}
	}
.) ';'.

expresion = (.int op; .) exp (.
	if ( !POperadores.empty() ) {
		if ( POperadores.top() == andop || POperadores.top() == orop) {
			buildCruadruple(POperadores.top());
		}
	} 
.)
{ boolOp<op> (.
	POperadores.push(op);
.)
exp }.

boolOp<int &op> = (. op = -1; .) ( "and"  (. op = andop; .)  | "or"  (. op = orop; .) ). 

exp = (.int op; .)  exp1 [ relOp<op> (.
	POperadores.push(op);
.) exp1 (.
	if ( !POperadores.empty() ) {
		if ( POperadores.top() == gtr || POperadores.top() == lss || POperadores.top() == diff || POperadores.top() == eqeq || POperadores.top() == lsseq || POperadores.top() == gtreq ) {
cout << "Entro a hacer cuadruplo... comparacion" << endl;
			buildCruadruple(POperadores.top());
		}
	} 
.) ].

relOp<int &op> = (. op = -1; .)
( '>' (. op = gtr; .) | 
'<' (. op = lss; .) | 
"<>" (. op = diff; .) | 
"==" (. op = eqeq; .) | 
"<=" (. op = lsseq; .) | 
">="  (. op = gtreq; .) ). 

exp1 = (.int op;.) termino (.
	if ( !POperadores.empty() ) {
		if ( POperadores.top() == plus || POperadores.top() == minus) {
			buildCruadruple(POperadores.top());
		}
	} .) { addOp<op> (.cout<<"op es: " << op << endl; POperadores.push(op);.)  termino (.
	if ( !POperadores.empty() ) {
		if ( POperadores.top() == plus || POperadores.top() == minus) {
			buildCruadruple(POperadores.top());
		}
	} .)
}.

addOp<int &op> = (. op = -1; .) ( '+' (. op = plus; .) | '-' (. op = minus; .)). 

termino = (.int op;.)  factor (.
	if ( !POperadores.empty() ) {
		if ( POperadores.top() == slash || POperadores.top() == times) {
			buildCruadruple(POperadores.top());
		}
	} 
.) { mulOp<op> (.
	POperadores.push(op);
.) factor (.
	if ( !POperadores.empty() ) {
		if ( POperadores.top() == slash || POperadores.top() == times) {
			buildCruadruple(POperadores.top());
		}
	} 
.) }.	

mulOp<int &op> = (. op = -1; .) ( '*' (. op = times; .) | '/' (. op = slash; .) ). 

factor = (. wchar_t* name; .)  ( Ident<name> (.
	diract = st.buscaVariable(numproc, name);
	cout << " tu dir es " << diract <<endl;
	POperandos.push(diract);
	PTipos.push(st.temptipo);

.)
[ ( index  | '(' expresion ')' ) ]| llamadaFuncE  | var_cte | '(' (. POperadores.push(-9999); .) exp')' (. 
	if( POperadores.top() == -9999) {
		POperadores.pop(); 
	} else {
	cout << "error" << endl;
	}
.) ).




funcion = "def" (funcV | funcT) '('[parametros]')' bloque (.
	buildCuadrupleM(RET,-1,-1,-1);	
	numproc = numproc+1;
.).

funcV = (. wchar_t* name;int type; .) "void" (. tipo_proc=-1 ; .) Ident<name>  (.
	if( st.checaDirProc(numproc, tipo_proc, name) ){
		st.insertaDirProc(numproc, tipo_proc, name,MemLoc.mint);
	}
.).

funcT = (. wchar_t* name;int type; .)  tipo<type> (. tipo_proc = type; .) Ident<name>  (.

	if( st.checaDirProc(numproc, tipo_proc, name) ){
		switch(type){
			case 0:
			MemLoc.mint = st.newDirProc(numproc, tipo_proc, name, MemLoc.mint);
			break;
			case 1:
			MemLoc.mfloat = st.newDirProc(numproc, tipo_proc, name, MemLoc.mfloat);
			break;
			case 2:
			MemLoc.mstring = st.newDirProc(numproc, tipo_proc, name, MemLoc.mstring);
			break;
			case 3:
			MemLoc.mboolean = st.newDirProc(numproc, tipo_proc, name, MemLoc.mboolean);
			break;
			case 4:
			MemLoc.mcomplex = st.newDirProc(numproc, tipo_proc, name, MemLoc.mcomplex);
			break;
			default:
			MemLoc.mint = st.newDirProc(numproc, tipo_proc, name, MemLoc.mint);
		}
	}

.).





parametros = (. wchar_t* name; int type; .)  tipo<type> Ident<name> (. 

switch(numproc){
case 0:
if( st.checaTablaParam(numproc, type, name) ){
	switch(type) {
		case 0:
			MemGlobal.mint = st.newTablaParam(numproc, type, name, MemGlobal.mint);
		break;
		case 1:
			MemGlobal.mfloat = st.newTablaParam(numproc, type, name, MemGlobal.mfloat);
		break;
		case 2:
			MemGlobal.mstring = st.newTablaParam(numproc, type, name, MemGlobal.mstring);
		break;
		case 3:
			MemGlobal.mboolean = st.newTablaParam(numproc, type, name, MemGlobal.mboolean);
		break;
		case 4:
			MemGlobal.mcomplex = st.newTablaParam(numproc, type, name, MemGlobal.mcomplex);
		break;
		default:
			MemGlobal.mint = st.newTablaParam(numproc, type, name, MemGlobal.mint);
	}
}
break;
default:

if( st.checaTablaParam(numproc, type, name) ){
	switch(type) {
		case 0:
			MemLoc.mint = st.newTablaParam(numproc, type, name, MemLoc.mint);
		break;
		case 1:
			MemLoc.mfloat = st.newTablaParam(numproc, type, name, MemLoc.mfloat);
		break;
		case 2:
			MemLoc.mstring = st.newTablaParam(numproc, type, name, MemLoc.mstring);
		break;
		case 3:
			MemLoc.mboolean = st.newTablaParam(numproc, type, name, MemLoc.mboolean);
		break;
		case 4:
			MemLoc.mcomplex = st.newTablaParam(numproc, type, name, MemLoc.mcomplex);
		break;
		default:
			MemLoc.mint = st.newTablaParam(numproc, type, name, MemLoc.mint);
	}
}

}




.)
{ ',' 
tipo<type> Ident<name> 
(. 
switch(numproc){
case 0:
if( st.checaTablaParam(numproc, type, name) ){
	switch(type) {
		case 0:
			MemGlobal.mint = st.newTablaParam(numproc, type, name, MemGlobal.mint);
		break;
		case 1:
			MemGlobal.mfloat = st.newTablaParam(numproc, type, name, MemGlobal.mfloat);
		break;
		case 2:
			MemGlobal.mstring = st.newTablaParam(numproc, type, name, MemGlobal.mstring);
		break;
		case 3:
			MemGlobal.mboolean = st.newTablaParam(numproc, type, name, MemGlobal.mboolean);
		break;
		case 4:
			MemGlobal.mcomplex = st.newTablaParam(numproc, type, name, MemGlobal.mcomplex);
		break;
		default:
			MemGlobal.mint = st.newTablaParam(numproc, type, name, MemGlobal.mint);
	}
}
break;
default:

if( st.checaTablaParam(numproc, type, name) ){
	switch(type) {
		case 0:
			MemLoc.mint = st.newTablaParam(numproc, type, name, MemLoc.mint);
		break;
		case 1:
			MemLoc.mfloat = st.newTablaParam(numproc, type, name, MemLoc.mfloat);
		break;
		case 2:
			MemLoc.mstring = st.newTablaParam(numproc, type, name, MemLoc.mstring);
		break;
		case 3:
			MemLoc.mboolean = st.newTablaParam(numproc, type, name, MemLoc.mboolean);
		break;
		case 4:
			MemLoc.mcomplex = st.newTablaParam(numproc, type, name, MemLoc.mcomplex);
		break;
		default:
			MemLoc.mint = st.newTablaParam(numproc, type, name, MemLoc.mint);
	}
}

}



.) }.

ciclo = (ciclofor | ciclowhile).
condicion = "if" '(' expresion ')' 
(. 
	int aux;
	aux=PTipos.top();
	if (aux == 3){
cout << "entra a hacer cuadruplo condicion" << endl;
		buildCuadruple4(POperandos.top());
		PSaltos.push((cont_cuadruple-1));
	} else {
		cout << "Semantic error: Type mismatch" << endl;
	}
.)
bloque ["elif" '(' expresion ')'
(. 
	int aux;
	aux=PTipos.top();
	if (aux == 3){
		buildCuadruple4(POperandos.top());
	} else {
	cout << "Semantic error: Type mismatch" << endl;
	}
.)
bloque { "elif" '(' expresion ')' bloque } ] [ "else" 
(. 
int salto;
buildCuadruple5(GOTO,-1,-1);
salto = PSaltos.top();
PSaltos.pop();
rellenar(salto, cont_cuadruple);
PSaltos.push((cont_cuadruple-1));

cout << "En psaltos despues de cuadruplo5 " << PSaltos.top() << endl;
cout << cont_cuadruple << endl;

 .)
bloque ]
(.
int sss;
sss = PSaltos.top();
PSaltos.pop();
rellenar(sss, cont_cuadruple);
.).
ciclowhile = "while" (. 
	cout << "entro al while" << endl;
	PSaltos.push(cont_cuadruple); 
.) '(' expresion ')' (.
	buildCuadruple3();
.) bloque (. 
	buildCuadrupleWhile();
.).
ciclofor = (. wchar_t* name; .)  "for" '(' asignacion ';' expresion (.
	buildCuadrupleFOR();
.) ')' bloque (.
cout << "salio bloque" << endl;
	buildCuadrupleM(0,asact,1,asact);
	int retorno = PSaltos.top();
	PSaltos.pop();
	buildCuadrupleM(GOTO,-1,-1,retorno);
	rellenar((retorno+1), cont_cuadruple);

.) .
escritura = "print" '(' exp{',' exp} ')'.
lectura = (. wchar_t* name; .)  "read" '(' Ident<name> [ '[' exp ']' ] ')'.
Sum_V = "sum_v" '(' expresion { ',' expresion } ')' ';'.
Mul_V = "mul_v" '('  expresion { ',' expresion } ')' ';'.
pro_ev = "pro_ev" '(' expresion ',' expresion ')' ';'.
Sum_M = (. wchar_t* name; .)  "sum_m" '(' Ident<name> '+' Ident<name> ')' ';'.
Inv_M = "inv_m" '(' expresion ')' ';'.
Mul_M = "mul_m" '(' expresion ',' expresion ')' ';'.
Trans_M = "trans_m" '(' expresion ')' ';'.
punto_medio = "p_m" '(' expresion ',' expresion ',' expresion ',' expresion ')'.
dist_2puntos = "dist_2" '(' expresion ',' expresion ',' expresion ',' expresion ')'.
rec_entre_2puntos = "rec_pp" '(' expresion ',' expresion ',' expresion ',' expresion ')'.
fGraph = "graph" '(' exp1 ')'.
fTrigonom = ("sin" | "csc" | "cos" | "cot" | "tan" | "sec") '(' expresion ')'.
log = ( 'E' | "log" | "ln" ) '(' expresion ')'.
fAlgebra = ( punto_medio | dist_2puntos | rec_entre_2puntos ).
fMatrix = ( Sum_M | Inv_M | Mul_M | Trans_M).
fVector = ( Sum_V | Mul_V | pro_ev ).

END matematrix. 
