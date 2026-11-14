// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00607051 ??0_LocaleUpdate@@QAE@PAUlocaleinfo_struct@@@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Thiscall local update object plus one locale pointer, RET4,return self. First set BYTEself+12=0. Supplied locale nonNULL copies only twoDWORDs at+0/+4; +8
// remains untouched and no thread-state pin. NULL locale: get thread data, save pointer+8; copy thread+108 locale and+104 multibyte into self0/+4; if each differs current global and
// thread+112 &global66598C==0, refresh via respective update helper. If mask0x2 in thread+112 is clear, OR0x2 and setself+12=1, otherwise leave byte0. Caller owns clearing pin only
// when byte1; ctor does not allocate local object or validate supplied locale/thread pointer. Thread/global values re-read between helpers; no snapshot/lock/cleanup in this body.
_LocaleUpdate *__thiscall _LocaleUpdate::_LocaleUpdate(_LocaleUpdate *this, struct localeinfo_struct *a2)
{
  DWORD *v3; // eax
  int v4; // eax

  *((_BYTE *)this + 12) = 0;
  if ( a2 )
  {
    *(_DWORD *)this = *(_DWORD *)a2;
    *((_DWORD *)this + 1) = *((_DWORD *)a2 + 1);
  }
  else
  {
    v3 = _getptd();
    *((_DWORD *)this + 2) = v3;
    *(_DWORD *)this = v3[27];
    *((_DWORD *)this + 1) = v3[26];
    if ( *(_UNKNOWN **)this != off_665A70 && (dword_66598C & v3[28]) == 0 )
      *(_DWORD *)this = __updatetlocinfo();
    if ( *((volatile LONG **)this + 1) != lpAddend && (dword_66598C & *(_DWORD *)(*((_DWORD *)this + 2) + 112)) == 0 )
      *((_DWORD *)this + 1) = __updatetmbcinfo();
    v4 = *((_DWORD *)this + 2);
    if ( (*(_BYTE *)(v4 + 112) & 2) == 0 )
    {
      *(_DWORD *)(v4 + 112) |= 2u;
      *((_BYTE *)this + 12) = 1;
    }
  }
  return this;
}

