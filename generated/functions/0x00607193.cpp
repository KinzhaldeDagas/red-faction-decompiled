// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00607193 ?_expandtime@@YAHPAUlocaleinfo_struct@@DPBUtm@@PAPADPAIPAU__lc_time_data@@I@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Time-data pointer is NOT struct tm (prototypes
// repaired to opaque DWORD*). Native byte layout: char* weekday arrays at0/1C (7 each, selected by%a/%A), month arrays38/68 (12 each,%b/%B), AM/PM pointers98/9C, mode0/1/other
// pattern pointersA0/A4/A8, API LCID DWORDAC, DWORD B0==1 selects manual path. Mixed ABI AL=SIGNED directive byte,EDX=const tm*,ECX=outputPointerSlot*,FOUR caller-popped stack slots
// {localeInfo*,remainingCounter*,timeData*,unsigned alternateFlag}. Return0/1. No own locale acquisition, universal capacity guard or NUL append. Accepted numeric directives: H
// hour0..23,width2; I same bound, modulo12 with0->12,width2; M minute0..59,width2; S seconds0..59,width2 (60 rejected); d day1..31,width2; m month0..11 ->+1,width2; j yday0..365
// ->+1,width3; w weekday0..6,width1; y year>=0 ->year%100,width2; Y year-1900..8099 ->year+1900,width4. No consistency/leap-year/date validation beyond EACH referenced field. Numeric
// paths call store_num with alternateFlag (nonzero enables its width-ignoring/truncation/reversal behavior), then return1 even if counter0 or incomplete digits. U/W require
// weekday0..6,yday0..365. U uses weekday directly; W uses weekday-1 except Sunday->6. If yday<adjustedWeekday number0, otherwise yday/7 + (yday%7>=adjustedWeekday), width2 through
// same numeric helper. a/A require weekday0..6 and copy selected table string; b/B require month0..11. p requires hour0..23 and copies AM for<=11 else PM. String copier is raw BYTE
// copier limited by remaining count, does NOT append NUL; no source-pointer guard or multibyte-boundary check here. x selects store_winword mode0 for alternate0,mode1 for nonzero. X
// always mode2. c does same short/long date first; if date helper0 OR remaining0 ->return0; else append ONE SPACE/decrement counter, call mode2 time and Booleanize its result. No
// reservation test beyond nonzero before space. Z AND z both call tzset then address-of-global665B10 helper, select pointer[tm_isdst!=0] (including negative isdst as true), byte-copy
// TIMEZONE NAME; z does NOT generate numeric UTC offset. tzset result ignored. Literal '%' directly writes/advances/decrements WITHOUT capacity test. Directive bytes4 and13 return1
// WITHOUT any output. Every OTHER directive returns0 with no own errno assignment. Invalid referenced tm field ->errno22,invalid_parameter5zeros,return0 if handler returns. No own
// pointer checks, full-calendar normalization, rollback or SEH; main formatter determines buffer/error handling after return.
int __usercall _expandtime@<eax>(
        char a1@<al>,
        const struct tm *a2@<edx>,
        char **a3@<ecx>,
        struct localeinfo_struct *a4,
        unsigned int *a5,
        _DWORD *a6,
        unsigned int a7)
{
  char **v7; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int tm_sec; // eax
  bool v15; // cc
  unsigned int v16; // esi
  _BYTE *v17; // edx
  unsigned int v18; // esi
  int v19; // eax
  int v20; // eax
  int v21; // ecx
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  unsigned int v26; // eax
  int v27; // eax
  int v28; // et2
  int v29; // eax
  int v30; // eax
  int v31; // eax
  int v32; // eax
  int v33; // eax
  int v34; // eax
  unsigned int tm_yday; // esi
  int tm_mday; // esi
  int v37; // eax
  unsigned int v38; // esi
  unsigned int v39; // esi
  unsigned int tm_mon; // esi
  int v42; // eax
  int v43; // eax
  int v44; // eax
  int v45; // eax
  _UNKNOWN ***v46; // eax
  int tm_year; // eax
  unsigned int tm_wday; // eax
  int tm_hour; // esi
  unsigned int v50; // [esp-8h] [ebp-18h]
  unsigned int v51; // [esp-4h] [ebp-14h]

  v7 = a3;
  if ( a1 > 89 )
  {
    if ( a1 > 109 )
    {
      v42 = a1 - 112;
      if ( !v42 )
      {
        tm_hour = a2->tm_hour;
        if ( (unsigned int)tm_hour >= 0x18 )
          goto LABEL_74;
        if ( tm_hour > 11 )
          v17 = (_BYTE *)a6[39];
        else
          v17 = (_BYTE *)a6[38];
        goto LABEL_96;
      }
      v43 = v42 - 7;
      if ( !v43 )
      {
        tm_wday = a2->tm_wday;
        if ( tm_wday <= 6 )
        {
          _store_num(tm_wday, 1u, a5, a3, a7);
          return 1;
        }
        goto LABEL_74;
      }
      v44 = v43 - 1;
      if ( !v44 )
      {
        if ( a7 )
          v25 = _store_winword(a4, 1, a2, a3, a5, a6);
        else
          v25 = _store_winword(a4, 0, a2, a3, a5, a6);
        return v25 != 0;
      }
      v45 = v44 - 1;
      if ( !v45 )
      {
        tm_year = a2->tm_year;
        if ( tm_year >= 0 )
        {
          v51 = a7;
          tm_sec = tm_year % 100;
          goto LABEL_61;
        }
        goto LABEL_74;
      }
      if ( v45 != 1 )
        return 0;
    }
    else
    {
      if ( a1 == 109 )
      {
        tm_mon = a2->tm_mon;
        if ( tm_mon >= 0xC )
          goto LABEL_74;
        tm_sec = tm_mon + 1;
        goto LABEL_60;
      }
      v30 = a1 - 90;
      if ( v30 )
      {
        v31 = v30 - 7;
        if ( !v31 )
        {
          v39 = a2->tm_wday;
          if ( v39 > 6 )
            goto LABEL_74;
          v17 = (_BYTE *)a6[v39];
          goto LABEL_96;
        }
        v32 = v31 - 1;
        if ( !v32 )
        {
          v38 = a2->tm_mon;
          if ( v38 >= 0xC )
            goto LABEL_74;
          v17 = (_BYTE *)a6[v38 + 14];
          goto LABEL_96;
        }
        v33 = v32 - 1;
        if ( v33 )
        {
          v34 = v33 - 1;
          if ( v34 )
          {
            if ( v34 != 6 )
              return 0;
            tm_yday = a2->tm_yday;
            if ( tm_yday > 0x16D )
              goto LABEL_74;
            v51 = a7;
            tm_sec = tm_yday + 1;
            v50 = 3;
LABEL_62:
            _store_num(tm_sec, v50, a5, v7, v51);
            return 1;
          }
          tm_mday = a2->tm_mday;
          if ( tm_mday < 1 || tm_mday > 31 )
            goto LABEL_74;
          tm_sec = a2->tm_mday;
LABEL_60:
          v51 = a7;
LABEL_61:
          v50 = 2;
          goto LABEL_62;
        }
        if ( a7 )
          v37 = _store_winword(a4, 1, a2, a3, a5, a6);
        else
          v37 = _store_winword(a4, 0, a2, a3, a5, a6);
        if ( !v37 || !*a5 )
          return 0;
        *(*v7)++ = 32;
        --*a5;
        v25 = _store_winword(a4, 2, a2, v7, a5, a6);
        return v25 != 0;
      }
    }
    __tzset();
    v46 = crt_address_of_00665b10();
    a3 = v7;
    v17 = v46[a2->tm_isdst != 0];
    goto LABEL_96;
  }
  if ( a1 == 89 )
  {
    v29 = a2->tm_year;
    if ( v29 < -1900 || v29 > 8099 )
      goto LABEL_74;
    v51 = a7;
    v50 = 4;
    tm_sec = v29 % 100 + 100 * (v29 / 100 + 19);
    goto LABEL_62;
  }
  if ( a1 > 73 )
  {
    v20 = a1 - 77;
    if ( v20 )
    {
      v21 = 6;
      v22 = v20 - 6;
      if ( v22 )
      {
        v23 = v22 - 2;
        if ( v23 )
        {
          v24 = v23 - 2;
          if ( v24 )
          {
            if ( v24 != 1 )
              return 0;
            v25 = _store_winword(a4, 2, a2, v7, a5, a6);
            return v25 != 0;
          }
          v26 = a2->tm_wday;
          if ( v26 > 6 )
            goto LABEL_74;
          if ( v26 )
            v21 = v26 - 1;
        }
        else
        {
          if ( a2->tm_wday > 6u )
            goto LABEL_74;
          v21 = a2->tm_wday;
        }
        v27 = a2->tm_yday;
        if ( (unsigned int)v27 <= 0x16D )
        {
          if ( v27 >= v21 )
          {
            v28 = v27 % 7;
            tm_sec = v27 / 7;
            if ( v28 >= v21 )
              ++tm_sec;
          }
          else
          {
            tm_sec = 0;
          }
          goto LABEL_60;
        }
        goto LABEL_74;
      }
      tm_sec = a2->tm_sec;
    }
    else
    {
      tm_sec = a2->tm_min;
    }
    if ( tm_sec >= 0 )
    {
      v15 = tm_sec <= 59;
LABEL_13:
      if ( v15 )
        goto LABEL_60;
    }
LABEL_74:
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return 0;
  }
  if ( a1 == 73 )
  {
    v19 = a2->tm_hour;
    if ( (unsigned int)v19 < 0x18 )
    {
      tm_sec = v19 % 12;
      if ( !tm_sec )
        tm_sec = 12;
      goto LABEL_60;
    }
    goto LABEL_74;
  }
  v9 = a1 - 4;
  if ( !v9 )
    return 1;
  v10 = v9 - 9;
  if ( !v10 )
    return 1;
  v11 = v10 - 24;
  if ( v11 )
  {
    v12 = v11 - 28;
    if ( v12 )
    {
      v13 = v12 - 1;
      if ( v13 )
      {
        if ( v13 == 6 )
        {
          tm_sec = a2->tm_hour;
          if ( tm_sec >= 0 )
          {
            v15 = tm_sec <= 23;
            goto LABEL_13;
          }
          goto LABEL_74;
        }
        return 0;
      }
      v16 = a2->tm_mon;
      if ( v16 >= 0xC )
        goto LABEL_74;
      v17 = (_BYTE *)a6[v16 + 26];
    }
    else
    {
      v18 = a2->tm_wday;
      if ( v18 > 6 )
        goto LABEL_74;
      v17 = (_BYTE *)a6[v18 + 7];
    }
LABEL_96:
    _store_str(a5, v17, a3);
    return 1;
  }
  *(*a3)++ = 37;
  --*a5;
  return 1;
}

