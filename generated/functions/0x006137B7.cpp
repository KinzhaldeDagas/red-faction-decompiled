// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006137B7 _cvtdate
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Internal mixedABI EAX=month1based,ECX=hour;
// NINEcaller-cleaned stackDWORDs(startFlag,ruleKind,yearSince1900,weekOrdinal,weekday,absoluteDay,minute,second,millis), no validation/ownlock. Leap iff(yearOffset%4==0 &&
// yearOffset%100!=0)||((yearOffset+1900)%400==0); cumulative preceding-month table NONLEAP665D20 indexedmonth,LEAP665CEC indexedmonth. ruleKindEXACT1: firstYday=cumulative[month]+1;
// firstWeekday=(365*yearOffset+(yearOffset+299)/400-(yearOffset-1)/100+(yearOffset-1)/4+firstYday-25563)%7 using signed32 arithmetic.
// Candidate=firstYday+weekday+7*weekOrdinal-firstWeekday minus7 iff firstWeekday<=weekday. WeekOrdinal5 (last) subtract7 ifcandidate exceedsmonthend table[month+1]. Other ruleKind:
// yday=cumulative[month]+absoluteDay; no wYear test. Millis=millis+1000*(second+60*(minute+60*hour)),modulo32. startFlagEXACT1 writes startyear/yday/millis665B18/1C/20, no
// offsetcorrection. Otherflag writes endyday/millis665B28/2C, checked dstbias665A88 getter(failureWatson), adds1000*SIGNEDbias, normalizes AT MOSTone day across0 or86400000, then
// endyear665B24. EAX return is incidental arithmetic/helper value, NOT status or stable timestamp. No bounds, invalid callback, general multi-day normalization or overflow
// protection.
int __usercall cvtdate@<eax>(
        int a1@<eax>,
        int a2@<ecx>,
        int a3,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10,
        int a11)
{
  int v11; // edi
  int v13; // eax
  int v14; // esi
  int v15; // esi
  int v16; // edx
  int result; // eax
  int v18; // esi
  int v19; // esi
  int v20; // ecx
  int v21; // [esp+14h] [ebp-4h] BYREF
  int v22; // [esp+24h] [ebp+Ch]

  v21 = 0;
  v11 = a5;
  if ( a4 == 1 )
  {
    if ( (a5 % 4 || !(a5 % 100)) && (a5 + 1900) % 400 )
    {
      v13 = 4 * a1;
      v14 = dword_665D20[a1];
    }
    else
    {
      v13 = 4 * a1;
      v14 = dword_665CEC[a1];
    }
    v22 = v13;
    v15 = v14 + 1;
    v11 = a5;
    v16 = (365 * a5 + (a5 + 299) / 400 - (a5 - 1) / 100 + v15 + (a5 - 1) / 4 - 25563) % 7;
    result = a7 + 7 * a6 - v16;
    if ( v16 > a7 )
      v18 = result + v15;
    else
      v18 = v15 + result - 7;
    if ( a6 == 5 )
    {
      result = (a5 % 4 || !(a5 % 100)) && (a5 + 1900) % 400
             ? *(int *)((char *)dword_665D24 + v22)
             : *(int *)((char *)&dword_665CF0 + v22);
      if ( v18 > result )
        v18 -= 7;
    }
  }
  else
  {
    if ( (a5 % 4 || (result = a5 / 100, !(a5 % 100))) && (result = (a5 + 1900) / 400, (a5 + 1900) % 400) )
      v19 = dword_665D20[a1];
    else
      v19 = dword_665CEC[a1];
    v18 = a8 + v19;
  }
  v20 = a11 + 1000 * (a10 + 60 * (a9 + 60 * a2));
  if ( a3 == 1 )
  {
    dword_665B1C = v18;
    dword_665B20 = v20;
    dword_665B18 = v11;
  }
  else
  {
    dword_665B28 = v18;
    dword_665B2C = v20;
    if ( crt_get_dword_00665a88_checked(&v21) )
      _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
    result = 1000 * v21;
    dword_665B2C += 1000 * v21;
    if ( dword_665B2C >= 0 )
    {
      result = 86400000;
      if ( dword_665B2C >= 86400000 )
      {
        dword_665B2C -= 86400000;
        ++dword_665B28;
      }
    }
    else
    {
      dword_665B2C += 86400000;
      --dword_665B28;
    }
    dword_665B24 = v11;
  }
  return result;
}

