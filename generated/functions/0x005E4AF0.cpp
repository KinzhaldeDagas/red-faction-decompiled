// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E4AF0 rf_vani_player_set_draw_state_flag4
// UNREALRED VERIFIED [texture-conversion-20261028]: Setsflags+404mask4onlyifbyteargument==1,elseclearsmask4. Returns this. Playbackchoosesdrawstate0x187CD38whenflagset,else0x187CC7C; no furthersemanticlabelinferred.
_DWORD *__thiscall rf_vani_player_set_draw_state_flag4(_DWORD *this, char a2)
{
  unsigned int v2; // edx

  if ( a2 == 1 )
    v2 = *(this + 101) | 4;
  else
    v2 = *(this + 101) & 0xFFFFFFFB;
  *(this + 101) = v2;
  return this;
}

