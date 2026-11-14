// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048A9F0 rf_mover_snapshot_restore
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] Existing mover stable-id match restores common60 and tail96. Bytes+64/+65 SIGN-extend into owner+0x2F8/+0x2FC; flags word+66 ZERO-extends into+0x318. Restore timer+0x310 and queue id fixup+0x314; restore remaining floats/dword. Unmatched current movers are left intact; no deletion or recreation pass. Always set global0x704605=1 after traversal, including zero matches; no immediate child-transform compose call in this body.
int __cdecl rf_mover_snapshot_restore(int a1, int a2)
{
  int result; // eax
  float copy_result[3]; // [esp+0h] [ebp-18h] BYREF
  char v4; // [esp+Fh] [ebp-9h]
  int i; // [esp+10h] [ebp-8h]
  int j; // [esp+14h] [ebp-4h]

  result = unk_70489C;
  for ( i = unk_70489C; (_UNKNOWN *)i != &unk_704610; i = *(_DWORD *)(i + 652) )
  {
    v4 = 0;
    for ( j = 0; j < a2; ++j )
    {
      if ( *(_DWORD *)(i + 32) == *(_DWORD *)(a1 + 96 * j) )
      {
        rf_object_snapshot_restore_common60(i, a1 + 96 * j);
        rf_vector_copy((float *)(i + 60), copy_result, (const float *)(i + 228));
        *(float *)(i + 752) = *(float *)(a1 + 96 * j + 60);
        *(_DWORD *)(i + 760) = *(char *)(a1 + 96 * j + 64);
        *(_DWORD *)(i + 764) = *(char *)(a1 + 96 * j + 65);
        *(_DWORD *)(i + 792) = *(unsigned __int16 *)(a1 + 96 * j + 66);
        *(float *)(i + 768) = *(float *)(a1 + 96 * j + 68);
        *(float *)(i + 776) = *(float *)(a1 + 96 * j + 72);
        rf_snapshot_unpack_replicator_remaining((int *)(i + 784), (int *)(a1 + 96 * j + 76));
        rf_restore_queue_object_identifier_fixup(*(_DWORD *)(a1 + 96 * j + 80), i + 788);
        *(float *)(i + 772) = *(float *)(a1 + 96 * j + 84);
        *(float *)(i + 756) = *(float *)(a1 + 96 * j + 88);
        result = a1;
        *(_DWORD *)(i + 780) = *(_DWORD *)(a1 + 96 * j + 92);
        v4 = 1;
        break;
      }
      result = j + 1;
    }
  }
  unk_704605 = 1;
  return result;
}

