// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E4A20 rf_vani_player_start
// UNREALRED VERIFIED [texture-conversion-20261028]: Ifresetbyte nonzero,elapsedtime+108=0 andframeindex+400=-1. Alwayssetsplayingflag0x40at+404,returns this. Doesnotclearpausedflag0x80orload/cachebitmaphere.
int __thiscall rf_vani_player_start(int this, char a2)
{
  if ( a2 )
  {
    *(float *)(this + 108) = 0.0;
    *(_DWORD *)(this + 400) = -1;
  }
  *(_DWORD *)(this + 404) |= 0x40u;
  return this;
}

