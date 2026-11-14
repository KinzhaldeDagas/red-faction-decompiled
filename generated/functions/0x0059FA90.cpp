// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059FA90 rf_binary_stream_read_float_versioned
// UNREALRED VERIFIED [mission-mover-layout-20261013] Version-gated float32 reader: if stream version is too old, return default; otherwise consume exactly 4 bytes and return read float unless stream error requests default. Value is returned in x87 ST0 (fld local/default; retn8), not EAX. Mover-loader float fields must be read from FSTP instructions even if cached pseudocode displays zero.
double __thiscall rf_binary_stream_read_float_versioned(int *this, int a2, float a3)
{
  float v5; // [esp+4h] [ebp-4h] BYREF

  if ( !rf_binary_stream_version_at_least(this, a2) )
    return a3;
  rf_vfile_read_buffered_bytes_versioned(this, (char *)&v5, 4u, 0, 0);
  if ( rf_vfile_get_open_slot_status(this) )
    return a3;
  else
    return v5;
}

