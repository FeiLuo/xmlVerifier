#!/usr/bin/env python   


g_mapPrintColor = {   
#default setting   
    'NORMAL' : 0,   
  
#font setting   
    'FONT_BOLD' : 1,   
    'FONT_UNDERLINE' : 4,   
    'FONT_SHINE' : 5,   
  
#foreground setting   
    'FOREGROUND_BACK' : 30,   
    'FOREGROUND_RED' : 31,   
    'FOREGROUND_GREEN' : 32,   
    'FOREGROUND_BROWN' : 33,   
    'FOREGROUND_BLUE' : 34,   
    'FOREGROUND_PUPLE' : 35,   
    'FOREGROUND_CYAN_BLUE' : 36,   
    'FOREGROUND_WHITE' : 37,   
    'FOREGROUND_UNDERLINE_ON'  : 38,   
    'FOREGROUND_UNDERLINE_OFF' : 39,   
  
#background setting   
    'BACKGROUND_BACK' : 40,   
    'BACKGROUND_RED' : 41,   
    'BACKGROUND_GREEN' : 42,   
    'BACKGROUND_BROWN' : 43,   
    'BACKGROUND_BLUE' : 44,   
    'BACKGROUND_PUPLE' : 45,   
    'BACKGROUND_CYAN_BLUE' : 46,   
    'BACKGROUND_WHITE' : 47,   
    'BACKGROUND_DEFAULT_BACK' : 49,   
};
  
def GetColorPrintParam(strKey):   
    nDefVal = g_mapPrintColor['NORMAL'];   
       
    if not strKey:   
        return nDefVal;   
       
    if g_mapPrintColor.has_key(strKey):   
        return g_mapPrintColor[strKey];
       
    return nDefVal;   

def ColorString(strPrint, nFont = 0, clrFore = 0, clrBack = 0):
    if not strPrint:   
        return ''
        
    strPrefix = "\033[%d;%d;%dm" %(nFont, clrFore, clrBack);   
    strSuffix = "\033[0m";   
    strMsg = strPrefix + strPrint + strSuffix;
    
    return strMsg;
  
def ColorPrint(strPrint, nFont = 0, clrFore = 0, clrBack = 0):   
    strMsg = ColorString(strPrint, nFont, clrFore, clrBack);
    print strMsg;
    return len(strPrint);   


nFont_Bold          = GetColorPrintParam('FONT_BOLD');
nFont_Underline     = GetColorPrintParam('FONT_UNDERLINE');
nFont_Shine         = GetColorPrintParam('FONT_SHINE');


nFore_Back          = GetColorPrintParam('FOREGROUND_BACK'); 
nFore_Red           = GetColorPrintParam('FOREGROUND_RED'); 
nFore_Green         = GetColorPrintParam('FOREGROUND_GREEN'); 
nFore_Brown         = GetColorPrintParam('FOREGROUND_BROWN'); 
nFore_Blue          = GetColorPrintParam('FOREGROUND_BLUE'); 
nFore_CyanBlue      = GetColorPrintParam('FOREGROUND_CYAN_BLUE'); 
nFore_White         = GetColorPrintParam('FOREGROUND_WHITE'); 
nFore_UnderlineOn   = GetColorPrintParam('FOREGROUND_UNDERLINE_ON'); 
nFore_UnderlineOff  = GetColorPrintParam('FOREGROUND_UNDERLINE_OFF'); 

nBack_BACK          = GetColorPrintParam('BACKGROUND_BACK');
nBack_Red           = GetColorPrintParam('BACKGROUND_RED');
nBack_Green         = GetColorPrintParam('BACKGROUND_GREEN');
nBack_Brown         = GetColorPrintParam('BACKGROUND_BROWN');
nBack_Blue          = GetColorPrintParam('BACKGROUND_BLUE');
nBack_Puple         = GetColorPrintParam('BACKGROUND_PUPLE');
nBack_CyanBlue      = GetColorPrintParam('BACKGROUND_CYAN_BLUE');
nBack_White         = GetColorPrintParam('BACKGROUND_WHITE');
nBack_DefaultBack   = GetColorPrintParam('BACKGROUND_DEFAULT_BACK');


