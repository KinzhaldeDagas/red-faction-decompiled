// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00562BE0 rf_model_handle_animation_remaining_time
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, tagged model bounds, scene transform propagation, by-value matrix ABI, named spheres and cyclic/action dispatch): Tag2 delegates character animation remaining time with action index. Tag3 ignores action index:instance bit4 set returns0;otherwise remaining=max(0,(definition int132-instance float16)*float0.06666667014360428). If positive returns it. When exactly0, scans runtime effect array28 stride164 over definition effect count92; any signed active-particle count148>0 returns float~1e-4 sentinel, else0. Thus can report tiny positive time after timeline ends while particles remain. No finite/pointer validation; unsupported tags0.
double __thiscall rf_model_handle_animation_remaining_time(_DWORD *this, int a2)
{
  char v3; // [esp+Bh] [ebp-Dh]
  int i; // [esp+Ch] [ebp-Ch]
  float v5; // [esp+10h] [ebp-8h]
  float v6; // [esp+14h] [ebp-4h]

  if ( *this == 2 )
    return rf_character_animation_remaining_time((_DWORD *)*(this + 1), a2);
  if ( *this != 3 )
    return 0.0;
  v3 = 0;
  if ( ((*(_DWORD *)*(this + 1) >> 2) & 1) != 0 )
    return 0.0;
  v6 = (double)*(int *)(*(this + 2) + 132) - *(float *)(*(this + 1) + 16);
  v5 = v6 * 0.06666667014360428;
  if ( v5 < 0.0 )
    v5 = 0.0;
  if ( v5 != 0.0 )
    return v5;
  for ( i = 0; i < *(_DWORD *)(*(_DWORD *)(*(this + 1) + 8) + 92); ++i )
  {
    if ( *(int *)(*(_DWORD *)(*(this + 1) + 28) + 164 * i + 148) > 0 )
    {
      v3 = 1;
      break;
    }
  }
  if ( v3 )
    return 0.000099999997;
  else
    return 0.0;
}

