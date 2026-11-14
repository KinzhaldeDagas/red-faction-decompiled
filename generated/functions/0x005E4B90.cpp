// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E4B90 rf_vani_player_reset_release
// UNREALRED VERIFIED [texture-conversion-20261028]: If flags+404mask0x10callsstreamingcleanup0x5E47B0,else0x5E4810whichonlyinvalidateshandlewithoutreleasingframes. Thenhandle+92=-1,clearsloadedflag0x20,emptiesnamebyte0. Retainsotherflags,time,indexandmetadata; returns this.
_DWORD *__thiscall rf_vani_player_reset_release(_DWORD *this)
{
  if ( (*(this + 101) & 0x10) != 0 )
    rf_vani_player_release_streaming_resources((int)this);
  else
    rf_vani_player_clear_sequence_handle_no_release(this);
  *(this + 23) = -1;
  *(this + 101) &= ~0x20u;
  *(_BYTE *)this = 0;
  return this;
}

