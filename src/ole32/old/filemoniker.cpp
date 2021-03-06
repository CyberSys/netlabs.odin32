/* $Id: filemoniker.cpp,v 1.1 2001-04-26 19:26:09 sandervl Exp $ */
/* 
 *  FileMonikers functions.
 * 
 * 20/9/99
 * 
 * Copyright 1999 David J. Raison
 * 
 * Direct port of Wine Implementation
 *   Copyright 1999  Noomen Hamza
 */

#include "ole32.h"
#include "heapstring.h"
#include "debugtools.h"
#include "filemoniker.h"
#include "winnls.h"

DEFAULT_DEBUG_CHANNEL(moniker)

/********************************************************************************/
/* FileMoniker prototype functions :                                            */

/* IUnknown prototype functions */
static HRESULT WINAPI FileMonikerImpl_QueryInterface(IMoniker* iface,REFIID riid,void** ppvObject);
static ULONG   WINAPI FileMonikerImpl_AddRef(IMoniker* iface);
static ULONG   WINAPI FileMonikerImpl_Release(IMoniker* iface);

/* IPersist prototype functions */
static HRESULT WINAPI FileMonikerImpl_GetClassID(IMoniker* iface, CLSID *pClassID);

/* IPersistStream prototype functions */
static HRESULT WINAPI FileMonikerImpl_IsDirty(IMoniker* iface);
static HRESULT WINAPI FileMonikerImpl_Load(IMoniker* iface, IStream* pStm);
static HRESULT WINAPI FileMonikerImpl_Save(IMoniker* iface, IStream* pStm, BOOL fClearDirty);
static HRESULT WINAPI FileMonikerImpl_GetSizeMax(IMoniker* iface, ULARGE_INTEGER* pcbSize);

/* IMoniker prototype functions */
static HRESULT WINAPI FileMonikerImpl_BindToObject(IMoniker* iface,IBindCtx* pbc, IMoniker* pmkToLeft, REFIID riid, VOID** ppvResult);
static HRESULT WINAPI FileMonikerImpl_BindToStorage(IMoniker* iface,IBindCtx* pbc, IMoniker* pmkToLeft, REFIID riid, VOID** ppvResult);
static HRESULT WINAPI FileMonikerImpl_Reduce(IMoniker* iface,IBindCtx* pbc, DWORD dwReduceHowFar,IMoniker** ppmkToLeft, IMoniker** ppmkReduced);
static HRESULT WINAPI FileMonikerImpl_ComposeWith(IMoniker* iface,IMoniker* pmkRight,BOOL fOnlyIfNotGeneric, IMoniker** ppmkComposite);
static HRESULT WINAPI FileMonikerImpl_Enum(IMoniker* iface,BOOL fForward, IEnumMoniker** ppenumMoniker);
static HRESULT WINAPI FileMonikerImpl_IsEqual(IMoniker* iface,IMoniker* pmkOtherMoniker);
static HRESULT WINAPI FileMonikerImpl_Hash(IMoniker* iface,DWORD* pdwHash);
static HRESULT WINAPI FileMonikerImpl_IsRunning(IMoniker* iface,IBindCtx* pbc, IMoniker* pmkToLeft, IMoniker* pmkNewlyRunning);
static HRESULT WINAPI FileMonikerImpl_GetTimeOfLastChange(IMoniker* iface, IBindCtx* pbc, IMoniker* pmkToLeft, FILETIME* pFileTime);
static HRESULT WINAPI FileMonikerImpl_Inverse(IMoniker* iface,IMoniker** ppmk);
static HRESULT WINAPI FileMonikerImpl_CommonPrefixWith(IMoniker* iface,IMoniker* pmkOther, IMoniker** ppmkPrefix);
static HRESULT WINAPI FileMonikerImpl_RelativePathTo(IMoniker* iface,IMoniker* pmOther, IMoniker** ppmkRelPath);
static HRESULT WINAPI FileMonikerImpl_GetDisplayName(IMoniker* iface,IBindCtx* pbc, IMoniker* pmkToLeft, LPOLESTR *ppszDisplayName);
static HRESULT WINAPI FileMonikerImpl_ParseDisplayName(IMoniker* iface,IBindCtx* pbc, IMoniker* pmkToLeft, LPOLESTR pszDisplayName, ULONG* pchEaten, IMoniker** ppmkOut);
static HRESULT WINAPI FileMonikerImpl_IsSystemMoniker(IMoniker* iface,DWORD* pwdMksys);

/********************************************************************************/
/* IROTData prototype functions                                                 */

/* IUnknown prototype functions */
static HRESULT WINAPI FileMonikerROTDataImpl_QueryInterface(IROTData* iface,REFIID riid,VOID** ppvObject);
static ULONG   WINAPI FileMonikerROTDataImpl_AddRef(IROTData* iface);
static ULONG   WINAPI FileMonikerROTDataImpl_Release(IROTData* iface);

/* IROTData prototype function */
static HRESULT WINAPI FileMonikerROTDataImpl_GetComparaisonData(IROTData* iface,BYTE* pbData,ULONG cbMax,ULONG* pcbData);

/********************************************************************************/
/* Virtual function table for the FileMonikerImpl class witch  include Ipersist,*/
/* IPersistStream and IMoniker functions.                                       */
static ICOM_VTABLE(IMoniker) VT_FileMonikerImpl =
{
    ICOM_MSVTABLE_COMPAT_DummyRTTIVALUE
    FileMonikerImpl_QueryInterface,
    FileMonikerImpl_AddRef,
    FileMonikerImpl_Release,
    FileMonikerImpl_GetClassID,
    FileMonikerImpl_IsDirty,
    FileMonikerImpl_Load,
    FileMonikerImpl_Save,
    FileMonikerImpl_GetSizeMax,
    FileMonikerImpl_BindToObject,
    FileMonikerImpl_BindToStorage,
    FileMonikerImpl_Reduce,
    FileMonikerImpl_ComposeWith,
    FileMonikerImpl_Enum,
    FileMonikerImpl_IsEqual,
    FileMonikerImpl_Hash,
    FileMonikerImpl_IsRunning,
    FileMonikerImpl_GetTimeOfLastChange,
    FileMonikerImpl_Inverse,
    FileMonikerImpl_CommonPrefixWith,
    FileMonikerImpl_RelativePathTo,
    FileMonikerImpl_GetDisplayName,
    FileMonikerImpl_ParseDisplayName,
    FileMonikerImpl_IsSystemMoniker
};

