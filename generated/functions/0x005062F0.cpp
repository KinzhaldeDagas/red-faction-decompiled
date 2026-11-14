// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005062F0 rf_trigger_snapshot_collect
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] Collect36-byte TRIGGER records from rf_trigger_runtime_list_head,next+0x28C,sentinel0x90B510. Entry+0 saved id owner+0x20;+4 quantized published position+0x3C;+12 raw flags+0x2A0;+16 float+0x2A8;+20 dword+0x2B0;+24 saved-id conversion of owner+0x2E4;+28/+32 packed deadlines+0x2F4/+0x2FC. Export BYTE count; no common60 prefix, carryover filter, shape/orientation payload or direct trigger activation.
_BYTE *__cdecl rf_trigger_snapshot_collect(int a1, _BYTE *a2)
{
  int i; // [esp+0h] [ebp-8h]
  int v4; // [esp+4h] [ebp-4h]

  v4 = 0;
  for ( i = rf_trigger_runtime_list_head; (_UNKNOWN *)i != &unk_90B510; i = *(_DWORD *)(i + 652) )
  {
    *(_DWORD *)(a1 + 36 * v4) = *(_DWORD *)(i + 32);
    rf_geomod_saved_position_encode_u16(
      (const float *)rf_world_solid,
      (const float *)(i + 60),
      (unsigned __int16 *)(a1 + 36 * v4 + 4));
    *(_DWORD *)(a1 + 36 * v4 + 12) = *(_DWORD *)(i + 672);
    *(float *)(a1 + 36 * v4 + 16) = *(float *)(i + 680);
    *(_DWORD *)(a1 + 36 * v4 + 20) = *(_DWORD *)(i + 688);
    *(_DWORD *)(a1 + 36 * v4 + 24) = rf_object_runtime_identifier_to_saved_identifier(*(_DWORD *)(i + 740));
    rf_snapshot_pack_replicator_remaining((int *)(i + 756), (int *)(a1 + 36 * v4 + 28));
    rf_snapshot_pack_replicator_remaining((int *)(i + 764), (int *)(a1 + 36 * v4++ + 32));
  }
  *a2 = v4;
  return a2;
}

