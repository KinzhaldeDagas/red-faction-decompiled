// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044DFD0 rf_hud_directional_damage_update
// UNREALRED VERIFIED [ingame-hud-layers] Consumes Player flags bits 13-16 into four alphas at +0x11E0..+0x11EC, setting active directions to one, fading inactive directions by frame delta, clamping at zero, then clearing producer bits.
unsigned int __cdecl rf_hud_directional_damage_update(int a1)
{
  unsigned int result; // eax
  int v2; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  if ( a1 )
  {
    v2 = *(int *)(a1 + 16) >> 13;
    for ( i = 0; i < 4; ++i )
    {
      if ( (v2 & (1 << i)) <= 0 )
      {
        *(float *)(a1 + 4 * i + 4576) = *(float *)(a1 + 4 * i + 4576) - rf_frame_delta_seconds;
        if ( *(float *)(a1 + 4 * i + 4576) < 0.0 )
          *(float *)(a1 + 4 * i + 4576) = 0.0;
      }
      else
      {
        *(float *)(a1 + 4 * i + 4576) = 1.0;
      }
    }
    result = *(_DWORD *)(a1 + 16) & 0xFFFE1FFF;
    *(_DWORD *)(a1 + 16) = result;
  }
  return result;
}

