// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00456540 rf_save_list_b_execute_save
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No consumed arguments; callback-supplied slots ignored. Unbounded concatenate prefix C string AT88E7D0 and LIVE edit text6F2788 into local
// path.57C380(path,path,.svl) replaces last-dot suffix of full path; no own validation/length bound. Call4F3B00(path,LIVE rf_local_fpgun_player) and IGNORE writer return. Clear
// edit6F2748 with4706C0 and font6F29AC; release array6F26AC with517F40; reenumerate456160; show46F150(localized title88E2D0,message88E2D4,NULL,NULL) EVEN IF writer failed. Ignore
// modal refusal. Constant-zero branches bypass English alternatives. Stack cookie present. No own permission/nonempty/overwrite recheck, captured dialog filename, rollback,
// last-used-path890400 update or panel close. Later Yes callback uses live text, not original checked path; actual writer admission/IO delegated. EAX incidental.
int rf_save_list_b_execute_save()
{
  char *v2; // [esp+14h] [ebp-138h]
  char *v3; // [esp+28h] [ebp-124h]
  CHAR v4; // [esp+2Fh] [ebp-11Dh]
  char *v5; // [esp+34h] [ebp-118h]
  CHAR *v6; // [esp+38h] [ebp-114h] BYREF
  char Str[268]; // [esp+3Ch] [ebp-110h] BYREF

  v6 = MEMORY[0x88E7D0];
  v5 = Str;
  do
  {
    v4 = *v6;
    *v5++ = *v6++;
  }
  while ( v4 );
  v3 = &unk_6F2788[strlen(unk_6F2788) + 1];
  v2 = (char *)&v6 + 3;
  while ( *++v2 )
    ;
  qmemcpy(v2, unk_6F2788, v3 - unk_6F2788);
  rf_path_replace_last_dot_suffix_unbounded(Str, Str, ".svl");
  rf_savegame_write_file_for_player(Str, rf_local_fpgun_player);
  rf_ui_edit_set_text_bounded(byte_6F2748, (char *)&byte_63548A, unk_6F29AC);
  rf_pointer_array_release_storage((void **)&unk_6F26AC);
  rf_save_list_b_enumerate_valid_save_records();
  return rf_ui_show_ok_modal(unk_88E2D0, unk_88E2D4, 0, 0);
}

