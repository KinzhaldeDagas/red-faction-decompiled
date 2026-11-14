// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061ED6B __mbsnbicmp_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid(E) means errnoE plus
// invalid_parameter(NULL,NULL,NULL,0,0); stated returns require callbackreturn. U=stackLocaleUpdate(inputLocale); on every normal return AFTERconstruction, clearPTD+112bit2 ONLYif
// U.cleanupBYTE12nonzero. No own unwind-finally pinrelease. MBrecord=U.secondpointer: flagDWORD+8,LCID+12,CP+4,class[c]BYTE+29+c withleadbit4/uppercasebit10h,caseMap[c]BYTE+285+c;
// two inclusiveWORDfoldranges(start16,end18,delta20) and(start22,end24,delta26),additionmodulo16. Cdecl(left,right,unsignedBYTEcount,locale). ConstructUthen
// count0->0withoutpointerchecks. MBflag0 delegatesCURRENTglobal-locale strnicmp(left,right,count),NOTexplicitlocale. MBpathNULLinputs invalid22/INT_MAX.
// MBpathsharedBYTEbudget:eachiterationreadleftfirstbyte,advanceleft/decrementbudgetONCE. Leftleadwithbudget0 treatsleftchar0; ifrightfirstbyteisALSOlead
// returnequal0immediately,elsecompare0torightRAWbyte(withoutcasefold). Leftleadwithbudget>0 andtrailNUL
// ->char0,otherwiseconsumelefttrail/formlead<<8|trailWITHOUTadditionalbudgetdecrement.
// Readrightfirstbyte/advance;rightleadwithbudget0->char0,elsedecrementbudgetONCEandconsume/formtrailiffnonNUL,otherwisechar0. Thus
// additionalbudgetdecrementisdrivenbyRIGHTlead,notbothstringsindependently. Compareunsigned16chars;differentnormalized-1/+1;equal0charORbudget0->0,elseloop. No
// trailingbyte-classvalidation orINT_MAXlimit. CompleteDBCScharsfoldbyfirstmatchingWORDrange+delta;singlebyteswithuppercasebit10hfoldviaBYTEcaseMap,otherwiseunchanged.
// Dangling/truncatedleadbecomes0ratherthanerrno; onlyterminal-left-budgetcasecomparesrightRAWbytewithoutfold. NoownNLSAPIorallocation.
int __cdecl _mbsnbicmp_l(const unsigned __int8 *Str1, const unsigned __int8 *Str2, size_t MaxCount, _locale_t Locale)
{
  int result; // eax
  const unsigned __int8 *v5; // edi
  unsigned __int16 v6; // cx
  bool v7; // zf
  int v8; // ecx
  unsigned __int16 v9; // si
  unsigned __int8 v10; // dl
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  _BYTE v17[4]; // [esp+4h] [ebp-18h] BYREF
  int v18; // [esp+8h] [ebp-14h]
  int v19; // [esp+Ch] [ebp-10h]
  char v20; // [esp+10h] [ebp-Ch]
  int v21; // [esp+14h] [ebp-8h]
  int v22; // [esp+18h] [ebp-4h]

  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)v17, (struct localeinfo_struct *)Locale);
  if ( !MaxCount )
  {
    if ( v20 )
      *(_DWORD *)(v19 + 112) &= ~2u;
    return 0;
  }
  if ( !*(_DWORD *)(v18 + 8) )
  {
    result = _strnicmp((const char *)Str1, (const char *)Str2, MaxCount);
    if ( v20 )
      *(_DWORD *)(v19 + 112) &= ~2u;
    return result;
  }
  if ( !Str1 )
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    if ( v20 )
      *(_DWORD *)(v19 + 112) &= ~2u;
    return 0x7FFFFFFF;
  }
  v5 = Str2;
  if ( !Str2 )
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    if ( v20 )
      *(_DWORD *)(v19 + 112) &= ~2u;
    return 0x7FFFFFFF;
  }
  while ( 1 )
  {
    v6 = *Str1;
    --MaxCount;
    ++Str1;
    v7 = (*(_BYTE *)((unsigned __int8)v6 + v18 + 29) & 4) == 0;
    v21 = v6;
    if ( v7 )
    {
      v12 = (unsigned __int16)v21 + v18;
      if ( (*(_BYTE *)(v12 + 29) & 0x10) != 0 )
        v13 = *(unsigned __int8 *)(v12 + 285);
      else
        v13 = (unsigned __int16)v21;
      v21 = v13;
      goto LABEL_32;
    }
    if ( !MaxCount )
    {
      v8 = *v5;
      v7 = (*(_BYTE *)(v8 + v18 + 29) & 4) == 0;
      v21 = 0;
      if ( !v7 )
        goto LABEL_51;
      v8 = (unsigned __int16)v8;
      v9 = 0;
      goto LABEL_46;
    }
    if ( !*Str1 )
    {
      v21 = 0;
LABEL_32:
      v9 = v21;
      goto LABEL_33;
    }
    v10 = *Str1++;
    v11 = (unsigned __int16)(v10 | (unsigned __int16)(v6 << 8));
    v9 = v11;
    v21 = v11;
    if ( (unsigned __int16)v11 < *(_WORD *)(v18 + 16) || (unsigned __int16)v11 > *(_WORD *)(v18 + 18) )
    {
      if ( (unsigned __int16)v11 >= *(_WORD *)(v18 + 22) && (unsigned __int16)v11 <= *(_WORD *)(v18 + 24) )
        v9 = *(_WORD *)(v18 + 26) + v11;
    }
    else
    {
      v9 = *(_WORD *)(v18 + 20) + v11;
    }
LABEL_33:
    v14 = *v5++;
    v7 = (*(_BYTE *)((unsigned __int8)v14 + v18 + 29) & 4) == 0;
    v22 = v14;
    if ( v7 )
    {
      v16 = (unsigned __int16)v22 + v18;
      if ( (*(_BYTE *)(v16 + 29) & 0x10) != 0 )
        v8 = *(unsigned __int8 *)(v16 + 285);
      else
        v8 = (unsigned __int16)v22;
LABEL_46:
      v22 = v8;
      goto LABEL_47;
    }
    if ( !MaxCount || (--MaxCount, !*v5) )
    {
      v22 = 0;
LABEL_47:
      LOWORD(v15) = v22;
      goto $test$27298;
    }
    v15 = (unsigned __int16)(*v5++ | (unsigned __int16)((_WORD)v14 << 8));
    v22 = v15;
    if ( (unsigned __int16)v15 < *(_WORD *)(v18 + 16) || (unsigned __int16)v15 > *(_WORD *)(v18 + 18) )
    {
      if ( (unsigned __int16)v15 >= *(_WORD *)(v18 + 22) && (unsigned __int16)v15 <= *(_WORD *)(v18 + 24) )
        LOWORD(v15) = *(_WORD *)(v18 + 26) + v15;
    }
    else
    {
      LOWORD(v15) = *(_WORD *)(v18 + 20) + v15;
    }
$test$27298:
    if ( (_WORD)v15 != v9 )
      break;
    if ( !v9 || !MaxCount )
    {
LABEL_51:
      if ( v20 )
        *(_DWORD *)(v19 + 112) &= ~2u;
      return 0;
    }
  }
  result = (unsigned __int16)v15 < v9 ? 1 : -1;
  if ( v20 )
    *(_DWORD *)(v19 + 112) &= ~2u;
  return result;
}

