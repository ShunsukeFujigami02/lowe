import macro
import math
import func
import ROOT

class minimizedfuncnoretro:
    def __init__(self,fm):
        self.fm = fm
        self.parnum = 6
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
    def returnvalue(self,invalue):
        l = 0.
        for hit in self.allhitinfo.hitinfolist:
            l += math.log(func.cherenkovangleerrorfunc(hit,invalue))
            l += func.toferrorlog(hit,invalue,func.emittimebyonePMTminusTestemittime,func.distance_position_pmt)
        return -l
    def Getfirstvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        if parnum == 4:
            return self.fm.GetValue("likelihoodT.reconstructdatalikelihood.Getdirection().CosTheta()",ievent)[0]
        if parnum == 5:
           return self.fm.GetValue("likelihoodT.reconstructdatalikelihood.Getdirection().Phi()",ievent)[0]
    def GetMinimizedvalue(self,parnum,ievent):
        return self.fm.GetValue("minimizeT.reconstructdataminimize.GetParameters(" + str(parnum) + ")",ievent)[0]
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

class minimizedfuncnoretromodifycostheta:
    def __init__(self,fm):
        self.fm = fm
        self.parnum = 6
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
    def returnvalue(self,invalue):
        ltime = 0.
        langle = 0.
        invaluecopyed = invalue
        if invalue[4] > 1. and invalue[4] < 3.:
            invaluecopyed[4] = 2 - invalue[4]
            invaluecopyed[5] = invalue[5] + macro.PI
        elif invalue[4] < -1. and invalue[4] > -3.:
            invaluecopyed[4] = -2 - invalue[4]
            invaluecopyed[5] = invalue[5] + macro.PI
        for hit in self.allhitinfo.hitinfolist:
            plangle = math.log(func.cherenkovangleerrorfunc(hit,invaluecopyed))
            langle += plangle
            ltime += func.toferrorlog(hit,invaluecopyed,func.emittimebyonePMTminusTestemittime,func.distance_position_pmt)
        return (-ltime - langle)
    def Getfirstvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        if parnum == 4:
            return self.fm.GetValue("likelihoodT.reconstructdatalikelihood.Getdirection().CosTheta()",ievent)[0]
        if parnum == 5:
           return self.fm.GetValue("likelihoodT.reconstructdatalikelihood.Getdirection().Phi()",ievent)[0]
    def GetMinimizedvalue(self,parnum,ievent):
        return self.fm.GetValue("minimizeT.reconstructdataminimize.GetParameter(" + str(parnum) + ")",ievent)[0]
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

class minimizedfuncnoretroseparatehitanddarkrate:
    def __init__(self,fm):
        self.fm = fm
        self.parnum = 6
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
        self.ncherenkovdigihits = len(self.allhitinfo.hitinfolist)
        self.hitnumexpected = self.ncherenkovdigihits - 63.19782
        if self.hitnumexpected < 1.:
            self.hitnumexpected = 1.
    def returnvalue(self,invalue):
        l = 0.
        invaluecopyed = invalue
        if invalue[4] > 1. and invalue[4] < 3.:
            invaluecopyed[4] = 2 - invalue[4]
            invaluecopyed[5] = invalue[5] + macro.PI
        elif invalue[4] < -1. and invalue[4] > -3.:
            invaluecopyed[4] = -2 - invalue[4]
            invaluecopyed[5] = invalue[5] + macro.PI
        for hit in self.allhitinfo.hitinfolist:
            l += math.log(self.hitnumexpected * func.toferrornodarkrate(hit,invaluecopyed,func.emittimebyonePMTminusTestemittime,func.distance_position_pmt) * func.cherenkovangleerrorfuncnodarkrate(hit,invaluecopyed) + 2.1e-6)
        return -l
    def Getfirstvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        if parnum == 4:
            return self.fm.GetValue("likelihoodT.reconstructdatalikelihood.Getdirection().CosTheta()",ievent)[0]
        if parnum == 5:
           return self.fm.GetValue("likelihoodT.reconstructdatalikelihood.Getdirection().Phi()",ievent)[0]
    def GetMinimizedvalue(self,parnum,ievent):
        return self.fm.GetValue("minimizeT.reconstructdataminimize.GetParameter(" + str(parnum) + ")",ievent)[0]
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


