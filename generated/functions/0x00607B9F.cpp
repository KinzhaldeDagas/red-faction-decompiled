// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00607B9F __localtime64_s
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid(E) below sets errnoE and calls
// invalid_parameter(NULL,NULL,NULL,0,0); stated error returns require that callback to return. tm is nine signedDWORDs:
// sec0,min4,hour8,mday12,mon16,yearSince1900=20,wday24,yday28,isdst32. Cdecl(tmOut,time64Ptr),errno-style0/error. NULLout invalid22/22; otherwise FIRST memset all36 outputbytes FF.
// NULLtime invalid22/22; signedtime outside0..0x793406FFF ->errno22/22 WITHOUT callback. tzset; checked daylight665A84,dstbias665A88,timezone665A80 getters, failures Watson5zeros.
// Time>259200: temp=time-SIGNEDtimezone, gmtime64_s(out,&temp); propagate nonzero. If daylight!=0 and isindst(out), temp-=SIGNEDdstbias, second gmtime64_s, propagate error; then
// isdst1. Otherwise isdst remains0 from gmtime. Time<=259200: first gmtime64_s(out,original), test DST on that unadjusted UTC tm; subtract timezone or SIGNED32(timezone+dstbias) from
// tm_sec, set isdst1 for DST. Normalize signed64 seconds/minutes modulo60 and hours modulo24; negative remainders add base and subtract one base from carry numerator before
// truncating division. Nonzero day carry updates wday with signed%7 and mday/yday. Negative carry crossing mday<=0 assumes previous December: yday+=carry+365,year--,mday+=31,mon11;
// positive carry has no general month/year rollover normalization. No own range checks on timezone/DST offsets, overflow guards, lock or output rollback beyond gmtime reset behavior.
// Extreme injected offsets can produce unnormalized fields in near-epoch path.
errno_t __cdecl _localtime64_s(struct tm *Tm, const __time64_t *Time)
{
  errno_t result; // eax
  __int64 v3; // kr00_8
  __int64 v4; // kr10_8
  __int64 v5; // kr20_8
  __int64 v6; // rax
  int v7; // ecx
  int v8; // edx
  __time64_t v9; // [esp+8h] [ebp-14h] BYREF
  int v10; // [esp+10h] [ebp-Ch] BYREF
  int v11; // [esp+14h] [ebp-8h] BYREF
  int v12; // [esp+18h] [ebp-4h] BYREF

  v11 = 0;
  v10 = 0;
  v12 = 0;
  if ( !Tm )
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return 22;
  }
  memset(Tm, 255, sizeof(struct tm));
  if ( !Time )
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return 22;
  }
  if ( *((int *)Time + 1) < 0 || *Time > 0x793406FFFLL )
  {
    *_errno() = 22;
    return 22;
  }
  __tzset();
  if ( crt_get_dword_00665a84_checked(&v11) )
    _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
  if ( crt_get_dword_00665a88_checked(&v10) )
    _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
  if ( crt_get_dword_00665a80_checked(&v12) )
    _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
  if ( *Time > 259200 )
  {
    v9 = *Time - v12;
    result = _gmtime64_s(Tm, &v9);
    if ( result )
      return result;
    if ( v11 && _isindst(Tm) )
    {
      v9 -= v10;
      result = _gmtime64_s(Tm, &v9);
      if ( result )
        return result;
      Tm->tm_isdst = 1;
    }
    return 0;
  }
  result = _gmtime64_s(Tm, Time);
  if ( result )
    return result;
  if ( v11 && _isindst(Tm) )
  {
    v3 = Tm->tm_sec - (__int64)(v10 + v12);
    Tm->tm_isdst = 1;
  }
  else
  {
    v3 = Tm->tm_sec - (__int64)v12;
  }
  Tm->tm_sec = v3 % 60;
  if ( v3 % 60 < 0 )
  {
    Tm->tm_sec = v3 % 60 + 60;
    v3 = __PAIR64__((unsigned int)__CFADD__((_DWORD)v3, -60) + HIDWORD(v3) - 1, (int)v3 - 60);
  }
  v4 = Tm->tm_min + v3 / 60;
  Tm->tm_min = v4 % 60;
  if ( v4 % 60 < 0 )
  {
    Tm->tm_min = v4 % 60 + 60;
    v4 -= 60;
  }
  v5 = Tm->tm_hour + v4 / 60;
  Tm->tm_hour = v5 % 24;
  if ( v5 % 24 < 0 )
  {
    Tm->tm_hour = v5 % 24 + 24;
    v5 -= 24;
  }
  v6 = v5 / 24;
  v7 = v5 / 24;
  if ( (((unsigned __int64)(v5 / 24) >> 32) & 0x80000000) != 0LL )
  {
    HIDWORD(v6) = ((int)v6 + Tm->tm_wday + 7) % 7;
    Tm->tm_mday += v6;
    LODWORD(v6) = Tm->tm_mday;
    Tm->tm_wday = HIDWORD(v6);
    if ( (int)v6 <= 0 )
    {
      Tm->tm_yday += v7 + 365;
      --Tm->tm_year;
      Tm->tm_mday = v6 + 31;
      Tm->tm_mon = 11;
      return 0;
    }
  }
  else
  {
    if ( v6 <= 0 )
      return 0;
    v8 = (v7 + Tm->tm_wday) % 7;
    Tm->tm_mday += v7;
    Tm->tm_wday = v8;
  }
  Tm->tm_yday += v7;
  return 0;
}

