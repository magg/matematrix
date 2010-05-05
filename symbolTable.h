#if !defined(SYMBOLTABLE_H__)
#define SYMBOLTABLE_H__

// NOTA: solo se puede compilar en linux
// compilado en Ubuntu 9.10 usando g++ (Ubuntu 4.4.1-4ubuntu9) 4.4.1
// compilado en Ubuntu 10.04 usando g++ (gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5)) 

#include <list>
#include <tr1/unordered_map>

using namespace std;
using namespace std::tr1;

//clase memoria 
class Memoria {

public:

int mint, mfloat, mstring, mboolean, mcomplex;

//arreglo de structs para simular las tablas memoria por tipo
typedef struct {
	int tipo;
	int dirV;
	int avail;
}tablaMem[1000];

tablaMem i,f,s,c,b;

int insertaInt(int dirv,int dirb, int tipo){
	i[dirv-dirb].tipo = tipo;
	i[dirv-dirb].dirV = dirv;

return dirv+1;
}

int insertaFloat(int dirv,int dirb, int tipo){
	f[dirv-dirb].tipo = tipo;
	f[dirv-dirb].dirV = dirv;

return dirv+1;
}


int insertaString(int dirv,int dirb, int tipo){
	s[dirv-dirb].tipo = tipo;
	s[dirv-dirb].dirV = dirv;

return dirv+1;
}

int insertaComplex(int dirv,int dirb, int tipo){
	c[dirv-dirb].tipo = tipo;
	c[dirv-dirb].dirV = dirv;

return dirv+1;
}

int insertaBoolean(int dirv,int dirb, int tipo){
	b[dirv-dirb].tipo = tipo;
	b[dirv-dirb].dirV = dirv;

return dirv+1;
}


};

//clase tamano que se usa en el dirProc
class Tamano {
public:
	int vContI;
	int vContF;
	int vContS;
	int vContC;
	int vContB;
	int pContI;
	int pContF;
	int pContS;
	int pContC;
	int pContB;
	int tContI;
	int tContF;
	int tContS;
	int tContC;
	int tContB;
};


//clase que se usa para simular las tablas de constantes por tipo
class constTable{
public:

int tempconst, constTipo;

//arreglos de structs que representan las tablas
typedef struct {
	int val;
	int dirV;
}intTable[1000];

typedef struct {
	bool val;
	int dirV;
}boolTable[1000];

typedef struct {
	float val;
	int dirV;
}floatTable[1000];

typedef struct {
	wchar_t* val;
	int dirV;
}stringTable[1000];

intTable in; floatTable fn; boolTable bn; stringTable sn;

	int insertaInt(int dirv,int dirb, int i){
		in[dirv-dirb].val = i;
		in[dirv-dirb].dirV = dirv;
		return dirv+1;
	}

	int insertaFloat(int dirv,int dirb, float f){
		fn[dirv-dirb].val = f;
		fn[dirv-dirb].dirV = dirv;
		return dirv+1;
	}

	int insertaBoolean(int dirv,int dirb, bool b){
		bn[dirv-dirb].val = b;
		bn[dirv-dirb].dirV = dirv;
		return dirv+1;
	}

	int insertaString(int dirv,int dirb, wchar_t* s){
		sn[dirv-dirb].val = s;
		sn[dirv-dirb].dirV = dirv;
		return dirv+1;
	}
};

