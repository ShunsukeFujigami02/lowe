import func
import macro
import math
import ROOT
import time

class goodnesscomparenodigital:
    def __init__(self,fm):
        self.fm = fm
        self.reflectivity = float(self.fm.GetTag("ReflectivityFactorTrapezoidReflectivity"))
        self.retroratio = 2.51128285714285748e-01*(self.reflectivity - 0.3) + 0.0813312
        self.log1minusp = math.log( 1 - self.retroratio)
        self.logp = math.log(self.retroratio)
        self.comparedigidir0 = math.log( 1 - self.retroratio) + 0.
        self.comparedigidir4 = math.log( 1 - self.retroratio) + 4.
        self.comparedigiref4 = math.log(self.retroratio) + 4.
        self.parnum = 6
        self.sigma = 5.
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
    def returnvalue(self,invalue):
        g = 0.
        for hit in self.allhitinfo.hitinfolist:
           toferrornoretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_position_pmt)
           toferroronretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_fly_retro)
           gnoretro = self.log1minusp + 4.*math.exp((-1/2.)*(toferrornoretro/self.sigma)*(toferrornoretro/self.sigma))
           gonretro = self.logp + 4.*math.exp((-1/2.)*(toferroronretro/self.sigma)*(toferroronretro/self.sigma))
           if gnoretro > gonretro:
               g+= gnoretro
           else:
               g+= gonretro
        return g
    def GetMinimizedvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        return 0.
    def GetTruevalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(0)",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(1)",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(2)",ievent)[0]
        if parnum == 3:
            return -self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTriggerTime()",ievent)[0]
        if parnum == 4:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.CosTheta()
        if parnum == 5:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.Phi()

class goodnesscomparenodigitalretroonly:
    def __init__(self,fm):
        self.fm = fm
        self.reflectivity = float(self.fm.GetTag("ReflectivityFactorTrapezoidReflectivity"))
        self.retroratio = 2.51128285714285748e-01*(self.reflectivity - 0.3) + 0.0813312
        self.log1minusp = math.log( 1 - self.retroratio)
        self.logp = math.log(self.retroratio)
        self.comparedigidir0 = math.log( 1 - self.retroratio) + 0.
        self.comparedigidir4 = math.log( 1 - self.retroratio) + 4.
        self.comparedigiref4 = math.log(self.retroratio) + 4.
        self.parnum = 6
        self.sigma = 5.
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
    def returnvalue(self,invalue):
        g = 0.
        for hit in self.allhitinfo.hitinfolist:
           toferrornoretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_position_pmt)
           toferroronretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_fly_retro)
           gnoretro = self.log1minusp + 4.*math.exp((-1/2.)*(toferrornoretro/self.sigma)*(toferrornoretro/self.sigma))
           gonretro = self.logp + 4.*math.exp((-1/2.)*(toferroronretro/self.sigma)*(toferroronretro/self.sigma))
           if gnoretro > gonretro:
               pass
           else:
               g+= gonretro
        return g
    def GetMinimizedvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        return 0.
    def GetTruevalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(0)",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(1)",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(2)",ievent)[0]
        if parnum == 3:
            return -self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTriggerTime()",ievent)[0]
        if parnum == 4:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.CosTheta()
        if parnum == 5:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.Phi()

class goodnesscomparenodigitaldirectonly:
    def __init__(self,fm):
        self.fm = fm
        self.reflectivity = float(self.fm.GetTag("ReflectivityFactorTrapezoidReflectivity"))
        self.retroratio = 2.51128285714285748e-01*(self.reflectivity - 0.3) + 0.0813312
        self.log1minusp = math.log( 1 - self.retroratio)
        self.logp = math.log(self.retroratio)
        self.comparedigidir0 = math.log( 1 - self.retroratio) + 0.
        self.comparedigidir4 = math.log( 1 - self.retroratio) + 4.
        self.comparedigiref4 = math.log(self.retroratio) + 4.
        self.parnum = 6
        self.sigma = 5.
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
    def returnvalue(self,invalue):
        g = 0.
        for hit in self.allhitinfo.hitinfolist:
           toferrornoretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_position_pmt)
           toferroronretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_fly_retro)
           gnoretro = self.log1minusp + 4.*math.exp((-1/2.)*(toferrornoretro/self.sigma)*(toferrornoretro/self.sigma))
           gonretro = self.logp + 4.*math.exp((-1/2.)*(toferroronretro/self.sigma)*(toferroronretro/self.sigma))
           if gnoretro > gonretro:
               g+= gnoretro
           else:
               pass
        return g
    def GetMinimizedvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        return 0.
    def GetTruevalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(0)",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(1)",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(2)",ievent)[0]
        if parnum == 3:
            return -self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTriggerTime()",ievent)[0]
        if parnum == 4:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.CosTheta()
        if parnum == 5:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.Phi()

