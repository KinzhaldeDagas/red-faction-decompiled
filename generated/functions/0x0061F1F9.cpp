// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061F1F9 __mbtowc_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): U=stackLocaleUpdate(inputLocale); on every normal
// return AFTERconstruction, clearPTD+112bit2 ONLYif U.cleanupBYTE12nonzero. No own unwind-finally pinrelease.
// Cdecl(optionalWCHAR*out,constchar*source,unsignedbytes,locale),bytesconsumed0/1/localeMax or-1. sourceNULL ORbytes0 ->0BEFOREU,withoutoutputwrite. SourcefirstNUL
// ->writeoutWORD0ifpresent,return0beforeU. NonemptyconstructU;rootLCID+20==0:zeroextendfirstunsignedbyteintooutifpresent,return1. NonCisleadbyte_l(firstunsignedbyte,&U).
// Nonlead:MultiByteToWideChar(rootCP,9,source,1,out,out!=NULL?1:0);nonzero->1,zero->errno42/-1. Lead:max=SIGNEDrootDWORD+172. Ifmax>1
// ANDSIGNED(bytes)>=max,attemptMultiByteToWideChar(rootCP,9,source,max,out,out!=NULL?1:0);nonzero->returnmax. Otherwise INCLUDINGfailedAPI,UNSIGNEDbytes>=max ANDsource[1]!=0
// ->returnmaxWITHOUTownerror/outputinitialization. Thus invalidpaircanreportsuccesslengthafterAPIfailure;fallbackmayreadsource[1]evenmax<=1. Onlyfallbacktoosmall/secondNUL sets
// errno42/-1. No invalidcallback,completeencodedcharacter-validation,state,bufferfillorrollback.
int __cdecl _mbtowc_l(wchar_t *DstCh, const char *SrcCh, size_t SrcSizeInBytes, _locale_t Locale)
{
  int result; // eax
  struct __crt_locale_data *locinfo; // eax
  int v6; // ecx
  bool v7; // zf
  __crt_locale_pointers Localea; // [esp+8h] [ebp-10h] BYREF
  int v9; // [esp+10h] [ebp-8h]
  char v10; // [esp+14h] [ebp-4h]

  if ( !SrcCh || !SrcSizeInBytes )
    return 0;
  if ( !*SrcCh )
  {
    if ( DstCh )
      *DstCh = 0;
    return 0;
  }
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&Localea, (struct localeinfo_struct *)Locale);
  if ( !*((_DWORD *)Localea.locinfo + 5) )
  {
    if ( DstCh )
      *DstCh = *(unsigned __int8 *)SrcCh;
    goto LABEL_11;
  }
  if ( _isleadbyte_l(*(unsigned __int8 *)SrcCh, &Localea) )
  {
    locinfo = Localea.locinfo;
    v6 = *((_DWORD *)Localea.locinfo + 43);
    if ( v6 > 1
      && (int)SrcSizeInBytes >= v6
      && (v7 = MultiByteToWideChar(*((_DWORD *)Localea.locinfo + 1), 9u, SrcCh, v6, DstCh, DstCh != nullptr) == 0,
          locinfo = Localea.locinfo,
          !v7)
      || SrcSizeInBytes >= *((_DWORD *)locinfo + 43) && SrcCh[1] )
    {
      result = *((_DWORD *)locinfo + 43);
      if ( v10 )
        *(_DWORD *)(v9 + 112) &= ~2u;
      return result;
    }
  }
  else if ( MultiByteToWideChar(*((_DWORD *)Localea.locinfo + 1), 9u, SrcCh, 1, DstCh, DstCh != nullptr) )
  {
LABEL_11:
    if ( v10 )
      *(_DWORD *)(v9 + 112) &= ~2u;
    return 1;
  }
  *_errno() = 42;
  if ( v10 )
    *(_DWORD *)(v9 + 112) &= ~2u;
  return -1;
}

