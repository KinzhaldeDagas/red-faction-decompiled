// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00474300 rf_item_snapshot_collect
// UNREALRED VERIFIED [object-entity-snapshot-continuation-20261027] Visit item list head0x6FB1C4,sentinel0x6FAF38,next+0x28C. Skip owner common mask0x800; pack80-byte entry: common60 prefix, remaining timer owner+0x2B0 at+60, floats+0x2B4/+0x2B8 at+64/+68, dword flags+0x2BC at+72, definition index+0x298 at+76. Export total through BYTE count pointer, no local capacity argument/clamp. Does not collect carryover-mask0x800 items.
_BYTE *__cdecl rf_item_snapshot_collect(int a1, _BYTE *a2)
{
  int i; // [esp+0h] [ebp-8h]
  int v4; // [esp+4h] [ebp-4h]

  v4 = 0;
  for ( i = unk_6FB1C4; (_UNKNOWN *)i != &unk_6FAF38; i = *(_DWORD *)(i + 652) )
  {
    if ( (*(_DWORD *)(i + 124) & 0x800) == 0 )
    {
      rf_object_snapshot_pack_common60(i, a1 + 80 * v4);
      rf_snapshot_pack_replicator_remaining((int *)(i + 688), (int *)(a1 + 80 * v4 + 60));
      *(float *)(a1 + 80 * v4 + 64) = *(float *)(i + 692);
      *(float *)(a1 + 80 * v4 + 68) = *(float *)(i + 696);
      *(_DWORD *)(a1 + 80 * v4 + 72) = *(_DWORD *)(i + 700);
      *(_DWORD *)(a1 + 80 * v4++ + 76) = *(_DWORD *)(i + 664);
    }
  }
  *a2 = v4;
  return a2;
}

