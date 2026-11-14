// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061CD22 __mbsnbicoll_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid(E) means errnoE plus
// invalid_parameter(NULL,NULL,NULL,0,0); stated returns require callbackreturn. U=stackLocaleUpdate(inputLocale); on every normal return AFTERconstruction, clearPTD+112bit2 ONLYif
// U.cleanupBYTE12nonzero. No own unwind-finally pinrelease. MBrecord=U.secondpointer: flagDWORD+8,LCID+12,CP+4,class[c]BYTE+29+c withleadbit4/uppercasebit10h,caseMap[c]BYTE+285+c;
// two inclusiveWORDfoldranges(start16,end18,delta20) and(start22,end24,delta26),additionmodulo16. Cdecl(left,right,unsignedBYTEcount,locale),intcollation. ConstructUthen
// count0returns0BEFOREpointerchecks. NonzeroNULLleft/right ORcount>INT_MAX ->invalid22/INT_MAX. MBflag0 delegatesstrnicoll_l(left,right,count,ORIGINALlocale). MBflag!=0
// crtCompareStringA(&U,MBLCID,1001h,left,count,right,count,MBCP);nonzero ->result-2,zero ->INT_MAXWITHOUTownerrnoassignment/invalidcallback. Countisbytebound,notcharcount.
// Noowncopy/fullUTFvalidation; errnoeffectsfromdelegatespreserved.
int __cdecl _mbsnbicoll_l(const unsigned __int8 *Str1, const unsigned __int8 *Str2, size_t MaxCount, _locale_t Locale)
{
  int result; // eax
  int v5; // eax
  _BYTE v6[4]; // [esp+4h] [ebp-10h] BYREF
  UINT *v7; // [esp+8h] [ebp-Ch]
  int v8; // [esp+Ch] [ebp-8h]
  char v9; // [esp+10h] [ebp-4h]

  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)v6, (struct localeinfo_struct *)Locale);
  if ( !MaxCount )
  {
    if ( v9 )
      *(_DWORD *)(v8 + 112) &= ~2u;
    return 0;
  }
  if ( Str1 && Str2 )
  {
    if ( MaxCount > 0x7FFFFFFF )
    {
      *_errno() = 22;
      _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
LABEL_15:
      if ( v9 )
        *(_DWORD *)(v8 + 112) &= ~2u;
      return 0x7FFFFFFF;
    }
    if ( v7[2] )
    {
      v5 = __crtCompareStringA(
             (struct localeinfo_struct *)v6,
             v7[3],
             0x1001u,
             (const char *)Str1,
             MaxCount,
             (const char *)Str2,
             MaxCount,
             v7[1]);
      if ( !v5 )
        goto LABEL_15;
      result = v5 - 2;
    }
    else
    {
      result = _strnicoll_l((const char *)Str1, (const char *)Str2, MaxCount, Locale);
    }
    if ( v9 )
      *(_DWORD *)(v8 + 112) &= ~2u;
  }
  else
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    if ( v9 )
      *(_DWORD *)(v8 + 112) &= ~2u;
    return 0x7FFFFFFF;
  }
  return result;
}

