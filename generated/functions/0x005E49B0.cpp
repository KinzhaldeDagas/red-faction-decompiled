// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E49B0 rf_vani_player_set_screen_position
// UNREALRED VERIFIED [texture-conversion-20261028]: Stores twointegerargumentsatplayer+96/+100,returnssecondargument. No viewportclamporscaling.
int __thiscall rf_vani_player_set_screen_position(_DWORD *this, int a2, int a3)
{
  *(this + 24) = a2;
  *(this + 25) = a3;
  return a3;
}

