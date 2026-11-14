// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061E042 ?__crtGetStringTypeA_stat@@YAHPAUlocaleinfo_struct@@KPBDHPAGHHH@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Internal ECX=localeinfo pointer,EAX
// rawBOOL/int,SEVENcaller-cleanedstackslots(infoType,constchar*source,SIGNEDbyteCount,WORD*types,UINTcodepage,LCID,finalFlag); correctedfalsecdecl/missingECX/pointer-likecount.
// NoownNULL/countvalidationorcalleroutputinitialization. Cache2021DCC0
// probesGetStringTypeW(1,fixedoneWCHAR,1,OWNstacktemp);successmode1,error120mode2,otherfailureleaves0andusesANSI;invalidnonzerootherthan1/2->0.
// Wmode:CP0fromlocaleRoot+4;MultiByteToWideCharqueryflags1|(finalFlag!=0?8:0),0->0WITHOUTtouchingcalleroutput.
// Requirepositivequeryn<=0x7FFFFFF0;allocate2*n+8,<=1024stackprobe/headerCCCC,largerheapmalloc/headerDDDD,data+8;allocationNULL->0withoutcalleroutputwrite.
// MemsetONLYconversiontemporary2*nbytes0,actualconversionflags1;0->freea/0.
// NonzeroactualUTF16unitcountcallsGetStringTypeW(infoType,temp,ACTUALcount,callerWORDoutput),rawBOOLforwardedafterfreea.
// Noequalquery/actualcountrequirement,outputelementcapacityvalidationorper-input-bytepadding. ANSImode0/2:LCID0fromlocaleRoot+20,CP0fromroot+4;ansicp==-1->0.
// DifferentlocaleACPconvertsourceviaconvertcp(inputCP,localeACP,source,&byteCount,NULL,0),NULL->0;otherwiseuseoriginalsource.
// GetStringTypeA(LCID,infoType,source,currentbyteCount,types),freeconvertedsourceifowned,rawBOOLreturn. Nonpositivecountsforwardedraw,notNUL-trimmedhere.
// Cookiecheckednormalreturns;noownerrno mapping,exception-finallyorrollback.
// Sizequery/allocation/conversionfailurecanreturn0withoutinitializingcallerWORDarray,confirmingsetSBUpLowunchecked-outputpath.
int __usercall __crtGetStringTypeA_stat@<eax>(
        struct localeinfo_struct *a1@<ecx>,
        DWORD dwInfoType,
        const char *lpMultiByteStr,
        int cbMultiByte,
        WORD *lpCharType,
        UINT CodePage,
        LCID Locale,
        int a8)
{
  int v8; // eax
  void *v9; // ebx
  int v11; // eax
  int v12; // edi
  unsigned int v13; // eax
  void *v14; // esp
  _DWORD *v15; // eax
  int v16; // eax
  char *v18; // esi
  UINT v19; // eax
  const char *v20; // eax
  BOOL StringTypeA; // edi
  _DWORD v22[3]; // [esp+0h] [ebp-14h] BYREF
  WORD CharType[2]; // [esp+Ch] [ebp-8h] BYREF

  v8 = unk_2021DCC;
  v9 = nullptr;
  if ( !unk_2021DCC )
  {
    if ( GetStringTypeW(1u, &String1, 1, CharType) )
    {
      unk_2021DCC = 1;
      goto LABEL_10;
    }
    if ( GetLastError() == 120 )
    {
      v8 = 2;
      unk_2021DCC = 2;
    }
    else
    {
      v8 = unk_2021DCC;
    }
  }
  if ( v8 != 2 && v8 )
  {
    if ( v8 != 1 )
      return 0;
LABEL_10:
    *(_DWORD *)CharType = 0;
    if ( !CodePage )
      CodePage = *(_DWORD *)(*(_DWORD *)a1 + 4);
    v11 = MultiByteToWideChar(CodePage, 8 * (a8 != 0) + 1, lpMultiByteStr, cbMultiByte, nullptr, 0);
    v12 = v11;
    if ( !v11 )
      return 0;
    if ( v11 <= 0 || (unsigned int)v11 > 0x7FFFFFF0 )
      goto LABEL_22;
    v13 = 2 * v11 + 8;
    if ( v13 > 0x400 )
    {
      v15 = malloc(2 * v12 + 8);
      if ( v15 )
      {
        *v15 = 56797;
        goto LABEL_20;
      }
    }
    else
    {
      v14 = alloca(v13);
      v15 = v22;
      if ( v22 )
      {
        v22[0] = 52428;
LABEL_20:
        v15 += 2;
      }
    }
    v9 = v15;
LABEL_22:
    if ( v9 )
    {
      memset(v9, 0, 2 * v12);
      v16 = MultiByteToWideChar(CodePage, 1u, lpMultiByteStr, cbMultiByte, (LPWSTR)v9, v12);
      if ( v16 )
        *(_DWORD *)CharType = GetStringTypeW(dwInfoType, (LPCWCH)v9, v16, lpCharType);
      _freea(v9);
      return *(_DWORD *)CharType;
    }
    return 0;
  }
  v18 = nullptr;
  if ( !Locale )
    Locale = *(_DWORD *)(*(_DWORD *)a1 + 20);
  if ( !CodePage )
    CodePage = *(_DWORD *)(*(_DWORD *)a1 + 4);
  v19 = __ansicp(Locale);
  if ( v19 == -1 )
    return 0;
  if ( v19 != CodePage )
  {
    v20 = (const char *)__convertcp(CodePage, v19, lpMultiByteStr, &cbMultiByte, nullptr, 0);
    v18 = (char *)v20;
    if ( !v20 )
      return 0;
    lpMultiByteStr = v20;
  }
  StringTypeA = GetStringTypeA(Locale, dwInfoType, lpMultiByteStr, cbMultiByte, lpCharType);
  if ( v18 )
    free(v18);
  return StringTypeA;
}

