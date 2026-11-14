// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004160A0 rf_clutter_snapshot_collect
// UNREALRED VERIFIED [object-entity-snapshot-continuation-20261027] Visit clutter list, excluding common mask0x800. Pack24-byte records: stable id+0; low state byte owner+0x2BC at+4; boolean hidden/common0x4000 at+5; quantized published position+0x3C at+6; remaining owner+0x2A4 timer at+12; raw dword owner+0x2A8 at+16; remaining owner+0x2B0 timer at+20. Count output is16-bit WORD, unlike item/entity byte counts. No common60 prefix, health or orientation in this payload.
__int16 __cdecl rf_clutter_snapshot_collect(int a1, _WORD *a2)
{
  int i; // [esp+0h] [ebp-8h]
  int v4; // [esp+4h] [ebp-4h]

  v4 = 0;
  for ( i = rf_clutter_list_head; (_UNKNOWN *)i != &unk_666D18; i = *(_DWORD *)(i + 652) )
  {
    if ( (*(_DWORD *)(i + 124) & 0x800) == 0 )
    {
      *(_DWORD *)(a1 + 24 * v4) = *(_DWORD *)(i + 32);
      rf_geomod_saved_position_encode_u16(
        (const float *)rf_world_solid,
        (const float *)(i + 60),
        (unsigned __int16 *)(a1 + 24 * v4 + 6));
      rf_snapshot_pack_replicator_remaining((int *)(i + 676), (int *)(a1 + 24 * v4 + 12));
      *(_DWORD *)(a1 + 24 * v4 + 16) = *(_DWORD *)(i + 680);
      rf_snapshot_pack_replicator_remaining((int *)(i + 688), (int *)(a1 + 24 * v4 + 20));
      *(_BYTE *)(a1 + 24 * v4 + 4) = *(_BYTE *)(i + 700);
      *(_BYTE *)(a1 + 24 * v4++ + 5) = (*(_DWORD *)(i + 124) & 0x4000) != 0;
    }
  }
  *a2 = v4;
  return v4;
}

