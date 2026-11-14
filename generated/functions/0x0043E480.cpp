// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043E480 rf_blood_surface_mark_snapshot_collect
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] Visit active blood surface-mark ring0x6E6254,next+0x4C. Export up to16 entries, stride18: quantized position node+0x14 at+0; four signed quaternion words for matrix node+0x20 at+6; raw color dword node+0x48 at+14. BYTE count; no age,current size,growth duration,maximum size or region pointer in payload. Native initializer0x43D360 supplies8 slots, distinct from collector limit16.
_BYTE *__cdecl rf_blood_surface_mark_snapshot_collect(int a1, _BYTE *a2)
{
  int v3; // [esp+0h] [ebp-1Ch]
  float v4[4]; // [esp+4h] [ebp-18h] BYREF
  int i; // [esp+14h] [ebp-8h]
  int v6; // [esp+18h] [ebp-4h]

  v6 = 0;
  for ( i = dword_6E6254; i; i = v3 )
  {
    if ( v6 < 16 )
    {
      rf_quaternion_set_from_matrix3_normalized_legacy(v4, (float *)(i + 32));
      rf_geomod_saved_position_encode_u16(
        (const float *)rf_world_solid,
        (const float *)(i + 20),
        (unsigned __int16 *)(a1 + 18 * v6));
      rf_snapshot_pack_quaternion_s16_times16383((_WORD *)(a1 + 18 * v6 + 6), v4);
      *(_DWORD *)(a1 + 18 * v6++ + 14) = *(_DWORD *)(i + 72);
    }
    if ( *(_DWORD *)(i + 76) == dword_6E6254 )
      v3 = 0;
    else
      v3 = *(_DWORD *)(i + 76);
  }
  *a2 = v6;
  return a2;
}