class goodnesscomparenodigital_ver2:
    def __init__(self,fm):
        self.fm = fm
        self.parnum = 6
        self.sigma = 5.
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
    def returnvalue(self,invalue):
        g = 0.
        for hit in self.allhitinfo.hitinfolist:
           toferrornoretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_position_pmt)
           toferroronretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_fly_retro)
           gnoretro = 4.*math.exp((-1/2.)*(toferrornoretro/self.sigma)*(toferrornoretro/self.sigma))
           gonretro = math.exp((-1/2.)*(toferroronretro/self.sigma)*(toferroronretro/self.sigma))
           if gnoretro > gonretro:
               g+= gnoretro
           else:
               g+= gonretro
        return g
    def GetMinimizedvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        return 0.
    def GetTruevalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(0)",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(1)",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(2)",ievent)[0]
        if parnum == 3:
            return -self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTriggerTime()",ievent)[0]
        if parnum == 4:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.CosTheta()
        if parnum == 5:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.Phi()

class goodnesscomparenodigital_ver2retroonly:
    def __init__(self,fm):
        self.fm = fm
        self.parnum = 6
        self.sigma = 5.
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
    def returnvalue(self,invalue):
        g = 0.
        for hit in self.allhitinfo.hitinfolist:
           toferrornoretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_position_pmt)
           toferroronretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_fly_retro)
           gnoretro = 4.*math.exp((-1/2.)*(toferrornoretro/self.sigma)*(toferrornoretro/self.sigma))
           gonretro = math.exp((-1/2.)*(toferroronretro/self.sigma)*(toferroronretro/self.sigma))
           if gnoretro > gonretro:
               pass
           else:
               g+= gonretro
        return g
    def GetMinimizedvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        return 0.
    def GetTruevalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(0)",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(1)",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(2)",ievent)[0]
        if parnum == 3:
            return -self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTriggerTime()",ievent)[0]
        if parnum == 4:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.CosTheta()
        if parnum == 5:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.Phi()

class goodnesscomparenodigital_ver2directonly:
    def __init__(self,fm):
        self.fm = fm
        self.parnum = 6
        self.sigma = 5.
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
    def returnvalue(self,invalue):
        g = 0.
        for hit in self.allhitinfo.hitinfolist:
           toferrornoretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_position_pmt)
           toferroronretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_fly_retro)
           gnoretro = 4.*math.exp((-1/2.)*(toferrornoretro/self.sigma)*(toferrornoretro/self.sigma))
           gonretro = math.exp((-1/2.)*(toferroronretro/self.sigma)*(toferroronretro/self.sigma))
           if gnoretro > gonretro:
               g+= gnoretro
           else:
               pass
        return g
    def GetMinimizedvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        return 0.
    def GetTruevalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(0)",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(1)",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(2)",ievent)[0]
        if parnum == 3:
            return -self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTriggerTime()",ievent)[0]
        if parnum == 4:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.CosTheta()
        if parnum == 5:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.Phi()

