// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E4AA0 rf_vani_player_set_reverse_flag
// UNREALRED VERIFIED [texture-conversion-20261028]: Setsflags+404mask2onlyifbyteargument==1,elseclearsmask2. Returns this. Playback0x5E4C80reversescalculatedframeindexwhileelapsedtimeincreases.
_DWORD *__thiscall rf_vani_player_set_reverse_flag(_DWORD *this, char a2)
{
  unsigned int v2; // edx

  if ( a2 == 1 )
    v2 = *(this + 101) | 2;
  else
    v2 = *(this + 101) & 0xFFFFFFFD;
  *(this + 101) = v2;
  return this;
}