class minimizedfuncnoretroadddarkratenum:
    def __init__(self,fm):
        self.fm = fm
        self.parnum = 7
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
        self.ncherenkovdigihits = len(self.allhitinfo.hitinfolist)
        self.expecteddarkrate = 63.19782
    def returnvalue(self,invalue):
        l = 0.
        invaluecopyed = invalue
        if invalue[4] > 1. and invalue[4] < 3.:
            invaluecopyed[4] = 2 - invalue[4]
            invaluecopyed[5] = invalue[5] + macro.PI
        elif invalue[4] < -1. and invalue[4] > -3.:
            invaluecopyed[4] = -2 - invalue[4]
            invaluecopyed[5] = invalue[5] + macro.PI
        hitnumexpected = self.ncherenkovdigihits - invalue[6]
        if hitnumexpected < 1.:
            hitnumexpected = 1.
        for hit in self.allhitinfo.hitinfolist:
            l += math.log(hitnumexpected * func.toferrornodarkrate(hit,invaluecopyed,func.emittimebyonePMTminusTestemittime,func.distance_position_pmt) * func.cherenkovangleerrorfuncnodarkrate(hit,invaluecopyed) + invalue[6]*3.3229e-8)
        if self.ncherenkovdigihits != 0:
            lgamma = 0.
            if invalue[6] > 0.:
                lgamma = math.lgamma(invalue[6] + 1)
            l += (-self.expecteddarkrate + invalue[6]* math.log(self.expecteddarkrate) - lgamma)
        return -l
    def Getfirstvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        if parnum == 4:
            return self.fm.GetValue("likelihoodT.reconstructdatalikelihood.Getdirection().CosTheta()",ievent)[0]
        if parnum == 5:
            return self.fm.GetValue("likelihoodT.reconstructdatalikelihood.Getdirection().Phi()",ievent)[0]
        if parnum == 6:
            return self.expecteddarkrate
       
    def GetMinimizedvalue(self,parnum,ievent):
        return self.fm.GetValue("minimizeT.reconstructdataminimize.GetParameter(" + str(parnum) + ")",ievent)[0]
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
        if parnum == 6:
            return self.expecteddarkrate

class minimizedfuncnoretroadddarkratenumaddacceptance:
    def __init__(self,fm):
        self.fm = fm
        self.parnum = 7
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
        self.ncherenkovdigihits = len(self.allhitinfo.hitinfolist)
        self.expecteddarkrate = 63.19782
    def returnvalue(self,invalue):
        l = 0.
        invaluecopyed = invalue
        if invalue[4] > 1. and invalue[4] < 3.:
            invaluecopyed[4] = 2 - invalue[4]
            invaluecopyed[5] = invalue[5] + macro.PI
        elif invalue[4] < -1. and invalue[4] > -3.:
            invaluecopyed[4] = -2 - invalue[4]
            invaluecopyed[5] = invalue[5] + macro.PI
        hitnumexpected = self.ncherenkovdigihits - invalue[6]
        if hitnumexpected < 1.:
            hitnumexpected = 1.
        for hit in self.allhitinfo.hitinfolist:
            costheta = pmtcostheta(hit,invaluecopyed)
            if costheta < 0.:
                costheta = 0.
            l += math.log(hitnumexpected * func.toferrornodarkrate(hit,invaluecopyed,func.emittimebyonePMTminusTestemittime,func.distance_position_pmt) * func.cherenkovangleerrorfuncnodarkrate(hit,invaluecopyed) * costheta + invalue[6]*3.3229e-8/2.)
        if self.ncherenkovdigihits != 0:
            lgamma = 1.
            if invalue[6] > 0.:
                lgamma = math.lgamma(invalue[6] + 1)
            l += (-self.expecteddarkrate + invalue[6]* math.log(self.expecteddarkrate) - lgamma)
        return -l
    def Getfirstvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        if parnum == 4:
            return self.fm.GetValue("likelihoodT.reconstructdatalikelihood.Getdirection().CosTheta()",ievent)[0]
        if parnum == 5:
            return self.fm.GetValue("likelihoodT.reconstructdatalikelihood.Getdirection().Phi()",ievent)[0]
        if parnum == 6:
            return self.expecteddarkrate
       
    def GetMinimizedvalue(self,parnum,ievent):
        return self.fm.GetValue("minimizeT.reconstructdataminimize.GetParameter(" + str(parnum) + ")",ievent)[0]
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
        if parnum == 6:
            return self.expecteddarkrate

