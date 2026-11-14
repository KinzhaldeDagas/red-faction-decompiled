// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00613471 __tzset_nolock
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs void timezone initializer; despite nolock
// name, acquires CRTlock7 for environment/cache/OS-stage, EH4 scope65ED40 finallyentry613718 (reloadESI borrowedTZ,unlock7). Snapshot live timezone665A80/daylight665A84/dstbias665A88
// via checked getters (failureWatson5zeros), obtain tzname array ADDRESS665B10 and locale codepage. ALWAYS clear OSrulevalid2021C5C and invalidate transition year
// caches665B18/665B24=-1. getenv_helper_nolock("TZ"). Absent/empty: free prior ownedTZcopy2021C60/clear; GetTimeZoneInformation into2021BB0. Only DWORD-1 isfailure; failure preserves
// snapshot params/names but still invalidates OSruleflag/caches. Success marksOSrulevalid1; timezone=Bias*60 plus StandardBias*60 ONLYif StandardDate.wMonth!=0.
// Daylight1/dstbias=(DaylightBias-StandardBias)*60 ONLYif DaylightDate.wMonth!=0 ANDDaylightBias!=0; else both0. Convert StandardName/DaylightName using
// localeCP,flags0,cch-1,capacity63,UsedDefaultChar output; failure/default substitution clears respective name[0],successsetsname[63]=0. NonemptyTZ: exact strcmp match cachedcopy
// exits without reparse BUTOSruleflag andtransitioncaches alreadyinvalidated. ChangedTZ frees priorcopy,malloc(strlen+1),publishNULL onfailure then skipparse retaining snapshots;
// copyfailureWatson. Store all three snapshot/OS params through scalar setters while lock7 held, then finally UNLOCK7. ONLYnew successfullycachedTZ parses AFTERunlock using
// ORIGINALBORROWEDenviron pointer, NOTownedcopy; concurrent environ mutation can invalidate it. strncpy_s first3bytes to standardname64, then cursor=TZ+3 even shortinput. Optional
// leadingminus atcursor setsnegate; atol hours*3600, scan plus/digit bytes; optional colon minutes*60 and optional colon seconds with digit-only scans; no complete
// grammar/range/overflow checks. Negate total if initialminus. SIGN-EXTENDED first remainingbyte becomes raw daylightDWORD,notbool; nonzero copies first3remainingbytes toDSTname,else
// clearsDSTname[0]. Publish parsedtimezone/daylight via direct address getters AFTERlock7release. dstbias remains SNAPSHOTvalue, not recomputed fromTZ text; explicit DST offset/rules
// are not parsed. No own lock6 (caller mayholdit), whole-operation exception transaction or errno preservation.
void _tzset_nolock()
{
  const char *v0; // eax
  const char *v1; // esi
  size_t v2; // eax
  size_t v3; // eax
  LPSTR *v4; // edi
  const char *v5; // esi
  char v6; // al
  int v7; // eax
  int v8; // eax
  int v9; // esi
  int v10; // esi
  int v11; // [esp+14h] [ebp-38h]
  unsigned int CodePage; // [esp+18h] [ebp-34h]
  BOOL UsedDefaultChar; // [esp+1Ch] [ebp-30h] BYREF
  int v14; // [esp+20h] [ebp-2Ch]
  int v15; // [esp+24h] [ebp-28h] BYREF
  int v16; // [esp+28h] [ebp-24h] BYREF
  LPSTR *v17; // [esp+2Ch] [ebp-20h]
  int v18; // [esp+30h] [ebp-1Ch] BYREF
  CPPEH_RECORD ms_exc; // [esp+34h] [ebp-18h]

  v11 = 0;
  v14 = 0;
  v18 = 0;
  v16 = 0;
  v15 = 0;
  _lock(7);
  ms_exc.registration.TryLevel = 0;
  v17 = (LPSTR *)crt_address_of_00665b10();
  if ( crt_get_dword_00665a80_checked(&v18) )
    _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
  if ( crt_get_dword_00665a84_checked(&v16) )
    _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
  if ( crt_get_dword_00665a88_checked(&v15) )
    _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
  CodePage = ___lc_codepage_func();
  unk_2021C5C = 0;
  dword_665B24 = -1;
  dword_665B18 = -1;
  v0 = _getenv_helper_nolock("TZ");
  v1 = v0;
  if ( !v0 || !*v0 )
  {
    if ( unk_2021C60 )
    {
      free(unk_2021C60);
      unk_2021C60 = nullptr;
    }
    if ( GetTimeZoneInformation(&MEMORY[0x2021BB0]) != -1 )
    {
      unk_2021C5C = 1;
      v18 = 60 * MEMORY[0x2021BB0].Bias;
      if ( unk_2021BF6 )
        v18 = 60 * unk_2021C04 + 60 * MEMORY[0x2021BB0].Bias;
      if ( unk_2021C4A && unk_2021C58 )
      {
        v16 = 1;
        v15 = 60 * (unk_2021C58 - unk_2021C04);
      }
      else
      {
        v16 = 0;
        v15 = 0;
      }
      if ( !WideCharToMultiByte(CodePage, 0, word_2021BB4, -1, *v17, 63, nullptr, &UsedDefaultChar) || UsedDefaultChar )
        **v17 = 0;
      else
        (*v17)[63] = 0;
      if ( !WideCharToMultiByte(CodePage, 0, word_2021C08, -1, v17[1], 63, nullptr, &UsedDefaultChar) || UsedDefaultChar )
        *v17[1] = 0;
      else
        v17[1][63] = 0;
    }
    goto LABEL_33;
  }
  if ( unk_2021C60 )
  {
    if ( !strcmp(v0, unk_2021C60) )
    {
LABEL_33:
      v14 = 1;
      goto LABEL_34;
    }
    if ( unk_2021C60 )
      free(unk_2021C60);
  }
  v2 = strlen(v1);
  unk_2021C60 = (char *)_malloc_crt(v2 + 1);
  if ( !unk_2021C60 )
    goto LABEL_33;
  v3 = strlen(v1);
  if ( strcpy_s(unk_2021C60, v3 + 1, v1) )
    _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
LABEL_34:
  crt_store_dword665A80_return_address(v18);
  crt_store_dword665A84_return_address(v16);
  crt_store_dword665A88_return_address(v15);
  ms_exc.registration.TryLevel = -2;
  _unlock(7);
  if ( !v14 )
  {
    v4 = v17;
    if ( strncpy_s(*v17, 0x40u, v1, 3u) )
      _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
    v5 = v1 + 3;
    if ( *v5 == 45 )
    {
      v11 = 1;
      ++v5;
    }
    v18 = 3600 * atol(v5);
    while ( 1 )
    {
      v6 = *v5;
      if ( *v5 != 43 && (v6 < 48 || v6 > 57) )
        break;
      ++v5;
    }
    if ( *v5 == 58 )
    {
      v7 = atol(++v5);
      v18 += 60 * v7;
      while ( *v5 >= 48 && *v5 <= 57 )
        ++v5;
      if ( *v5 == 58 )
      {
        v8 = atol(++v5);
        v18 += v8;
        while ( *v5 >= 48 && *v5 <= 57 )
          ++v5;
      }
    }
    if ( v11 )
      v18 = -v18;
    v16 = *v5;
    if ( v16 )
    {
      if ( strncpy_s(v4[1], 0x40u, v5, 3u) )
        _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
    }
    else
    {
      *v4[1] = 0;
    }
    v9 = v18;
    *crt_address_of_00665a80() = v9;
    v10 = v16;
    *crt_address_of_00665a84() = v10;
  }
}

