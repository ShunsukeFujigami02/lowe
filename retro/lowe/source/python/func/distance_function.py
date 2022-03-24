import math
import ROOT
import macro

def distance_position_pmt(hitinfo,invalue):
    pmt = hitinfo.Get3Position()
    position = macro.Vector3(invalue[0],invalue[1],invalue[2])
    p_p = pmt - position
    return math.sqrt(p_p*p_p)

def distance_position_retro(hitinfo,invalue):
    positionx = invalue[0]
    positiony = invalue[1]
    positionz = invalue[2]
    pmtx = hitinfo.Get3Position().x
    pmty = hitinfo.Get3Position().y
    pmtz = hitinfo.Get3Position().z
    WCradius = hitinfo.WCradius
    sqrtpmt= math.sqrt(pmtx*pmtx + pmty*pmty)
    if WCradius < sqrtpmt:
        pmtx = pmtx*WCradius/sqrtpmt
        pmty = pmty*WCradius/sqrtpmt
    WClength = hitinfo.WClength
    half_WClength = WClength/2.
    a = (pmtx - positionx)*(pmtx - positionx) + (pmty - positiony) * (pmty - positiony)
    b = positionx * (positionx - pmtx) + positiony* (positiony - pmty)
    c = positionx * positionx + positiony * positiony - WCradius* WCradius
    t = 0.
    if a != 0.:
        t = (b-math.sqrt(b*b-a*c))/a
    else:
        t = -c/(2*b)
    z = positionz + (pmtz - positionz)*t
    if (-half_WClength < z ) and (half_WClength > z):
        pass
    elif z > half_WClength:
        t = (half_WClength - positionz)/(pmtz - positionz)
        z = half_WClength
    else:
        t = (-half_WClength - positionz)/(pmtz - positionz)
        z = - half_WClength
    x = positionx + (pmtx - positionx)*t
    y = positiony + (pmty - positiony)*t
    d2 = math.sqrt((positionx - x)*(positionx - x) + (positiony - y)*(positiony - y) + (positionz - z) * (positionz - z))
    return d2

def distance_fly_retro(hitinfo,invalue):
    d_p_p = distance_position_pmt(hitinfo,invalue)
    d_p_r = distance_position_retro(hitinfo,invalue)
    return (d_p_p + 2* d_p_r)

dfunctiondict = {}
