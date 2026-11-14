// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060A8E1 _asctime_s
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid(E) below sets errnoE and calls
// invalid_parameter(NULL,NULL,NULL,0,0); stated error returns require that callback to return. tm is nine signedDWORDs:
// sec0,min4,hour8,mday12,mon16,yearSince1900=20,wday24,yday28,isdst32. Cdecl(buffer,unsignedSize,tmPtr),0/22. NULLbuffer ORsize0 invalid22/22 without buffer write. Otherwise
// buffer[0]=0 BEFORE size>=26 and tm checks. Require yearSince1900>=0 with NOupperbound; mon0..11,hour0..23,min/sec0..59,mday>=1 and month length from665D24 with Gregorian leap
// February29 allowance,wday0..6. Invalid calendar/shortsize also invalid22, NOT range34. Success writes exactly26bytes "Www Mmm dd hh:mm:ss yyyy\n\0" using fixed English triple
// tables64C31C/64C334; DAY IS ZERO-PADDED (01), not space-padded. Year first two chars derived from yearOffset/100+19 divided10, lasttwo from yearOffset%100; no four-digit-year
// validation, huge years yield non-digit/truncated byte output. tm_yday/isdst and consistency of weekday are not checked. No locale, allocation, own lock or error clearing beyond
// initial NUL; rest of caller buffer untouched.
errno_t __cdecl asctime_s(char *Buffer, size_t SizeInBytes, const struct tm *Tm)
{
  char *v3; // esi
  int v4; // edi
  unsigned int tm_mon; // edx
  unsigned int tm_wday; // eax
  int v8; // eax
  int v9; // edx
  char v10; // bl
  _BYTE *v11; // esi
  char v12; // dl
  char v13; // dl
  char v14; // dl
  char v15; // dl
  char v16; // dl
  int v17; // edx

  v3 = Buffer;
  v4 = 0;
  if ( Buffer
    && SizeInBytes
    && (*Buffer = 0, SizeInBytes >= 0x1A)
    && Tm
    && Tm->tm_year >= 0
    && (tm_mon = Tm->tm_mon, tm_mon < 0xC)
    && Tm->tm_hour < 0x18u
    && Tm->tm_min < 0x3Cu
    && Tm->tm_sec < 0x3Cu )
  {
    if ( Tm->tm_mday >= 1
      && (dword_665D28[tm_mon] - dword_665D24[tm_mon] >= Tm->tm_mday
       || (!((Tm->tm_year + 1900) % 4) && (Tm->tm_year + 1900) % 100 || !((Tm->tm_year + 1900) % 400))
       && (tm_mon = Tm->tm_mon, tm_mon == 1)
       && Tm->tm_mday <= 29)
      && (tm_wday = Tm->tm_wday, tm_wday <= 6) )
    {
      v8 = 3 * tm_wday;
      v9 = 3 * tm_mon;
      do
      {
        *v3 = byte_64C31C[v8 + v4];
        v10 = byte_64C334[v9 + v4++];
        v3[4] = v10;
        ++v3;
      }
      while ( v4 < 3 );
      *v3 = 32;
      v11 = v3 + 4;
      *v11 = 32;
      v12 = Tm->tm_mday % 10;
      *++v11 = Tm->tm_mday / 10 + 48;
      *++v11 = v12 + 48;
      v11[1] = 32;
      v13 = Tm->tm_hour % 10;
      v11 += 2;
      *v11++ = Tm->tm_hour / 10 + 48;
      *v11 = v13 + 48;
      v11[1] = 58;
      v14 = Tm->tm_min % 10;
      v11 += 2;
      *v11++ = Tm->tm_min / 10 + 48;
      *v11 = v14 + 48;
      v11[1] = 58;
      v15 = Tm->tm_sec % 10;
      v11 += 2;
      *v11++ = Tm->tm_sec / 10 + 48;
      *v11 = v15 + 48;
      v11[1] = 32;
      v11 += 2;
      v16 = (Tm->tm_year / 100 + 19) % 10;
      *v11++ = (Tm->tm_year / 100 + 19) / 10 + 48;
      *v11 = v16 + 48;
      v17 = Tm->tm_year % 100;
      v11[1] = v17 / 10 + 48;
      v11[2] = v17 % 10 + 48;
      v11[3] = 10;
      v11[4] = 0;
      return 0;
    }
    else
    {
      *_errno() = 22;
      _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
      return 22;
    }
  }
  else
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return 22;
  }
}