/********************************************************************************/
/* Virtual function table for the IROTData class.                               */
static ICOM_VTABLE(IROTData) VT_ROTDataImpl =
{
    ICOM_MSVTABLE_COMPAT_DummyRTTIVALUE
    FileMonikerROTDataImpl_QueryInterface,
    FileMonikerROTDataImpl_AddRef,
    FileMonikerROTDataImpl_Release,
    FileMonikerROTDataImpl_GetComparaisonData
};

/*******************************************************************************
 *        FileMoniker_QueryInterface
 *******************************************************************************/
HRESULT WINAPI FileMonikerImpl_QueryInterface(IMoniker* iface,REFIID riid,void** ppvObject)
{
    ICOM_THIS(FileMonikerImpl,iface);
  
  TRACE("(%p,%p,%p)\n",This,riid,ppvObject);

    /* Perform a sanity check on the parameters.*/
    if ( (This==0) || (ppvObject==0) )
	return E_INVALIDARG;
  
    /* Initialize the return parameter */
  *ppvObject = 0;

    /* Compare the riid with the interface IDs implemented by this object.*/
    if (IsEqualIID(&IID_IUnknown, riid)      ||
        IsEqualIID(&IID_IPersist, riid)      ||
        IsEqualIID(&IID_IPersistStream,riid) ||
        IsEqualIID(&IID_IMoniker, riid)
       )
        *ppvObject = iface;
    
    else if (IsEqualIID(&IID_IROTData, riid))
        *ppvObject = (IROTData*)&(This->lpvtbl2);

    /* Check that we obtained an interface.*/
    if ((*ppvObject)==0)
        return E_NOINTERFACE;
  
    /* Query Interface always increases the reference count by one when it is successful */
  FileMonikerImpl_AddRef(iface);

    return S_OK;
}

/******************************************************************************
 *        FileMoniker_AddRef
 ******************************************************************************/
ULONG WINAPI FileMonikerImpl_AddRef(IMoniker* iface)
{
    ICOM_THIS(FileMonikerImpl,iface);

    TRACE("(%p)\n",iface);

    return ++(This->ref);
}

/******************************************************************************
 *        FileMoniker_Release
 ******************************************************************************/
ULONG WINAPI FileMonikerImpl_Release(IMoniker* iface)
{
    ICOM_THIS(FileMonikerImpl,iface);

    TRACE("(%p)\n",iface);

    This->ref--;

    /* destroy the object if there's no more reference on it */
    if (This->ref==0){

        FileMonikerImpl_Destroy(This);

        return 0;
    }
    return This->ref;;
}

/******************************************************************************
 *        FileMoniker_GetClassID
 ******************************************************************************/
HRESULT WINAPI FileMonikerImpl_GetClassID(IMoniker* iface,
                                          CLSID *pClassID)/* Pointer to CLSID of object */
{
    TRACE("(%p,%p),stub!\n",iface,pClassID);

    if (pClassID==NULL)
        return E_POINTER;

    *pClassID = CLSID_FileMoniker;
        
    return S_OK;
}

/******************************************************************************
 *        FileMoniker_IsDirty
 ******************************************************************************/
HRESULT WINAPI FileMonikerImpl_IsDirty(IMoniker* iface)
{
    /* Note that the OLE-provided implementations of the IPersistStream::IsDirty
       method in the OLE-provided moniker interfaces always return S_FALSE because
       their internal state never changes. */

    TRACE("(%p)\n",iface);

    return S_FALSE;
}

/******************************************************************************
 *        FileMoniker_Load
 ******************************************************************************/
HRESULT WINAPI FileMonikerImpl_Load(IMoniker* iface,IStream* pStm)
{
    HRESULT res;
    CHAR* filePathA=NULL;
    WCHAR* filePathW=NULL;
    ULONG bread;
    WORD  wbuffer;
    DWORD i;
    DWORD dwAnsiLength, dwUnicodeLength;
    DWORD dwOffsetToEndUnicodeStr; 
    WCHAR tempUnicodePath[MAX_PATH];
    ICOM_THIS(FileMonikerImpl,iface);

    TRACE("(%p,%p)\n",iface,pStm);

    /* this function locate and read from the stream the filePath string writen by FileMonikerImpl_Save */

    /* first WORD is non significative */
    res=IStream_Read(pStm,&wbuffer,sizeof(WORD),&bread);
    if (bread!=sizeof(WORD) || wbuffer!=0)
        return E_FAIL;
    
    /* read filePath string length (plus one) */
    res=IStream_Read(pStm,&dwAnsiLength,sizeof(DWORD),&bread);
    if (bread != sizeof(DWORD))
        return E_FAIL;

    if(dwAnsiLength > 0)
    {
        /* read filePath string */
        filePathA=(CHAR *)HeapAlloc(GetProcessHeap(),0,dwAnsiLength);
        res=IStream_Read(pStm,filePathA,dwAnsiLength,&bread);
        if (bread != dwAnsiLength)
            return E_FAIL;
    }
    tempUnicodePath[0] = 0;
    if(filePathA != NULL)
    {
        MultiByteToWideChar(CP_ACP, 0, filePathA, -1, tempUnicodePath, MAX_PATH);
    }
    FileMonikerImpl_CheckFileFormat(This, tempUnicodePath);

    IStream_Read(pStm, &(This->wNetworkDomainLenght), sizeof(WORD), &bread);
    if(bread != sizeof(WORD))
    {
        return E_FAIL;
    }
    /* read the first constant */
    IStream_Read(pStm,&wbuffer,sizeof(WORD),&bread);
    if (bread != sizeof(WORD) || wbuffer != 0xDEAD)
        return E_FAIL;
	
    for(i=0;i<10;i++){
        res=IStream_Read(pStm,&wbuffer,sizeof(WORD),&bread);
        if (bread!=sizeof(WORD) || wbuffer!=0)
            return E_FAIL;
    }
    
    res=IStream_Read(pStm,&dwOffsetToEndUnicodeStr,sizeof(DWORD),&bread);
    if (bread != sizeof(DWORD))
        return E_FAIL;
    if(dwOffsetToEndUnicodeStr != 0)
    {
        res=IStream_Read(pStm,&dwUnicodeLength,sizeof(DWORD),&bread);
        if (bread!=sizeof(DWORD))
            return E_FAIL;


        res=IStream_Read(pStm,&wbuffer,sizeof(WORD),&bread);
        if (bread!=sizeof(WORD) || wbuffer!=0x3)
            return E_FAIL;

        if(dwUnicodeLength > 0)
        {
            filePathW=(WCHAR *)HeapAlloc(GetProcessHeap(),0,dwUnicodeLength + sizeof(WCHAR));
            res=IStream_Read(pStm, filePathW, dwUnicodeLength,&bread);
            filePathW[dwAnsiLength-1]=0;
            if (bread!=dwUnicodeLength)
                return E_FAIL;
        }
    }
    else
    {
        if(filePathA != NULL)
        {
            filePathW=(WCHAR *)HeapAlloc(GetProcessHeap(),0,dwAnsiLength*sizeof(WCHAR));
            MultiByteToWideChar(CP_ACP, 0, filePathA, -1, filePathW, dwAnsiLength); 
            filePathW[dwAnsiLength-1]=0;
        }
    }

    if (This->filePathName!=NULL)
        HeapFree(GetProcessHeap(),0,This->filePathName);

    This->filePathName=filePathW;

    if(filePathA != NULL)
    {
        HeapFree(GetProcessHeap(),0,filePathA);
    }
    
    return res;
}

