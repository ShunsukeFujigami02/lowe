import func
import math

def toferrorlog(hitinfo,invalue,toferrorfunc,dfunc):
    toferror = toferrorfunc(hitinfo,invalue,dfunc)
    if toferror < -10.7:
        return -3.8223
    elif toferror < 12.5:
        return 1.23223e+01 * (math.exp(-((toferror-2.22484e+00)/1.50065e+01)*((toferror-2.22484e+00)/1.50065e+01)/2.) - 1. )
    elif toferror < 50.:
        return math.exp(-1.05939e-01*(toferror - 1.05331e+01)) - 3.20458
    elif toferror < 300.:
        return math.exp(-6.42035e-03*(toferror - 2.21593e+01)) -4.04614
    else:
        return -3.877
def toferrornodarkrate(hitinfo,invalue,toferrorfunc,dfunc):
    toferror = toferrorfunc(hitinfo,invalue,dfunc)
    if toferror < -11.:
        return math.exp(-5.25564239 + 0.626995 * toferror)
    elif toferror < 11.:
        s = (toferror - 2.14584e+00)/1.26003e+01
        return math.exp(1.16255e+01* math.exp(-s*s/2.) -18.76104239)
    elif toferror < 100.:
        return math.exp(math.exp(-4.14653e-02 * (toferror -2.38228e+01)) - 1.163209239e+01)
    else:
        return math.exp(-9.85559239e+00 -0.0170638 *toferror)

#def toferrornodarkratever2(hitinfo,invalue,toferrorfunc,dfunc):
#    toferror = toferrorfunc(hitinfo,invalue,dfunc)
#    if toferror < -11.:
#        return math.exp(6.68898e-01*(toferror + 11.) -1.20149198330000004e+01)
#    elif toferror < 11.:
#        s = (toferror - 2.14584e+00)/1.26003e+01
#        return math.exp(1.16255e+01* math.exp(-s*s/2.) -18.76104239)
#    elif toferror < 70.:
#        return math.exp(math.exp(-6.62174e-02 * (toferror -1.88790e+01)) -9.67888951523942787e+00 - math.exp(-6.62174e-02 * (11. - 1.88790e+01)))
#    elif toferror < 150.:
#        return math.exp(-6.85832e-06* toferror*toferror -9.81309e-03*toferror -1.13299467648632763e+01 + 6.85832e-06 * 70.* 70. + 9.81309e-03* 70.)
#    else:
#        return math.exp(-1.76608e-02 * (toferror - 150.) -1.22357004635306872e+01)

def toferrornodarkratever2(hitinfo,invalue,toferrorfunc,dfunc):
    toferror = toferrorfunc(hitinfo,invalue,dfunc)
    if toferror < -10.:
        return math.exp(6.60733e-01*(toferror + 10.) + 8.04749304380208130e+00 - 1.84068658236999205e+01)
    elif toferror < 10.:
        s = (toferror - 2.35177e-01)/1.24789e+01
        return math.exp(1.12652e+01* math.exp(-s*s/2.) -1.84068658236999205e+01)
    elif toferror < 70.:
        return math.exp(math.exp(-4.34364e-02 * (toferror -1.80667e+01)) +8.29427077758401232e+00 - math.exp(-4.34364e-02 * (10. - 1.80667e+01)) - 1.84068658236999205e+01)
    elif toferror < 150.:
        return math.exp(-3.93675e-05* toferror*toferror -2.42127e-03*toferror +6.97944384747111268e+00 + 3.93675e-05 * 70.* 70. + 2.42127e-03* 70. - 1.84068658236999205e+01)
    else:
        return math.exp(-1.77550e-02 * (toferror - 150.) + 6.09287392854065768e+00 - 1.84068658236999205e+01)


def toferrornodarkrateOnretroDir(hitinfo,invalue,toferrorfunc,dfunc,retroratio):
    I = 9.34201880158831715e+05
    NPMT = 11146
    sfactor = math.log((1/I)*math.sqrt((1-retroratio)/NPMT))
    toferror = toferrorfunc(hitinfo,invalue,dfunc)
    if toferror < -10.:
        return math.exp(6.60733e-01*(toferror + 10.) + 8.04749304380208130e+00 + sfactor)
    elif toferror < 10.:
        s = (toferror - 2.35177e-01)/1.24789e+01
        return math.exp(1.12652e+01* math.exp(-s*s/2.) + sfactor)
    elif toferror < 70.:
        return math.exp(math.exp(-4.34364e-02 * (toferror -1.80667e+01)) +8.29427077758401232e+00 - math.exp(-4.34364e-02 * (10. - 1.80667e+01)) + sfactor)
    elif toferror < 150.:
        return math.exp(-3.93675e-05* toferror*toferror -2.42127e-03*toferror +6.97944384747111268e+00 + 3.93675e-05 * 70.* 70. + 2.42127e-03* 70. + sfactor)
    else:
        return math.exp(-1.77550e-02 * (toferror - 150.) + 6.09287392854065768e+00 + sfactor)

