// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E5020 rf_vani_player_is_playing
// UNREALRED VERIFIED [bitmap-lifecycle-20261028]: Returns normalized bool(flags DWORD at this+404 & 0x40). Does not inspect paused flag, handle, duration or frame data, and does not advance playback.
BOOL __thiscall rf_vani_player_is_playing(_DWORD *this)
{
  return (*(this + 101) & 0x40) != 0;
}