class goodnesscomparedigital:
    def __init__(self,fm):
        self.fm = fm
        self.reflectivity = float(self.fm.GetTag("ReflectivityFactorTrapezoidReflectivity"))
        self.retroratio = 2.51128285714285748e-01*(self.reflectivity - 0.3) + 0.0813312
        self.comparedigidir0 = math.log( 1 - self.retroratio) + 0.
        self.comparedigidir4 = math.log( 1 - self.retroratio) + 4.
        self.comparedigiref4 = math.log(self.retroratio) + 4.
        self.parnum = 6
        self.sigma = 5.
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
    def returnvalue(self,invalue):
        g = 0.
        for hit in self.allhitinfo.hitinfolist:
           toferrornoretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_position_pmt)
           if math.fabs(toferrornoretro) < self.sigma:
               g += self.comparedigidir4
               continue
           toferroronretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_fly_retro)
           if math.fabs(toferroronretro) < self.sigma:
               g += self.comparedigiref4
               continue
           g+= self.comparedigidir0
        return g
    def GetMinimizedvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        return 0.
    def GetTruevalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(0)",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(1)",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(2)",ievent)[0]
        if parnum == 3:
            return -self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTriggerTime()",ievent)[0]
        if parnum == 4:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.CosTheta()
        if parnum == 5:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.Phi()

class goodnesscomparedigitaldir4only:
    def __init__(self,fm):
        self.fm = fm
        self.reflectivity = float(self.fm.GetTag("ReflectivityFactorTrapezoidReflectivity"))
        self.retroratio = 2.51128285714285748e-01*(self.reflectivity - 0.3) + 0.0813312
        self.comparedigidir0 = math.log( 1 - self.retroratio) + 0.
        self.comparedigidir4 = math.log( 1 - self.retroratio) + 4.
        self.comparedigiref4 = math.log(self.retroratio) + 4.
        self.parnum = 6
        self.sigma = 5.
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
    def returnvalue(self,invalue):
        g = 0.
        for hit in self.allhitinfo.hitinfolist:
           toferrornoretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_position_pmt)
           if math.fabs(toferrornoretro) < self.sigma:
               g += self.comparedigidir4
               continue
           toferroronretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_fly_retro)
           if math.fabs(toferroronretro) < self.sigma:
               continue
        return g
    def GetMinimizedvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        return 0.
    def GetTruevalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(0)",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(1)",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(2)",ievent)[0]
        if parnum == 3:
            return -self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTriggerTime()",ievent)[0]
        if parnum == 4:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.CosTheta()
        if parnum == 5:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.Phi()

class goodnesscomparedigitaldir0only:
    def __init__(self,fm):
        self.fm = fm
        self.reflectivity = float(self.fm.GetTag("ReflectivityFactorTrapezoidReflectivity"))
        self.retroratio = 2.51128285714285748e-01*(self.reflectivity - 0.3) + 0.0813312
        self.comparedigidir0 = math.log( 1 - self.retroratio) + 0.
        self.comparedigidir4 = math.log( 1 - self.retroratio) + 4.
        self.comparedigiref4 = math.log(self.retroratio) + 4.
        self.parnum = 6
        self.sigma = 5.
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
    def returnvalue(self,invalue):
        g = 0.
        for hit in self.allhitinfo.hitinfolist:
           toferrornoretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_position_pmt)
           if math.fabs(toferrornoretro) < self.sigma:
               continue
           toferroronretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_fly_retro)
           if math.fabs(toferroronretro) < self.sigma:
               continue
           g+=self.comparedigidir0
        return g
    def GetMinimizedvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        return 0.
    def GetTruevalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(0)",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(1)",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(2)",ievent)[0]
        if parnum == 3:
            return -self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTriggerTime()",ievent)[0]
        if parnum == 4:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.CosTheta()
        if parnum == 5:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.Phi()

class goodnesscomparedigitalref4only:
    def __init__(self,fm):
        self.fm = fm
        self.reflectivity = float(self.fm.GetTag("ReflectivityFactorTrapezoidReflectivity"))
        self.retroratio = 2.51128285714285748e-01*(self.reflectivity - 0.3) + 0.0813312
        self.comparedigidir0 = math.log( 1 - self.retroratio) + 0.
        self.comparedigidir4 = math.log( 1 - self.retroratio) + 4.
        self.comparedigiref4 = math.log(self.retroratio) + 4.
        self.parnum = 6
        self.sigma = 5.
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
    def returnvalue(self,invalue):
        g = 0.
        for hit in self.allhitinfo.hitinfolist:
           toferrornoretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_position_pmt)
           if math.fabs(toferrornoretro) < self.sigma:
               continue
           toferroronretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_fly_retro)
           if math.fabs(toferroronretro) < self.sigma:
               g += self.comparedigiref4
               continue
        return g
    def GetMinimizedvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        return 0.
    def GetTruevalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(0)",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(1)",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(2)",ievent)[0]
        if parnum == 3:
            return -self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTriggerTime()",ievent)[0]
        if parnum == 4:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.CosTheta()
        if parnum == 5:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.Phi()