def toferrornodarkrateOnretroRef(hitinfo,invalue,toferrorfunc,dfunc,retroratio):
    I = 9.34201880158831715e+05
    NPMT = 11146
    sfactor = math.log((1/I)*math.sqrt((retroratio)/NPMT))
    toferror = toferrorfunc(hitinfo,invalue,dfunc)
    if toferror < -10.:
        return math.exp(6.60733e-01*(toferror + 10.) + 8.04749304380208130e+00 + sfactor)
    elif toferror < 10.:
        s = (toferror - 2.35177e-01)/1.24789e+01
        return math.exp(1.12652e+01* math.exp(-s*s/2.) + sfactor)
    elif toferror < 70.:
        return math.exp(math.exp(-4.34364e-02 * (toferror -1.80667e+01)) +8.29427077758401232e+00 - math.exp(-4.34364e-02 * (10. - 1.80667e+01)) + sfactor)
    elif toferror < 150.:
        return math.exp(-3.93675e-05* toferror*toferror -2.42127e-03*toferror +6.97944384747111268e+00 + 3.93675e-05 * 70.* 70. + 2.42127e-03* 70. + sfactor)
    else:
        return math.exp(-1.77550e-02 * (toferror - 150.) + 6.09287392854065768e+00 + sfactor)

def toferrornodarkrateOnretroRefdirect(toferror,retroratio):
    I = 9.34201880158831715e+05
    NPMT = 11146
    sfactor = math.log((1/I)*math.sqrt((retroratio)/NPMT))
    print (sfactor)
    if toferror < -10.:
        return math.exp(6.60733e-01*(toferror + 10.) + 8.04749304380208130e+00 + sfactor)
    elif toferror < 10.:
        s = (toferror - 2.35177e-01)/1.24789e+01
        return math.exp(1.12652e+01* math.exp(-s*s/2.) + sfactor)
    elif toferror < 70.:
        return math.exp(math.exp(-4.34364e-02 * (toferror -1.80667e+01)) +8.29427077758401232e+00 - math.exp(-4.34364e-02 * (10. - 1.80667e+01)) + sfactor)
    elif toferror < 150.:
        return math.exp(-3.93675e-05* toferror*toferror -2.42127e-03*toferror +6.97944384747111268e+00 + 3.93675e-05 * 70.* 70. + 2.42127e-03* 70. + sfactor)
    else:
        return math.exp(-1.77550e-02 * (toferror - 150.) + 6.09287392854065768e+00 + sfactor)

def toferrornodarkrateOnretroDirdirect(toferror,retroratio):
    I = 9.34201880158831715e+05
    NPMT = 11146
    sfactor = math.log((1/I)*math.sqrt((1-retroratio)/NPMT))
    print (sfactor)
    if toferror < -10.:
        return math.exp(6.60733e-01*(toferror + 10.) + 8.04749304380208130e+00 + sfactor)
    elif toferror < 10.:
        s = (toferror - 2.35177e-01)/1.24789e+01
        return math.exp(1.12652e+01* math.exp(-s*s/2.) + sfactor)
    elif toferror < 70.:
        return math.exp(math.exp(-4.34364e-02 * (toferror -1.80667e+01)) +8.29427077758401232e+00 - math.exp(-4.34364e-02 * (10. - 1.80667e+01)) + sfactor)
    elif toferror < 150.:
        return math.exp(-3.93675e-05* toferror*toferror -2.42127e-03*toferror +6.97944384747111268e+00 + 3.93675e-05 * 70.* 70. + 2.42127e-03* 70. + sfactor)
    else:
        return math.exp(-1.77550e-02 * (toferror - 150.) + 6.09287392854065768e+00 + sfactor)

