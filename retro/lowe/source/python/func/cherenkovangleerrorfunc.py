import ROOT
import math
import macro

def cherenkovangleerrorfunc(hitinfo,invalue):
    a0 = 0.97648
    b0 = 3.51958
    a1 = 0.88353
    b1 = -3.52407
    vect = macro.Vector3()
    vect.SetMagCosThetaPhi(1.,invalue[4],invalue[5])
    hitvec = hitinfo.Get3Position() - macro.Vector3(invalue[0],invalue[1],invalue[2])
    costheta = (hitvec * vect)/((hitvec.Mag())*(vect.Mag()))
    if costheta < 0.75:
        return (1 + a0 * (math.exp(b0 * (costheta - 0.75 )) -1))
    else:
        return (1 + a1 * (math.exp(b1 * (costheta - 0.75 )) - 1))

def cherenkovangleerrorfuncnodarkrate(hitinfo,invalue):
    vect = macro.Vector3()
    vect.SetMagCosThetaPhi(1.,invalue[4],invalue[5])
    hitvec = hitinfo.Get3Position() - macro.Vector3(invalue[0],invalue[1],invalue[2])
    costheta = (hitvec * vect)/((hitvec.Mag())*(vect.Mag())) 
    if costheta < 0.2:
        return math.exp(-6.31511678e+00 + 2.07887e+00 * costheta) + 7.40412636970511897e-04
    elif costheta < 0.732:
        return math.exp(-7.57641678e+00 + 4.35829e+00 * costheta) + 2.40447334220583600e-03
    elif costheta < 0.7605:
        s = (costheta - 7.46527e-01)/1.05105e-02
        return 3.56181379527811190e-02* math.exp(-s*s/2.)
    else:
        return 3.92478266796359651e-02 + -3.15646023267431991e-02*costheta

def cherenkovangleerrorfuncnodarkratever2(hitinfo,invalue):
    vect = macro.Vector3()
    vect.SetMagCosThetaPhi(1.,invalue[4],invalue[5])
    hitvec = hitinfo.Get3Position() - macro.Vector3(invalue[0],invalue[1],invalue[2])
    costheta = (hitvec * vect)/((hitvec.Mag())*(vect.Mag())) 
    if costheta < 0.2:
        return math.exp(-6.326106061e+00 + 2.21102e+00 * costheta) + 3.56527787154126445e-03 - math.exp(-6.326106061e+00 + 2.21102e+00 * 0.2)
    elif costheta < 0.734:
        return math.exp(-7.25356606128095915e+00 + 3.90134e+00 * costheta) + 1.44221009587363787e-02 - math.exp(-7.25356606128095915e+00 + 3.90134e+00 * 0.734)
    elif costheta < 0.7594:
        s = (costheta - 7.46966e-01)/9.45515e-03
        return 3.69283432565277667e-02 * math.exp(-s*s/2.)
    else:
        return -3.31248733512162150e-02 * (costheta - 0.7594) + 1.55531680686258611e-02

def cherenkovangleerrorfuncnodarkrateOnretroDir(hitinfo,invalue,retroratio):
    vect = macro.Vector3()
    vect.SetMagCosThetaPhi(1.,invalue[4],invalue[5])
    hitvec = hitinfo.Get3Position() - macro.Vector3(invalue[0],invalue[1],invalue[2])
    costheta = (hitvec * vect)/((hitvec.Mag())*(vect.Mag()))
    I = 1.33729337950334557e+04
    NPMT = 11146
    afactor = (1/I)*math.sqrt((1-retroratio)/NPMT)
    sfactor = math.log(afactor)
    if costheta < 0.2:
        return math.exp(7.83420e+00 + 2.21102e+00 * costheta + sfactor) + 5.03361039235597582e+03*afactor - math.exp(7.83420e+00 + 2.21102e+00 * 0.2 + sfactor)
    elif costheta < 0.734:
        return math.exp(6.90684e+00 + 3.90134e+00 * costheta + sfactor) + 2.03617333293911543e+04*afactor - math.exp(6.90684e+00 + 3.90134e+00 * 0.734 + sfactor)
    elif costheta < 0.7594:
        s = (costheta - 7.46966e-01)/9.45515e-03
        return 5.21370e+04*afactor * math.exp(-s*s/2.)
    else:
        return -4.67671e+04*afactor * (costheta - 0.7594) + 2.19586218087540583e+04*afactor

