// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006139AE __isindst_nolock
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): tm is nine signedDWORDs:
// sec0,min4,hour8,mday12,mon16,yearSince1900=20,wday24,yday28,isdst32. Internal EDI=tmPtr, normalizedBOOL EAX, no own lock/NULL/calendar validation. Checked daylight665A84 getter,
// failureWatson; value0 ->0 BEFOREtm dereference. If tm_year differs from EITHER cachedstart/end year, recompute BOTH via cvtdate. OSrulevalid2021C5C: use DaylightDate2021C48 and
// StandardDate2021BF4 WORDfields; wYear==0 chooses relative weekday/week rule,nonzero choosesabsolute mday for REQUESTEDtm_year (actualwYear ignored),time WORDfields zeroextended.
// NoOSrules: beforeyearOffset107 use firstSundayApril02:00,lastSundayOctober02:00;107+ use secondSundayMarch02:00,firstSundayNovember02:00, no older historicalUSexceptions. cvtdate
// end converts daylight endtime tostandard-localtime byaddingdstbias. Compare SIGNEDtm_yday. Startday<endday: strict interior1,strict exterior0. Startday>=endday: strict outeryear
// portions1,strict gap0. Boundary day computes signed32 secondsOfDay*1000; ifday==startday returnmillis>=startMillis (start inclusive),otherwise returnmillis<endMillis (end
// exclusive). Equal start/endday choosesstarttest duefirstbranch. Ignores tm_isdst,mon,mday,wday; usesyear/yday/sec/min/hour only. No tzset call; caller must initialize state.
BOOL __usercall _isindst_nolock@<eax>(_DWORD *a1@<edi>)
{
  int v2; // edx
  int v3; // eax
  int v4; // ecx
  int v5; // edx
  int v6; // eax
  int v8; // [esp+4h] [ebp-Ch]
  int v9; // [esp+8h] [ebp-8h]
  int v10; // [esp+Ch] [ebp-4h] BYREF

  v10 = 0;
  if ( crt_get_dword_00665a84_checked(&v10) )
    _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
  if ( !v10 )
    return 0;
  v2 = a1[5];
  if ( v2 != dword_665B18 || v2 != dword_665B24 )
  {
    if ( unk_2021C5C )
    {
      if ( unk_2021C48 )
        cvtdate(unk_2021C4A, unk_2021C50, 1, 0, v2, 0, 0, unk_2021C4E, unk_2021C52, unk_2021C54, unk_2021C56);
      else
        cvtdate(unk_2021C4A, unk_2021C50, 1, 1, v2, unk_2021C4E, unk_2021C4C, 0, unk_2021C52, unk_2021C54, unk_2021C56);
      if ( unk_2021BF4 )
        cvtdate(unk_2021BF6, unk_2021BFC, 0, 0, a1[5], 0, 0, unk_2021BFA, unk_2021BFE, unk_2021C00, unk_2021C02);
      else
        cvtdate(
          unk_2021BF6,
          unk_2021BFC,
          0,
          1,
          a1[5],
          unk_2021BFA,
          unk_2021BF8,
          0,
          unk_2021BFE,
          unk_2021C00,
          unk_2021C02);
    }
    else
    {
      v3 = 3;
      v4 = 2;
      v8 = 11;
      v9 = 1;
      if ( v2 < 107 )
      {
        v3 = 4;
        v4 = 1;
        v8 = 10;
        v9 = 5;
      }
      cvtdate(v3, 2, 1, 1, v2, v4, 0, 0, 0, 0, 0);
      cvtdate(v8, 2, 0, 1, a1[5], v9, 0, 0, 0, 0, 0);
    }
  }
  v5 = a1[7];
  if ( dword_665B1C < dword_665B28 )
  {
    if ( v5 >= dword_665B1C && v5 <= dword_665B28 )
    {
      if ( v5 > dword_665B1C && v5 < dword_665B28 )
        return 1;
      goto LABEL_30;
    }
    return 0;
  }
  if ( v5 < dword_665B28 || v5 > dword_665B1C )
    return 1;
  if ( v5 > dword_665B28 && v5 < dword_665B1C )
    return 0;
LABEL_30:
  v6 = 1000 * (*a1 + 60 * (a1[1] + 60 * a1[2]));
  if ( v5 == dword_665B1C )
    return v6 >= dword_665B20;
  else
    return v6 < dword_665B2C;
}

