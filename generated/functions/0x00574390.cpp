// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00574390 rf_bitmap_set_global_reduction_mode
// UNREALRED VERIFIED [bitmap-lifecycle-20261028]: If requested mode differs from global0x1897454, stores it and traverses active bitmap records from0x1897434 until sentinel0x18973E0 through next+84. Calls0x574400(stored handle+36,mode) for each. No cache release, list mutation protection or per-record result handling. Return incidental prior global/list pointer, not count or success.
int __cdecl rf_bitmap_set_global_reduction_mode(int a1)
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  result = dword_1897454;
  if ( dword_1897454 != a1 )
  {
    dword_1897454 = a1;
    for ( i = dword_1897434; (_UNKNOWN *)i != &unk_18973E0; i = *(_DWORD *)(i + 84) )
    {
      rf_bitmap_set_slot_reduction_mode(*(_DWORD *)(dword_1897344 + 108 * ((i - dword_1897344) / 108) + 36), a1);
      result = i;
    }
  }
  return result;
}

