// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006201E8 __mbsicmp_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid(E) means errnoE plus
// invalid_parameter(NULL,NULL,NULL,0,0); stated returns require callbackreturn. U=stackLocaleUpdate(inputLocale); on every normal return AFTERconstruction, clearPTD+112bit2 ONLYif
// U.cleanupBYTE12nonzero. No own unwind-finally pinrelease. MBrecord=U.secondpointer: flagDWORD+8,LCID+12,CP+4,class[c]BYTE+29+c withleadbit4/uppercasebit10h,caseMap[c]BYTE+285+c;
// two inclusiveWORDfoldranges(start16,end18,delta20) and(start22,end24,delta26),additionmodulo16. Cdecl(left,right,locale),intcompare.
// ConstructU,validatebothnonNULLBEFOREMBflagfallback,invalid22/INT_MAX. MBflag0 delegatesstricmp_l(left,right,&U). MBpath:singlebyteuppercasebit10h
// ->caseMap(loweroppositecase),otherwiseunchanged. CompleteDBCSlead+nonzeroTrail ->crtLCMapStringA(&U,MBLCID,200h,original2bytes,2,stack2bytes,2,MBCP,1).
// Return1usesLOWBYTEoutput,return2formsoutput[0]<<8|output[1];ANYotherresult ->errno22/INT_MAXWITHOUTinvalidcallback. Danglinglead+NULtreatedchar0.
// Compareunsigned16mappedchars,normalized-1/0/+1;loopuntilequal0. EachDBCSinputconsumes2bytesevenwhenmappingoutput1; no trailclasscheck.
// DBCSusesUPPERCASEmap200h,unlikeboundedWORDfolding;singlebytepathusesclassmap. Outputscratchnotinitialized;mappinghelperpositive-unwrittenreturncanpropagateuncheckeddata.
// Noowncapacitylimit,allocationorrollback.
int __cdecl _mbsicmp_l(const unsigned __int8 *Str1, const unsigned __int8 *Str2, _locale_t Locale)
{
  const unsigned __int8 *v3; // edx
  int result; // eax
  const unsigned __int8 *v5; // ebx
  struct __crt_multibyte_data *mbcinfo; // eax
  unsigned __int16 v7; // cx
  char *v8; // edx
  unsigned __int16 v9; // si
  int v10; // eax
  unsigned __int16 v11; // ax
  unsigned __int16 v12; // dx
  char *v13; // ecx
  unsigned __int16 v14; // cx
  unsigned __int16 v15; // cx
  int v16; // eax
  unsigned __int16 v17; // ax
  unsigned __int16 v18; // dx
  char *v19; // ecx
  __crt_locale_pointers Localea; // [esp+4h] [ebp-14h] BYREF
  int v21; // [esp+Ch] [ebp-Ch]
  char v22; // [esp+10h] [ebp-8h]
  unsigned __int8 DestStr; // [esp+14h] [ebp-4h] BYREF
  unsigned __int8 DestStr_1; // [esp+15h] [ebp-3h]
  char *String1; // [esp+20h] [ebp+8h]

  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&Localea, (struct localeinfo_struct *)Locale);
  v3 = Str1;
  if ( !Str1 )
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    if ( v22 )
      *(_DWORD *)(v21 + 112) &= ~2u;
    return 0x7FFFFFFF;
  }
  v5 = Str2;
  if ( !Str2 )
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    if ( v22 )
      *(_DWORD *)(v21 + 112) &= ~2u;
    return 0x7FFFFFFF;
  }
  mbcinfo = Localea.mbcinfo;
  if ( !*((_DWORD *)Localea.mbcinfo + 2) )
  {
    result = _stricmp_l((const char *)Str1, (const char *)Str2, &Localea);
    if ( v22 )
      *(_DWORD *)(v21 + 112) &= ~2u;
    return result;
  }
  while ( 1 )
  {
    v7 = *v3;
    v8 = (char *)(v3 + 1);
    String1 = v8;
    if ( (*((_BYTE *)mbcinfo + (unsigned __int8)v7 + 29) & 4) != 0 )
    {
      if ( *v8 )
      {
        v10 = __crtLCMapStringA(
                (struct localeinfo_struct *)&Localea,
                *((_DWORD *)mbcinfo + 3),
                0x200u,
                v8 - 1,
                2,
                (char *)&DestStr,
                2,
                *((_DWORD *)mbcinfo + 1),
                1);
        if ( v10 == 1 )
        {
          v11 = DestStr;
        }
        else
        {
          if ( v10 != 2 )
            goto LABEL_37;
          v11 = DestStr_1 + (DestStr << 8);
        }
        ++String1;
        v9 = v11;
        mbcinfo = Localea.mbcinfo;
      }
      else
      {
        v9 = 0;
      }
    }
    else
    {
      v12 = v7;
      v13 = (char *)mbcinfo + v7;
      v9 = (v13[29] & 0x10) != 0 ? (unsigned __int8)v13[285] : v12;
    }
    v14 = *v5++;
    if ( (*((_BYTE *)mbcinfo + (unsigned __int8)v14 + 29) & 4) != 0 )
      break;
    v18 = v14;
    v19 = (char *)mbcinfo + v14;
    if ( (v19[29] & 0x10) != 0 )
      v15 = (unsigned __int8)v19[285];
    else
      v15 = v18;
LABEL_34:
    if ( v15 != v9 )
    {
      result = v15 < v9 ? 1 : -1;
      if ( v22 )
        *(_DWORD *)(v21 + 112) &= ~2u;
      return result;
    }
    if ( !v9 )
    {
      if ( v22 )
        *(_DWORD *)(v21 + 112) &= ~2u;
      return 0;
    }
    v3 = (const unsigned __int8 *)String1;
  }
  if ( !*v5 )
  {
    v15 = 0;
    goto LABEL_34;
  }
  v16 = __crtLCMapStringA(
          (struct localeinfo_struct *)&Localea,
          *((_DWORD *)mbcinfo + 3),
          0x200u,
          (const char *)v5 - 1,
          2,
          (char *)&DestStr,
          2,
          *((_DWORD *)mbcinfo + 1),
          1);
  if ( v16 == 1 )
  {
    v17 = DestStr;
LABEL_30:
    v15 = v17;
    mbcinfo = Localea.mbcinfo;
    ++v5;
    goto LABEL_34;
  }
  if ( v16 == 2 )
  {
    v17 = DestStr_1 + (DestStr << 8);
    goto LABEL_30;
  }
LABEL_37:
  *_errno() = 22;
  if ( v22 )
    *(_DWORD *)(v21 + 112) &= ~2u;
  return 0x7FFFFFFF;
}