/******************************************************************************
 *        FileMoniker_Save
 ******************************************************************************/
HRESULT WINAPI FileMonikerImpl_Save(IMoniker* iface,
                                    IStream* pStm,/* poniter to the stream where the object is to be saved */
                                    BOOL fClearDirty)/* Specifies whether to clear the dirty flag */
{
    /* this function saves data of this object. In the begining I thougth that I have just to write
     * the filePath string on Stream. But, when I tested this function whith windows programs samples !
     * I noted that it was not the case. So I analysed data writen by this function on Windows system and 
     * what did this function do exactly ! but I have no idear a bout its logic !
     * I guessed data who must be writen on stream wich is:
     * 1) WORD constant:zero 2) length of the path string ("\0" included) 3) path string type A
     * 4) DWORD constant : 0xDEADFFFF 5) ten WORD constant: zero  6) DWORD: double-length of the the path
     * string type W ("\0" not included) 7) WORD constant: 0x3 8) filePath unicode string.
     *  if the length(filePath) > 8 or.length(filePath) == 8 stop at step 5)
     */

    ICOM_THIS(FileMonikerImpl,iface);        

    HRESULT res;
    LPOLESTR filePathW=This->filePathName;
    CHAR*     filePathA=NULL;
    DWORD  len=0;

    WORD  constant1 = 0xDEAD; /* these constants are detected after analysing the data structure writen by */
    WORD   constant2 = 0x3;        /* FileMoniker_Save function in a windows program system */
    WORD wUnicodeLen=0xFFFF;  
    DWORD dwOffsetToEndUnicodeStr=0; 

    WORD   zero=0;
    DWORD doubleLenHex;
    int i=0;


    TRACE("(%p,%p,%d)\n",iface,pStm,fClearDirty);

    if (pStm==NULL)
        return E_POINTER;
    if(filePathW == NULL)
    {
        return S_FALSE;  /* TODO: Check what windows returns */
    }

    doubleLenHex=lstrlenW(filePathW) * sizeof(WCHAR); /* Doesn't include the "\0" */
    len = lstrlenW(filePathW)+1;
    filePathA=(CHAR *)HeapAlloc(GetProcessHeap(), 0,len);
    lstrcpyWtoA(filePathA,filePathW);
    
    if(!This->bIsLongFileName && len > 1)
    {
        
        dwOffsetToEndUnicodeStr = sizeof(DWORD) + sizeof(WORD) + doubleLenHex;
    }

    /* write a DWORD seted to 0 : constant */
    /* TODO: Not Sure, but I believe that this is a constant for  char types */
    /* eg. 0000 for Ansi, 0003 for Unicode, will need to verify this  */
    res=IStream_Write(pStm,&zero,sizeof(WORD),NULL);

    /* write length of filePath string ( "\0" included )*/
    res=IStream_Write(pStm,&len,sizeof(DWORD),NULL);

    /* write filePath string type A */
    res=IStream_Write(pStm,filePathA,len,NULL);

    /*When the file path is a network path, it fills this value with */
    /*Lenght in of the domain/share drive name */
    res=IStream_Write(pStm, &(This->wNetworkDomainLenght), sizeof(wUnicodeLen), NULL);
    /* write a WORD seted to 0xDEAD: constant */
    res=IStream_Write(pStm,&constant1,sizeof(constant1),NULL);
	
    len--;
    /* write 10 times a WORD seted to 0 : constants */
    for(i=0;i<10;i++)
        res=IStream_Write(pStm,&zero,sizeof(WORD),NULL);

    /* when a file path is a file or network path that doesn't fallow the dos 8.3 format  */
    /* it creates the unicode data.  This value is offset */
    /* where the Unicode string ends.  If the file is a long dos filename (or network containing a long filename)*/
    /* it doesn't create it's unicode counterpart */    
    res=IStream_Write(pStm, &dwOffsetToEndUnicodeStr, sizeof(DWORD), NULL);
    if(dwOffsetToEndUnicodeStr != 0)
    {
        /* write double-length (hexa representation) of the path string*/
        res=IStream_Write(pStm, &doubleLenHex, sizeof(DWORD),NULL);
        /* write a WORD seted to 0x3: constant */
        /* TODO: (same as above) Not Sure, but I believe that this is a constant for  char types */
        /* eg. 0000 for Ansi, 0003 for Unicode, will need to verify this  */
        res=IStream_Write(pStm, &constant2, sizeof(WORD),NULL);
        /* write path unicode string */
        if(doubleLenHex > 0)
        {
            res=IStream_Write(pStm, filePathW, doubleLenHex,NULL);
        }
    }
    if(filePathA != NULL)
    {
        HeapFree(GetProcessHeap(),0,filePathA);
    }
    return res;
}

/******************************************************************************
 *        FileMoniker_GetSizeMax
 ******************************************************************************/
HRESULT WINAPI FileMonikerImpl_GetSizeMax(IMoniker* iface,ULARGE_INTEGER* pcbSize)
{
    ICOM_THIS(FileMonikerImpl,iface);

    if (pcbSize==NULL)
        return E_POINTER;

    /* GetSizeMax = SizeToSave + 2*len + 22 */
    FileMonikerImpl_GetSizeToSave(iface,pcbSize);
    pcbSize->LowPart += 2 * lstrlenW(This->filePathName) + 22;
    pcbSize->HighPart = 0;

    TRACE("(iface:%p pcbSize:(LowPart:%ld - HighPart:0))\n",iface,pcbSize->LowPart);
    return S_OK;
}

