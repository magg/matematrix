
# Se declara la clase
class virtualMachine(object):
	# Funcion que se corre al crear un objeto de la clase
	def __init__(self):
		self.initialize()

	def initialize(self):
		self.dict = {}
		f = open('/home/magg/coco-r/cuadruplos', 'r')
		line = f.readlines()
		f.close()
		for foo in line:
			lista = foo.split()
			x1 = int(lista[0])
			x2 = lista[1]
			x3 = lista[2]
			x4 = lista[3]
			x5 = lista[4]
			self.dict[x1] = (x2,x3,x4,x5)
		for n, (op, opdo1, opdo2, res) in self.dict.items():
			self.interpret(op)		
	
	def interpret(self,x):
		switch = {
			    '0' : self.zero,
			    '1' : self.suma,
			}
		if x in switch:
     			switch[x]()
		else:
     			pass

	def zero(self):
		print 0

	def suma(self):
		print "suma"

if __name__ == '__main__':
	v=virtualMachine()


