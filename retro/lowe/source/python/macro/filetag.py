

class filetag:
    def __init__(self,tagname,tagtype,value):
        self.tagname = tagname
        self.tagtype = tagtype
        self.value = value
    def Print(self):
        print ("(tagname,tagtype,value) = (" + str(self.tagname) + "," + str(self.tagtype) + "," + str(self.value) + ")")