class goodnesscompare:
    def __init__(self,fm):
        self.fm = fm
        self.parnum = 6
        self.sigma = 5.
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
    def returnvalue(self,invalue):
        g = 0.
        for hit in self.allhitinfo.hitinfolist:
            resnoretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_position_pmt)/self.sigma
            resonretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_fly_retro)/self.sigma
            if math.fabs(resnoretro) < math.fabs(resonretro):
                g+= math.exp(-resnoretro*resnoretro/2.)
            else:
                g+= math.exp(-resonretro*resonretro/2.)
        return g
    def GetMinimizedvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        return 0.
    def GetTruevalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(0)",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(1)",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(2)",ievent)[0]
        if parnum == 3:
            return -self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTriggerTime()",ievent)[0]
        if parnum == 4:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.CosTheta()
        if parnum == 5:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.Phi()

class goodnesscompareretroonlytrueretrolike:
    def __init__(self,fm):
        self.fm = fm
        self.parnum = 6
        self.sigma = 5.
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
        self.invaluetrue = []
        for i in range(self.parnum):
            self.invaluetrue.append(self.GetTruevalue(i,ievent))
    def returnvalue(self,invalue):
        g = 0.
        for hit in self.allhitinfo.hitinfolist:
            vectrue = macro.Vector3()
            vectrue.SetMagCosThetaPhi(1.,self.invaluetrue[4],self.invaluetrue[5])
            vechit = hit.Get3Position() - macro.Vector3(invalue[4],invalue[5])
            anglecos = vectrue.AngleCos(vechit)
            if anglecos > 0.:
                continue
            resonretrotrue = func.emittimebyonePMTminusTestemittime(hit,self.invaluetrue,func.distance_fly_retro)/self.sigma
            if math.fabs(resonretrotrue) > 4.:
                continue
            resnoretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_position_pmt)/self.sigma
            resonretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_fly_retro)/self.sigma
            if math.fabs(resnoretro) < math.fabs(resonretro):
                pass
            else:
                g+= math.exp(-resonretro*resonretro/2.)
        return g
    def GetMinimizedvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        return 0.
    def GetTruevalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(0)",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(1)",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(2)",ievent)[0]
        if parnum == 3:
            return -self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTriggerTime()",ievent)[0]
        if parnum == 4:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.CosTheta()
        if parnum == 5:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.Phi()

class goodnesscompareretroonly:
    def __init__(self,fm):
        self.fm = fm
        self.parnum = 6
        self.sigma = 5.
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
    def returnvalue(self,invalue):
        g = 0.
        for hit in self.allhitinfo.hitinfolist:
            resnoretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_position_pmt)/self.sigma
            resonretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_fly_retro)/self.sigma
            if math.fabs(resnoretro) < math.fabs(resonretro):
                pass
            else:
                g+= math.exp(-resonretro*resonretro/2.)
        return g
    def GetMinimizedvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        return 0.
    def GetTruevalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(0)",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(1)",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(2)",ievent)[0]
        if parnum == 3:
            return -self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTriggerTime()",ievent)[0]
        if parnum == 4:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.CosTheta()
        if parnum == 5:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.Phi()

class goodnesscomparedirectonly:
    def __init__(self,fm):
        self.fm = fm
        self.parnum = 6
        self.sigma = 5.
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
    def returnvalue(self,invalue):
        g = 0.
        for hit in self.allhitinfo.hitinfolist:
            resnoretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_position_pmt)/self.sigma
            resonretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_fly_retro)/self.sigma
            if math.fabs(resnoretro) > math.fabs(resonretro):
                pass
            else:
                g+= math.exp(-resnoretro*resnoretro/2.)
        return g
    def GetMinimizedvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        return 0.
    def GetTruevalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(0)",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(1)",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(2)",ievent)[0]
        if parnum == 3:
            return -self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTriggerTime()",ievent)[0]
        if parnum == 4:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.CosTheta()
        if parnum == 5:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.Phi()

