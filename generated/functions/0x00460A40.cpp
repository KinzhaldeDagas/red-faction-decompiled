// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00460A40 rf_multiplayer_profile_commit_dirty_name
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Noarg. Raw dirtyBYTE6F4AD6 zero ->no work. Otherwise construct owned8-byte RFString from edit Cstring6F4B48,pass by value to verified
// player_set_display_name_from_owned_string (caller cleanup8). Only nonzero setterAL AND runtimeBYTE ANY nonzero invoke send_local_display_name. Then clear dirty regardless setter
// failure/runtime/send outcome. No own empty/length/player/authority admission;setter/sender own policies. No character commit/rollback,edit-buffer reset or retry retention. Existing
// int return is guard/delegate residue,not uniform name-changed status.
char rf_multiplayer_profile_commit_dirty_name()
{
  char result; // al
  int v1[2]; // [esp-8h] [ebp-18h] BYREF
  char v2; // [esp+3h] [ebp-Dh]
  _DWORD *v3; // [esp+4h] [ebp-Ch]
  int *v4; // [esp+8h] [ebp-8h]
  char v5; // [esp+Fh] [ebp-1h]

  result = unk_6F4AD6;
  if ( unk_6F4AD6 )
  {
    v4 = v1;
    v3 = rf_string_construct_from_cstr(v1, unk_6F4B48);
    result = rf_player_set_display_name_from_owned_string(v1[0], (char *)v1[1]);
    v2 = result;
    v5 = result;
    if ( result )
    {
      result = rf_multiplayer_runtime_mode;
      if ( rf_multiplayer_runtime_mode )
        result = rf_multiplayer_send_local_display_name();
    }
    unk_6F4AD6 = 0;
  }
  return result;
}

