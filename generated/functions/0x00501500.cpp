// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00501500 rf_event_play_vclip_forward
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] event_play_vclip forward, vtable0x63E384 slot+4. Only raw clip id event+0x2C0!=-1 calls rf_vclip_spawn_runtime_effect(id,helper(event+4),event+0x40,event+0x40,float+0x2C4,-1,0,1). Same event position pointer passed as both vector arguments. No target scan or successful-spawn retry in body.
int __thiscall rf_event_play_vclip_forward(int this)
{
  int result; // eax
  int first_dword; // eax
  float v3; // [esp+0h] [ebp-14h]

  result = this;
  if ( *(_DWORD *)(this + 704) != -1 )
  {
    v3 = *(float *)(this + 708);
    first_dword = rf_receiver_get_first_dword((void *)(this + 4));
    return rf_vclip_spawn_runtime_effect(*(_DWORD *)(this + 704), first_dword, this + 64, this + 64, v3, -1, 0, 1);
  }
  return result;
}