class minimizedfuncnoretroseparatehitanddarkratever2:
    def __init__(self,fm):
        self.fm = fm
        self.parnum = 6
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
        self.ncherenkovdigihits = len(self.allhitinfo.hitinfolist)
        self.hitnumexpected = self.ncherenkovdigihits - 63.19782
        if self.hitnumexpected < 1.:
            self.hitnumexpected = 1.
    def returnvalue(self,invalue):
        l = 0.
        invaluecopyed = invalue
        if invalue[4] > 1. and invalue[4] < 3.:
            invaluecopyed[4] = 2 - invalue[4]
            invaluecopyed[5] = invalue[5] + macro.PI
        elif invalue[4] < -1. and invalue[4] > -3.:
            invaluecopyed[4] = -2 - invalue[4]
            invaluecopyed[5] = invalue[5] + macro.PI
        for hit in self.allhitinfo.hitinfolist:
            l += math.log(self.hitnumexpected * func.toferrornodarkratever2(hit,invaluecopyed,func.emittimebyonePMTminusTestemittime,func.distance_position_pmt) * func.cherenkovangleerrorfuncnodarkratever2(hit,invaluecopyed) + 2.1e-6)
        return -l
    def Getfirstvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        if parnum == 4:
            return self.fm.GetValue("likelihoodT.reconstructdatalikelihood.Getdirection().CosTheta()",ievent)[0]
        if parnum == 5:
           return self.fm.GetValue("likelihoodT.reconstructdatalikelihood.Getdirection().Phi()",ievent)[0]
    def GetMinimizedvalue(self,parnum,ievent):
        return self.fm.GetValue("minimizeT.reconstructdataminimize.GetParameter(" + str(parnum) + ")",ievent)[0]
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


class minimizedfuncnoretroadddarkratenumver2:
    def __init__(self,fm):
        self.fm = fm
        self.parnum = 7
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
        self.ncherenkovdigihits = len(self.allhitinfo.hitinfolist)
        self.expecteddarkrate = 63.19782
    def returnvalue(self,invalue):
        l = 0.
        invaluecopyed = invalue
        if invalue[4] > 1. and invalue[4] < 3.:
            invaluecopyed[4] = 2 - invalue[4]
            invaluecopyed[5] = invalue[5] + macro.PI
        elif invalue[4] < -1. and invalue[4] > -3.:
            invaluecopyed[4] = -2 - invalue[4]
            invaluecopyed[5] = invalue[5] + macro.PI
        hitnumexpected = self.ncherenkovdigihits - invalue[6]
        if hitnumexpected < 1.:
            hitnumexpected = 1.
        for hit in self.allhitinfo.hitinfolist:
            l += math.log(hitnumexpected * func.toferrornodarkratever2(hit,invaluecopyed,func.emittimebyonePMTminusTestemittime,func.distance_position_pmt) * func.cherenkovangleerrorfuncnodarkratever2(hit,invaluecopyed) + invalue[6]*3.3229e-8)
        if self.ncherenkovdigihits != 0:
            lgamma = 0.
            if invalue[6] > 0.:
                lgamma = math.lgamma(invalue[6] + 1)
            l += (-self.expecteddarkrate + invalue[6]* math.log(self.expecteddarkrate) - lgamma)
        return -l
    def Getfirstvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        if parnum == 4:
            return self.fm.GetValue("likelihoodT.reconstructdatalikelihood.Getdirection().CosTheta()",ievent)[0]
        if parnum == 5:
            return self.fm.GetValue("likelihoodT.reconstructdatalikelihood.Getdirection().Phi()",ievent)[0]
        if parnum == 6:
            return self.expecteddarkrate
       
    def GetMinimizedvalue(self,parnum,ievent):
        return self.fm.GetValue("minimizeT.reconstructdataminimize.GetParameter(" + str(parnum) + ")",ievent)[0]
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
        if parnum == 6:
            return self.expecteddarkrate