HRESULT FileMonikerImpl_GetSizeToSave(IMoniker* iface,ULARGE_INTEGER* pcbSize)
{
    ICOM_THIS(FileMonikerImpl,iface);
    DWORD len = lstrlenW(This->filePathName);

    if (pcbSize==NULL)
        return E_POINTER;

    pcbSize->LowPart = sizeof(WORD)      +  /* first WORD is 0 */
        sizeof(DWORD)     +  /* length of filePath including "\0" in the end of the string */
        len + 1           +  /* filePath string */
        sizeof(DWORD)     +  /* constant : 0xDEADFFFF */
        10 * sizeof(WORD) +  /* 10 zero WORD */
        sizeof(DWORD) +       /* size of the unicode filePath: "\0" not included */
        ((!This->bIsLongFileName) ?
         sizeof(DWORD)     +  /* size of the unicode filePath: "\0" not included */
         sizeof(WORD)      +  /* constant : 0x3 */
         len * sizeof(WCHAR) : 0); /* unicde filePath string */
    pcbSize->HighPart = 0;

    return S_OK;
}


void WINAPI FileMonikerImpl_CheckFileFormat(FileMonikerImpl* This, LPCOLESTR lpszPathName)
{
    int len;
    WCHAR tempShortPath[MAX_PATH];

    This->bIsNetworkPath = FALSE;
    This->bIsLongFileName = FALSE;
    This->wNetworkDomainLenght = 0xFFFF;

    /* TODO: Not handling invalid filesname  and invalid UNC Filenames */
    /* Filenames that doesn't conform to dos 8.3, are handled diffently when saving and loading */
    /* Same applies to network path, but only after the \\Domain\Share path */

    if(lpszPathName == NULL)
    {
        return;
    }

    len = lstrlenW(lpszPathName);
    if( len >= 2)
    {
        /* Is this a network path */
        if(lpszPathName[0] == '\\' && lpszPathName[1] == '\\')
        {
            int i=2; /* Skip the \\ */
            int j=0;
            This->bIsNetworkPath = TRUE;
            /* Skip Domain name \ share drive name */
            for(j =0; j < 2; j++)
            {
                for(; i < len && lpszPathName[i] != '\\'; i++)
                {
                }
                i++;
            }
            This->wNetworkDomainLenght = i-1;
            if( i < len)
            {
                /* Check to see if the file fallows the dos file format (8.3)*/
                GetShortPathNameW(&(lpszPathName[i]), tempShortPath, MAX_PATH);
                if(lstrcmpiW(&(lpszPathName[i]), tempShortPath) != 0)
                {
                    This->bIsLongFileName = TRUE;
                }
            }
        }
        
        else
        {
            GetShortPathNameW(lpszPathName, tempShortPath, MAX_PATH);
            if(lstrcmpiW(lpszPathName, tempShortPath) != 0)
            {
                This->bIsLongFileName = TRUE;
            }
        }
    }
}
/******************************************************************************
 *         FileMoniker_Construct (local function)
 *******************************************************************************/
HRESULT WINAPI FileMonikerImpl_Construct(FileMonikerImpl* This, LPCOLESTR lpszPathName)
{
    int nb=0,i;
    int sizeStr=lstrlenW(lpszPathName);
    LPOLESTR *tabStr=0;
    WCHAR twoPoint[]={'.','.',0};
    WCHAR bkSlash[]={'\\',0};
    BYTE addBkSlash;
    
    TRACE("(%p,%p)\n",This,lpszPathName);

    /* Initialize the virtual fgunction table. */
    This->lpvtbl1      = &VT_FileMonikerImpl;
    This->lpvtbl2      = &VT_ROTDataImpl;
    This->ref          = 0;

    This->filePathName=(WCHAR *)HeapAlloc(GetProcessHeap(),0,sizeof(WCHAR)*(sizeStr+1));

    if (This->filePathName==NULL)
        return E_OUTOFMEMORY;

    lstrcpyW(This->filePathName,lpszPathName);

    nb=FileMonikerImpl_DecomposePath(This->filePathName,&tabStr);

    if (nb > 0 ){

        addBkSlash=1;
        if (lstrcmpW(tabStr[0],twoPoint)!=0)
            addBkSlash=0;
        else
            for(i=0;i<nb;i++){

                if ( (lstrcmpW(tabStr[i],twoPoint)!=0) && (lstrcmpW(tabStr[i],bkSlash)!=0) ){
                    addBkSlash=0;
                    break;
                }
                else

                    if (lstrcmpW(tabStr[i],bkSlash)==0 && i<nb-1 && lstrcmpW(tabStr[i+1],bkSlash)==0){
                        *tabStr[i]=0;
                        sizeStr--;
                        addBkSlash=0;
                        break;
                    }
            }

        if (lstrcmpW(tabStr[nb-1],bkSlash)==0)
            addBkSlash=0;

        This->filePathName=(WCHAR *)HeapReAlloc(GetProcessHeap(),0,This->filePathName,(sizeStr+1)*sizeof(WCHAR));

        *This->filePathName=0;
    
        for(i=0;tabStr[i]!=NULL;i++)
            lstrcatW(This->filePathName,tabStr[i]);
    
        if (addBkSlash)
            lstrcatW(This->filePathName,bkSlash);
    }

    FileMonikerImpl_CheckFileFormat(This, This->filePathName);
    for(i=0; tabStr[i]!=NULL;i++)
        CoTaskMemFree(tabStr[i]);
    CoTaskMemFree(tabStr);

    return S_OK;
}

/******************************************************************************
 *        FileMoniker_Destroy (local function)
 *******************************************************************************/
HRESULT WINAPI FileMonikerImpl_Destroy(FileMonikerImpl* This)
{
    TRACE("(%p)\n",This);

    if (This->filePathName!=NULL)
            HeapFree(GetProcessHeap(),0,This->filePathName);

    HeapFree(GetProcessHeap(),0,This);

    return S_OK;
}

/******************************************************************************
 *                  FileMoniker_BindToObject
 ******************************************************************************/
