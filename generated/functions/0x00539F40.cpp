// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00539F40 rf_procedural_bitmap_pool_clear
// UNREALRED VERIFIED [resource-pools-20261028]: Repeatedly releases active head0x142665C through0x539F70 untilnull. Frees generated bitmap references, recycles fixed records; does not reinitialize sine table or destroy auxiliary registry.
int rf_procedural_bitmap_pool_clear()
{
  int result; // eax
  _DWORD *i; // [esp+0h] [ebp-4h]

  result = unk_142665C;
  for ( i = (_DWORD *)unk_142665C; i; i = (_DWORD *)unk_142665C )
    result = rf_procedural_bitmap_record_release(i);
  return result;
}

