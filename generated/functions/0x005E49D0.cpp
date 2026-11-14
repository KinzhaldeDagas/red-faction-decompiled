// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E49D0 rf_vani_player_set_loop_flag
// UNREALRED VERIFIED [texture-conversion-20261028]: Setsflags+404mask1onlyifbyteargument==1,elseclearsmask1. Returns this. Doesnotresettimeorframeindex.
_DWORD *__thiscall rf_vani_player_set_loop_flag(_DWORD *this, char a2)
{
  unsigned int v2; // edx

  if ( a2 == 1 )
    v2 = *(this + 101) | 1;
  else
    v2 = *(this + 101) & 0xFFFFFFFE;
  *(this + 101) = v2;
  return this;
}

