// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E4B40 rf_vani_player_set_hold_last_flag
// UNREALRED VERIFIED [texture-conversion-20261028]: Setsflags+404mask8onlyifbyteargument==1,elseclearsmask8. Returns this. Playbackhold-lastselectsframecount-1afterduration,evenifreverseflagset.
_DWORD *__thiscall rf_vani_player_set_hold_last_flag(_DWORD *this, char a2)
{
  unsigned int v2; // edx

  if ( a2 == 1 )
    v2 = *(this + 101) | 8;
  else
    v2 = *(this + 101) & 0xFFFFFFF7;
  *(this + 101) = v2;
  return this;
}