HRESULT WINAPI FileMonikerImpl_BindToObject(IMoniker* iface,
                                            IBindCtx* pbc,
                                            IMoniker* pmkToLeft,
                                            REFIID riid,
                                            VOID** ppvResult)
{
    HRESULT   res=E_FAIL;
    CLSID     clsID;
    IUnknown* pObj=0;
    IRunningObjectTable *prot=0;
    IPersistFile  *ppf=0;
    IClassFactory *pcf=0;
    IClassActivator *pca=0;
    
    ICOM_THIS(FileMonikerImpl,iface);    

    *ppvResult=0;

    TRACE("(%p,%p,%p,%p,%p)\n",iface,pbc,pmkToLeft,riid,ppvResult);

    if(pmkToLeft==NULL){
        
        res=IBindCtx_GetRunningObjectTable(pbc,&prot);

        if (SUCCEEDED(res)){
            /* if the requested class was loaded befor ! we dont need to reload it */
            res = IRunningObjectTable_GetObject(prot,iface,&pObj);

            if (res==S_FALSE){
                /* first activation of this class */
                res=GetClassFile(This->filePathName,&clsID);
                if (SUCCEEDED(res)){

                    res=CoCreateInstance(&clsID,NULL,CLSCTX_ALL,&IID_IPersistFile,(void**)&ppf);
                    if (SUCCEEDED(res)){

                        res=IPersistFile_Load(ppf,This->filePathName,STGM_READ);
                        if (SUCCEEDED(res)){

                            pObj=(IUnknown*)ppf;
                            IUnknown_AddRef(pObj);
                        }
                    }
                }
            }
        }
    }
    else{
        res=IMoniker_BindToObject(pmkToLeft,pbc,NULL,&IID_IClassFactory,(void**)&pcf);

        if (res==E_NOINTERFACE){

            res=IMoniker_BindToObject(pmkToLeft,pbc,NULL,&IID_IClassActivator,(void**)&pca);
        
            if (res==E_NOINTERFACE)
                return MK_E_INTERMEDIATEINTERFACENOTSUPPORTED;
        }
        if (pcf!=NULL){

            IClassFactory_CreateInstance(pcf,NULL,&IID_IPersistFile,(void**)ppf);

            res=IPersistFile_Load(ppf,This->filePathName,STGM_READ);

            if (SUCCEEDED(res)){

                pObj=(IUnknown*)ppf;
                IUnknown_AddRef(pObj);
            }
        }
        if (pca!=NULL){

            FIXME("()");
            
            /*res=GetClassFile(This->filePathName,&clsID);

            if (SUCCEEDED(res)){

                res=IClassActivator_GetClassObject(pca,&clsID,CLSCTX_ALL,0,&IID_IPersistFile,(void**)&ppf);

                if (SUCCEEDED(res)){

                    pObj=(IUnknown*)ppf;
                    IUnknown_AddRef(pObj);
                }
            }*/
        }
}

    if (pObj!=NULL){
        /* get the requested interface from the loaded class */
        res= IUnknown_QueryInterface(pObj,riid,ppvResult);

        IBindCtx_RegisterObjectBound(pbc,(IUnknown*)*ppvResult);

        IUnknown_Release(pObj);
    }

    if (prot!=NULL)
        IRunningObjectTable_Release(prot);

    if (ppf!=NULL)
        IPersistFile_Release(ppf);

    if (pca!=NULL)
        IClassActivator_Release(pca);

    if (pcf!=NULL)
        IClassFactory_Release(pcf);
    
    return res;
}

/******************************************************************************
 *        FileMoniker_BindToStorage
 ******************************************************************************/
HRESULT WINAPI FileMonikerImpl_BindToStorage(IMoniker* iface,
                                             IBindCtx* pbc,
                                             IMoniker* pmkToLeft,
                                             REFIID riid,
                                             VOID** ppvObject)
{
    LPOLESTR filePath=0;
    IStorage *pstg=0;
    HRESULT res;

    TRACE("(%p,%p,%p,%p,%p)\n",iface,pbc,pmkToLeft,riid,ppvObject);

    if (pmkToLeft==NULL){

        if (IsEqualIID(&IID_IStorage, riid)){

            /* get the file name */
            FileMonikerImpl_GetDisplayName(iface,pbc,pmkToLeft,&filePath);

            /* verifie if the file contains a storage object */
            res=StgIsStorageFile(filePath);

            if(res==S_OK){

                res=StgOpenStorage(filePath,NULL,STGM_READWRITE|STGM_SHARE_DENY_WRITE,NULL,0,&pstg);

                if (SUCCEEDED(res)){

                    *ppvObject=pstg;

                    IStorage_AddRef(pstg);

                    return res;
                }
            }
            CoTaskMemFree(filePath);
        }
        else
            if ( (IsEqualIID(&IID_IStream, riid)) || (IsEqualIID(&IID_ILockBytes, riid)) )

                return E_UNSPEC;
            else

                return E_NOINTERFACE;
    }
    else {

        FIXME("(%p,%p,%p,%p,%p)\n",iface,pbc,pmkToLeft,riid,ppvObject);

    return E_NOTIMPL;
}
    return res;
}

/******************************************************************************
 *        FileMoniker_Reduce
 ******************************************************************************/
HRESULT WINAPI FileMonikerImpl_Reduce(IMoniker* iface,
                                      IBindCtx* pbc,
                                      DWORD dwReduceHowFar,
                                      IMoniker** ppmkToLeft,
                                      IMoniker** ppmkReduced)
{
    TRACE("(%p,%p,%ld,%p,%p)\n",iface,pbc,dwReduceHowFar,ppmkToLeft,ppmkReduced);

    if (ppmkReduced==NULL)
        return E_POINTER;

    FileMonikerImpl_AddRef(iface);

    *ppmkReduced=iface;

    return MK_S_REDUCED_TO_SELF;
}
/******************************************************************************
 *        FileMoniker_ComposeWith
 ******************************************************************************/
