// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055FA60 rf_string_right_count
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, string ownership/extent layout and branch conditions): Thiscall source, output object, requested count. Signed comparison: count>=stored extent copies whole source C string. For0<count<extent, reserves count+1 and strncpy count+1 bytes from source.buffer+extent-count; assumes that range includes source terminator, with no separate final-NUL write. Count<=0 leaves empty temporary. Copy-constructs output, destroys temporary, returns output. Uses stored extent rather than strlen, so prior in-place trim affects semantics.
_DWORD *__thiscall rf_string_right_count(void *this, _DWORD *a2, int a3)
{
  char *v5[2]; // [esp+Ch] [ebp-14h] BYREF
  int v6; // [esp+1Ch] [ebp-4h]

  rf_string_construct_empty(v5);
  v6 = 1;
  if ( a3 < *(_DWORD *)this )
  {
    if ( a3 > 0 )
    {
      rf_string_reset_and_reserve_extent(v5, a3 + 1);
      strncpy(v5[1], (const char *)(*((_DWORD *)this + 1) + *(_DWORD *)this - a3), a3 + 1);
    }
  }
  else
  {
    rf_string_assign_cstr_bounded((int)v5, *((char **)this + 1), -1);
  }
  rf_string_copy_construct_from_object(a2, v5);
  LOBYTE(v6) = 0;
  rf_string_destroy_buffer(v5);
  return a2;
}

