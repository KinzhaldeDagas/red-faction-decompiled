// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573F10 rf_bitmap_set_load_context_byte
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Stores supplied raw byte at189744C and returns it. Used by texture residency begin/end. Readers include bitmap header probing and TGA CPU loading; load_with_optional_mipmap_generation temporarily clears/restores it. No normalization, iteration or device call.
char __cdecl rf_bitmap_set_load_context_byte(char a1)
{
  unk_189744C = a1;
  return a1;
}

