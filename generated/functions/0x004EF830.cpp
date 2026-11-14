// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EF830 rf_undercover_apply_local_weapon_skin_profile
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, thermal renderer x87 branches, native stack aliases, localization pool writes and skin-profile selection): No arguments. Only if signed DWORD87FC0C equals EXACTLY1: gets C string from profile RFString87FC28, calls first-matching skin-profile helper with global local player model52,count1,profile base87FC28,and that same name; ignores returned index. No own player/model NULL or asset-success check. Does not test undercover-active byte87FC01 here.
void rf_undercover_apply_local_weapon_skin_profile()
{
  char *v0; // eax

  if ( unk_87FC0C == 1 )
  {
    v0 = (char *)rf_string_object_c_str_or_empty(unk_87FC28);
    rf_model_apply_first_matching_skin_profile(*(_DWORD *)(rf_local_fpgun_player + 52), 1, (int)unk_87FC28, v0);
  }
}

