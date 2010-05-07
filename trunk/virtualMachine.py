# se importa la clase de memoria para el manejo de memoria 
from memoria import memoriaVirtual

# Se declara la clase
class virtualMachine(object):
	# Funcion que se corre al crear un objeto de la clase
	def __init__(self):
		self.memGlobal = memoriaVirtual()
		self.memTemp = memoriaVirtual()
		self.memConst = memoriaVirtual()
		self.memLoc = memoriaVirtual()
		self.memPoint = memoriaVirtual()
		self.initialize()
	
	#funcion que iniciliza todas las variables globales y carga los archivos de cuadruplos y de constantes
	def initialize(self):
		self.memGlobal.mint = 1000
		self.memGlobal.mfloat = 2000
		self.memGlobal.mstring = 3000
		self.memGlobal.mboolean = 4000
		self.memGlobal.mcomplex = 5000

		self.memTemp.mint = 6000
		self.memTemp.mfloat = 7000
		self.memTemp.mstring = 8000
		self.memTemp.mboolean = 9000
		self.memTemp.mcomplex = 10000

		self.memConst.mint = 11000
		self.memConst.mfloat = 12000
		self.memConst.mstring = 13000
		self.memConst.mboolean = 14000
		self.memConst.mcomplex = 15000
		
		self.memLoc.mint = 20000
		self.memLoc.mfloat = 21000
		self.memLoc.mstring = 22000
		self.memLoc.mboolean = 23000
		self.memLoc.mcomplex = 25000
		
		self.memPoint.mint = 26000
		self.memPoint.mfloat=27000
		self.memPoint.mstring=28000
		self.memPoint.mboolean=29000
		self.memPoint.mcomplex=30000

		self.dict = {}
		self.PExe = []
		self.PCuadruplo = []
		self.cuadruplo = 0
		f = open('/home/magg/matematrix/trunk/cuadruplos.matrix', 'r')
		line = f.readlines()
		f.close()
		ci = open('/home/magg/matematrix/trunk/int.cte', 'r')
		line1 = ci.readlines()
		ci.close()
		cf = open('/home/magg/matematrix/trunk/float.cte', 'r')
		line2 = cf.readlines()
		cf.close()
		cb = open('/home/magg/matematrix/trunk/bool.cte', 'r')
		line3 = cb.readlines()
		cb.close()
		cs = open('/home/magg/matematrix/trunk/str.cte', 'r')
		line4 = cs.readlines()
		cs.close()
		for foo1 in line1:
			lista1 = foo1.split()
			x1 = int(lista1[0])
			x2 = int(lista1[1])
			self.memConst.memInt(x1-11000,x2)
		for foo2 in line2:
			lista2 = foo2.split()
			x1 = int(lista2[0])
			x2 = float(lista2[1])
			self.memConst.memFloat(x1-12000,x2)
		for foo3 in line3:
			lista3 = foo3.split()
			x1 = int(lista3[0])
			x2 = bool(lista3[1])
			self.memConst.memBoolean(x1-14000,x2)
		for foo4 in line4:
			lista4 = foo4.split()
			x1 = int(lista4[0])
			x2 = lista4[1]
			self.memConst.memString(x1-13000,x2)			
		for foo in line:
			lista = foo.split()
			x1 = int(lista[0])
			x2 = int(lista[1])
			x3 = int(lista[2])
			x4 = int(lista[3])
			x5 = int(lista[4])
			self.dict[x1] = (x2,x3,x4,x5)
		L = self.dict.keys()
		n = len(L)
		self.cuadruplo = 1	
		self.flag = False
		#ciclo pricipal que recorre los cuadruplos	
		while self.cuadruplo <= n:
			if self.flag != True:
				(op,opdo1,opdo2,res) = self.dict[self.cuadruplo]
				self.interpret(op,opdo1,opdo2,res)
			else: 
				break
	
	# funcion que simula el switch grandote que es requerido en la maquina virtual
	# en este caso dependiendo del OP hace una funcion
	# el switch es simuladoc on un diccionario (tabla de hashing) de Python	
	def interpret(self,x,y,z,w):
		switch = {
			0 : self.suma,
			1 : self.resta,
			2 : self.mul,
			3 : self.div,
			4 : self.diff,
			5 : self.great,
			6 : self.less,
			7 : self.greateq,
			8 : self.lesseq,
			9 : self.equaleq,
			10 : self.andop,
			11 : self.orop,
			12 : self.equ,
			13 : self.ret,
			14 : self.gotov,
			15 : self.gotof,
			16 : self.goto,
			17 : self.param,
			18 : self.printf,
			19 : self.returnf,
			20 : self.era,
			21 : self.gosub,
			22 : self.readf,
			23 : self.fin,
			24 : self.pm,
			25 : self.sqrt,
			26 : self.poww,
			27 : self.dist,
			28 : self.ecu,
			29 : self.sin,
			30 : self.csc,
			31 : self.cos,
			32 : self.cot,
			33 : self.tan,
			34 : self.sec,
			40 : self.verf
			}
		if x in switch:
     			switch[x](y,z,w)
		else:
     			pass
        
	# funcion que busca dos operados dependiendo del rango de memoria en que se encuentra
	# regresa una tupla con los dos operadores
	def memSearch(self, a, b):
		y = 0
		if a >= 1000 and a < 2000:
			x = self.memGlobal.getInt(a - self.memGlobal.mint)
			t1 = 0
		if a >= 2000 and a < 3000:
			x = self.memGlobal.getFloat(a - self.memGlobal.mfloat)
			t1 = 1
		if a >= 3000 and a < 4000:
			x = self.memGlobal.getString(a - self.memGlobal.mstring)
			t1 = 2
		if a >= 4000 and a < 5000:
			x = self.memGlobal.getBoolean(a - self.memGlobal.mboolean)
			t1 = 3
		if a >= 6000 and a < 7000:
			x = self.memTemp.getInt(a - self.memTemp.mint)
			t1 = 0
		if a >= 7000 and a < 8000:
			x = self.memTemp.getFloat(a - self.memTemp.mfloat)
			t1 = 1
		if a >= 8000 and a < 9000:
			x = self.memTemp.getString(a - self.memTemp.mstring)
			t1 = 2
		if a >= 9000 and a < 10000:
			x = self.memTemp.getBoolean(a - self.memTemp.mboolean)
			t1 = 3
		if a >= 11000 and a < 12000:
			x = self.memConst.getInt(a-self.memConst.mint)
			t1 = 0
		if a >= 12000 and a < 13000:
			x = self.memConst.getFloat(a-self.memConst.mfloat)
			t1 = 1
		if a >= 13000 and a < 14000:
			x = self.memConst.getString(a-self.memConst.mstring)
			t1 = 2
		if a >= 14000 and a < 15000:
			x = self.memConst.getBoolean(a-self.memConst.mboolean)
			t1 = 3	
		if a >= 20000 and a < 21000:
			x = self.memLoc.getInt(a-self.memLoc.mint)
			t1 = 0
		if a >= 21000 and a < 22000:
			x = self.memLoc.getFloat(a-self.memLoc.mfloat)
			t1 = 1
		if a >= 22000 and a < 23000:
			x = self.memLoc.getString(a-self.memLoc.mstring)
			t1 = 2
		if a >= 23000 and a < 24000:
			x = self.memLoc.getBoolean(a-self.memLoc.mboolean)
			t1 = 3
		if a >= 26000 and a < 27000:
			x = self.memPoint.getInt(a-self.memPoint.mint)
			t1 = 0
		if a >= 27000 and a < 28000:
			x = self.memPoint.getFloat(a-self.memPoint.mfloat)
			t1 = 1
		if a >= 28000 and a < 29000:
			x = self.memPoint.getString(a-self.memPoint.mstring)
			t1 = 2
		if a >= 29000 and a < 30000:
			x = self.memPoint.getBoolean(a-self.memPoint.mboolean)
			t1 = 3
		if b >= 1000 and b < 2000:
			y = self.memGlobal.getInt(b-self.memGlobal.mint)
			t2 = 0
		if b >= 2000 and b < 3000:
			y = self.memGlobal.getFloat(b-self.memGlobal.mfloat)
			t2 = 1
		if b >= 3000 and b < 4000:
			y = self.memGlobal.getString(b-self.memGlobal.mstring)
			t2 = 2
		if b >= 4000 and b < 5000:
			y = self.memGlobal.getBoolean(b-self.memGlobal.mboolean)
			t2 = 3
		if b >= 6000 and b < 7000:
			y = self.memTemp.getInt(b-self.memTemp.mint)
			t2 = 0
		if b >= 7000 and b < 8000:
			y = self.memTemp.getFloat(b-self.memTemp.mfloat)
			t2 = 1
		if b >= 8000 and b < 9000:
			y = self.memTemp.getString(b-self.memTemp.mstring)
			t2 = 2
		if b >= 9000 and b < 10000:
			y = self.memTemp.getBoolean(b-self.memTemp.mboolean)
			t2 = 3
		if b >= 11000 and b < 12000:
			y = self.memConst.getInt(b-self.memConst.mint)
			t2 = 0
		if b >= 12000 and b < 13000:
			y = self.memConst.getFloat(b-self.memConst.mfloat)
			t2 = 1
		if b >= 13000 and b < 14000:
			y = self.memConst.getString(b-self.memConst.mstring)
			t2 = 2
		if b >= 14000 and b < 15000:
			y = self.memConst.getBoolean(b-self.memConst.mboolean)	
			t2 = 3
		if b >= 20000 and b < 21000:
			y = self.memLoc.getInt(b-self.memLoc.mint)
			t2 = 0
		if b >= 21000 and b < 22000:
			y = self.memLoc.getFloat(b-self.memLoc.mfloat)
			t2 = 1
		if b >= 22000 and b < 23000:
			y = self.memLoc.getString(b-self.memLoc.mstring)
			t2 = 2
		if b >= 23000 and b < 24000:
			y = self.memLoc.getBoolean(b-self.memLoc.mboolean)
			t2 = 3
		if b >= 26000 and b < 27000:
			y = self.memPoint.getInt(b-self.memPoint.mint)
			t1 = 0
		if b >= 27000 and b < 28000:
			y = self.memPoint.getFloat(b-self.memPoint.mfloat)
			t1 = 1
		if b >= 28000 and b < 29000:
			y = self.memPoint.getString(b-self.memPoint.mstring)
			t1 = 2
		if b >= 29000 and b < 30000:
			y = self.memPoint.getBoolean(b-self.memPoint.mboolean)
			t1 = 3
		return (x,y)

	#funcion que guarda un valor en la lista de memoria dependiendo del rango de la memoria
	def memAdd(self,a,s):
		if a >= 1000 and a < 2000:
			self.memGlobal.memInt(a-self.memGlobal.mint,s)
		if a >= 2000 and a < 3000:
			self.memGlobal.memFloat(a-self.memGlobal.mfloat,s)
		if a >= 3000 and a < 4000:
			self.memGlobal.memString(a-self.memGlobal.mstring,s)
		if a >= 4000 and a < 5000:
			self.memGlobal.memBoolean(a-self.memGlobal.mboolean,s)
		if a >= 6000 and a < 7000:
			self.memTemp.memInt(a-self.memTemp.mint,s)
		if a >= 7000 and a < 8000:
			self.memTemp.memFloat(a-self.memTemp.mfloat,s)
		if a >= 8000 and a < 9000:
			self.memTemp.memString(a-self.memTemp.mstring,s)
		if a >= 9000 and a < 10000:
			self.memTemp.memBoolean(a-self.memTemp.mboolean,s)
		if a >= 11000 and a < 12000:
			self.memConst.memInt(a-self.memConst.mint,s)
		if a >= 12000 and a < 13000:
			self.memConst.memFloat(a-self.memConst.mfloat,s)
		if a >= 13000 and a < 14000:
			self.memConst.memString(a-self.memConst.mstring,s)
		if a >= 14000 and a < 15000:
			self.memConst.memBoolean(a-self.memConst.mboolean,s)
		if a >= 20000 and a < 21000:
			self.memLoc.memInt(a-self.memLoc.mint,s)
		if a >= 21000 and a < 22000:
			self.memLoc.memFloat(a-self.memLoc.mfloat,s)
		if a >= 22000 and a < 23000:
			self.memLoc.memString(a-self.memLoc.mstring,s)
		if a >= 23000 and a < 24000:
			self.memLoc.memBoolean(a-self.memLoc.mboolean,s)
		if a >= 26000 and a < 27000:
			self.memPoint.memInt(a-self.memPoint.mint,s)
		if a >= 27000 and a < 28000:
			self.memPoint.memFloat(a-self.memPoint.mfloat,s)
		if a >= 28000 and a < 29000:
			self.memPoint.memString(a-self.memPoint.mstring,s)
		if a >= 29000 and a < 30000:
			self.memPoint.memBoolean(a-self.memPoint.mboolean,s)
	
	# funcion que se usa para la asignacion en donde obtiene el valor dependiendo del rango
	# y manda a llamar a memAdd para guardarla
	def memAss(self, b, s):
		if b >= 1000 and b < 2000:
			y = self.memGlobal.getInt(b-self.memGlobal.mint)
			self.memAdd(s,y)
		if b >= 2000 and b < 3000:
			y = self.memGlobal.getFloat(b-self.memGlobal.mfloat)
			self.memAdd(s,y)
		if b >= 3000 and b < 4000:
			y = self.memGlobal.getString(b-self.memGlobal.mstring)
			self.memAdd(s,y)
		if b >= 4000 and b < 5000:
			y = self.memGlobal.getBoolean(b-self.memGlobal.mboolean)
			self.memAdd(s,y)
		if b >= 6000 and b < 7000:
			y = self.memTemp.getInt(b-self.memTemp.mint)
			self.memAdd(s,y)
		if b >= 7000 and b < 8000:
			y = self.memTemp.getFloat(b-self.memTemp.mfloat)
			self.memAdd(s,y)
		if b >= 8000 and b < 9000:
			y = self.memTemp.getString(b-self.memTemp.mstring)
			self.memAdd(s,y)
		if b >= 9000 and b < 10000:
			y = self.memTemp.getBoolean(b-self.memTemp.mboolean)
			self.memAdd(s,y)
		if b >= 11000 and b < 12000:
			y = self.memConst.getInt(b-self.memConst.mint)
			self.memAdd(s,y)
		if b >= 12000 and b < 13000:
			y = self.memConst.getFloat(b-self.memConst.mfloat)
			self.memAdd(s,y)
		if b >= 13000 and b < 14000:
			y = self.memConst.getString(b-self.memConst.mstring)
			self.memAdd(s,y)
		if b >= 14000 and b < 15000:
			y = self.memConst.getBoolean(b-self.memConst.mboolean)
			self.memAdd(s,y)	
		if b >= 20000 and b < 21000:
			y = self.memLoc.getInt(b-self.memLoc.mint)
			self.memAdd(s,y)
		if b >= 21000 and b < 22000:
			y = self.memLoc.getFloat(b-self.memLoc.mfloat)
			self.memAdd(s,y)
		if b >= 22000 and b < 23000:
			y = self.memLoc.getString(b-self.memLoc.mstring)
			self.memAdd(s,y)
		if b >= 23000 and b < 24000:
			y = self.memLoc.getBoolean(b-self.memLoc.mboolean)
			self.memAdd(s,y)
		if b >= 26000 and b < 27000:
			y = self.memPoint.getInt(b-self.memPoint.mint)
			self.memAdd(s,y)
		if b >= 27000 and b < 28000:
			y = self.memPoint.getFloat(b-self.memPoint.mfloat)
			self.memAdd(s,y)
		if b >= 28000 and b < 29000:
			y = self.memPoint.getString(b-self.memPoint.mstring)
			self.memAdd(s,y)
		if b >= 29000 and b < 30000:
			y = self.memPoint.getBoolean(b-self.memPoint.mboolean)
			self.memAdd(s,y)
	
	# funcion que usa para imprimir a pantalla
	def memPrint(self, b):
		if b >= 1000 and b < 2000:
			y = self.memGlobal.getInt(b-self.memGlobal.mint)
			print y
		if b >= 2000 and b < 3000:
			y = self.memGlobal.getFloat(b-self.memGlobal.mfloat)
			print y
		if b >= 3000 and b < 4000:
			y = self.memGlobal.getString(b-self.memGlobal.mstring)
			print y
		if b >= 4000 and b < 5000:
			y = self.memGlobal.getBoolean(b-self.memGlobal.mboolean)
			print y
		if b >= 6000 and b < 7000:
			y = self.memTemp.getInt(b-self.memTemp.mint)
			print y
		if b >= 7000 and b < 8000:
			y = self.memTemp.getFloat(b-self.memTemp.mfloat)
			print y
		if b >= 8000 and b < 9000:
			y = self.memTemp.getString(b-self.memTemp.mstring)
			print y
		if b >= 9000 and b < 10000:
			y = self.memTemp.getBoolean(b-self.memTemp.mboolean)
			print y
		if b >= 11000 and b < 12000:
			y = self.memConst.getInt(b-self.memConst.mint)
			print y
		if b >= 12000 and b < 13000:
			y = self.memConst.getFloat(b-self.memConst.mfloat)
			print y
		if b >= 13000 and b < 14000:
			y = self.memConst.getString(b-self.memConst.mstring)
			print y
		if b >= 14000 and b < 15000:
			y = self.memConst.getBoolean(b-self.memConst.mboolean)
			print y
		if b >= 20000 and b < 21000:
			y = self.memLoc.getInt(b-self.memLoc.mint)
			print y
		if b >= 21000 and b < 22000:
			y = self.memLoc.getFloat(b-self.memLoc.mfloat)
			print y
		if b >= 22000 and b < 23000:
			y = self.memLoc.getString(b-self.memLoc.mstring)
			print y
		if b >= 23000 and b < 24000:
			y = self.memLoc.getBoolean(b-self.memLoc.mboolean)
			print y
		if b >= 26000 and b < 27000:
			y = self.memPoint.getInt(b-self.memPoint.mint)
			print y
		if b >= 27000 and b < 28000:
			y = self.memPoint.getFloat(b-self.memPoint.mfloat)
			print y
		if b >= 28000 and b < 29000:
			y = self.memPoint.getString(b-self.memPoint.mstring)
			print y
		if b >= 29000 and b < 30000:
			y = self.memPoint.getBoolean(b-self.memPoint.mboolean)
			print y
	
	# funcion que se usa para lleer de pantalla
	def memRead(self,a,s):
		if a >= 1000 and a < 2000:
			ss = int(s)
			self.memGlobal.memInt(a-self.memGlobal.mint,ss)
		if a >= 2000 and a < 3000:
			ss = float(s)
			self.memGlobal.memFloat(a-self.memGlobal.mfloat,ss)
		if a >= 3000 and a < 4000:
			ss = str(s)
			self.memGlobal.memString(a-self.memGlobal.mstring,ss)
		if a >= 4000 and a < 5000:
			ss = bool(s)
			self.memGlobal.memBoolean(a-self.memGlobal.mboolean,ss)
		if a >= 6000 and a < 7000:
			ss = int(s)
			self.memTemp.memInt(a-self.memTemp.mint,ss)
		if a >= 7000 and a < 8000:
			ss = float(s)
			self.memTemp.memFloat(a-self.memTemp.mfloat,ss)
		if a >= 8000 and a < 9000:
			ss = str(s)
			self.memTemp.memString(a-self.memTemp.mstring,ss)
		if a >= 9000 and a < 10000:
			ss = bool(s)
			self.memTemp.memBoolean(a-self.memTemp.mboolean,ss)
		if a >= 11000 and a < 12000:
			ss = int(s)
			self.memConst.memInt(a-self.memConst.mint,ss)
		if a >= 12000 and a < 13000:
			ss = float(s)
			self.memConst.memFloat(a-self.memConst.mfloat,ss)
		if a >= 13000 and a < 14000:
			ss = str(s)
			self.memConst.memString(a-self.memConst.mstring,ss)
		if a >= 14000 and a < 15000:
			ss = bool(s)
			self.memConst.memBoolean(a-self.memConst.mboolean,ss)
		if a >= 20000 and a < 21000:
			ss = int(s)
			self.memLoc.memInt(a-self.memLoc.mint,ss)
		if a >= 21000 and a < 22000:
			ss = float(s)
			self.memLoc.memFloat(a-self.memLoc.mfloat,ss)
		if a >= 22000 and a < 23000:
			ss = str(s)
			self.memLoc.memString(a-self.memLoc.mstring,ss)
		if a >= 23000 and a < 24000:
			ss = bool(s)
		 	self.memLoc.memBoolean(a-self.memLoc.mboolean,ss)

	#funcion que se usa para los gotof y busca el valor dependiendo de la direccion virtual
	def funcFalso(self,b):
		if b >= 4000 and b < 5000:
			y = self.memGlobal.getBoolean(b-self.memGlobal.mboolean)
		if b >= 9000 and b < 10000:
			y = self.memTemp.getBoolean(b-self.memTemp.mboolean)
		if b >= 14000 and b < 15000:
			y = self.memConst.getBoolean(b-self.memConst.mboolean)
		if b >= 23000 and b < 24000:
			y = self.memLoc.getBoolean(b-self.memLoc.mboolean)
		return y

	# funcion que guarda los paramatros en la lista de parametros
	def memPar(self, a, s):
		if a >= 20000 and a < 21000: 
			self.memParam.memInt(a-self.memParam.mint,s)
		if a >= 21000 and a < 22000:
			self.memParam.memFloat(a-self.memParam.mfloat,s)
		if a >= 22000 and a < 23000:
			self.memParam.memString(a-self.memParam.mstring,s)
		if a >= 23000 and a < 24000:
			self.memParam.memBoolean(a-self.memParam.mboolean,s)
	
	# funcion que busca el valor en las listas de memoria y despues manda a llamar a
	# memPar para que se ocupe de guardar el valor
	def memAsp(self, b, s):
		if b >= 1000 and b < 2000:
			y = self.memGlobal.getInt(b-self.memGlobal.mint)
			self.memPar(s,y)
		if b >= 2000 and b < 3000:
			y = self.memGlobal.getFloat(b-self.memGlobal.mfloat)
			self.memPar(s,y)
		if b >= 3000 and b < 4000:
			y = self.memGlobal.getString(b-self.memGlobal.mstring)
			self.memPar(s,y)
		if b >= 4000 and b < 5000:
			y = self.memGlobal.getBoolean(b-self.memGlobal.mboolean)
			self.memPar(s,y)
		if b >= 6000 and b < 7000:
			y = self.memTemp.getInt(b-self.memTemp.mint)
			self.memPar(s,y)
		if b >= 7000 and b < 8000:
			y = self.memTemp.getFloat(b-self.memTemp.mfloat)
			self.memPar(s,y)
		if b >= 8000 and b < 9000:
			y = self.memTemp.getString(b-self.memTemp.mstring)
			self.memPar(s,y)
		if b >= 9000 and b < 10000:
			y = self.memTemp.getBoolean(b-self.memTemp.mboolean)
			self.memPar(s,y)
		if b >= 11000 and b < 12000:
			y = self.memConst.getInt(b-self.memConst.mint)
			self.memPar(s,y)
		if b >= 12000 and b < 13000:
			y = self.memConst.getFloat(b-self.memConst.mfloat)
			self.memPar(s,y)
		if b >= 13000 and b < 14000:
			y = self.memConst.getString(b-self.memConst.mstring)
			self.memPar(s,y)
		if b >= 14000 and b < 15000:
			y = self.memConst.getBoolean(b-self.memConst.mboolean)
			self.memPar(s,y)	
		if b >= 20000 and b < 21000:
			y = self.memLoc.getInt(b-self.memLoc.mint)
			self.memPar(s,y)
		if b >= 21000 and b < 22000:
			y = self.memLoc.getFloat(b-self.memLoc.mfloat)
			self.memPar(s,y)
		if b >= 22000 and b < 23000:
			y = self.memLoc.getString(b-self.memLoc.mstring)
			self.memPar(s,y)
		if b >= 23000 and b < 24000:
			y = self.memLoc.getBoolean(b-self.memLoc.mboolean)
			self.memPar(s,y)
		if b >= 26000 and a < 27000:
			y = self.memPoint.getInt(b-self.memPoint.mint)
			self.memPar(s,y)
		if b >= 27000 and a < 28000:
			y = self.memPoint.getFloat(b-self.memPoint.mfloat)
			self.memPar(s,y)
		if b >= 28000 and a < 29000:
			y = self.memPoint.getString(b-self.memPoint.mstring)
			self.memPar(s,y)
		if b >= 29000 and a < 30000:
			y = self.memPoint.getBoolean(b-self.memPoint.mboolean)
			self.memPar(s,y)

	# funcion que obtiene verifica las dimensiones del arreglo
	def memArr(self, b, s):
		if b >= 1000 and b < 2000:
			y = self.memGlobal.getInt(b-self.memGlobal.mint)
		if b >= 2000 and b < 3000:
			y = self.memGlobal.getFloat(b-self.memGlobal.mfloat)
		if b >= 3000 and b < 4000:
			y = self.memGlobal.getString(b-self.memGlobal.mstring)
		if b >= 4000 and b < 5000:
			y = self.memGlobal.getBoolean(b-self.memGlobal.mboolean)
		if b >= 6000 and b < 7000:
			y = self.memTemp.getInt(b-self.memTemp.mint)
		if b >= 7000 and b < 8000:
			y = self.memTemp.getFloat(b-self.memTemp.mfloat)
		if b >= 8000 and b < 9000:
			y = self.memTemp.getString(b-self.memTemp.mstring)
		if b >= 9000 and b < 10000:
			y = self.memTemp.getBoolean(b-self.memTemp.mboolean)
		if b >= 11000 and b < 12000:
			y = self.memConst.getInt(b-self.memConst.mint)
		if b >= 12000 and b < 13000:
			y = self.memConst.getFloat(b-self.memConst.mfloat)
		if b >= 13000 and b < 14000:
			y = self.memConst.getString(b-self.memConst.mstring)
		if b >= 14000 and b < 15000:
			y = self.memConst.getBoolean(b-self.memConst.mboolean)
		if b >= 20000 and b < 21000:
			y = self.memLoc.getInt(b-self.memLoc.mint)
		if b >= 21000 and b < 22000:
			y = self.memLoc.getFloat(b-self.memLoc.mfloat)
		if b >= 22000 and b < 23000:
			y = self.memLoc.getString(b-self.memLoc.mstring)
		if b >= 23000 and b < 24000:
			y = self.memLoc.getBoolean(b-self.memLoc.mboolean)
	
	def memReturn(self, b, s):
		if b >= 1000 and b < 2000:
			y = self.memGlobal.getInt(b-self.memGlobal.mint)
			self.memAdd(s,y)
		if b >= 2000 and b < 3000:
			y = self.memGlobal.getFloat(b-self.memGlobal.mfloat)
			self.memAdd(s,y)
		if b >= 3000 and b < 4000:
			y = self.memGlobal.getString(b-self.memGlobal.mstring)
			self.memAdd(s,y)
		if b >= 4000 and b < 5000:
			y = self.memGlobal.getBoolean(b-self.memGlobal.mboolean)
			self.memAdd(s,y)
		if b >= 6000 and b < 7000:
			y = self.memTemp.getInt(b-self.memTemp.mint)
			self.memAdd(s,y)
		if b >= 7000 and b < 8000:
			y = self.memTemp.getFloat(b-self.memTemp.mfloat)
			self.memAdd(s,y)
		if b >= 8000 and b < 9000:
			y = self.memTemp.getString(b-self.memTemp.mstring)
			self.memAdd(s,y)
		if b >= 9000 and b < 10000:
			y = self.memTemp.getBoolean(b-self.memTemp.mboolean)
			self.memAdd(s,y)
		if b >= 11000 and b < 12000:
			y = self.memConst.getInt(b-self.memConst.mint)
			self.memAdd(s,y)
		if b >= 12000 and b < 13000:
			y = self.memConst.getFloat(b-self.memConst.mfloat)
			self.memAdd(s,y)
		if b >= 13000 and b < 14000:
			y = self.memConst.getString(b-self.memConst.mstring)
			self.memAdd(s,y)
		if b >= 14000 and b < 15000:
			y = self.memConst.getBoolean(b-self.memConst.mboolean)
			self.memAdd(s,y)
		if b >= 20000 and b < 21000:
			y = self.memLoc.getInt(b-self.memLoc.mint)
			self.memAdd(s,y)
		if b >= 21000 and b < 22000:
			y = self.memLoc.getFloat(b-self.memLoc.mfloat)
			self.memAdd(s,y)
		if b >= 22000 and b < 23000:
			y = self.memLoc.getString(b-self.memLoc.mstring)
			self.memAdd(s,y)
		if b >= 23000 and b < 24000:
			y = self.memLoc.getBoolean(b-self.memLoc.mboolean)
			self.memAdd(s,y)
		if b >= 26000 and b < 27000:
			y = self.memPoint.getInt(b-self.memPoint.mint)
			self.memAdd(s,y)
		if b >= 27000 and b < 28000:
			y = self.memPoint.getFloat(b-self.memPoint.mfloat)
			self.memAdd(s,y)
		if b >= 28000 and b < 29000:
			y = self.memPoint.getString(b-self.memPoint.mstring)
			self.memAdd(s,y)
		if b >= 29000 and b < 30000:
			y = self.memPoint.getBoolean(b-self.memPoint.mboolean)
			self.memAdd(s,y)

	# el siguiente bloque de funciones son los casos para todos operadores del switch			
	def suma(self, opdo1, opdo2, res):
		self.cuadruplo+=1
		(a,b) = self.memSearch(opdo1,opdo2)	
		s = a + b
		self.memAdd(res, s)

	def resta(self, opdo1, opdo2, res):
		self.cuadruplo+=1
		(a,b) = self.memSearch(opdo1,opdo2)
		s = a - b
		self.memAdd(res, s)

	def mul(self, opdo1, opdo2, res):
		self.cuadruplo+=1
		(a,b) = self.memSearch(opdo1,opdo2)
		s = a * b            
		self.memAdd(res, s)

	def div(self, opdo1, opdo2, res):
		self.cuadruplo+=1
		(a,b) = self.memSearch(opdo1,opdo2)
		s = a / b            
		self.memAdd(res, s)

	def diff(self, opdo1, opdo2, res):
		self.cuadruplo+=1
		(a,b) = self.memSearch(opdo1,opdo2)
		s = a != b
		self.memAdd(res, s)

	def great(self, opdo1, opdo2, res):
		self.cuadruplo+=1
		(a,b) = self.memSearch(opdo1,opdo2)
		s = a > b
		self.memAdd(res, s)

	def less(self, opdo1, opdo2, res):
		self.cuadruplo+=1
		(a,b) = self.memSearch(opdo1,opdo2)
		s = a < b
		self.memAdd(res, s)

	def greateq(self, opdo1, opdo2, res):
		self.cuadruplo+=1
		(a,b) = self.memSearch(opdo1,opdo2)
		s = a >= b
		self.memAdd(res, s)

	def lesseq(self, opdo1, opdo2, res):
		self.cuadruplo+=1
		(a,b) = self.memSearch(opdo1,opdo2)
		s = a <= b
		self.memAdd(res, s)

	def equaleq(self, opdo1, opdo2, res):
		self.cuadruplo+=1
		(a,b) = self.memSearch(opdo1,opdo2)
		s = a == b
		self.memAdd(res, s)

	def andop(self, opdo1, opdo2, res):
		self.cuadruplo+=1
		(a,b) = self.memSearch(opdo1,opdo2)
		s = a and b
		self.memAdd(res, s, opdo2)

	def orop(self, opdo1, opdo2, res):
		self.cuadruplo+=1
		(a,b) = self.memSearch(opdo1,opdo2)
		s = a or b
		self.memAdd(res, s)

	def equ(self, opdo1, opdo2, res):
		self.cuadruplo+=1	
		self.memAss(opdo2,res)

	def ret(self, opdo1, opdo2, res):
		del self.memLoc.memTablei[:]  
		del self.memLoc.memTablef[:]
		del self.memLoc.memTableb[:]
		del self.memLoc.memTables[:]
		p_cuadruplo= self.PCuadruplo.pop()
		self.cuadruplo = p_cuadruplo
		self.memLoc = self.PExe.pop()

	def gotov(self, opdo1, opdo2, res):
		b = self.funcFalso(opdo1)
		if b == True:
			self.cuadruplo = res
		else: 
			self.cuadruplo+=1

	def gotof(self, opdo1, opdo2, res):
		b = self.funcFalso(opdo1)
		if b == False:
			self.cuadruplo = res
		else: 
			self.cuadruplo+=1

	def goto(self, opdo1, opdo2, res):
		self.cuadruplo = res

	def param(self, opdo1, opdo2, res):
		self.cuadruplo+=1
		self.memAsp(opdo1,res)

	def printf(self, opdo1, opdo2, res):
		self.cuadruplo+=1
		self.memPrint(opdo1)

	def returnf(self, opdo1, opdo2, res):
		self.cuadruplo+=1
		self.memReturn(opdo2,res)

	def era(self, opdo1, opdo2, res):
		self.cuadruplo+=1
		self.memParam = memoriaVirtual()
		self.memParam.mint = 20000;
		self.memParam.mfloat = 21000;
		self.memParam.mstring = 22000;
		self.memParam.mboolean = 23000;	

	def gosub(self, opdo1, opdo2, res):
		self.PExe.append(self.memLoc)
		a = self.cuadruplo+1
		self.PCuadruplo.append(a)
		del self.memLoc.memTablei[:]  
		del self.memLoc.memTablef[:]
		del self.memLoc.memTableb[:]
		del self.memLoc.memTables[:]
		self.memLoc.memTablei = self.memParam.memTablei
		self.memLoc.memTablef = self.memParam.memTablef     
		self.memLoc.memTableb = self.memParam.memTableb   
		self.memLoc.memTables = self.memParam.memTables    
		self.cuadruplo=opdo1      

	def readf(self, opdo1, opdo2, res):
		self.cuadruplo+=1
		resp = raw_input("Dame entrada ")
		self.memRead(opdo1,resp)

	def fin(self, opdo1, opdo2, res):
		self.flag = True

	def pm(self, opdo1, opdo2, res):
		print "pm"

	def sqrt(self, opdo1, opdo2, res):
		print "sqrt"

	def poww(self, opdo1, opdo2, res):
		print "poww"

	def dist(self, opdo1, opdo2, res):
		print "dist"

	def ecu(self, opdo1, opdo2, res):
		print "ecu"

	def sin(self, opdo1, opdo2, res):
		print "sin"

	def csc(self, opdo1, opdo2, res):
		print "csc"
		
	def cos(self, opdo1, opdo2, res):
		print "cos"

	def cot(self, opdo1, opdo2, res):
		print "cot"

	def tan(self, opdo1, opdo2, res):
		print "tan"

	def sec(self, opdo1, opdo2, res):
		print "sec"

	def verf(self, opdo1, opdo2, res):
		self.cuadruplo+=1
		b = self.memArr(opdo1,res)
		#if b < opdo2 or b > res:
		#	print "Index out of range!"

if __name__ == '__main__':
	v=virtualMachine()


