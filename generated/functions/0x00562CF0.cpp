// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00562CF0 rf_model_animation_duration_by_kind
// UNREALRED VERIFIED [sound-event-duration-continuation-20261027] Model animation-duration method returning x87 ST(0). Descriptor kind dword+0: kind2 delegates model pointer +4 and requested clip index to 0x587720; kind3 ignores clip index and returns float-rounded signed dword[descriptor+8 pointer +0x84] multiplied by exact double 0.06666667014360428 at 0x640888. Other kinds return 0. Kind3 body has no nonnegative clamp. Descriptor kind labels beyond the observed branches are not inferred here.
double __thiscall rf_model_animation_duration_by_kind(_DWORD *this, int a2)
{
  if ( *this == 2 )
    return rf_model_clip_tick_duration_seconds((_DWORD *)*(this + 1), a2);
  if ( *this != 3 )
    return 0.0;
  return (float)((double)*(int *)(*(this + 2) + 132) * 0.06666667014360428);
}

