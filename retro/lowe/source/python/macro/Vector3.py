import math

class Vector3:
    def __init__(self,x=None,y=None,z=None):
        if x == None:
            self.x = 0.
        else:
            self.x = x
        if y == None:
            self.y = 0
        else:
            self.y = y
        if z == None:
            self.z = 0
        else:
            self.z = z
    def SetMagCosThetaPhi(self,mag,costheta,phi):
        self.x = mag * math.sqrt(1 - costheta* costheta) * math.cos(phi)
        self.y = mag * math.sqrt(1 - costheta* costheta) * math.sin(phi)
        self.z = mag * costheta
    def __add__(self,other):
        x = self.x + other.x
        y = self.y + other.y
        z = self.z + other.z
        return Vector3(x,y,z)
    def __sub__(self,other):
        x = self.x - other.x
        y = self.y - other.y
        z = self.z - other.z
        return Vector3(x,y,z)
    def __mul__(self,other):
        return (self.x * other.x + self.y * other.y + self.z * other.z)
    def __iadd__(self,other):
        self.x += other.x
        self.y += other.y
        self.z += other.z
        return self
    def __isub__(self,other):
        self.x -= other.x
        self.y -= other.y
        self.z -= other.z
        return self
    def __eq__(self,other):
        return (self.x == other.x) and (self.y == other.y) and (self.z == other.z)
    def __ne__(self,other):
        return not (self == other)
    def scalarmulti(self,scalar):
        self.x *= scalar
        self.y *= scalar
        self.z *= scalar
        return self
    def __truediv__(self,value):
        x = self.x/value
        y = self.y/value
        z = self.z/value
        return Vector3(x,y,z)
    def Mag(self):
        return math.sqrt(self.x * self.x + self.y * self.y + self.z * self.z)
    def AngleCos(self,other):
        return (self * other)/(self.Mag() * other.Mag())
