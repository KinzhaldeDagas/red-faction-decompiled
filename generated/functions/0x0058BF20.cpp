// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058BF20 rf_font_invalidate_all_atlas_bitmap_handles
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Walks font records at193B688, stride108, for count193BB98; writes -1 to atlas bitmap handle+84 in each. Does not release the bitmap or font allocations, reset other fields, or rebuild atlas immediately. Text-to-bitmap caller58D5F0 lazily recreates a negative atlas handle. EAX incidental loop count.
int rf_font_invalidate_all_atlas_bitmap_handles()
{
  int result; // eax
  _DWORD *v1; // [esp+0h] [ebp-Ch]
  int i; // [esp+4h] [ebp-8h]

  v1 = &unk_193B688;
  for ( i = 0; i < unk_193BB98; ++i )
  {
    v1[21] = -1;
    v1 += 27;
    result = i + 1;
  }
  return result;
}

