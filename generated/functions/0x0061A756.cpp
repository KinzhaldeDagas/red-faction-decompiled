// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061A756 __mbspbrk_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid(E) means errnoE plus
// invalid_parameter(NULL,NULL,NULL,0,0); stated returns require callbackreturn. U=stackLocaleUpdate(inputLocale); on every normal return AFTERconstruction, clearPTD+112bit2 ONLYif
// U.cleanupBYTE12nonzero. No own unwind-finally pinrelease. MBrecord=U.secondpointer: flagDWORD+8,LCID+12,CP+4,class[c]BYTE+29+c withleadbit4/uppercasebit10h,caseMap[c]BYTE+285+c;
// two inclusiveWORDfoldranges(start16,end18,delta20) and(start22,end24,delta26),additionmodulo16. Cdecl(source,control,locale),borrowedfirstmatch/NULL. ConstructUbeforevalidation.
// MBflag0 delegatesstrpbrk withrawpointers,ownNULLchecksONLYMBpath. MBpathrequiresbothnonNULLelseinvalid22/NULL. Scan sourcecharboundaries; for eachscancontrolcharboundaries.
// Controllead: matchsourcefirstbyte+sourcefollowingbyteexactly,OR ifcontroltrailbyteNUL BREAKMATCHREGARDLESSsourcebytes. Thus
// malformedtrailingcontrolleadmatchesANYcurrentnonNULsource. Othercontrolbyteexactmatch. No controlmatch ->advance source2ifleadwithnonNULtrail;danglingsourceleadNULendswithNULL.
// Emptycontrolmatchesnothing. No trail-classvalidation,capacitychecks,copyorallocation.
unsigned __int8 *__cdecl _mbspbrk_l(const unsigned __int8 *String, const unsigned __int8 *Control, _locale_t Locale)
{
  unsigned __int8 *result; // eax
  const unsigned __int8 *v4; // ecx
  const unsigned __int8 *i; // eax
  unsigned __int8 v6; // dl
  _BYTE v7[4]; // [esp+8h] [ebp-10h] BYREF
  int v8; // [esp+Ch] [ebp-Ch]
  int v9; // [esp+10h] [ebp-8h]
  char v10; // [esp+14h] [ebp-4h]

  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)v7, (struct localeinfo_struct *)Locale);
  if ( !*(_DWORD *)(v8 + 8) )
  {
    result = (unsigned __int8 *)strpbrk((const char *)String, (const char *)Control);
LABEL_23:
    if ( v10 )
      *(_DWORD *)(v9 + 112) &= ~2u;
    return result;
  }
  v4 = String;
  if ( String && Control )
  {
    if ( *String )
    {
      do
      {
        for ( i = Control; *i; ++i )
        {
          v6 = *i;
          if ( (*(_BYTE *)(*i + v8 + 29) & 4) != 0 )
          {
            if ( v6 == *v4 && i[1] == v4[1] || !i[1] )
              break;
            ++i;
          }
          else if ( v6 == *v4 )
          {
            break;
          }
        }
        if ( *i )
          break;
        if ( (*(_BYTE *)(*v4 + v8 + 29) & 4) != 0 && !*++v4 )
          break;
        ++v4;
      }
      while ( *v4 );
    }
    result = *v4 != 0 ? (unsigned __int8 *)v4 : nullptr;
    goto LABEL_23;
  }
  *_errno() = 22;
  _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
  if ( v10 )
    *(_DWORD *)(v9 + 112) &= ~2u;
  return nullptr;
}

