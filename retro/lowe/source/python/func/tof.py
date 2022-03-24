import macro

def emittimebyonePMT(hitinfo,invalue,dfunc):
    invalue3vec = [invalue[0],invalue[1],invalue[2]]
    hittime = hitinfo.hittime;
    tofvalue = hittime - macro.offset - (dfunc(hitinfo,invalue3vec)-macro.doffset)/macro.v_light_in_water
    return tofvalue

def emittimebyonePMTminusTestemittime(hitinfo,invalue,dfunc):
    return (emittimebyonePMT(hitinfo,invalue,dfunc) - invalue[3])

    