HRESULT WINAPI FileMonikerImpl_ComposeWith(IMoniker* iface,
                                           IMoniker* pmkRight,
                                           BOOL fOnlyIfNotGeneric,
                                           IMoniker** ppmkComposite)
{
    HRESULT res;
    LPOLESTR str1=0,str2=0,*strDec1=0,*strDec2=0,newStr=0;
    WCHAR twoPoint[]={'.','.',0};
    WCHAR bkSlash[]={'\\',0};
    IBindCtx *bind=0;
    int i=0,j=0,lastIdx1=0,lastIdx2=0;
    DWORD mkSys;

    TRACE("(%p,%p,%d,%p)\n",iface,pmkRight,fOnlyIfNotGeneric,ppmkComposite);

    if (ppmkComposite==NULL)
        return E_POINTER;

    if (pmkRight==NULL)
	return E_INVALIDARG;

    *ppmkComposite=0;
    
    IMoniker_IsSystemMoniker(pmkRight,&mkSys);

    /* check if we have two filemonikers to compose or not */
    if(mkSys==MKSYS_FILEMONIKER){

        CreateBindCtx(0,&bind);

        FileMonikerImpl_GetDisplayName(iface,bind,NULL,&str1);
        IMoniker_GetDisplayName(pmkRight,bind,NULL,&str2);

        /* decompose pathnames of the two monikers : (to prepare the path merge operation ) */
        lastIdx1=FileMonikerImpl_DecomposePath(str1,&strDec1)-1;
        lastIdx2=FileMonikerImpl_DecomposePath(str2,&strDec2)-1;

        if ((lastIdx1==-1 && lastIdx2>-1)||(lastIdx1==1 && lstrcmpW(strDec1[0],twoPoint)==0))
            return MK_E_SYNTAX;

        if(lstrcmpW(strDec1[lastIdx1],bkSlash)==0)
            lastIdx1--;

        /* for etch "..\" in the left of str2 remove the right element from str1 */
        for(i=0; ( (lastIdx1>=0) && (strDec2[i]!=NULL) && (lstrcmpW(strDec2[i],twoPoint)==0) ) ;i+=2){

            lastIdx1-=2;
        }

        /* the length of the composed path string  is raised by the sum of the two paths lengths  */
        newStr=(WCHAR *)HeapAlloc(GetProcessHeap(),0,sizeof(WCHAR)*(lstrlenW(str1)+lstrlenW(str2)+1));
	
	  if (newStr==NULL)
		return E_OUTOFMEMORY;

        /* new path is the concatenation of the rest of str1 and str2 */
        for(*newStr=0,j=0;j<=lastIdx1;j++)
            lstrcatW(newStr,strDec1[j]);

        if ((strDec2[i]==NULL && lastIdx1>-1 && lastIdx2>-1) || lstrcmpW(strDec2[i],bkSlash)!=0)
            lstrcatW(newStr,bkSlash);
            
        for(j=i;j<=lastIdx2;j++)
            lstrcatW(newStr,strDec2[j]);
        
        /* create a new moniker with the new string */
        res=CreateFileMoniker(newStr,ppmkComposite);

        /* free all strings space memory used by this function */
        HeapFree(GetProcessHeap(),0,newStr);

        for(i=0; strDec1[i]!=NULL;i++)
            CoTaskMemFree(strDec1[i]);
        for(i=0; strDec2[i]!=NULL;i++)
            CoTaskMemFree(strDec2[i]);
        CoTaskMemFree(strDec1);
        CoTaskMemFree(strDec2);

        CoTaskMemFree(str1);
        CoTaskMemFree(str2);

        return res;
    }
    else if(mkSys==MKSYS_ANTIMONIKER){

        *ppmkComposite=NULL;
        return S_OK;
    }
    else if (fOnlyIfNotGeneric){

        *ppmkComposite=NULL;
        return MK_E_NEEDGENERIC;
    }
    else

        return CreateGenericComposite(iface,pmkRight,ppmkComposite);
}

/******************************************************************************
 *        FileMoniker_Enum
 ******************************************************************************/
HRESULT WINAPI FileMonikerImpl_Enum(IMoniker* iface,BOOL fForward, IEnumMoniker** ppenumMoniker)
{
    TRACE("(%p,%d,%p)\n",iface,fForward,ppenumMoniker);

    if (ppenumMoniker == NULL)
        return E_POINTER;

    *ppenumMoniker = NULL;

    return S_OK;
}

/******************************************************************************
 *        FileMoniker_IsEqual
 ******************************************************************************/
HRESULT WINAPI FileMonikerImpl_IsEqual(IMoniker* iface,IMoniker* pmkOtherMoniker)
{
    ICOM_THIS(FileMonikerImpl,iface);
    CLSID clsid;
    LPOLESTR filePath;
    IBindCtx* bind;
    HRESULT res;

    TRACE("(%p,%p)\n",iface,pmkOtherMoniker);

    if (pmkOtherMoniker==NULL)
        return S_FALSE;

    IMoniker_GetClassID(pmkOtherMoniker,&clsid);

    if (!IsEqualCLSID(&clsid,&CLSID_FileMoniker))

        return S_FALSE;

    res=CreateBindCtx(0,&bind);
    if (FAILED(res))
        return res;

    IMoniker_GetDisplayName(pmkOtherMoniker,bind,NULL,&filePath);
    
    if (lstrcmpiW(filePath,
                  This->filePathName)!=0)

        return S_FALSE;
    
    return S_OK;
}

/******************************************************************************
 *        FileMoniker_Hash
 ******************************************************************************/
HRESULT WINAPI FileMonikerImpl_Hash(IMoniker* iface,DWORD* pdwHash)
{
    ICOM_THIS(FileMonikerImpl,iface);

    int  h = 0,i,skip,len;
    int  off = 0;
    LPOLESTR val;

    if (pdwHash==NULL)
        return E_POINTER;
    
    val =  This->filePathName;
    len = lstrlenW(val);

    if (len < 16) {
        for (i = len ; i > 0; i--) {
            h = (h * 37) + val[off++];
 	}
    } else {
        /* only sample some characters */
 	skip = len / 8;
 	for (i = len ; i > 0; i -= skip, off += skip) {
            h = (h * 39) + val[off];
 	}
}

    *pdwHash=h;

    return S_OK;
}

/******************************************************************************
 *        FileMoniker_IsRunning
 ******************************************************************************/
HRESULT WINAPI FileMonikerImpl_IsRunning(IMoniker* iface,
                                         IBindCtx* pbc,
                                         IMoniker* pmkToLeft,
                                         IMoniker* pmkNewlyRunning)
{
    IRunningObjectTable* rot;
    HRESULT res;

    TRACE("(%p,%p,%p,%p)\n",iface,pbc,pmkToLeft,pmkNewlyRunning);

    if ( (pmkNewlyRunning!=NULL) && (IMoniker_IsEqual(pmkNewlyRunning,iface)==S_OK) )
        return S_OK;

    if (pbc==NULL)
        return E_POINTER;

    res=IBindCtx_GetRunningObjectTable(pbc,&rot);

    if (FAILED(res))
        return res;

    res = IRunningObjectTable_IsRunning(rot,iface);

    IRunningObjectTable_Release(rot);

    return res;
}

/******************************************************************************
 *        FileMoniker_GetTimeOfLastChange
 ******************************************************************************/
HRESULT WINAPI FileMonikerImpl_GetTimeOfLastChange(IMoniker* iface,
                                                   IBindCtx* pbc,
                                                   IMoniker* pmkToLeft,
                                                   FILETIME* pFileTime)
{
    ICOM_THIS(FileMonikerImpl,iface);
    IRunningObjectTable* rot;
    HRESULT res;
    WIN32_FILE_ATTRIBUTE_DATA info;

    TRACE("(%p,%p,%p,%p)\n",iface,pbc,pmkToLeft,pFileTime);

    if (pFileTime==NULL)
        return E_POINTER;

    if (pmkToLeft!=NULL)
        return E_INVALIDARG;

    res=IBindCtx_GetRunningObjectTable(pbc,&rot);

    if (FAILED(res))
        return res;

    res= IRunningObjectTable_GetTimeOfLastChange(rot,iface,pFileTime);

    if (FAILED(res))
    { /* the moniker is not registred */

        if (!GetFileAttributesExW(This->filePathName, GetFileExInfoStandard, &info))
            return MK_E_NOOBJECT;
        
        *pFileTime=info.ftLastWriteTime;
    }

    return S_OK;
}

