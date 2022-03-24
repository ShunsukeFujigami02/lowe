import ROOT
import macro
import math

class hitinfo:
    def __init__(self,hit,geom):
        self.hittime = hit.GetT()
        self.tubeId = hit.GetTubeId()
        pmt = geom.GetPMT(self.tubeId - 1)
        WCradiustemp = geom.GetWCCylRadius()
        WClengthtemp = geom.GetWCCylLength()
        if math.fabs(WCradiustemp - macro.SKRadius) < 1.:
            self.WCradius = 1686.
        else:
            self.WCradius = WCradiustemp
        if math.fabs(WClengthtemp - macro.SKLength) < 1.:
            self.WClength = 3620.
        else:
            self.WClength = WClengthtemp
        self.pmtx = pmt.GetPosition(0)
        self.pmty = pmt.GetPosition(1)
        self.pmtz = pmt.GetPosition(2)
        self.orientx = pmt.GetOrientation(0)
        self.orienty = pmt.GetOrientation(1)
        self.orientz = pmt.GetOrientation(2)
    def Get3Position(self):
        return macro.Vector3(self.pmtx,self.pmty,self.pmtz)
    def Get3Orientation(self):
        return macro.Vector3(self.orientx,self.orienty,self.orientz)
    
class allhitinfo:
    def __init__(self,fm,event):
        self.hitinfolist = []
        wcsimrootgeom = fm.GetValue("wcsimGeoT.wcsimrootgeom",0)[0]
        WCradiustemp = wcsimrootgeom.GetWCCylRadius()
        WClengthtemp = wcsimrootgeom.GetWCCylLength()
        if math.fabs(WCradiustemp - macro.SKRadius) < 1.:
            self.WCradius = 1686.
        else:
            self.WCradius = WCradiustemp
        if math.fabs(WClengthtemp - macro.SKLength) < 1.:
            self.WClength = 3620.
        else:
            self.WClength = WClengthtemp
        wcsimroottrigger = fm.GetValue("wcsimT.wcsimrootevent.GetTrigger(0)",event)[0]
        self.ncherenkovdigihits = wcsimroottrigger.GetNcherenkovdigihits()
        for k in range(self.ncherenkovdigihits):
            hit = wcsimroottrigger.GetCherenkovDigiHits().At(k)
            self.hitinfolist.append(hitinfo(hit,wcsimrootgeom))
    
