// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061EFB0 __mbsnbcmp_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid(E) means errnoE plus
// invalid_parameter(NULL,NULL,NULL,0,0); stated returns require callbackreturn. U=stackLocaleUpdate(inputLocale); on every normal return AFTERconstruction, clearPTD+112bit2 ONLYif
// U.cleanupBYTE12nonzero. No own unwind-finally pinrelease. MBrecord=U.secondpointer: flagDWORD+8,LCID+12,CP+4,class[c]BYTE+29+c withleadbit4/uppercasebit10h,caseMap[c]BYTE+285+c;
// two inclusiveWORDfoldranges(start16,end18,delta20) and(start22,end24,delta26),additionmodulo16. Cdecl(left,right,unsignedBYTEcount,locale),case-sensitive.
// Count0->0BEFORELocaleUpdateconstruction. NonzeroconstructU;MBflag0 delegatesstrncmp,rawreturndifferencenotnormalizedhere. MBpathNULLinputs invalid22/INT_MAX.
// MBpathsharedBYTEbudget:eachiterationreadleftfirstbyte,advanceleft/decrementbudgetONCE. Leftleadwithbudget0 treatsleftchar0; ifrightfirstbyteisALSOlead
// returnequal0immediately,elsecompare0torightRAWbyte(withoutcasefold). Leftleadwithbudget>0 andtrailNUL
// ->char0,otherwiseconsumelefttrail/formlead<<8|trailWITHOUTadditionalbudgetdecrement.
// Readrightfirstbyte/advance;rightleadwithbudget0->char0,elsedecrementbudgetONCEandconsume/formtrailiffnonNUL,otherwisechar0. Thus
// additionalbudgetdecrementisdrivenbyRIGHTlead,notbothstringsindependently. Compareunsigned16chars;differentnormalized-1/+1;equal0charORbudget0->0,elseloop. No
// trailingbyte-classvalidation orINT_MAXlimit. No casefolding,APIcalls,allocationorownerrnoonmalformed/truncatedlead.
int __cdecl _mbsnbcmp_l(const unsigned __int8 *Str1, const unsigned __int8 *Str2, size_t MaxCount, _locale_t Locale)
{
  int result; // eax
  const unsigned __int8 *v5; // esi
  unsigned __int16 v6; // ax
  unsigned __int16 v7; // cx
  int v8; // eax
  unsigned __int8 v9; // al
  _BYTE v10[4]; // [esp+4h] [ebp-10h] BYREF
  int v11; // [esp+8h] [ebp-Ch]
  int v12; // [esp+Ch] [ebp-8h]
  char v13; // [esp+10h] [ebp-4h]

  if ( !MaxCount )
    return 0;
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)v10, (struct localeinfo_struct *)Locale);
  if ( !*(_DWORD *)(v11 + 8) )
  {
    result = strncmp((const char *)Str1, (const char *)Str2, MaxCount);
    if ( v13 )
      *(_DWORD *)(v12 + 112) &= ~2u;
    return result;
  }
  if ( !Str1 )
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    if ( v13 )
      *(_DWORD *)(v12 + 112) &= ~2u;
    return 0x7FFFFFFF;
  }
  v5 = Str2;
  if ( !Str2 )
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    if ( v13 )
      *(_DWORD *)(v12 + 112) &= ~2u;
    return 0x7FFFFFFF;
  }
  while ( 1 )
  {
    v6 = *Str1;
    --MaxCount;
    ++Str1;
    v7 = v6;
    if ( (*(_BYTE *)((unsigned __int8)v6 + v11 + 29) & 4) == 0 )
      goto LABEL_24;
    if ( MaxCount )
    {
      if ( *Str1 )
      {
        v9 = *Str1++;
        v7 = v9 | (unsigned __int16)(v7 << 8);
      }
      else
      {
        v7 = 0;
      }
LABEL_24:
      LOWORD(v8) = *v5++;
      if ( (*(_BYTE *)((unsigned __int8)v8 + v11 + 29) & 4) != 0 )
      {
        if ( MaxCount && (--MaxCount, *v5) )
          LOWORD(v8) = *v5++ | (unsigned __int16)((_WORD)v8 << 8);
        else
          LOWORD(v8) = 0;
      }
      goto $test$27297;
    }
    v8 = *v5;
    v7 = 0;
    if ( (*(_BYTE *)(v8 + v11 + 29) & 4) != 0 )
      goto LABEL_17;
$test$27297:
    if ( (_WORD)v8 != v7 )
      break;
    if ( !v7 || !MaxCount )
    {
LABEL_17:
      if ( v13 )
        *(_DWORD *)(v12 + 112) &= ~2u;
      return 0;
    }
  }
  result = (unsigned __int16)v8 < v7 ? 1 : -1;
  if ( v13 )
    *(_DWORD *)(v12 + 112) &= ~2u;
  return result;
}

