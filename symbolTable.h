#if !defined(SYMBOLTABLE_H__)
#define SYMBOLTABLE_H__

// NOTA: solo se puede compilar en linux
// compilado en Ubuntu 9.10 usando g++ (Ubuntu 4.4.1-4ubuntu9) 4.4.1

#include <list>
#include <tr1/unordered_map>

using namespace std;
using namespace std::tr1;

class Memoria {

public:

int mint, mfloat, mstring, mboolean, mcomplex;

typedef struct {
	int tipo;
	int dirV;
	int avail;
}tablaMem[1000];

tablaMem i,f,s,c,b;

//int integers[1000];
//float floats[1000];
//wchar_t strings[1000];
//int complexs[1000];
//bool booleans[1000];

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


class constTable{
public:

int tempconst, constTipo;

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


class symbolTable {
public:

int temptipo, tempdir, temptipop, tempnumproc, tempnumarr;

typedef struct {
	int lsup;
	int linf;
	int m;
} tablaArr;

typedef struct {
	wchar_t* name;
	int tipo;
	int dirV;
	int key;
} tablaVars;

typedef struct {
	wchar_t* name;
	int tipo;
	int dirV;
} tablaParam;

typedef struct {
	wchar_t* name;
	int tipo;
	int dirV;
	Tamano tam;
	int dirI;
	list<tablaVars> vars;
	list<tablaParam> param;
} dirProc;

typedef struct {
	list<tablaArr> dim;
} dArr;

unordered_map<int, dirProc> hmap;
unordered_map<int, dArr> hdim;

void insertaDirProc(int a, int type, wchar_t* name, int m){
	dirProc x;
	x.name = name; x.tipo = type; x.dirV = m; 	
	x.tam.vContI=0; x.tam.pContI=0; x.tam.tContI=0;
	x.tam.vContF=0; x.tam.pContF=0; x.tam.tContF=0;
	x.tam.vContS=0; x.tam.pContS=0; x.tam.tContS=0;
	x.tam.vContC=0; x.tam.pContC=0; x.tam.tContC=0;
	x.tam.vContB=0; x.tam.pContB=0; x.tam.tContB=0;

	hmap[a] = x;

}

int newTablaVar(int a, int tipo, wchar_t* nombre, int m){
		
tablaVars x;

switch(tipo) {
	case 0:
		x.name = nombre; x.tipo = tipo; x.dirV = m;
		hmap[a].vars.push_back(x);
		hmap[a].tam.vContI = hmap[a].tam.vContI + 1;
		
	break;
	case 1:
		x.name = nombre; x.tipo = tipo; x.dirV = m;
		hmap[a].vars.push_back(x);
		hmap[a].tam.vContF+=1;
	break;
	case 2:
		x.name = nombre; x.tipo = tipo; x.dirV = m;
		hmap[a].vars.push_back(x);
		hmap[a].tam.vContS+=1;
	break;
	case 3:
		x.name = nombre; x.tipo = tipo; x.dirV = m;
		hmap[a].vars.push_back(x);
		hmap[a].tam.vContB+=1;
	break;
	case 4:
		x.name = nombre; x.tipo = tipo; x.dirV = m;
		hmap[a].vars.push_back(x);
		hmap[a].tam.vContC+=1;
	break;
	default:
		x.name = nombre; x.tipo = tipo; x.dirV = m;
		hmap[a].vars.push_back(x);
}

return m+1;
}


void agregaDim(int a,int llave, wchar_t* name){
	
	list<tablaVars>::iterator p;
	for (p=hmap[a].vars.begin(); p!=hmap[a].vars.end(); p++) {	
		if ( wcscmp(p->name, name) == 0 ) {
			p->key = llave;
		} 
	}


}

void newTablaDesc(int a, int inf, int sup, int k, int llave){

	tablaArr x;
	x.lsup = sup;
	x.linf = inf;
	x.m = k;
	hdim[llave].dim.push_back(x);

}

void printArr(){

list<tablaArr>::iterator p;
for(unordered_map<int, dArr>::iterator tt = hdim.begin(); tt != hdim.end(); tt++){
	cout << (*tt).first;
	for (p=(*tt).second.dim.begin(); p!=(*tt).second.dim.end(); p++) {
		cout << " => ("<< p->linf << "," << p->lsup << "," << p->m << " )" <<endl;
	}
}

}

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

int dameSup(int a, int m){

int k=0; 

list<tablaArr>::iterator p;
int i = 1;
for (p=hdim[a].dim.begin(); p!=hdim[a].dim.end(); p++) {
		if (i == m){ 
			k = p->lsup;
		} else {
			i++;
		}
	}

return k;

}

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
		suma = suma * m[dim-1];
		almacenaK(a, dim, m[dim-1]);
		dim++;
	}
	K = suma;
	K = -1*K;	
	almacenaK(a, dim, K);

return aux-1;
}

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

void insertaContDirProc(int a,int c){
	hmap[a].dirI = c;
}

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


bool checaDirProc(int a, int tipo, wchar_t* nombre){

bool b = false;

	for(unordered_map<int, dirProc>::iterator it = hmap.begin(); it != hmap.end(); it ++){
		if( wcscmp((*it).second.name, nombre) !=0 ){
			b = true;		
		}
	}

return b;
}



bool checaDirProc2(wchar_t* nombre){

bool b = false;

	for(unordered_map<int, dirProc>::iterator it = hmap.begin(); it != hmap.end(); it ++){
		if( wcscmp((*it).second.name, nombre) == 0 ){
			b = true;		
		}
	}

return b;
}

int checaDirProc3(wchar_t* nombre){

	for(unordered_map<int, dirProc>::iterator it = hmap.begin(); it != hmap.end(); it ++){
		if( wcscmp((*it).second.name, nombre) == 0 ){
			tempnumproc = (*it).first;		
		}
	}

return tempnumproc ;
}


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

int buscaVariable(int a, wchar_t* name){
int b = 0;	
	list<tablaVars>::iterator p;
	for (p=hmap[a].vars.begin(); p!=hmap[a].vars.end(); p++) {	
		if ( wcscmp(p->name, name) == 0 ) {
			b = 1;
			temptipo = p->tipo;
			tempdir = p->dirV;
		} 
	}

if (b == 0){
	list<tablaParam>::iterator q;
			for (q=hmap[a].param.begin(); q!=hmap[a].param.end(); q++) {	
				//cout << "entro 2ndo for" << endl;
				if ( wcscmp(p->name, name) == 0 ) {
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
				} 
	}

}

	return tempdir;
}

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
		cout << p->tipo << ", " << p->dirV << ") " ;
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
