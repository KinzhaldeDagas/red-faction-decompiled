// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00621FA7 __mbschr_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid(E) means errnoE plus
// invalid_parameter(NULL,NULL,NULL,0,0); stated returns require callbackreturn. U=stackLocaleUpdate(inputLocale); on every normal return AFTERconstruction, clearPTD+112bit2 ONLYif
// U.cleanupBYTE12nonzero. No own unwind-finally pinrelease. MBrecord=U.secondpointer: flagDWORD+8,LCID+12,CP+4,class[c]BYTE+29+c withleadbit4/uppercasebit10h,caseMap[c]BYTE+285+c;
// two inclusiveWORDfoldranges(start16,end18,delta20) and(start22,end24,delta26),additionmodulo16. Cdecl(source,unsigned32C,locale),borrowedfirstmatch/NULL. ConstructUthenNULLsource
// invalid22/NULL. MBflag0 delegatesstrchr(rawC). MBpathcomparesFULLDWORDCtosinglebyte/big-endianDBCSchar;validmatchreturnscharstart,trailbytesnevertestedindependently.
// OrdinaryNULmatchedONLYifC0. Danglinglead+NULreturnsNULLunconditionally,EVENsearchC0 (differsfrommbsrchr_l). Nohigh-C/trailvalidation,allocation,mutationorownerrnoformalformedtext.
unsigned __int8 *__cdecl _mbschr_l(const unsigned __int8 *Str, unsigned int C, _locale_t Locale)
{
  unsigned __int8 *result; // eax
  unsigned __int16 v4; // cx
  _BYTE v5[4]; // [esp+4h] [ebp-10h] BYREF
  int v6; // [esp+8h] [ebp-Ch]
  int v7; // [esp+Ch] [ebp-8h]
  char v8; // [esp+10h] [ebp-4h]

  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)v5, (struct localeinfo_struct *)Locale);
  result = (unsigned __int8 *)Str;
  if ( Str )
  {
    if ( *(_DWORD *)(v6 + 8) )
    {
      while ( 1 )
      {
        v4 = *result;
        if ( !*result )
          break;
        if ( (*(_BYTE *)((unsigned __int8)v4 + v6 + 29) & 4) != 0 )
        {
          if ( !*++result )
            goto LABEL_17;
          if ( C == (*result | (v4 << 8)) )
          {
            --result;
            goto LABEL_15;
          }
        }
        else if ( C == *result )
        {
          break;
        }
        ++result;
      }
      if ( C == *result )
        goto LABEL_15;
LABEL_17:
      if ( v8 )
        *(_DWORD *)(v7 + 112) &= ~2u;
      return nullptr;
    }
    else
    {
      result = (unsigned __int8 *)strchr((const char *)Str, C);
LABEL_15:
      if ( v8 )
        *(_DWORD *)(v7 + 112) &= ~2u;
    }
  }
  else
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    if ( v8 )
      *(_DWORD *)(v7 + 112) &= ~2u;
    return nullptr;
  }
  return result;
}

