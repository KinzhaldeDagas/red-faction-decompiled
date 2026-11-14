// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004ED9D0 rf_fpgun_load_interlace_screen_bitmap
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model cache fallback, material replacement, leg animation transitions and native caller ABI): Loads interlace64x64.tga with bitmap options-1,1 on every call, stores returned integer in663018 and returns it, including failure-1. No previous-handle cleanup, reuse or warmup here.
int rf_fpgun_load_interlace_screen_bitmap()
{
  int result; // eax

  result = rf_bitmap_load_with_optional_mipmap_generation("interlace64x64.tga", (void *)0xFFFFFFFF, 1);
  dword_663018 = result;
  return result;
}

