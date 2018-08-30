import sys
import os
import shutil


newtemplate = "tes1t"

def ReplaceString(strData,old,new):
    #strData = ""
    strData = strData.replace(old,new)
    return strData



def ReplaceFile(CurPath,NewPath,CurFileName,old,new):
    CurFileName = str(CurFileName)
    NewFileName = ReplaceString(CurFileName,old,new)
    
    
    CurFilePath = os.path.join(CurPath,CurFileName)
    NewFilePath = os.path.join(NewPath,NewFileName)
    
    CurFP = open(CurFilePath,"r")
    NewFP = open(NewFilePath,"w")
    
    CurData = CurFP.read()
    NewData = CurData.replace(old,new)
    
    
    NewFP.write(NewData)
    
    
    CurFP.close()
    NewFP.close()
    
def RecurseDir(CurRoot,NewRoot,old,new):
    CurFileItems = os.listdir(CurRoot)
    for item in CurFileItems:
        itemPath = os.path.join(CurRoot,item)
        if os.path.isfile(itemPath):
            ReplaceFile(CurRoot,NewRoot,item,old,new)
        elif os.path.isdir(itemPath):
            newitem = ReplaceString(item,old,new)
            NewSubPath = os.path.join(NewRoot,newitem)
            
            if not os.path.isdir(NewSubPath):
                os.mkdir(NewSubPath)

            CurSubPath = os.path.join(CurRoot,item)
            
            RecurseDir(CurSubPath,NewSubPath,old,new)
            


if __name__ == "__main__":
    
    newtemplate = raw_input("please input new ActionName:")
    
    CurRoot = r".\template"
    "Trans" + newtemplate + "Action"
    NewRoot = ".\\" +  "Trans" + newtemplate + "Action"
    if  not os.path.isdir(NewRoot):
        os.mkdir(NewRoot)    
    
    RecurseDir(CurRoot,NewRoot,"9999",newtemplate)

    os.system("pause")
    
    
    



    


    