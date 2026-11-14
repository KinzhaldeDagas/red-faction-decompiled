// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E46C0 rf_vani_player_cache_vbm_sequence
// UNREALRED VERIFIED [texture-conversion-20261028]: LoadsVBMsequencebynameatthis,outputsframecount+84/framerate+88,storesbasehandle+92. Handle-1returns-1; successduration+104=count/rate,thenwarmupbindseachhandlebase+i fori0..count-1. Returns0. No frameratezero orwarmupresultchecks; doesnotdecodeVANIframes.
int __thiscall rf_vani_player_cache_vbm_sequence(int this)
{
  int i; // [esp+4h] [ebp-4h]

  *(_DWORD *)(this + 92) = rf_bitmap_vbm_sequence_load((char *)this, (_DWORD *)(this + 84), (_DWORD *)(this + 88));
  if ( *(_DWORD *)(this + 92) == -1 )
    return -1;
  *(float *)(this + 104) = (double)*(int *)(this + 84) / (double)*(int *)(this + 88);
  if ( *(_DWORD *)(this + 92) != -1 )
  {
    for ( i = 0; i < *(_DWORD *)(this + 84); ++i )
      rf_renderer_bind_texture_for_level_warmup(i + *(_DWORD *)(this + 92));
  }
  return 0;
}