/******************************************************************************
 *        FileMoniker_Inverse
 ******************************************************************************/
HRESULT WINAPI FileMonikerImpl_Inverse(IMoniker* iface,IMoniker** ppmk)
{

    TRACE("(%p,%p)\n",iface,ppmk);

    return CreateAntiMoniker(ppmk);
}

/******************************************************************************
 *        FileMoniker_CommonPrefixWith
 ******************************************************************************/
HRESULT WINAPI FileMonikerImpl_CommonPrefixWith(IMoniker* iface,IMoniker* pmkOther,IMoniker** ppmkPrefix)
{

    LPOLESTR pathThis,pathOther,*stringTable1,*stringTable2,commonPath;
    IBindCtx *pbind;
    DWORD mkSys;
    ULONG nb1,nb2,i,sameIdx;
    BOOL machimeNameCase=FALSE;

    if (ppmkPrefix==NULL)
        return E_POINTER;

    if (pmkOther==NULL)
        return E_INVALIDARG;
    
    *ppmkPrefix=0;
    
    /* check if we have the same type of moniker */
    IMoniker_IsSystemMoniker(pmkOther,&mkSys);

    if(mkSys==MKSYS_FILEMONIKER){

        CreateBindCtx(0,&pbind);

        /* create a string based on common part of the two paths */

        IMoniker_GetDisplayName(iface,pbind,NULL,&pathThis);
        IMoniker_GetDisplayName(pmkOther,pbind,NULL,&pathOther);

        nb1=FileMonikerImpl_DecomposePath(pathThis,&stringTable1);
        nb2=FileMonikerImpl_DecomposePath(pathOther,&stringTable2);

        if (nb1==0 || nb2==0)
            return MK_E_NOPREFIX;

        commonPath=(WCHAR *)HeapAlloc(GetProcessHeap(),0,sizeof(WCHAR)*(min(lstrlenW(pathThis),lstrlenW(pathOther))+1));

        *commonPath=0;
        
        for(sameIdx=0; ( (stringTable1[sameIdx]!=NULL) &&
                         (stringTable2[sameIdx]!=NULL) &&
                         (lstrcmpiW(stringTable1[sameIdx],stringTable2[sameIdx])==0)); sameIdx++);

        if (sameIdx > 1 && *stringTable1[0]=='\\' && *stringTable2[1]=='\\'){

            machimeNameCase=TRUE;

            for(i=2;i<sameIdx;i++)

                if( (*stringTable1[i]=='\\') && (i+1 < sameIdx) && (*stringTable1[i+1]=='\\') ){
                    machimeNameCase=FALSE;
                    break;
}
        }

        if (machimeNameCase && *stringTable1[sameIdx-1]=='\\')
            sameIdx--;
        
        if (machimeNameCase && (sameIdx<=3) && (nb1 > 3 || nb2 > 3) )
            return MK_E_NOPREFIX;

        for(i=0;i<sameIdx;i++)
            lstrcatW(commonPath,stringTable1[i]);
        
        for(i=0;i<nb1;i++)
            CoTaskMemFree(stringTable1[i]);

        CoTaskMemFree(stringTable1);

        for(i=0;i<nb2;i++)
            CoTaskMemFree(stringTable2[i]);

        CoTaskMemFree(stringTable2);

        HeapFree(GetProcessHeap(),0,commonPath);
        
        return CreateFileMoniker(commonPath,ppmkPrefix);
    }
    else
        return MonikerCommonPrefixWith(iface,pmkOther,ppmkPrefix);
}

/******************************************************************************
 *        DecomposePath (local function)
 ******************************************************************************/
int WINAPI FileMonikerImpl_DecomposePath(LPOLESTR str, LPOLESTR** stringTable)
{
    WCHAR bSlash[] = {'\\',0};
    WCHAR word[MAX_PATH];
    int i=0,j,tabIndex=0;
    LPOLESTR *strgtable ;

    int len=lstrlenW(str);

    strgtable = (LPOLESTR *)CoTaskMemAlloc(len*sizeof(LPOLESTR));
    
    if (strgtable==NULL)
	return E_OUTOFMEMORY;
    
    while(str[i]!=0){

        if(str[i]==bSlash[0]){

            strgtable[tabIndex]=(WCHAR *)CoTaskMemAlloc(2*sizeof(WCHAR));

            if (strgtable[tabIndex]==NULL)
	    	return E_OUTOFMEMORY;

            lstrcpyW(strgtable[tabIndex++],bSlash);

            i++;

        }
        else {

            for(j=0; str[i]!=0 && str[i]!=bSlash[0] ; i++,j++)
                word[j]=str[i];

            word[j]=0;

            strgtable[tabIndex]=(WCHAR *)CoTaskMemAlloc(sizeof(WCHAR)*(j+1));

            if (strgtable[tabIndex]==NULL)
                return E_OUTOFMEMORY;

            lstrcpyW(strgtable[tabIndex++],word);
        }
    }
    strgtable[tabIndex]=NULL;
    
    *stringTable=strgtable;
    
    return tabIndex;
}

/******************************************************************************
 *        FileMoniker_RelativePathTo
 ******************************************************************************/
