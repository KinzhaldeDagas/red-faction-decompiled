// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061DB39 __wctomb_s_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid(E) means errnoE plus
// invalid_parameter(NULL,NULL,NULL,0,0); stated returns require callbackreturn. U=stackLocaleUpdate(inputLocale); on every normal return AFTERconstruction, clearPTD+112bit2 ONLYif
// U.cleanupBYTE12nonzero. No own unwind-finally pinrelease. Cdecl(optionalint*converted,char*out,unsignedcapacity,WCHAR,locale),errno-style0/E. outNULL ANDcapacity>0
// FIRSTreturns0/writesconverted0ifpresent,BEFOREINT_MAXcheckorlocaleconstruction,evenhugecapacity. Othercasesinitializeconverted=-1ifpresent. capacity>INT_MAX invalid22/22beforeU.
// ConstructU;rootLCID+20==0:Cpath,WCHAR>255 ->zeroALLcapacitybytesifoutnonNULL/capacity>0,errno42/42. ValidbyteWCHAR:outnonnullcapacity0
// invalid34/34;elsewriteLOWBYTEifout,converted1,success0 (outNULL/capacity0validquery). NonC:WideCharToMultiByte(rootCP,0,&WCHAR,1,out,capacity,NULL,&usedDefaultBOOL),BOOLlocal0.
// APInonzeroandusedDefault0 ->converted=returnedbytecount,0. SubstitutionORAPI0othererror ->errno42/42,outputNOTcleared/rolledback. API0/GetLastError122
// ->zeroALLcapacityifoutandpositive,invalid34/34. NonCdoesnotpre-rejectoutnonnullcapacity0;OSquerybehaviorforwarded. No
// conversionstate,ownallocation,dosmaperr,successerrnoclearorNULappendingbeyondencodingWCHAR0.
errno_t __cdecl _wctomb_s_l(int *SizeConverted, char *MbCh, size_t SizeInBytes, wchar_t WCh, _locale_t Locale)
{
  char *v5; // esi
  size_t v6; // edi
  errno_t result; // eax
  errno_t v8; // esi
  int v9; // eax
  int v10; // [esp+Ch] [ebp-10h] BYREF
  int v11; // [esp+14h] [ebp-8h]
  char v12; // [esp+18h] [ebp-4h]

  v5 = MbCh;
  v6 = SizeInBytes;
  if ( !MbCh && SizeInBytes )
  {
    if ( SizeConverted )
      *SizeConverted = 0;
    return 0;
  }
  if ( SizeConverted )
    *SizeConverted = -1;
  if ( v6 > 0x7FFFFFFF )
  {
    v8 = 22;
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return v8;
  }
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&v10, (struct localeinfo_struct *)Locale);
  if ( !*(_DWORD *)(v10 + 20) )
  {
    if ( WCh > 0xFFu )
    {
      if ( v5 && v6 )
        memset(v5, 0, v6);
      goto LABEL_16;
    }
    if ( v5 )
    {
      if ( !v6 )
      {
LABEL_21:
        v8 = 34;
        *_errno() = 34;
        _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
        if ( v12 )
          *(_DWORD *)(v11 + 112) &= ~2u;
        return v8;
      }
      *v5 = WCh;
    }
    if ( SizeConverted )
      *SizeConverted = 1;
LABEL_26:
    if ( v12 )
      *(_DWORD *)(v11 + 112) &= ~2u;
    return 0;
  }
  MbCh = nullptr;
  v9 = WideCharToMultiByte(*(_DWORD *)(v10 + 4), 0, &WCh, 1, v5, v6, nullptr, (LPBOOL)&MbCh);
  if ( v9 )
  {
    if ( !MbCh )
    {
      if ( SizeConverted )
        *SizeConverted = v9;
      goto LABEL_26;
    }
  }
  else if ( GetLastError() == 122 )
  {
    if ( v5 && v6 )
      memset(v5, 0, v6);
    goto LABEL_21;
  }
LABEL_16:
  *_errno() = 42;
  result = *_errno();
  if ( v12 )
    *(_DWORD *)(v11 + 112) &= ~2u;
  return result;
}

