// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048A880 rf_mover_snapshot_collect
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] Collect96-byte mover records from list0x70489C,sentinel0x704610,next+0x28C. Common60 prefix plus float owner+0x2F0 at+60; low bytes+0x2F8/+0x2FC at+64/+65; low word flags+0x318 at+66; floats+0x300/+0x308 at+68/+72; remaining deadline+0x310 at+76; saved-id reference+0x314 at+80; floats+0x304/+0x2F4 at+84/+88; raw dword+0x30C at+92. BYTE count; no carryover-filter gate here. Common pack can mutate live health/armor through its clamps.
_BYTE *__cdecl rf_mover_snapshot_collect(int a1, _BYTE *a2)
{
  int i; // [esp+0h] [ebp-8h]
  int v4; // [esp+4h] [ebp-4h]

  v4 = 0;
  for ( i = unk_70489C; (_UNKNOWN *)i != &unk_704610; i = *(_DWORD *)(i + 652) )
  {
    rf_object_snapshot_pack_common60(i, a1 + 96 * v4);
    *(float *)(a1 + 96 * v4 + 60) = *(float *)(i + 752);
    *(_BYTE *)(a1 + 96 * v4 + 64) = *(_BYTE *)(i + 760);
    *(_BYTE *)(a1 + 96 * v4 + 65) = *(_BYTE *)(i + 764);
    *(_WORD *)(a1 + 96 * v4 + 66) = *(_WORD *)(i + 792);
    *(float *)(a1 + 96 * v4 + 68) = *(float *)(i + 768);
    *(float *)(a1 + 96 * v4 + 72) = *(float *)(i + 776);
    rf_snapshot_pack_replicator_remaining((int *)(i + 784), (int *)(a1 + 96 * v4 + 76));
    *(_DWORD *)(a1 + 96 * v4 + 80) = rf_object_runtime_identifier_to_saved_identifier(*(_DWORD *)(i + 788));
    *(float *)(a1 + 96 * v4 + 84) = *(float *)(i + 772);
    *(float *)(a1 + 96 * v4 + 88) = *(float *)(i + 756);
    *(_DWORD *)(a1 + 96 * v4++ + 92) = *(_DWORD *)(i + 780);
  }
  *a2 = v4;
  return a2;
}

