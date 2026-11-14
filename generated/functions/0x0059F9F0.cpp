// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059F9F0 rf_binary_stream_read_int32_versioned
// UNREALRED VERIFIED [mission-visibility-20261020] Version-gated signed32 read with default: stream version below arg0 returns arg1 without consuming4bytes. Legacy-entry reader4826F0 passes shared scratch0x6FCCA8 as arg0, so a nonempty list cannot always be modeled as unconditional name/int32 pairs.
int __thiscall rf_binary_stream_read_int32_versioned(int *this, int a2, int a3)
{
  int v5; // [esp+4h] [ebp-4h] BYREF

  if ( !rf_binary_stream_version_at_least(this, a2) )
    return a3;
  rf_vfile_read_buffered_bytes_versioned(this, (char *)&v5, 4u, 0, 0);
  if ( rf_vfile_get_open_slot_status(this) )
    return a3;
  else
    return v5;
}