//clase symbolTable en donde se crea y llena el dirProc
class symbolTable {
public:

int temptipo, tempdir, temptipop, tempnumproc, tempnumarr, tempdim, tempdimfinal;

//struct para la tabla de arreglo
typedef struct {
	int lsup;
	int linf;
	int m;
} tablaArr;

//struct que simula la tabla de variables
typedef struct {
	wchar_t* name;
	int tipo;
	int dirV;
	int key;
} tablaVars;

//struct que simula la tabla de parametros
typedef struct {
	wchar_t* name;
	int tipo;
	int dirV;
} tablaParam;

//struct que representa la estructura basica del dirProc
typedef struct {
	wchar_t* name;
	int tipo;
	int dirV;
	Tamano tam;
	int dirI;
	list<tablaVars> vars;
	list<tablaParam> param;
} dirProc;

//struct que se usa para hacer el calculo de los arreglos
typedef struct {
	list<tablaArr> dim;
} dArr;

// tabla de hashing del directorio de procedimiento
unordered_map<int, dirProc> hmap;
//tabla de hasing que usa el calculo de arreglos
unordered_map<int, dArr> hdim;

//funcion que inserta por primera vez un renglon al dirProc
void insertaDirProc(int a, int type, wchar_t* name, int m){
	dirProc x;
	x.name = name; x.tipo = type; x.dirV = m; x.dirI=0;	
	x.tam.vContI=0; x.tam.pContI=0; x.tam.tContI=0;
	x.tam.vContF=0; x.tam.pContF=0; x.tam.tContF=0;
	x.tam.vContS=0; x.tam.pContS=0; x.tam.tContS=0;
	x.tam.vContC=0; x.tam.pContC=0; x.tam.tContC=0;
	x.tam.vContB=0; x.tam.pContB=0; x.tam.tContB=0;

	hmap[a] = x;

}

//funcion que inserta nuevos renglones a la tabla de variables
int newTablaVar(int a, int tipo, wchar_t* nombre, int m){
		
tablaVars x;

switch(tipo) {
	case 0:
		x.name = nombre; x.tipo = tipo; x.dirV = m; x.key= -1;
		hmap[a].vars.push_back(x);
		hmap[a].tam.vContI = hmap[a].tam.vContI + 1;
		
	break;
	case 1:
		x.name = nombre; x.tipo = tipo; x.dirV = m; x.key= -1;
		hmap[a].vars.push_back(x);
		hmap[a].tam.vContF+=1;
	break;
	case 2:
		x.name = nombre; x.tipo = tipo; x.dirV = m; x.key= -1;
		hmap[a].vars.push_back(x);
		hmap[a].tam.vContS+=1;
	break;
	case 3:
		x.name = nombre; x.tipo = tipo; x.dirV = m; x.key= -1;
		hmap[a].vars.push_back(x);
		hmap[a].tam.vContB+=1;
	break;
	case 4:
		x.name = nombre; x.tipo = tipo; x.dirV = m; x.key= -1;
		hmap[a].vars.push_back(x);
		hmap[a].tam.vContC+=1;
	break;
	default:
		x.name = nombre; x.tipo = tipo; x.dirV = m; x.key= -1;
		hmap[a].vars.push_back(x);
}

return m+1;
}

//funcion que apunta al parametro K y regresa dirV
int returnParamK(int a, int k){
			list<tablaParam>::iterator q;
			int i = 1;
			int dir=0;	
			for (q=hmap[a].param.begin(); q!=hmap[a].param.end(); q++) {	
				if ( i == k ) {
					dir = q->dirV;				
				} else {
					i++;
				}

			}

return dir;
}

//funcion que regresa la dirI
int buscaDirInicio(int a){

return hmap[a].dirI;
}

//funcion que agrega a tablaVar un id para saber que la variable es dimensionada
void agregaDim(int a,int llave, wchar_t* name){
	
	list<tablaVars>::iterator p;
	for (p=hmap[a].vars.begin(); p!=hmap[a].vars.end(); p++) {	
		if ( wcscmp(p->name, name) == 0 ) {
			p->key = llave;
		} 
	}


}

//agrega un nuevo renglon a la tabla para los calculos de arreglos
void newTablaDesc(int a, int inf, int sup, int k, int llave){

	tablaArr x;
	x.lsup = sup;
	x.linf = inf;
	x.m = k;
	hdim[llave].dim.push_back(x);

}

//funcion que imprime las listas de structs que se generan al calcular arreglos
void printArr(){

list<tablaArr>::iterator p;
for(unordered_map<int, dArr>::iterator tt = hdim.begin(); tt != hdim.end(); tt++){
	cout << (*tt).first;
	for (p=(*tt).second.dim.begin(); p!=(*tt).second.dim.end(); p++) {
		cout << " => ("<< p->linf << "," << p->lsup << "," << p->m << " )" <<endl;
	}
}

}

//funcion que checa si es nulo
bool checaNulo(int a, int m){
cout << "valor de m en checa nulo" << m <<  endl;
int i = 1;
bool b = false;
list<tablaArr>::iterator p;
	for (p=hdim[a].dim.begin(); p!=hdim[a].dim.end(); p++) {
		if (i == m){ 
			if (p!=hdim[a].dim.end()){
			b=true;
			cout << "entre a checa nulo b es true" << endl;
			}
		}
	i++;
	}
return b;
}

// funcion que regresa el num de dimensiones de una variable dimensionada
int getDim(int a){
int i = 0;
list<tablaArr>::iterator p;
	for (p=hdim[a].dim.begin(); p!=hdim[a].dim.end(); p++) {
		i++;
	}
return i;
}

// funcion que almacena los valores en el struct para hacer el calculo de arreglos
void almacenaConsArr(int a, int m, int n){

list<tablaArr>::iterator p;
int i = 1;
for (p=hdim[a].dim.begin(); p!=hdim[a].dim.end(); p++) {
		if (i == m){
			p->linf = 0; 
			p->lsup = n;
		} else {
			i++;
		}
	}

}

// funcion que regresa el limite sup de una dimension
int dameSup(int a, int m){

int k=0; 

list<tablaArr>::iterator p;
int i = 1;
for (p=hdim[a].dim.begin(); p!=hdim[a].dim.end(); p++) {
		if (i == m){ 
			k = p->lsup;
		}
	i++;
	}

return k;

}

// funcion que regresa la m del calculo de arreglos
int dameM(int a, int m){
int k=0;
list<tablaArr>::iterator p;
int i = 1;
for (p=hdim[a].dim.begin(); p!=hdim[a].dim.end(); p++) {
		if (i == m){ 

			k = p->m;
		} 
	i++;
	}
return k;

}

// funcion que almacena el valor de K/m
void almacenaK(int a, int m, int k){

list<tablaArr>::iterator p;
int i = 1;

for (p=hdim[a].dim.begin(); p!=hdim[a].dim.end(); p++) {
		if (i == m){
			p->m = k;
		} else {
			i++;
		}
	}
}

//funcion que hace el calculo en si de los arreglos
int loopDim(int R, int numdim, int *m, int a) {

int dim = 1;
int suma = 0;
int aux = R;
int K;
int ls;
	while(dim < numdim){
		ls = dameSup(a,dim);
		m[dim-1] = R / (ls + 1);
		R = m[dim-1];   
		suma = suma + 0 * m[dim-1];
		almacenaK(a, dim, m[dim-1]);
		dim++;
	}
	K = suma;
	K = -1*K;
	cout << dim << endl;	
	almacenaK(a, dim, K);

return aux-1;
}

// funcion que checa si la variable ya existe en la tabla de variables
bool checaTablaVars(int a, int tipo, wchar_t* nombre){

bool b = false;

	if (hmap[a].vars.empty()) {
		b = true;
	} else {
		list<tablaVars>::iterator p;
		for (p=hmap[a].vars.begin(); p!=hmap[a].vars.end(); p++) {	
				if ( wcscmp(p->name, nombre) != 0 ) {
					b = true;
				} 
		}
	}
return b;
}

//funcion que agrega un nuevo renglo a la tabla de parametros
int newTablaParam(int a, int tipo, wchar_t* nombre, int m){
		tablaParam x;
switch(tipo) {
	case 0:
		x.name = nombre; x.tipo = tipo; x.dirV = m;
		hmap[a].param.push_back(x);
		hmap[a].tam.pContI = hmap[a].tam.pContI + 1;
		
	break;
	case 1:
		x.name = nombre; x.tipo = tipo; x.dirV = m;
		hmap[a].param.push_back(x);
		hmap[a].tam.pContF+=1;
	break;
	case 2:
		x.name = nombre; x.tipo = tipo; x.dirV = m;
		hmap[a].param.push_back(x);
		hmap[a].tam.pContS+=1;
	break;
	case 3:
		x.name = nombre; x.tipo = tipo; x.dirV =m;
		hmap[a].param.push_back(x);
		hmap[a].tam.pContB+=1;
	break;
	case 4:
		x.name = nombre; x.tipo = tipo; x.dirV = m;
		hmap[a].param.push_back(x);
		hmap[a].tam.pContC+=1;
	break;
	default:
		x.name = nombre; x.tipo = tipo; x.dirV = m;
		hmap[a].param.push_back(x);
}
return m+1;
}

// funcion que checa si existe el parametro en la tabla de parametros
bool checaTablaParam(int a, int tipo, wchar_t* nombre){

bool b = false;

	if (hmap[a].param.empty()) {
		b = true;
	} else {
		list<tablaParam>::iterator  q;
		for (q=hmap[a].param.begin(); q!=hmap[a].param.end(); q++) {	
				if ( wcscmp(q->name, nombre) != 0 ) {
					b = true;
				} 
		}
	}
return b;
}

//funcion que inserta al dirProc la dir de Inicio
void insertaContDirProc(int a,int c){
	hmap[a].dirI = c;
}

//funcion que agrega un nuevo renglo de dirProc
int newDirProc(int a, int type, wchar_t* nombre, int m){

	dirProc x;
	x.name = nombre; x.tipo = type; x.dirV = m; 
	x.tam.vContI=0; x.tam.pContI=0; x.tam.tContI=0;
	x.tam.vContF=0; x.tam.pContF=0; x.tam.tContF=0;
	x.tam.vContS=0; x.tam.pContS=0; x.tam.tContS=0;
	x.tam.vContC=0; x.tam.pContC=0; x.tam.tContC=0;
	x.tam.vContB=0; x.tam.pContB=0; x.tam.tContB=0;
	hmap[a] = x;
return m+1;
}

//funcion que checa si existe el nombre de una funcion en el dirproc
bool checaDirProc(int a, int tipo, wchar_t* nombre){

bool b = false;

	for(unordered_map<int, dirProc>::iterator it = hmap.begin(); it != hmap.end(); it ++){
		if( wcscmp((*it).second.name, nombre) !=0 ){
			b = true;		
		}
	}

return b;
}

//funcion que checa si existe el nombre de una funcion en el dirproc
bool checaDirProc2(wchar_t* nombre){

bool b = false;

	for(unordered_map<int, dirProc>::iterator it = hmap.begin(); it != hmap.end(); it ++){
		if( wcscmp((*it).second.name, nombre) == 0 ){
			b = true;		
		}
	}

return b;
}

//funcion que checa si existe el nombre de una funcion en el dirproc y regresa su numproc
int checaDirProc3(wchar_t* nombre){

	for(unordered_map<int, dirProc>::iterator it = hmap.begin(); it != hmap.end(); it ++){
		if( wcscmp((*it).second.name, nombre) == 0 ){
			tempnumproc = (*it).first;		
		}
	}

return tempnumproc ;
}

//funcion que verifica parametro para la generacion del cuadruplo param
int verificaParametro(int a, int k){
bool b = false;
int t;
int cont=1;
	if(hmap.find(a) != hmap.end()) {
		list<tablaParam>::iterator q;
		for (q=hmap[a].param.begin(); q!=hmap[a].param.end(); q++) {
			if (k == cont){
				t = q->tipo;
				b = true;
			} else {
				cont++;			
			} 
		}
	}

	if (b) {
		return t;
	} else{
		return -1;
	}

}

//funcion que busca una variable en la tabla de variables y parametros
// en todos los ambitos, local y global
int buscaVariable(int a, wchar_t* name){
int b = 0;	
	list<tablaVars>::iterator p;
	for (p=hmap[a].vars.begin(); p!=hmap[a].vars.end(); p++) {	
		if ( wcscmp(p->name, name) == 0 ) {
			b = 1;
			temptipo = p->tipo;
			tempdir = p->dirV;
			tempdim = p->key;
		} 
	}

if (b == 0){
	list<tablaParam>::iterator q;
			for (q=hmap[a].param.begin(); q!=hmap[a].param.end(); q++) {	
				//cout << "entro al for param" << endl;
				//wcout << name << p->name << endl;
				if ( wcscmp(q->name, name) == 0 ) {
					//cout << "entro al if dentro del for 2" << endl;
					temptipo = q->tipo;
					tempdir = q->dirV;
					b = 1;					
				}  

			}
}
if (b == 0){

	for (p=hmap[0].vars.begin(); p!=hmap[0].vars.end(); p++) {
				//cout << "entro 3er for" << endl;	
				if ( wcscmp(p->name, name) == 0 ) {
					//cout << "entro al if dentro del for 3" << endl;
					temptipo = p->tipo;
					tempdir = p->dirV;
					tempdim = p->key;					
				} 
	}

}

	return tempdir;
}

//funcion que imprime el directorio de procedimientos
void printLista(){
	list<tablaVars>::iterator p;
	list<tablaParam>::iterator q;
	for(unordered_map<int, dirProc>::iterator it = hmap.begin(); it != hmap.end(); it ++){
		cout << (*it).first << " => (";
		wcout << (*it).second.name << ", ";
		cout << (*it).second.tipo << ", " << (*it).second.dirV << ", " << (*it).second.dirI << ", ";
		cout << /*(*it).second.tamano*/ "\n " ;

		cout << (*it).second.tam.vContI << ", " << (*it).second.tam.pContI << ", " <<  (*it).second.tam.tContI <<  "\n ";
		cout << (*it).second.tam.vContF << ", " <<  (*it).second.tam.pContF << ", " <<  (*it).second.tam.tContF <<  "\n ";
		cout << (*it).second.tam.vContS << ", " <<  (*it).second.tam.pContS << ", " <<  (*it).second.tam.tContS <<  "\n ";
		cout << (*it).second.tam.vContC << ", " <<  (*it).second.tam.pContC << ", " <<  (*it).second.tam.tContC <<  "\n ";
		cout << (*it).second.tam.vContB << ", " <<  (*it).second.tam.pContB << ", " <<  (*it).second.tam.tContB <<  "\n ";
		
		cout << "[";
	for (p=(*it).second.vars.begin(); p!=(*it).second.vars.end(); p++) {
		cout << " (" ;
		wcout << p->name << ", " ;
		cout << p->tipo << ", " << p->dirV << ", " << p->key << ") " ;
	}
	cout << " ]";
	cout << ", " << "{ ";
	for (q=(*it).second.param.begin(); q!=(*it).second.param.end(); q++) {
		cout << " (";
		wcout << q->name;
		cout << ", " << q->tipo << ", " << q->dirV << ") ";
	}
	cout << " }";
	cout << ')' << endl;
	}

}


};

#endif
