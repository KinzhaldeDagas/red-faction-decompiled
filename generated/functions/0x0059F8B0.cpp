// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059F8B0 rf_binary_stream_read_char8_versioned
// UNREALRED VERIFIED [binary-fields-20261029]: Thiscall stream,minimum version,default8-bit value. Below minimum returns default without reading. Otherwise reads1 byte through raw buffered reader(version0),then if stream status nonzero returns default;else returns byte in AL. Does not clear error or undo consumed bytes. Parallel0x59F900 uses same-width byte semantics; no byte-order conversion.
char __thiscall rf_binary_stream_read_char8_versioned(int *this, int a2, char a3)
{
  char v5; // [esp+7h] [ebp-1h] BYREF

  if ( !rf_binary_stream_version_at_least(this, a2) )
    return a3;
  rf_vfile_read_buffered_bytes_versioned(this, &v5, 1u, 0, 0);
  if ( rf_vfile_get_open_slot_status(this) )
    return a3;
  else
    return v5;
}

