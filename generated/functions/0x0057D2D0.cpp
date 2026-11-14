// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057D2D0 rf_stream_adapter_read_u16_string_to_rf_string
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Releases RFString8 buffer, explicitly clears extent0, reads uint16 length from adapter. Zero leaves empty object and returnsAX0. Positive length reserves that extent, bulk-reads payload into buffer+4, then writes buffer[length]=NUL. Ignores bulk-read failure (including exact-end memory rejection), so terminator can accompany uninitialized payload. Positive path returns object bits; return is not uniform length/status.
unsigned __int16 __cdecl rf_stream_adapter_read_u16_string_to_rf_string(void *a1, int a2)
{
  unsigned __int16 result; // ax
  size_t Size; // [esp+0h] [ebp-4h]

  rf_string_release_buffer_keep_extent((_DWORD *)a2);
  *(_DWORD *)a2 = 0;
  result = rf_stream_adapter_read_uint16(a1);
  Size = result;
  if ( result )
  {
    rf_string_reset_and_reserve_extent((_DWORD *)a2, result);
    rf_stream_adapter_read_bytes((int **)a1, *(char **)(a2 + 4), Size);
    *(_BYTE *)(*(_DWORD *)(a2 + 4) + Size) = 0;
    return a2;
  }
  return result;
}

