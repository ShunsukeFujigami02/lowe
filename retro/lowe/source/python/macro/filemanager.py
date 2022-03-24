import ROOT
import csv
import func
import macro

def GetKeyNames( self , dir = ''):
    self.cd(dir)
    return [key.GetName() for key in ROOT.gDirectory.GetListOfKeys()]

class filemanager:
    filedictofdict = {}
    def __init__(self,filename):
        self.treedict = {}
        self.treenametobranchdict = {}
        self.subfile = []
        self.subfilename = []
        self.l = []
        self.hasevent = []
        self.filetaglist = []
        filehead = filename.replace(".root",'')
        filecsv = filehead + ".csv"
        fi = open(filecsv)
        reader = csv.reader(fi)
        l = [row for row in reader]
        icsv = 0
        for lin in l:
            if icsv == 0:
                icsv += 1
                continue
            self.filetaglist.append(macro.filetag(lin[0],lin[1],lin[2]))

        for l0 in l[0]:
            self.subfilename.append(l0)
            subfileroot = l0.replace(".csv",'') + ".root"
            self.subfile.append(filemanager(subfileroot))
        self.filename = filename
        self.f = ROOT.TFile(filename)
        treename = self.f.GetKeyNames()
        for name in treename:
            self.treedict[name] = self.f.Get(name)
            branchdictin = {}
            brlist = self.treedict[name].GetListOfBranches()
            nbr = brlist.GetEntries()
            itr = brlist.MakeIterator()
            for i in range(nbr):
                branch = itr()
                bname = branch.GetName()
                branchdictin[bname] = branch
                self.treedict[name].GetEntry(0)
                if bname == "wcsimrootevent":
                    self.treedict[name].GetBranch(bname).SetAutoDelete()

            self.treenametobranchdict[name] = branchdictin
        
    def GetValue(self,valuename,event):
        value = [0.,"true"]
        try:
            valuesplit = valuename.split('.')
            treename = valuesplit[0]
            branchname = valuesplit[1]
            valueremovebranchname = valuename.replace(treename + '.' + branchname,'')
            exevalue = ""
            self.treedict[treename].GetEntry(event)
            exevalue = 'self.treenametobranchdict["' + treename + '"]["' + branchname + '"]' +  valueremovebranchname
            print (exevalue)
            value[0] = (eval(exevalue))
            value[1] = "true"
            return value
        except Exception as e:
            print(e)
            for sub in self.subfile:
                return sub.GetValue(valuename,event)
            value[1] = "false"
            return value
    def Gethitinfo(self,ievent,hitnum):
        hit = self.treenametobranchdict["wcsimT"]["wcsimrootevent"].GetTrigger(0).GetCherenkovDigiHits().At(hitnum)
        wcsimrootgeom = self.treenametobranchdict["wcsimGeoT"]["wcsimrootgeom"]
        info = macro.hitinfo(hit,wcsimrootgeom)
        return info

    def GetNeventmax(self):
        value = 0
        for t in self.treedict.values():
            if value < t.GetEntries():
                value = t.GetEntries()
        return value
    def GetTag(self,tagname):
        for tag in self.filetaglist:
            if tagname == tag.tagname:
                return tag.value
        for sub in self.subfile:
            return sub.GetTag(tagname)
        return "false"
    def PrintTag(self):
        print ("PrintTag start")
        for tag in self.filetaglist:
            tag.Print()
        for sub in self.subfile:
            return sub.PrintTag()