def cherenkovangleerrorfuncnodarkrateOnretroRef(hitinfo,invalue,retroratio):
    vect = macro.Vector3()
    vect.SetMagCosThetaPhi(1.,invalue[4],invalue[5])
    hitvec = hitinfo.Get3Position() - macro.Vector3(invalue[0],invalue[1],invalue[2])
    costheta = (hitvec * vect)/((hitvec.Mag())*(vect.Mag()))
    costheta = -costheta
    I = 1.33729337950334557e+04
    NPMT = 11146
    afactor = (1/I)*math.sqrt((retroratio)/NPMT)
    sfactor = math.log(afactor)
    if costheta < 0.2:
        return math.exp(7.83420e+00 + 2.21102e+00 * costheta + sfactor) + 5.03361039235597582e+03*afactor - math.exp(7.83420e+00 + 2.21102e+00 * 0.2 + sfactor)
    elif costheta < 0.734:
        return math.exp(6.90684e+00 + 3.90134e+00 * costheta + sfactor) + 2.03617333293911543e+04*afactor - math.exp(6.90684e+00 + 3.90134e+00 * 0.734 + sfactor)
    elif costheta < 0.7594:
        s = (costheta - 7.46966e-01)/9.45515e-03
        return 5.21370e+04*afactor * math.exp(-s*s/2.)
    else:
        return -4.67671e+04*afactor * (costheta - 0.7594) + 2.19586218087540583e+04*afactor

def cherenkovangleerrorfuncnodarkrateOnretroRefdirect(costheta,retroratio):
    costheta = -costheta
    I = 1.33729337950334557e+04
    NPMT = 11146
    afactor = (1/I)*math.sqrt((retroratio)/NPMT)
    print ("afactor = " + str(afactor))
    sfactor = math.log(afactor)
    print ("sfactor = " + str(sfactor))
    if costheta < 0.2:
        return math.exp(7.83420e+00 + 2.21102e+00 * costheta + sfactor) + 5.03361039235597582e+03*afactor - math.exp(7.83420e+00 + 2.21102e+00 * 0.2 + sfactor)
    elif costheta < 0.734:
        return math.exp(6.90684e+00 + 3.90134e+00 * costheta + sfactor) + 2.03617333293911543e+04*afactor - math.exp(6.90684e+00 + 3.90134e+00 * 0.734 + sfactor)
    elif costheta < 0.7594:
        s = (costheta - 7.46966e-01)/9.45515e-03
        return 5.21370e+04*afactor * math.exp(-s*s/2.)
    else:
        return -4.67671e+04*afactor * (costheta - 0.7594) + 2.19586218087540583e+04*afactor

def cherenkovangleerrorfuncnodarkrateOnretroDirdirect(costheta,retroratio):
    I = 1.33729337950334557e+04
    NPMT = 11146
    afactor = (1/I)*math.sqrt((1-retroratio)/NPMT)
    print ("afactor" + str(afactor))
    sfactor = math.log(afactor)
    print ("sfactor" + str(sfactor))
    if costheta < 0.2:
        return math.exp(7.83420e+00 + 2.21102e+00 * costheta + sfactor) + 5.03361039235597582e+03*afactor - math.exp(7.83420e+00 + 2.21102e+00 * 0.2 + sfactor)
    elif costheta < 0.734:
        return math.exp(6.90684e+00 + 3.90134e+00 * costheta + sfactor) + 2.03617333293911543e+04*afactor - math.exp(6.90684e+00 + 3.90134e+00 * 0.734 + sfactor)
    elif costheta < 0.7594:
        s = (costheta - 7.46966e-01)/9.45515e-03
        return 5.21370e+04*afactor * math.exp(-s*s/2.)
    else:
        return -4.67671e+04*afactor * (costheta - 0.7594) + 2.19586218087540583e+04*afactor

