// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F8D0 rf_string_substring_inclusive
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, glyph/string layouts, read/write flow and callers): Thiscall source object, output object, start, inclusiveEnd. end==-1 maps to storedExtent-1; Count=end-start+1. Constructs a temporary with nonnegative requested capacity, strncpy Count bytes from source.buffer+start, writes NUL at destination[Count], copy-constructs output and destroys temporary. No start/end/order/count validation before copy. Negative Count still reaches strncpy as a size and indexes destination negatively despite constructor clamping reserve to0. Returns output pointer.
_DWORD *__thiscall rf_string_substring_inclusive(_DWORD *this, _DWORD *a2, int a3, int a4)
{
  int Count; // [esp+Ch] [ebp-18h]
  char *v7; // [esp+10h] [ebp-14h] BYREF
  char *Destination; // [esp+14h] [ebp-10h]
  int v9; // [esp+20h] [ebp-4h]

  if ( a4 == -1 )
    a4 = *this - 1;
  Count = a4 - a3 + 1;
  rf_string_construct_reserved_extent(&v7, Count);
  v9 = 1;
  strncpy(Destination, (const char *)(a3 + *(this + 1)), Count);
  Destination[Count] = 0;
  rf_string_copy_construct_from_object(a2, &v7);
  LOBYTE(v9) = 0;
  rf_string_destroy_buffer(&v7);
  return a2;
}