class goodnesscomparedirectonlytruedirectlike:
    def __init__(self,fm):
        self.fm = fm
        self.parnum = 6
        self.sigma = 5.
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
        self.invaluetrue = []
        for i in range(self.parnum):
            self.invaluetrue.append(self.GetTruevalue(i,ievent))
    def returnvalue(self,invalue):
        g = 0.
        for hit in self.allhitinfo.hitinfolist:
            vectrue = macro.Vector3()
            vectrue.SetMagCosThetaPhi(1.,self.invaluetrue[4],self.invaluetrue[5])
            vechit = hit.Get3Position() - macro.Vector3(invalue[4],invalue[5])
            anglecos = vectrue.AngleCos(vechit)
            if anglecos < 0.:
                continue
            resnoretrotrue = func.emittimebyonePMTminusTestemittime(hit,self.invaluetrue,func.distance_position_pmt)/self.sigma
            if math.fabs(resnoretrotrue) > 4.:
                continue
            resnoretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_position_pmt)/self.sigma
            resonretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_fly_retro)/self.sigma
            if math.fabs(resnoretro) > math.fabs(resonretro):
                pass
            else:
                g+= math.exp(-resnoretro*resnoretro/2.)
        return g
    def GetMinimizedvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        return 0.
    def GetTruevalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(0)",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(1)",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(2)",ievent)[0]
        if parnum == 3:
            return -self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTriggerTime()",ievent)[0]
        if parnum == 4:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.CosTheta()
        if parnum == 5:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.Phi()

class goodnesscompareretroonlytruedirectlike:
    def __init__(self,fm):
        self.fm = fm
        self.parnum = 6
        self.sigma = 5.
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
        self.invaluetrue = []
        for i in range(self.parnum):
            self.invaluetrue.append(self.GetTruevalue(i,ievent))
    def returnvalue(self,invalue):
        g = 0.
        for hit in self.allhitinfo.hitinfolist:
            vectrue = macro.Vector3()
            vectrue.SetMagCosThetaPhi(1.,self.invaluetrue[4],self.invaluetrue[5])
            vechit = hit.Get3Position() - macro.Vector3(invalue[4],invalue[5])
            anglecos = vectrue.AngleCos(vechit)
            if anglecos < 0.:
                continue
            resnoretrotrue = func.emittimebyonePMTminusTestemittime(hit,self.invaluetrue,func.distance_position_pmt)/self.sigma
            if math.fabs(resnoretrotrue) > 4.:
                continue
            resnoretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_position_pmt)/self.sigma
            resonretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_fly_retro)/self.sigma
            if math.fabs(resnoretro) < math.fabs(resonretro):
                pass
            else:
                g+= math.exp(-resonretro*resonretro/2.)
        return g
    def GetMinimizedvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        return 0.
    def GetTruevalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(0)",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(1)",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(2)",ievent)[0]
        if parnum == 3:
            return -self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTriggerTime()",ievent)[0]
        if parnum == 4:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.CosTheta()
        if parnum == 5:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.Phi()

class goodnesscomparedirectonlytrueretrolike:
    def __init__(self,fm):
        self.fm = fm
        self.parnum = 6
        self.sigma = 5.
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
        self.invaluetrue = []
        for i in range(self.parnum):
            self.invaluetrue.append(self.GetTruevalue(i,ievent))
    def returnvalue(self,invalue):
        g = 0.
        for hit in self.allhitinfo.hitinfolist:
            vectrue = macro.Vector3()
            vectrue.SetMagCosThetaPhi(1.,self.invaluetrue[4],self.invaluetrue[5])
            vechit = hit.Get3Position() - macro.Vector3(invalue[4],invalue[5])
            anglecos = vectrue.AngleCos(vechit)
            if anglecos > 0.:
                continue
            resonretrotrue = func.emittimebyonePMTminusTestemittime(hit,self.invaluetrue,func.distance_fly_retro)/self.sigma
            if math.fabs(resonretrotrue) > 4.:
                continue
            resnoretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_position_pmt)/self.sigma
            resonretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_fly_retro)/self.sigma
            if math.fabs(resnoretro) > math.fabs(resonretro):
                pass
            else:
                g+= math.exp(-resnoretro*resnoretro/2.)
        return g
    def GetMinimizedvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        return 0.
    def GetTruevalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(0)",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(1)",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(2)",ievent)[0]
        if parnum == 3:
            return -self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTriggerTime()",ievent)[0]
        if parnum == 4:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.CosTheta()
        if parnum == 5:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.Phi()

