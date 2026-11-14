// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E4A60 rf_vani_player_stop_clear_pause
// UNREALRED VERIFIED [texture-conversion-20261028]: Clearsplayingflag0x40andpausedflag0x80at+404,returns this. Doesnotresettime/frameindexorfreeanyresource.
_DWORD *__thiscall rf_vani_player_stop_clear_pause(_DWORD *this)
{
  *(this + 101) &= ~0x40u;
  *(this + 101) &= ~0x80u;
  return this;
}

