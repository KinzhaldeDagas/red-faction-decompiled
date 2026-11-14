// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055FB30 rf_string_mid_start_count
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, string ownership/extent layout and branch conditions): Thiscall source, output object, signed start, requested count. Constructs temporary reserve using original count, then reduces copy count when start+count>stored extent. Copies only if resulting count>0, adds NUL and copy-constructs output. Negative count or start beyond extent typically yields empty; negative start is not rejected and may read before source buffer. No signed-add overflow or source-NULL check. Returns output pointer.
_DWORD *__thiscall rf_string_mid_start_count(_DWORD *this, _DWORD *a2, int a3, int Count)
{
  char *v6; // [esp+Ch] [ebp-14h] BYREF
  char *Destination; // [esp+10h] [ebp-10h]
  int v8; // [esp+1Ch] [ebp-4h]

  rf_string_construct_reserved_extent(&v6, Count);
  v8 = 1;
  if ( Count + a3 > *this )
    Count = *this - a3;
  if ( Count > 0 )
  {
    strncpy(Destination, (const char *)(a3 + *(this + 1)), Count);
    Destination[Count] = 0;
  }
  rf_string_copy_construct_from_object(a2, &v6);
  LOBYTE(v8) = 0;
  rf_string_destroy_buffer(&v6);
  return a2;
}

