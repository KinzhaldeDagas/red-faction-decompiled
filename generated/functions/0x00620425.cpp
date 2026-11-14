// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00620425 __mbsrchr_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid(E) means errnoE plus
// invalid_parameter(NULL,NULL,NULL,0,0); stated returns require callbackreturn. U=stackLocaleUpdate(inputLocale); on every normal return AFTERconstruction, clearPTD+112bit2 ONLYif
// U.cleanupBYTE12nonzero. No own unwind-finally pinrelease. MBrecord=U.secondpointer: flagDWORD+8,LCID+12,CP+4,class[c]BYTE+29+c withleadbit4/uppercasebit10h,caseMap[c]BYTE+285+c;
// two inclusiveWORDfoldranges(start16,end18,delta20) and(start22,end24,delta26),additionmodulo16. Cdecl(source,unsigned32C,locale),borrowedlastmatch/NULL. ConstructUthenNULLsource
// invalid22/NULL. MBflag0 delegatesstrrchr(rawC);MBpathcomparesFULLDWORDCtozeroextendedsinglebyteorbig-endianlead<<8|trail,nevermatchestrailbytesalone.
// ScanincludesordinaryterminalNUL,soC0returnsit. Completelead+nonzeroTrail:matchrecordsLEADaddress.
// CRUCIALdanglinglead+NUL:ifNOpriorrecordedmatch,recordCURRENTNULpointerREGARDLESSC;otherwisekeepprior match;thenstop. Consequentlymalformedtrailing
// leadcanreturnendpointerforanabsentnonzerocharacter. NoC-range/trailvalidation,allocation,mutationorownerrnoonmalformedsource.
unsigned __int8 *__cdecl _mbsrchr_l(const unsigned __int8 *String, unsigned int C, _locale_t Locale)
{
  const unsigned __int8 *v3; // ecx
  unsigned __int8 *result; // eax
  unsigned __int8 v5; // dl
  int v6; // eax
  bool v7; // zf
  _BYTE v8[4]; // [esp+4h] [ebp-14h] BYREF
  int v9; // [esp+8h] [ebp-10h]
  int v10; // [esp+Ch] [ebp-Ch]
  char v11; // [esp+10h] [ebp-8h]
  unsigned __int8 *v12; // [esp+14h] [ebp-4h]

  v12 = nullptr;
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)v8, (struct localeinfo_struct *)Locale);
  v3 = String;
  if ( !String )
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    if ( v11 )
      *(_DWORD *)(v10 + 112) &= ~2u;
    return nullptr;
  }
  if ( !*(_DWORD *)(v9 + 8) )
  {
    result = (unsigned __int8 *)strrchr((const char *)String, C);
    if ( v11 )
      *(_DWORD *)(v10 + 112) &= ~2u;
    return result;
  }
  do
  {
    v5 = *v3;
    v6 = *v3;
    if ( (*(_BYTE *)((unsigned __int8)v6 + v9 + 29) & 4) != 0 )
    {
      v5 = *++v3;
      if ( *v3 )
      {
        if ( C == (v5 | (v6 << 8)) )
          v12 = (unsigned __int8 *)(v3 - 1);
        goto LABEL_16;
      }
      v7 = v12 == nullptr;
    }
    else
    {
      v7 = C == v6;
    }
    if ( v7 )
      v12 = (unsigned __int8 *)v3;
LABEL_16:
    ++v3;
  }
  while ( v5 );
  if ( v11 )
    *(_DWORD *)(v10 + 112) &= ~2u;
  return v12;
}

