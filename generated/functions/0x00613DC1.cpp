// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00613DC1 __gmtime64_s
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid(E) below sets errnoE and calls
// invalid_parameter(NULL,NULL,NULL,0,0); stated error returns require that callback to return. tm is nine signedDWORDs:
// sec0,min4,hour8,mday12,mon16,yearSince1900=20,wday24,yday28,isdst32. Cdecl(tmOut,signed64Ptr),0/22. NULLout invalid22/22. Validout FIRST memset36bytesFF,then NULLtime invalid22/22.
// Accept signedtime [-43200,0x7934126CF] inclusive; outsideerrno22/22 WITHOUTcallback. Initial year estimate q=trunc(time/31536000),yearOffset=q+70; subtract Gregorian
// elapsedyearseconds with signed64 allmul/ADC. If remaindernegative decrementestimatedyear and add365days plusoneifpreviousyearleap; otherwise useestimatedyear/leapflag.
// yday=remainingseconds/86400,then splitdayremainder; scan leap665CF0/nonleap665D24 cumulative monthends untilfirst>=yday,mon=index-1,mday=yday-table[mon].
// wday=SIGNED(trunc(ORIGINALtime/86400)+4)%7. Thus acceptednegative halfday timestamps yield wday4 although date resolves1969-12-31: preserve truncation behavior, no floor
// correction. Hour=dayseconds/3600,min=remaining/60,sec=remainder,isdst0;writeallnineDWORDs. Numeric constants31536000/86400 are IMMEDIATES despite offset-like disassembly, not
// reads. No locale, timezone,DSTlookup, allocation or own lock; successful call does not clear errno.
errno_t __cdecl _gmtime64_s(struct tm *Tm, const __time64_t *Time)
{
  unsigned int v4; // ecx
  unsigned int v5; // eax
  __int64 v6; // rax
  unsigned int v7; // edi
  int v8; // eax
  unsigned int v9; // et0
  int v10; // et0
  unsigned int v11; // edi
  unsigned int v12; // et0
  int *v13; // edx
  int tm_yday; // eax
  int i; // ecx
  int v16; // ecx
  signed __int64 v17; // kr30_8
  int v18; // [esp+Ch] [ebp-Ch]
  unsigned int v19; // [esp+Ch] [ebp-Ch]
  int v20; // [esp+10h] [ebp-8h]
  int v21; // [esp+14h] [ebp-4h]
  int Tma; // [esp+20h] [ebp+8h]

  v21 = 0;
  if ( !Tm || (memset(Tm, 255, sizeof(struct tm)), !Time) )
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return 22;
  }
  v4 = *(_DWORD *)Time;
  v5 = *((_DWORD *)Time + 1);
  if ( *Time < -43200 || __SPAIR64__(v5, v4) > 0x7934126CFLL )
  {
    *_errno() = 22;
    return 22;
  }
  v6 = __SPAIR64__(v5, v4) / (unsigned int)&unk_1E13380;
  v20 = v6 + 69;
  Tma = v6 + 70;
  v7 = 86400 * (-365 * v6 - (((int)v6 + 369) / 400 - ((int)v6 + 69) / 100 + ((int)v6 + 69) / 4 - 17)) + *(_DWORD *)Time;
  v18 = (unsigned __int64)(86400
                         * (-365LL * (int)v6 - (((int)v6 + 369) / 400 - ((int)v6 + 69) / 100 + ((int)v6 + 69) / 4 - 17))
                         + *Time) >> 32;
  if ( v18 >= 0 )
  {
    if ( (Tma % 4 || !(Tma % 100)) && ((int)v6 + 1970) % 400 )
      goto LABEL_18;
    goto LABEL_17;
  }
  v8 = v6 + 69;
  v9 = (unsigned int)((unsigned int)&unk_1E13380 + __PAIR64__(v18, v7)) >> 32;
  v7 += (unsigned int)&unk_1E13380;
  v18 = v9;
  Tma = v20;
  if ( !(v20 % 4) )
  {
    if ( v20 % 100 )
    {
LABEL_13:
      v10 = (__PAIR64__(v18, v7) + 86400) >> 32;
      v7 += 86400;
      v18 = v10;
LABEL_17:
      v21 = 1;
      goto LABEL_18;
    }
    v8 = v20;
  }
  if ( !((v8 + 1900) % 400) )
    goto LABEL_13;
LABEL_18:
  Tm->tm_year = Tma;
  Tm->tm_yday = __SPAIR64__(v18, v7) / 86400;
  v12 = (-86400LL * (int)(__SPAIR64__(v18, v7) / 86400) + __PAIR64__(v18, v7)) >> 32;
  v11 = __SPAIR64__(v18, v7) % 86400;
  v19 = v12;
  v13 = &dword_665CF0;
  if ( !v21 )
    v13 = dword_665D24;
  tm_yday = Tm->tm_yday;
  for ( i = 1; v13[i] < tm_yday; ++i )
    ;
  v16 = i - 1;
  Tm->tm_mon = v16;
  Tm->tm_mday = tm_yday - v13[v16];
  Tm->tm_wday = (int)(*Time / 86400 + 4) % 7;
  Tm->tm_hour = __SPAIR64__(v19, v11) / 3600;
  v17 = -3600LL * (int)(__SPAIR64__(v19, v11) / 3600) + __PAIR64__(v19, v11);
  Tm->tm_min = v17 / 60;
  Tm->tm_isdst = 0;
  Tm->tm_sec = v17 % 60;
  return 0;
}

