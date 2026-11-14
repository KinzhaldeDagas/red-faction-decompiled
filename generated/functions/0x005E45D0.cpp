// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E45D0 rf_vani_player_construct
// UNREALRED VERIFIED [texture-conversion-20261028]: Constructs embeddedvfile atthis+120 via0x5923E0,emptiesnamebyte0,sets pixelbuffer+112,palettebuffer+116null. Returns this. Doesnotinitializeotherplayerfields/flags; loadinitializer0x5E4860setsmetadata/defaults.
_DWORD *__thiscall rf_vani_player_construct(_DWORD *this)
{
  rf_vfile_construct_unopened(this + 30);
  *(_BYTE *)this = 0;
  *(this + 28) = 0;
  *(this + 29) = 0;
  return this;
}

