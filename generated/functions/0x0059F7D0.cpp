// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059F7D0 rf_binary_stream_read_string_object_u16_length
// UNREALRED VERIFIED [binary-fields-20261029]: cdecl stream,RF string-object pointer. Calls0x55F580 on object,sets first DWORD0,reads unsigned16-bit length through0x59F9A0(version0,default0). Nonzero length calls0x55F530(object,length),reads that many bytes into object buffer+4,then appends NUL at buffer[length]. Does not inspect read status before NUL store or restore prior object on failure. Prefix length0 leaves cleared object. Return is incidental EAX from WORD getter on empty prefix (only low16 defined),or FULL object address on nonempty prefix. Existing unsigned-short return prototype is misleading; not a character count.
unsigned __int16 __cdecl rf_binary_stream_read_string_object_u16_length(int *a1, int a2)
{
  unsigned __int16 result; // ax
  size_t Size; // [esp+0h] [ebp-4h]

  rf_string_release_buffer_keep_extent((_DWORD *)a2);
  *(_DWORD *)a2 = 0;
  result = rf_binary_stream_read_uint16_versioned(a1, 0, 0);
  Size = result;
  if ( result )
  {
    rf_string_reset_and_reserve_extent((_DWORD *)a2, result);
    rf_vfile_read_buffered_bytes_versioned(a1, *(char **)(a2 + 4), Size, 0, 0);
    *(_BYTE *)(*(_DWORD *)(a2 + 4) + Size) = 0;
    return a2;
  }
  return result;
}

