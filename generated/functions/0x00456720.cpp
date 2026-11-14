// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00456720 rf_save_list_b_request_save
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No consumed arguments. FIRST clear modeBYTE6F23D0. Unbounded strlen(edit text6F2788); empty shows46F150(title88E2D0,message88E3AC,NULL,NULL). Nonempty
// calls4F6F50 quicksave admission with NO pushed args (residual ECX pseudoparameter is not a consumed argument); AL0 shows OK message88E368. Allowed: unbounded copy edit text ONLY,
// without prefix88E7D0, into local path;57C380 in place .svl;57CE90(path,rootDWORD88E41C) loose-file stat predicate. Nonzero AL
// requests46F2A0(title88E2D0,message88E3B0,Yes456540,NoNULL,option0); callback passed, not called here. AL0 directly calls456540. No trim/sanitize/35-character bound/full validation,
// rollback, selection reset or close. Confirmation stores callback rather than filename snapshot; later456540 uses LIVE edit text and does not rerun4F6F50 in wrapper. Writer still
// owns its own checks. Cookie epilogue, path-dependent return residue.
int rf_save_list_b_request_save()
{
  char *v0; // ecx
  char v2; // [esp+Bh] [ebp-13Dh]
  char *v3; // [esp+10h] [ebp-138h]
  char *v4; // [esp+14h] [ebp-134h]
  char *v6; // [esp+34h] [ebp-114h]
  char Str[268]; // [esp+38h] [ebp-110h] BYREF

  byte_6F23D0[0] = 0;
  v6 = unk_6F2788;
  do
    v0 = v6;
  while ( *v6++ );
  if ( v6 == (char *)&unk_6F2789 )
    return rf_ui_show_ok_modal(unk_88E2D0, unk_88E3AC, 0, 0);
  if ( !rf_quicksave_is_allowed(v0) )
    return rf_ui_show_ok_modal(unk_88E2D0, unk_88E368, 0, 0);
  v4 = unk_6F2788;
  v3 = Str;
  do
  {
    v2 = *v4;
    *v3++ = *v4++;
  }
  while ( v2 );
  rf_path_replace_last_dot_suffix_unbounded(Str, Str, ".svl");
  if ( rf_vfile_loose_path_stat_exists(Str, unk_88E41C) )
    return rf_ui_show_yes_no_modal(unk_88E2D0, unk_88E3B0, (int)rf_save_list_b_execute_save, 0, 0);
  else
    return rf_save_list_b_execute_save();
}

