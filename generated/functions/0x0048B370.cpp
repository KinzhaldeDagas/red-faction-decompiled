// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048B370 rf_mover_reverse_linear_segment
// UNREALRED VERIFIED [mission-mover-runtime-20261013] Reverses active linear segment: elapsed=0 then ordered clamp against old-direction travel parameter, travelled=distance-travelled clamped [0,distance], flip direction bit0x2000, swap current/target, speed=0 and velocity=0. Existing physical position is retained; do not teleport to either key or restart distance at zero.
// UNREALRED VERIFIED [mission-mover-events-20261020] Reverse_Mover calls this existing segment reversal only after waiting/idle and selected-direction guards. Current/target index validity is tested here. No rotating-type exclusion; the source retains angle and wait deadline while resetting elapsed, complementing distance, flipping direction and clearing speed/velocity.
float *__cdecl rf_mover_reverse_linear_segment(int a1)
{
  float *result; // eax
  int v2; // [esp+8h] [ebp-14h]
  float v3; // [esp+Ch] [ebp-10h]
  int v4; // [esp+10h] [ebp-Ch]
  float v5; // [esp+14h] [ebp-8h]
  int v6; // [esp+18h] [ebp-4h]

  result = (float *)a1;
  if ( *(_DWORD *)(a1 + 760) != -1 && *(_DWORD *)(a1 + 764) != -1 )
  {
    v6 = *(_DWORD *)sub_552200((_DWORD *)(a1 + 668), *(_DWORD *)(a1 + 760));
    v2 = *(_DWORD *)sub_552200((_DWORD *)(a1 + 668), *(_DWORD *)(a1 + 764));
    if ( (*(_DWORD *)(a1 + 792) & 0x2000) != 0 )
      v5 = *(float *)(v6 + 56);
    else
      v5 = *(float *)(v2 + 60);
    v3 = rf_vector_distance((const float *)(v6 + 4), (const float *)(v2 + 4));
    *(float *)(a1 + 768) = 0.0;
    *(float *)(a1 + 772) = v3 - *(float *)(a1 + 772);
    rf_float_clamp_in_place((float *)(a1 + 768), 0.0, v5);
    rf_float_clamp_in_place((float *)(a1 + 772), 0.0, v3);
    if ( (*(_DWORD *)(a1 + 792) & 0x2000) != 0 )
      *(_DWORD *)(a1 + 792) &= ~0x2000u;
    else
      *(_DWORD *)(a1 + 792) |= 0x2000u;
    v4 = *(_DWORD *)(a1 + 760);
    *(_DWORD *)(a1 + 760) = *(_DWORD *)(a1 + 764);
    *(_DWORD *)(a1 + 764) = v4;
    *(float *)(a1 + 756) = 0.0;
    return rf_vector3_zero_return_destination((float *)(a1 + 324));
  }
  return result;
}