def toferrornodarkratever2direct(toferror):
    if toferror < -10.:
        return math.exp(6.60733e-01*(toferror + 10.) + 8.04749304380208130e+00 - 1.84068658236999205e+01)
    elif toferror < 10.:
        s = (toferror - 2.35177e-01)/1.24789e+01
        return math.exp(1.12652e+01* math.exp(-s*s/2.) -1.84068658236999205e+01)
    elif toferror < 70.:
        return math.exp(math.exp(-4.34364e-02 * (toferror -1.80667e+01)) +8.29427077758401232e+00 - math.exp(-4.34364e-02 * (10. - 1.80667e+01)) - 1.84068658236999205e+01)
    elif toferror < 150.:
        return math.exp(-3.93675e-05* toferror*toferror -2.42127e-03*toferror +6.97944384747111268e+00 + 3.93675e-05 * 70.* 70. + 2.42127e-03* 70. - 1.84068658236999205e+01)
    else:
        return math.exp(-1.77550e-02 * (toferror - 150.) + 6.09287392854065768e+00 - 1.84068658236999205e+01)

def toferrornodarkratesharp(hitinfo,invalue,toferrorfunc,dfunc):
    toferror = toferrorfunc(hitinfo,invalue,dfunc)
    if toferror < -8.:
        return math.exp(-6.66592543 + 0.61134 * toferror)
    elif toferror < 12.:
        s = (toferror - 1.97609e+00)/1.12309e+01
        return math.exp(9.67919e+00* math.exp(-s*s/2.) - 18.11902543)
    elif toferror < 19.:
        return math.exp(-8.74319543 -0.240512 * toferror)
    else:
        return math.exp(-13.11657543 - 0.0196635 * toferror)

def toferrornodarkrateloose(hitinfo,invalue,toferrorfunc,dfunc):
    toferror = toferrorfunc(hitinfo,invalue,dfunc)
    if toferror < -11.:
        return math.exp(-4.69125737 + 0.670138 * toferror)
    elif toferror < 11.:
        s = (toferror - 2.19461e+00)/1.26094e+01
        return math.exp(1.15643e+01* math.exp(-s*s/2.) -18.74495737)
    elif toferror < 100.:
        return math.exp(math.exp(-4.00300e-02 * (toferror -2.35884e+01)) - 11.59763737)
    else:
        return math.exp(-9.79260737 - 0.0171459 *toferror)

def toferrornodarkrateloosedirect(toferror):
    if toferror < -11.:
        return math.exp(-4.69125737 + 0.670138 * toferror)
    elif toferror < 11.:
        s = (toferror - 2.19461e+00)/1.26094e+01
        return math.exp(1.15643e+01* math.exp(-s*s/2.) -18.74495737)
    elif toferror < 100.:
        return math.exp(math.exp(-4.00300e-02 * (toferror -2.35884e+01)) - 11.59763737)
    else:
        return math.exp(-9.79260737 - 0.0171459 *toferror)

def toferrornodarkratesharpdirect(toferror):
    if toferror < -8.:
        return math.exp(-6.66592543 + 0.61134 * toferror)
    elif toferror < 12.:
        s = (toferror - 1.97609e+00)/1.12309e+01
        return math.exp(9.67919e+00* math.exp(-s*s/2.) - 18.11902543)
    elif toferror < 19.:
        return math.exp(-8.74319543 -0.240512 * toferror)
    else:
        return math.exp(-13.11657543 - 0.0196635 * toferror)

def toferrornodarkratedirect(toferror):
    if toferror < -11.:
        return math.exp(-5.25564239 + 0.626995 * toferror)
    elif toferror < 11.:
        s = (toferror - 2.14584e+00)/1.26003e+01
        return math.exp(1.16255e+01* math.exp(-s*s/2.) -18.76104239)
    elif toferror < 100.:
        return math.exp(math.exp(-4.14653e-02 * (toferror -2.38228e+01)) - 1.163209239e+01)
    else:
        return math.exp(-9.85559239e+00 -0.0170638 *toferror)
    


def toferrorlogdirect(toferror):
    if toferror < -10.7:
        return -3.8223
    elif toferror < 12.5:
        return 1.23223e+01 * (math.exp(-((toferror-2.22484e+00)/1.50065e+01)*((toferror-2.22484e+00)/1.50065e+01)/2.) - 1.)
    elif toferror < 50.:
        return math.exp(-1.05939e-01*(toferror - 1.05331e+01)) - 3.20458
    elif toferror < 300.:
        return math.exp(-6.42035e-03*(toferror - 2.21593e+01)) -4.04614
    else:
        return -3.877