class minimizedfuncnoretroadddarkratenumaddacceptancever2:
    def __init__(self,fm):
        self.fm = fm
        self.parnum = 7
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
        self.ncherenkovdigihits = len(self.allhitinfo.hitinfolist)
        self.expecteddarkrate = 63.19782
    def returnvalue(self,invalue):
        l = 0.
        invaluecopyed = invalue
        if invalue[4] > 1. and invalue[4] < 3.:
            invaluecopyed[4] = 2 - invalue[4]
            invaluecopyed[5] = invalue[5] + macro.PI
        elif invalue[4] < -1. and invalue[4] > -3.:
            invaluecopyed[4] = -2 - invalue[4]
            invaluecopyed[5] = invalue[5] + macro.PI
        hitnumexpected = self.ncherenkovdigihits - invalue[6]
        if hitnumexpected < 1.:
            hitnumexpected = 1.
        for hit in self.allhitinfo.hitinfolist:
            costheta = pmtcostheta(hit,invaluecopyed)
            if costheta < 0.:
                costheta = 0.
            l += math.log(hitnumexpected * func.toferrornodarkratever2(hit,invaluecopyed,func.emittimebyonePMTminusTestemittime,func.distance_position_pmt) * func.cherenkovangleerrorfuncnodarkratever2(hit,invaluecopyed) * costheta + invalue[6]*3.3229e-8/2.)
        if self.ncherenkovdigihits != 0:
            lgamma = 1.
            if invalue[6] > 0.:
                lgamma = math.lgamma(invalue[6] + 1)
            l += (-self.expecteddarkrate + invalue[6]* math.log(self.expecteddarkrate) - lgamma)
        return -l
    def Getfirstvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        if parnum == 4:
            return self.fm.GetValue("likelihoodT.reconstructdatalikelihood.Getdirection().CosTheta()",ievent)[0]
        if parnum == 5:
            return self.fm.GetValue("likelihoodT.reconstructdatalikelihood.Getdirection().Phi()",ievent)[0]
        if parnum == 6:
            return self.expecteddarkrate
       
    def GetMinimizedvalue(self,parnum,ievent):
        return self.fm.GetValue("minimizeT.reconstructdataminimize.GetParameter(" + str(parnum) + ")",ievent)[0]
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
        if parnum == 6:
            return self.expecteddarkrate

