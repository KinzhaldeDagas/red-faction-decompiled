// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E4610 rf_vani_player_destroy
// UNREALRED VERIFIED [texture-conversion-20261028]: Calls0x5E4B90toreset/releaseresourcesaccordingflag0x10,then destroys embeddedvfile+120 via0x592420. Doesnotdeleteplayerobject. Returnvfiledestructorresult,notplaybackstatus.
int *__thiscall rf_vani_player_destroy(int *this)
{
  rf_vani_player_reset_release(this);
  return rf_vfile_destruct_close_if_open(this + 30);
}

