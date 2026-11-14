// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00617150 ___loctotime64_t
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review):
// Cdecl(year,month,day,unsignedHour,unsignedMinute,unsignedSecond,DSTselector), signed64 EDX:EAX corrected from false int; all five callers consume pair. Validate year-1900
// SIGNED70..1100 (1970..3000), unsignedmonth-1<=11,hour<=23,minute/second<=59,day>=1 and month length via cumulative day table665D20 with Gregorian leap-year February29 exception.
// Invalid sets errno22 and BOTH return halves-1, no invalid callback. Compute signed64 local epoch seconds: dayOfYear=day+cumulative[month]+(leap && month>2);
// days=365*(year-1970)+(yearOffset+299)/400-(yearOffset-1)/100+(yearOffset-1)/4-17+dayOfYear; scale24,60,60 with allmul and ADC carry, add hour/minute/second. tzset then checked
// DWORD getters665A84(daylight),665A88(dstbias),665A80(timezone); getterfailureWatson(5zeros). Add SIGNED timezone seconds to64result. DSTselector==1 always adds SIGNED dstbias;
// selector==-1 adds iff daylight nonzero AND isindst(partial tm initialized sec/min/hour/month-1/yearOffset/yday) true; other selectors no DST adjustment. Return full64 EDX:EAX, no
// final epoch-range clamp. tm mday/wday/isdst scratch fields not initialized by this function. No own lock, allocation, NULL pointers or doserrno reset.
__int64 __cdecl __loctotime64_t(int a1, int a2, int a3, unsigned int a4, unsigned int a5, unsigned int a6, int a7)
{
  int v7; // esi
  int v8; // ebx
  int v9; // ecx
  __int64 v10; // kr18_8
  _DWORD v12[10]; // [esp+Ch] [ebp-34h] BYREF
  int v13; // [esp+34h] [ebp-Ch] BYREF
  int v14; // [esp+38h] [ebp-8h] BYREF
  int v15; // [esp+3Ch] [ebp-4h] BYREF
  int v16; // [esp+48h] [ebp+8h]

  v7 = a1 - 1900;
  v14 = 0;
  v13 = 0;
  v15 = 0;
  if ( a1 - 1900 < 70
    || v7 > 1100
    || (v8 = a2, (unsigned int)(a2 - 1) > 0xB)
    || a4 > 0x17
    || a5 > 0x3B
    || a6 > 0x3B
    || a3 < 1
    || (v9 = dword_665D20[a2], dword_665D24[a2] - v9 < a3)
    && ((v7 % 4 || !(v7 % 100)) && a1 % 400 || (v8 = a2, a2 != 2) || a3 > 29) )
  {
    *_errno() = 22;
    return -1;
  }
  else
  {
    v16 = a3 + v9;
    if ( (!(v7 % 4) && v7 % 100 || !((v7 + 1900) % 400)) && v8 > 2 )
      ++v16;
    v12[9] = (unsigned __int64)(365 * (v7 - 70LL) + (v7 + 299) / 400 - (v7 - 1) / 100 + (v7 - 1) / 4 - 17) >> 32;
    __tzset();
    if ( crt_get_dword_00665a84_checked(&v14) )
      _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
    if ( crt_get_dword_00665a88_checked(&v13) )
      _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
    if ( crt_get_dword_00665a80_checked(&v15) )
      _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
    v12[7] = v16;
    v10 = v15
        + (int)a6
        + 60
        * ((int)a5
         + 60 * ((int)a4 + 24 * (v16 + 365 * (v7 - 70LL) + (v7 + 299) / 400 - (v7 - 1) / 100 + (v7 - 1) / 4 - 17)));
    v12[4] = a2 - 1;
    v12[2] = a4;
    v12[1] = a5;
    v12[5] = v7;
    v12[0] = a6;
    if ( a7 == 1 || a7 == -1 && v14 && _isindst(v12) )
      v10 += v13;
    return v10;
  }
}