class minimizedfunconretroadddarkratenumaddacceptance:
    def __init__(self,fm):
        self.fm = fm
        reflectivity = float(self.fm.GetTag("ReflectivityFactorTrapezoidReflectivity"))
        self.retroratio = 2.51128285714285748e-01*(reflectivity - 0.3) + 0.0813312
        self.parnum = 7
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
        self.ncherenkovdigihits = len(self.allhitinfo.hitinfolist)
        self.expecteddarkrate = 63.19782
    def returnvalue(self,invalue):
        l = 0.
        invaluecopyed = invalue
        if invalue[4] > 1. and invalue[4] < 3.:
            invaluecopyed[4] = 2 - invalue[4]
            invaluecopyed[5] = invalue[5] + macro.PI
        elif invalue[4] < -1. and invalue[4] > -3.:
            invaluecopyed[4] = -2 - invalue[4]
            invaluecopyed[5] = invalue[5] + macro.PI
        hitnumexpected = self.ncherenkovdigihits - invalue[6]
        if hitnumexpected < 1.:
            hitnumexpected = 1.
        for hit in self.allhitinfo.hitinfolist:
            costheta = pmtcostheta(hit,invaluecopyed)
            if costheta < 0.:
                costheta = 0.
            l += math.log(hitnumexpected * (func.toferrornodarkrateOnretroDir(hit,invaluecopyed,func.emittimebyonePMTminusTestemittime,func.distance_position_pmt,self.retroratio) * func.cherenkovangleerrorfuncnodarkrateOnretroDir(hit,invaluecopyed,self.retroratio) + func.toferrornodarkrateOnretroRef(hit,invaluecopyed,func.emittimebyonePMTminusTestemittime,func.distance_fly_retro,self.retroratio) * func.cherenkovangleerrorfuncnodarkrateOnretroRef(hit,invaluecopyed,self.retroratio))* costheta + invalue[6]*3.3229e-8/2.)
        if self.ncherenkovdigihits != 0:
            lgamma = 1.
            if invalue[6] > 0.:
                lgamma = math.lgamma(invalue[6] + 1)
            l += (-self.expecteddarkrate + invalue[6]* math.log(self.expecteddarkrate) - lgamma)
        return -l
    def GetDirectPart(self,invalue):
        l = 0.
        invaluecopyed = invalue
        if invalue[4] > 1. and invalue[4] < 3.1:
            invaluecopyed[4] = 2 - invalue[4]
            invaluecopyed[5] = invalue[5] + macro.PI
        elif invalue[4] < -1. and invalue[4] > -3.1:
            invaluecopyed[4] = -2 - invalue[4]
            invaluecopyed[5] = invalue[5] + macro.PI
        hitnumexpected = self.ncherenkovdigihits - invalue[6]
        if hitnumexpected < 1.:
            hitnumexpected = 1.
        if invalue[6] < 1.:
            invaluecopyed[6] = 1.
        for hit in self.allhitinfo.hitinfolist:
            costheta = pmtcostheta(hit,invaluecopyed)
            if costheta < 0.:
                costheta = 0.
            DirPart = hitnumexpected * func.toferrornodarkrateOnretroDir(hit,invaluecopyed,func.emittimebyonePMTminusTestemittime,func.distance_position_pmt,self.retroratio) * func.cherenkovangleerrorfuncnodarkrateOnretroDir(hit,invaluecopyed,self.retroratio) * costheta
            RefPart = hitnumexpected * func.toferrornodarkrateOnretroRef(hit,invaluecopyed,func.emittimebyonePMTminusTestemittime,func.distance_fly_retro,self.retroratio) * func.cherenkovangleerrorfuncnodarkrateOnretroRef(hit,invaluecopyed,self.retroratio)* costheta
            DarkPart = invaluecopyed[6]*3.3229e-8/2.
            l+= (DirPart/(DirPart + RefPart + DarkPart))*math.log(DirPart + RefPart + DarkPart)
        return -l
    def GetReflectPart(self,invalue):
        l = 0.
        invaluecopyed = invalue
        if invalue[4] > 1. and invalue[4] < 3.1:
            invaluecopyed[4] = 2 - invalue[4]
            invaluecopyed[5] = invalue[5] + macro.PI
        elif invalue[4] < -1. and invalue[4] > -3.1:
            invaluecopyed[4] = -2 - invalue[4]
            invaluecopyed[5] = invalue[5] + macro.PI
        hitnumexpected = self.ncherenkovdigihits - invalue[6]
        if hitnumexpected < 1.:
            hitnumexpected = 1.
        if invalue[6] < 1.:
            invaluecopyed[6] = 1.
        for hit in self.allhitinfo.hitinfolist:
            costheta = pmtcostheta(hit,invaluecopyed)
            if costheta < 0.:
                costheta = 0.
            DirPart = hitnumexpected * func.toferrornodarkrateOnretroDir(hit,invaluecopyed,func.emittimebyonePMTminusTestemittime,func.distance_position_pmt,self.retroratio) * func.cherenkovangleerrorfuncnodarkrateOnretroDir(hit,invaluecopyed,self.retroratio)*costheta
            RefPart = hitnumexpected * func.toferrornodarkrateOnretroRef(hit,invaluecopyed,func.emittimebyonePMTminusTestemittime,func.distance_fly_retro,self.retroratio) * func.cherenkovangleerrorfuncnodarkrateOnretroRef(hit,invaluecopyed,self.retroratio)* costheta
            DarkPart = invaluecopyed[6]*3.3229e-8/2.
            l+= (RefPart/(DirPart + RefPart + DarkPart))*math.log(DirPart + RefPart + DarkPart)
        return -l
    def GetDarkPart(self,invalue):
        l = 0.
        invaluecopyed = invalue
        if invalue[4] > 1. and invalue[4] < 3.1:
            invaluecopyed[4] = 2 - invalue[4]
            invaluecopyed[5] = invalue[5] + macro.PI
        elif invalue[4] < -1. and invalue[4] > -3.1:
            invaluecopyed[4] = -2 - invalue[4]
            invaluecopyed[5] = invalue[5] + macro.PI
        hitnumexpected = self.ncherenkovdigihits - invalue[6]
        if hitnumexpected < 1.:
            hitnumexpected = 1.
        if invalue[6] < 1.:
            invaluecopyed[6] = 1.
        for hit in self.allhitinfo.hitinfolist:
            costheta = pmtcostheta(hit,invaluecopyed)
            if costheta < 0.:
                costheta = 0.
            DirPart = hitnumexpected * func.toferrornodarkrateOnretroDir(hit,invaluecopyed,func.emittimebyonePMTminusTestemittime,func.distance_position_pmt,self.retroratio) * func.cherenkovangleerrorfuncnodarkrateOnretroDir(hit,invaluecopyed,self.retroratio)*costheta
            RefPart = hitnumexpected * func.toferrornodarkrateOnretroRef(hit,invaluecopyed,func.emittimebyonePMTminusTestemittime,func.distance_fly_retro,self.retroratio) * func.cherenkovangleerrorfuncnodarkrateOnretroRef(hit,invaluecopyed,self.retroratio)* costheta
            DarkPart = invaluecopyed[6]*3.3229e-8/2.
            l+= (DarkPart/(DirPart + RefPart + DarkPart))*math.log(DirPart + RefPart + DarkPart)
        return -l

    def Getfirstvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        if parnum == 4:
            return self.fm.GetValue("likelihoodT.reconstructdatalikelihood.Getdirection().CosTheta()",ievent)[0]
        if parnum == 5:
            return self.fm.GetValue("likelihoodT.reconstructdatalikelihood.Getdirection().Phi()",ievent)[0]
        if parnum == 6:
            return self.expecteddarkrate
       
    def GetMinimizedvalue(self,parnum,ievent):
        return self.fm.GetValue("minimizeT.reconstructdataminimize.GetParameter(" + str(parnum) + ")",ievent)[0]
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
        if parnum == 6:
            return self.expecteddarkrate

