// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00444940 rf_prepare_start_level_and_request_panel5
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments. Compare current level RFString6FC31C case-insensitively with train01.rfl, then train02.rfl; either selects
// train01.rfl. Otherwise glass_house.rfl selects itself. Only other levels consult command-line option88E45C: ANY nonzero enabled byte fetches borrowed argument pointer, performs
// uncapped byte copy INCLUDING NUL into local buffer at EBP-21C, replaces LAST DOT suffix anywhere in that full path with .rfl through57C380, then strips ONLY the last backslash
// prefix. Forward slashes are not stripped, parent-directory dots participate in suffix replacement, and NULL/length/empty arguments are not guarded. Disabled option selects
// l1s1.rfl. Each branch constructs empty save RFString and chosen level RFString DIRECTLY as two8-byte by-value stack objects, then4798E0 copies level into6FC300/save into6FC2F8 and
// destroys both arguments. All branches then call4494C0 initialization notice/cache helper plus unforced panel5 request; no own world load, save validation, explicit error recovery
// or rollback on panel refusal. Two chunks include four save-temporary unwind thunks and C++/cookie handler. Final int is delegate/cookie-tail residue, not proof a level was loaded
// or panel request accepted.
int rf_prepare_start_level_and_request_panel5()
{
  int v1; // [esp-10h] [ebp-290h] BYREF
  char *v2; // [esp-Ch] [ebp-28Ch]
  int v3; // [esp-8h] [ebp-288h] BYREF
  char *v4; // [esp-4h] [ebp-284h]
  _DWORD *v5; // [esp+4h] [ebp-27Ch]
  _DWORD *v6; // [esp+8h] [ebp-278h]
  _DWORD *v7; // [esp+Ch] [ebp-274h]
  _DWORD *v8; // [esp+10h] [ebp-270h]
  _DWORD *v9; // [esp+14h] [ebp-26Ch]
  _DWORD *v10; // [esp+18h] [ebp-268h]
  char v11; // [esp+1Fh] [ebp-261h]
  char *v12; // [esp+20h] [ebp-260h]
  char *v13; // [esp+24h] [ebp-25Ch]
  const char *argument; // [esp+28h] [ebp-258h]
  _DWORD *v15; // [esp+2Ch] [ebp-254h]
  _DWORD *v16; // [esp+30h] [ebp-250h]
  _DWORD *v17; // [esp+34h] [ebp-24Ch]
  _DWORD *v18; // [esp+38h] [ebp-248h]
  _DWORD *v19; // [esp+3Ch] [ebp-244h]
  _DWORD *v20; // [esp+40h] [ebp-240h]
  int *v21; // [esp+44h] [ebp-23Ch]
  void *v22; // [esp+48h] [ebp-238h]
  int *v23; // [esp+4Ch] [ebp-234h]
  void *v24; // [esp+50h] [ebp-230h]
  int *v25; // [esp+54h] [ebp-22Ch]
  void *v26; // [esp+58h] [ebp-228h]
  int *v27; // [esp+5Ch] [ebp-224h]
  void *v28; // [esp+60h] [ebp-220h]
  char Str[516]; // [esp+64h] [ebp-21Ch] BYREF
  char *Source; // [esp+26Ch] [ebp-14h]
  char *last_char_wrapper; // [esp+270h] [ebp-10h]
  int v32; // [esp+27Ch] [ebp-4h]

  if ( rf_string_equals_case_insensitive((int)unk_6FC31C, "train01.rfl")
    || rf_string_equals_case_insensitive((int)unk_6FC31C, "train02.rfl") )
  {
    v28 = &v3;
    v20 = rf_string_construct_from_cstr(&v3, (char *)&byte_63347B);
    v19 = v20;
    v32 = 0;
    v27 = &v1;
    v18 = rf_string_construct_from_cstr(&v1, "train01.rfl");
    v32 = -1;
    rf_level_transition_assign_level_and_save_strings(v1, v2, v3, v4);
  }
  else if ( rf_string_equals_case_insensitive((int)unk_6FC31C, "glass_house.rfl") )
  {
    v26 = &v3;
    v17 = rf_string_construct_from_cstr(&v3, (char *)&byte_633491);
    v16 = v17;
    v32 = 1;
    v25 = &v1;
    v15 = rf_string_construct_from_cstr(&v1, "glass_house.rfl");
    v32 = -1;
    rf_level_transition_assign_level_and_save_strings(v1, v2, v3, v4);
  }
  else if ( rf_command_line_bool_option_is_enabled(byte_88E45C) )
  {
    argument = rf_command_line_option_get_argument(byte_88E45C);
    v13 = Str;
    v12 = Str;
    do
    {
      v11 = *argument;
      *v13 = v11;
      ++argument;
      ++v13;
    }
    while ( v11 );
    rf_path_replace_last_dot_suffix_unbounded(Str, Str, ".rfl");
    Source = Str;
    last_char_wrapper = rf_cstring_find_last_char_wrapper(Str, 92);
    if ( last_char_wrapper )
      Source = last_char_wrapper + 1;
    v24 = &v3;
    v10 = rf_string_construct_from_cstr(&v3, (char *)&byte_633492);
    v9 = v10;
    v32 = 2;
    v23 = &v1;
    v8 = rf_string_construct_from_cstr(&v1, Source);
    v32 = -1;
    rf_level_transition_assign_level_and_save_strings(v1, v2, v3, v4);
  }
  else
  {
    v22 = &v3;
    v7 = rf_string_construct_from_cstr(&v3, (char *)&byte_633493);
    v6 = v7;
    v32 = 3;
    v21 = &v1;
    v5 = rf_string_construct_from_cstr(&v1, "l1s1.rfl");
    v32 = -1;
    rf_level_transition_assign_level_and_save_strings(v1, v2, v3, v4);
  }
  return rf_client_level_entry_initialize_and_request_panel5();
}

