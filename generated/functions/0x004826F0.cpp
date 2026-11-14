// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004826F0 rf_rfl_discard_legacy_object_entries
// UNREALRED VERIFIED [mission-visibility-20261020] Shared legacy-entry reader: version52 signed count, then for each entry version0 length-prefixed name into scratch0x6FCCC0 and an int32 read whose minimum-version ARGUMENT is the current value at0x6FCCA8, default0. This scratch starts-1 and is also written by multiplayer-respawn UID loading0x47F7A0. Do not assume five booleans or an unconditional fixed-size list. All1610 entities and12659 clutter records across94 retail v180 maps contain count0. UnrealRed rejects nonempty lists until this shared loader state is modeled.
int __cdecl rf_rfl_discard_legacy_object_entries(_DWORD *a1)
{
  int int32_versioned; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  int32_versioned = rf_binary_stream_read_int32_versioned(a1, 52, 0);
  for ( i = 0; i < int32_versioned; ++i )
  {
    rf_binary_stream_read_string_object_versioned(a1, unk_6FCCC0, 0, nullptr);
    rf_binary_stream_read_int32_versioned(a1, dword_6FCCA8, 0);
  }
  return 0;
}

