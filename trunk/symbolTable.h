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


class symbolTable {
public:

int temptipo, tempdir;

typedef struct {
	int lsup;
	int linf;
	int m;
} tablaArr;

typedef struct {
	wchar_t* name;
	int tipo;
	int dirV;
	list<tablaArr> dim;
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

unordered_map<int, dirProc> hmap;

void insertaDirProc(int a, int type, wchar_t* name, int m, int c){
	dirProc x;
	x.name = name; x.tipo = type; x.dirV = m; x.dirI = c; 	
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


int newTablaVarArr(int a, int tipo, wchar_t* nombre, int m){

tablaVars x;

return m;
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
		cout << (*it).second.tipo << ", " << (*it).second.dirV << ", "; 
		cout << /*(*it).second.tamano*/ "\n " ;

		cout << (*it).second.tam.vContI << ", " << (*it).second.tam.pContI << ", " <<  (*it).second.tam.tContI <<  "\n ";
		cout << (*it).second.tam.vContF << ", " <<  (*it).second.tam.pContF << ", " <<  (*it).second.tam.tContF <<  "\n ";
		cout << (*it).second.tam.vContS << ", " <<  (*it).second.tam.pContS << ", " <<  (*it).second.tam.tContS <<  "\n ";
		cout << (*it).second.tam.vContC << ", " <<  (*it).second.tam.pContC << ", " <<  (*it).second.tam.tContC <<  "\n ";
		cout << (*it).second.tam.vContB << ", " <<  (*it).second.tam.pContB << ", " <<  (*it).second.tam.tContB <<  "\n ";
		

		cout << (*it).second.dirI << ", "; 
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