class minimizedfuncnoretroadddarkratenumaddacceptanceseparatecostheta:
    def __init__(self,fm):
        self.fm = fm
        self.parnum = 7
    def SetAllhitinfo(self,ievent):
        self.allhitinfo = macro.allhitinfo(self.fm,ievent)
        self.ncherenkovdigihits = len(self.allhitinfo.hitinfolist)
        self.expecteddarkrate = 63.19782
    def returnvalue(self,invalue):
        l = 0.
        invaluecopyed = invalue
        if invalue[4] > 1. and invalue[4] < 3.:
            invaluecopyed[4] = 2 - invalue[4]
            invaluecopyed[5] = invalue[5] + macro.PI
        elif invalue[4] < -1. and invalue[4] > -3.:
            invaluecopyed[4] = -2 - invalue[4]
            invaluecopyed[5] = invalue[5] + macro.PI
        hitnumexpected = self.ncherenkovdigihits - invalue[6]
        if hitnumexpected < 1.:
            hitnumexpected = 1.
        for hit in self.allhitinfo.hitinfolist:
            costheta = pmtcostheta(hit,invaluecopyed)
            if costheta < 0.:
                costheta = 0.
            l += math.log(hitnumexpected * ( func.toferrornodarkratesharp(hit,invaluecopyed,func.emittimebyonePMTminusTestemittime,func.distance_position_pmt) * func.cherenkovangleerrorfuncnodarkratesharp(hit,invaluecopyed) + func.toferrornodarkrateloose(hit,invaluecopyed,func.emittimebyonePMTminusTestemittime,func.distance_position_pmt) * func.cherenkovangleerrorfuncnodarkrateloose(hit,invaluecopyed)) * costheta + invalue[6]*3.3229e-8/2.)
        if self.ncherenkovdigihits != 0:
            lgamma = 1.
            if invalue[6] > 0.:
                lgamma = math.lgamma(invalue[6] + 1)
            l += (-self.expecteddarkrate + invalue[6]* math.log(self.expecteddarkrate) - lgamma)
        return -l
    def Getfirstvalue(self,parnum,ievent):
        if parnum == 0:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().X()",ievent)[0]
        if parnum == 1:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Y()",ievent)[0]
        if parnum == 2:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().Z()",ievent)[0]
        if parnum == 3:
            return self.fm.GetValue("goodnessT.reconstructdata.Get4Vector().T()",ievent)[0]
        if parnum == 4:
            return self.fm.GetValue("likelihoodT.reconstructdatalikelihood.Getdirection().CosTheta()",ievent)[0]
        if parnum == 5:
            return self.fm.GetValue("likelihoodT.reconstructdatalikelihood.Getdirection().Phi()",ievent)[0]
        if parnum == 6:
            return self.expecteddarkrate
       
    def GetMinimizedvalue(self,parnum,ievent):
        return self.fm.GetValue("minimizeT.reconstructdataminimize.GetParameter(" + str(parnum) + ")",ievent)[0]
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
        if parnum == 6:
            return self.expecteddarkrate

def pmtcostheta(hitinfo,invalue):
    vec = macro.Vector3(invalue[0],invalue[1],invalue[2]) - hitinfo.Get3Position()
    costheta = hitinfo.Get3Orientation().AngleCos(vec)
    return costheta
