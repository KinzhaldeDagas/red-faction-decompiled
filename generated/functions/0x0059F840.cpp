// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059F840 rf_binary_stream_read_bool_versioned
// UNREALRED VERIFIED [mission-startup-20261020] Trigger boolean normalization matters for use, weapon, auto-Use, startup and vehicle flags: raw nonzero becomes1. The adjacent NPC policy goes through raw-byte0x59F900 and must remain numeric.
// UNREALRED VERIFIED [combat-route-operands-20261111] RFL custom attack-range v148 enable uses this BOOL reader: successful raw0 becomes0 and ANY nonzero including2/255 becomes1;4811C0 stores normalized byte Entity7C8/AI528, then401FD0 exact==1 is satisfied. Preserve rawRF float atEntity7CC/AI52C without CM roundtrip; do not invent unnormalized native528 values from serialized source bytes.
bool __thiscall rf_binary_stream_read_bool_versioned(int *this, int a2, char a3)
{
  char v5; // [esp+7h] [ebp-5h] BYREF
  size_t Size; // [esp+8h] [ebp-4h]

  Size = 1;
  if ( !rf_binary_stream_version_at_least(this, a2) )
    return a3;
  rf_vfile_read_buffered_bytes_versioned(this, &v5, Size, 0, 0);
  if ( rf_vfile_get_open_slot_status(this) )
    return a3;
  else
    return v5 != 0;
}

