class memoriaVirtual(object):

	def __init__(self):
		self.initialize()

	def initialize(self):
		self.mint = 0
		self.mfloat = 0
		self.mstring = 0
		self.mboolean = 0
		self.memTablei = []
		self.memTablef = []
		self.memTableb = []
		self.memTables = []
		for foo in range(1000):
			self.memTablei.append(0)
			self.memTablef.append(0.0)
			self.memTableb.append(None)
			self.memTables.append("")

	def memInt(self, a, b):
		self.memTablei[a] = b

	def memFloat(self, a, b):
		self.memTablef[a] = b
		
	def memString(self, a, b):
		self.memTables[a] = b

	def memBoolean(self, a, b):
		self.memTableb[a] = b

	def getInt(self,a):
		return self.memTablei[a]

	def getFloat(self,a):
		return self.memTablef[a]

	def getString(self,a):
		return self.memTables[a]

	def getBoolean(self,a):
		return self.memTableb[a]