class goodnesscomparedirectonlytrueothers:
    def __init__(self,fm):
        self.fm = fm
        self.parnum = 6
        self.sigma = 5.
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
        self.invaluetrue = []
        for i in range(self.parnum):
            self.invaluetrue.append(self.GetTruevalue(i,ievent))
    def returnvalue(self,invalue):
        g = 0.
        for hit in self.allhitinfo.hitinfolist:
            vectrue = macro.Vector3()
            vectrue.SetMagCosThetaPhi(1.,self.invaluetrue[4],self.invaluetrue[5])
            vechit = hit.Get3Position() - macro.Vector3(invalue[4],invalue[5])
            anglecos = vectrue.AngleCos(vechit)
            if anglecos < 0.:
                resonretrotrue = func.emittimebyonePMTminusTestemittime(hit,self.invaluetrue,func.distance_fly_retro)/self.sigma
                if math.fabs(resonretrotrue) < 4.:
                    continue
            if anglecos > 0.:
                resnoretrotrue = func.emittimebyonePMTminusTestemittime(hit,self.invaluetrue,func.distance_position_pmt)/self.sigma
                if math.fabs(resnoretrotrue) < 4.:
                    continue
            resnoretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_position_pmt)/self.sigma
            resonretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_fly_retro)/self.sigma
            if math.fabs(resnoretro) > math.fabs(resonretro):
                pass
            else:
                g+= math.exp(-resnoretro*resnoretro/2.)
        return g
    def GetMinimizedvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        return 0.
    def GetTruevalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(0)",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(1)",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(2)",ievent)[0]
        if parnum == 3:
            return -self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTriggerTime()",ievent)[0]
        if parnum == 4:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.CosTheta()
        if parnum == 5:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.Phi()

class goodnesscompareretroonlytrueothers:
    def __init__(self,fm):
        self.fm = fm
        self.parnum = 6
        self.sigma = 5.
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
        self.invaluetrue = []
        for i in range(self.parnum):
            self.invaluetrue.append(self.GetTruevalue(i,ievent))
    def returnvalue(self,invalue):
        g = 0.
        for hit in self.allhitinfo.hitinfolist:
            vectrue = macro.Vector3()
            vectrue.SetMagCosThetaPhi(1.,self.invaluetrue[4],self.invaluetrue[5])
            vechit = hit.Get3Position() - macro.Vector3(invalue[4],invalue[5])
            anglecos = vectrue.AngleCos(vechit)
            if anglecos < 0.:
                resonretrotrue = func.emittimebyonePMTminusTestemittime(hit,self.invaluetrue,func.distance_fly_retro)/self.sigma
                if math.fabs(resonretrotrue) < 4.:
                    continue
            if anglecos > 0.:
                resnoretrotrue = func.emittimebyonePMTminusTestemittime(hit,self.invaluetrue,func.distance_position_pmt)/self.sigma
                if math.fabs(resnoretrotrue) < 4.:
                    continue
            resnoretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_position_pmt)/self.sigma
            resonretro = func.emittimebyonePMTminusTestemittime(hit,invalue,func.distance_fly_retro)/self.sigma
            if math.fabs(resnoretro) < math.fabs(resonretro):
                pass
            else:
                g+= math.exp(-resonretro*resonretro/2.)
        return g
    def GetMinimizedvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        return 0.
    def GetTruevalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(0)",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(1)",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(2)",ievent)[0]
        if parnum == 3:
            return -self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTriggerTime()",ievent)[0]
        if parnum == 4:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.CosTheta()
        if parnum == 5:
            truedirx = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(0)",ievent)[0]
            truediry = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(1)",ievent)[0]
            truedirz = self.fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetPdir(2)",ievent)[0]
            direction = ROOT.TVector3(truedirx,truediry,truedirz)
            return direction.Phi()