HRESULT WINAPI FileMonikerImpl_RelativePathTo(IMoniker* iface,IMoniker* pmOther, IMoniker** ppmkRelPath)
{
    IBindCtx *bind;
    HRESULT res;
    LPOLESTR str1=0,str2=0,*tabStr1=0,*tabStr2=0,relPath=0;
    DWORD len1=0,len2=0,sameIdx=0,j=0;
    WCHAR back[] ={'.','.','\\',0};
    
    TRACE("(%p,%p,%p)\n",iface,pmOther,ppmkRelPath);

    if (ppmkRelPath==NULL)
        return E_POINTER;

    if (pmOther==NULL)
        return E_INVALIDARG;
    
    res=CreateBindCtx(0,&bind);
    if (FAILED(res))
	return res;

    res=IMoniker_GetDisplayName(iface,bind,NULL,&str1);
    if (FAILED(res))
	return res;
    res=IMoniker_GetDisplayName(pmOther,bind,NULL,&str2);
    if (FAILED(res))
	return res;

    len1=FileMonikerImpl_DecomposePath(str1,&tabStr1);
    len2=FileMonikerImpl_DecomposePath(str2,&tabStr2);

    if (FAILED(len1) || FAILED(len2))
	return E_OUTOFMEMORY;
	
    /* count the number of similar items from the begin of the two paths */
    for(sameIdx=0; ( (tabStr1[sameIdx]!=NULL) &&
		   (tabStr2[sameIdx]!=NULL) &&
               (lstrcmpiW(tabStr1[sameIdx],tabStr2[sameIdx])==0)); sameIdx++);

    /* begin the construction of relativePath */
    /* if the two paths have a consecutive similar item from the begin ! the relativePath will be composed */
    /* by "..\\" in the begin */
    relPath=(WCHAR *)HeapAlloc(GetProcessHeap(),0,sizeof(WCHAR)*(1+lstrlenW(str1)+lstrlenW(str2)));

    *relPath=0;

    if (len2>0 && !(len1==1 && len2==1 && sameIdx==0))
        for(j=sameIdx;(tabStr1[j] != NULL); j++)
            if (*tabStr1[j]!='\\')
                lstrcatW(relPath,back);

    /* add items of the second path (similar items with the first path are not included) to the relativePath */
    for(j=sameIdx;tabStr2[j]!=NULL;j++)
        lstrcatW(relPath,tabStr2[j]);
    
    res=CreateFileMoniker(relPath,ppmkRelPath);
    
    for(j=0; tabStr1[j]!=NULL;j++)
        CoTaskMemFree(tabStr1[j]);
    for(j=0; tabStr2[j]!=NULL;j++)
        CoTaskMemFree(tabStr2[j]);
    CoTaskMemFree(tabStr1);
    CoTaskMemFree(tabStr2);
    CoTaskMemFree(str1);
    CoTaskMemFree(str2);
    HeapFree(GetProcessHeap(),0,relPath);

    if (len1==0 || len2==0 || (len1==1 && len2==1 && sameIdx==0))
        return MK_S_HIM;

    return res;
}

/******************************************************************************
 *        FileMoniker_GetDisplayName
 ******************************************************************************/
HRESULT WINAPI FileMonikerImpl_GetDisplayName(IMoniker* iface,
                                              IBindCtx* pbc,
                                              IMoniker* pmkToLeft,
                                              LPOLESTR *ppszDisplayName)
{
    ICOM_THIS(FileMonikerImpl,iface);

    int len=lstrlenW(This->filePathName);

    TRACE("(%p,%p,%p,%p)\n",iface,pbc,pmkToLeft,ppszDisplayName);

    if (ppszDisplayName==NULL)
        return E_POINTER;

    if (pmkToLeft!=NULL)
        return E_INVALIDARG;

    *ppszDisplayName=(WCHAR *)CoTaskMemAlloc(sizeof(WCHAR)*(len+1));
    if (*ppszDisplayName==NULL)
        return E_OUTOFMEMORY;

    lstrcpyW(*ppszDisplayName,This->filePathName);
    
    return S_OK;
}

/******************************************************************************
 *        FileMoniker_ParseDisplayName
 ******************************************************************************/
HRESULT WINAPI FileMonikerImpl_ParseDisplayName(IMoniker* iface,
                                                IBindCtx* pbc,
                                                IMoniker* pmkToLeft,
                                                LPOLESTR pszDisplayName,
                                                ULONG* pchEaten,
                                                IMoniker** ppmkOut)
{
    FIXME("(%p,%p,%p,%p,%p,%p),stub!\n",iface,pbc,pmkToLeft,pszDisplayName,pchEaten,ppmkOut);
    return E_NOTIMPL;
}

/******************************************************************************
 *        FileMoniker_IsSystemMonker
 ******************************************************************************/
HRESULT WINAPI FileMonikerImpl_IsSystemMoniker(IMoniker* iface,DWORD* pwdMksys)
{
    TRACE("(%p,%p)\n",iface,pwdMksys);

    if (!pwdMksys)
        return E_POINTER;
    
    (*pwdMksys)=MKSYS_FILEMONIKER;

    return S_OK;
}

/*******************************************************************************
 *        FileMonikerIROTData_QueryInterface
 *******************************************************************************/
HRESULT WINAPI FileMonikerROTDataImpl_QueryInterface(IROTData *iface,REFIID riid,VOID** ppvObject)
{

    ICOM_THIS_From_IROTData(IMoniker, iface);

    TRACE("(%p,%p,%p)\n",This,riid,ppvObject);

    return FileMonikerImpl_QueryInterface(This, riid, ppvObject);
}

/***********************************************************************
 *        FileMonikerIROTData_AddRef
 */
ULONG   WINAPI FileMonikerROTDataImpl_AddRef(IROTData *iface)
{
    ICOM_THIS_From_IROTData(IMoniker, iface);

    TRACE("(%p)\n",This);

    return FileMonikerImpl_AddRef(This);
}

/***********************************************************************
 *        FileMonikerIROTData_Release
 */
ULONG   WINAPI FileMonikerROTDataImpl_Release(IROTData* iface)
{
    ICOM_THIS_From_IROTData(IMoniker, iface);
    
    TRACE("(%p)\n",This);

    return FileMonikerImpl_Release(This);
}

/******************************************************************************
 *        FileMonikerIROTData_GetComparaisonData
 ******************************************************************************/
HRESULT WINAPI FileMonikerROTDataImpl_GetComparaisonData(IROTData* iface,
                                                         BYTE* pbData,
                                                         ULONG cbMax,
                                                         ULONG* pcbData)
{
    FIXME("(),stub!\n");
    return E_NOTIMPL;
}

/******************************************************************************
 *        CreateFileMoniker16
 ******************************************************************************/
HRESULT WINAPI CreateFileMoniker16(LPCOLESTR16 lpszPathName,LPMONIKER* ppmk)
{

    FIXME("(%s,%p),stub!\n",lpszPathName,ppmk);
    return E_NOTIMPL;
}

/******************************************************************************
 *        CreateFileMoniker
 ******************************************************************************/
HRESULT WINAPI CreateFileMoniker(LPCOLESTR lpszPathName, LPMONIKER * ppmk)
{
    FileMonikerImpl* newFileMoniker = 0;
    HRESULT  hr = E_FAIL;
    IID riid=IID_IMoniker;

    TRACE("(%p,%p)\n",lpszPathName,ppmk);

    if (ppmk==NULL)
        return E_POINTER;

    if(lpszPathName==NULL)
        return MK_E_SYNTAX;
            
    *ppmk=0;
        
    newFileMoniker = (FileMonikerImpl *)HeapAlloc(GetProcessHeap(), 0, sizeof(FileMonikerImpl));

    if (newFileMoniker == 0)
        return E_OUTOFMEMORY;

    hr = FileMonikerImpl_Construct(newFileMoniker,lpszPathName);

    if (SUCCEEDED(hr))
	hr = FileMonikerImpl_QueryInterface((IMoniker*)newFileMoniker,&riid,(void**)ppmk);
    else
        HeapFree(GetProcessHeap(),0,newFileMoniker);

    return hr;
}