def cherenkovangleerrorfuncnodarkratever2direct(costheta):
    if costheta < 0.2:
        return math.exp(-6.326106061e+00 + 2.21102e+00 * costheta) + 3.56527787154126445e-03 - math.exp(-6.326106061e+00 + 2.21102e+00 * 0.2)
    elif costheta < 0.734:
        return math.exp(-7.25356606128095915e+00 + 3.90134e+00 * costheta) + 1.44221009587363787e-02 - math.exp(-7.25356606128095915e+00 + 3.90134e+00 * 0.734)
    elif costheta < 0.7594:
        s = (costheta - 7.46966e-01)/9.45515e-03
        return 3.69283432565277667e-02 * math.exp(-s*s/2.)
    else:
        return -3.31248733512162150e-02 * (costheta - 0.7594) + 1.55531680686258611e-02

def cherenkovangleerrorfuncnodarkrateloose(hitinfo,invalue):
    vect = macro.Vector3()
    vect.SetMagCosThetaPhi(1.,invalue[4],invalue[5])
    hitvec = hitinfo.Get3Position() - macro.Vector3(invalue[0],invalue[1],invalue[2])
    costheta = (hitvec * vect)/((hitvec.Mag())*(vect.Mag())) 
    if costheta < 0.2:
        return math.exp(-6.30477726e+00 + 2.07887e+00 * costheta) + 7.48107865e-04
    elif costheta < 0.746720557:
        return math.exp(-7.56607726e+00 + 4.35829e+00 * costheta) + 2.429463422e-3
    else:
        return 3.965573567e-02 + -3.189265833e-02*costheta

def cherenkovangleerrorfuncnodarkratesharp(hitinfo,invalue):
    vect = macro.Vector3()
    vect.SetMagCosThetaPhi(1.,invalue[4],invalue[5])
    hitvec = hitinfo.Get3Position() - macro.Vector3(invalue[0],invalue[1],invalue[2])
    costheta = (hitvec * vect)/((hitvec.Mag())*(vect.Mag()))
    s = (costheta - 7.46821e-01)/5.81326e-03
    return 0.1457694753 * math.exp(-s*s/2.)

def cherenkovangleerrorfuncnodarkrateloosedirect(costheta):
    if costheta < 0.2:
        return math.exp(-6.30477726e+00 + 2.07887e+00 * costheta) + 7.48107865e-04
    elif costheta < 0.746720557:
        return math.exp(-7.56607726e+00 + 4.35829e+00 * costheta) + 2.429463422e-3
    else:
        return 3.965573567e-02 + -3.189265833e-02*costheta

def cherenkovangleerrorfuncnodarkratedirect(costheta):
    if costheta < 0.2:
        return math.exp(-6.31511678e+00 + 2.07887e+00 * costheta) + 7.40412636970511897e-04
    elif costheta < 0.732:
        return math.exp(-7.57641678e+00 + 4.35829e+00 * costheta) + 2.40447334220583600e-03
    elif costheta < 0.7605:
        s = (costheta - 7.46527e-01)/1.05105e-02
        return 3.56181379527811190e-02* math.exp(-s*s/2.)
    else:
        return 3.92478266796359651e-02 + -3.15646023267431991e-02*costheta

def cherenkovangleerrorfuncdirect(costheta):
    a0 = 0.97648
    b0 = 3.51958
    a1 = 0.88353
    b1 = -3.52407
    if costheta < 0.75:
        return (1 + a0 * (math.exp(b0 * (costheta - 0.75 )) -1))
    else:
        return (1 + a1 * (math.exp(b1 * (costheta - 0.75 )) - 1))

    
