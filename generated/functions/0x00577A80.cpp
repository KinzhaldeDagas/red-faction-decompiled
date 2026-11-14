// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00577A80 rf_bitmap_pixel16_toggle_high_bit_run
// UNREALRED VERIFIED [bitmap-loading-20261028]: For caller pixel count, XORs each16-bit word with0x8000 in place. Toggles rather than sets alpha/high bit; no format test or conversion. Returns count loop artifact for positive count; return undefined/uninitialized when no loop executes. No pointer/count bounds guard.
int __cdecl rf_bitmap_pixel16_toggle_high_bit_run(_WORD *a1, int a2)
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < a2; ++i )
  {
    *a1++ ^= 0x8000u;
    result = i + 1;
  }
  return result;
}

