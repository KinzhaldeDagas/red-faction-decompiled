// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00502180 rf_mission_events_release_type10_effect_handles
// UNREALRED VERIFIED [mission-play-animation-file-20261013] Observed cleanup walks event type10 (comparison0xA), then releases event+0x2C4 if!=-1. Do not label this type12 custom-animation cleanup without additional evidence; nearby0x502060 explicitly preloads type12.
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] Iterate event registry; only numeric type10 Explode and effect handle event+0x2C4!=-1 calls0x507860(handle). Does not clear stored handle afterward, filter type12 Custom_Animation, or release all event resources.
int rf_mission_events_release_type10_effect_handles()
{
  int result; // eax
  int v1; // eax
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(unk_90B0E0);
    if ( i >= result )
      break;
    if ( *(_DWORD *)(*(_DWORD *)sub_552200(unk_90B0E0, i) + 656) == 10 )
    {
      v1 = sub_552200(unk_90B0E0, i);
      if ( *(_DWORD *)(*(_DWORD *)v1 + 708) != -1 )
        rf_vclip_preload_bitmap_and_vfx_stub(*(_DWORD *)(*(_DWORD *)v1 + 708));
    }
  }
  return result;
}

