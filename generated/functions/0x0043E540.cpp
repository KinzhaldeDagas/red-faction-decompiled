// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043E540 rf_blood_surface_mark_snapshot_restore
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] For each18-byte input use free-head0x6E6228 only; if empty skip entry without eviction. Decode position/orientation and color, then reset node floats(age,current size,growth duration,max size,growth rate)=(8.0,0.5,8.0,0.5,~0.19634955). Query region through0x517060, unlink free node and append active ring0x6E6254. Restored mark starts fully grown rather than restoring saved elapsed time. No active-ring reset or duplicate matching before replay.
void __cdecl rf_blood_surface_mark_snapshot_restore(int a1, int a2)
{
  void *v2; // eax
  float v3[4]; // [esp+0h] [ebp-1Ch] BYREF
  int v4; // [esp+10h] [ebp-Ch]
  unsigned __int16 *packed_position; // [esp+14h] [ebp-8h]
  int i; // [esp+18h] [ebp-4h]

  for ( i = 0; i < a2; ++i )
  {
    packed_position = (unsigned __int16 *)(a1 + 18 * i);
    v4 = unk_6E6228;
    if ( !unk_6E6228 )
      continue;
    rf_float4_construct_zero_zero_zero_one(v3);
    rf_geomod_saved_position_decode_u16((const float *)rf_world_solid, packed_position, (float *)(v4 + 20));
    rf_snapshot_unpack_quaternion_s16(v3, (__int16 *)packed_position + 3);
    rf_quaternion_to_matrix3_rows(v3, (float *)(v4 + 32));
    *(float *)v4 = 8.0;
    *(float *)(v4 + 4) = 0.5;
    *(float *)(v4 + 8) = 8.0;
    *(float *)(v4 + 12) = 0.5;
    *(float *)(v4 + 16) = 0.19634955;
    *(_DWORD *)(v4 + 72) = *(_DWORD *)(packed_position + 7);
    v2 = rf_world_resolve_cached_room(
           (void *)rf_world_solid,
           nullptr,
           (const float *)(v4 + 20),
           (const float *)(v4 + 20),
           0);
    *(_DWORD *)(v4 + 68) = v2;
    if ( unk_6E6228 == v4 )
    {
      if ( *(_DWORD *)(v4 + 76) == v4 )
      {
        *(_DWORD *)(v4 + 76) = 0;
        *(_DWORD *)(v4 + 80) = 0;
        unk_6E6228 = 0;
        goto LABEL_9;
      }
      unk_6E6228 = *(_DWORD *)(v4 + 76);
    }
    *(_DWORD *)(*(_DWORD *)(v4 + 80) + 76) = *(_DWORD *)(v4 + 76);
    *(_DWORD *)(*(_DWORD *)(v4 + 76) + 80) = *(_DWORD *)(v4 + 80);
    *(_DWORD *)(v4 + 76) = 0;
    *(_DWORD *)(v4 + 80) = 0;
LABEL_9:
    if ( dword_6E6254 )
    {
      *(_DWORD *)(v4 + 80) = *(_DWORD *)(dword_6E6254 + 80);
      *(_DWORD *)(v4 + 76) = dword_6E6254;
      *(_DWORD *)(*(_DWORD *)(dword_6E6254 + 80) + 76) = v4;
      *(_DWORD *)(dword_6E6254 + 80) = v4;
    }
    else
    {
      *(_DWORD *)(v4 + 76) = v4;
      *(_DWORD *)(v4 + 80) = v4;
      dword_6E6254 = v4;
    }
  }
}

