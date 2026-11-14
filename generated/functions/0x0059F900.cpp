// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059F900 rf_binary_stream_read_byte_versioned
// UNREALRED VERIFIED [mission-startup-20261020] Raw-byte primitive consumes exactly one byte on supported versions, preserving values0..255, unlike0x59F840. Trigger NPC activation policy is read through this function.
char __thiscall rf_binary_stream_read_byte_versioned(int *this, int a2, char a3)
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

