// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E27D0 rf_player_set_display_name_from_owned_string
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player view/movement/light/shield/score contracts and owned RFString native ABI): Takes OWNED8-byte RFString BY VALUE: two caller-popped DWORDs(stored extent,buffer). Corrected incomplete one-C-string prototype to explicit raw two-field representation. Both native callers460A40/4DA2B0 reserve8 bytes, construct RFString at ESP, call then ADD ESP8 and test AL. Callee destroys owned stack RFString on every normal path and SEH unwind. Global local-player NULL returns AL0 after destruction. Trim leading/trailing SPACE/TAB/LF, compute actual strlen; reject <=0 or>20 BYTES, dispatch localized88E3D0/88E344 via console when console-visible nonzero, otherwise modal. On accepted1..20 bytes, replace current percent byte0x25 with underscore. Otherwise IMPORTANT native4E29A1 reads BYTE[global1809820+index] and compares
// backslash0x5C; on match replace CURRENT name byte, even if unrelated. This is global console-argument scratch, NOT current RFString buffer and NOT zero sentinel17F1114; UI source6F4B48 differs, trimming can misalign console source too. Thus does not reliably sanitize every name backslash. Assign accepted RFString to local player+8, destroy argument, return AL1. No networking, uniqueness or further character whitelist here; executable behavior documented without patching.
char __cdecl rf_player_set_display_name_from_owned_string(int name_extent, char *name_buffer)
{
  int i; // [esp+20h] [ebp-10h]

  if ( !rf_local_fpgun_player )
    goto LABEL_10;
  rf_string_trim_leading_space_tab_lf((int)&name_extent);
  rf_string_trim_trailing_space_tab_lf((int)&name_extent);
  if ( (int)rf_string_length_from_cstr((const char **)&name_extent) <= 0 )
  {
    if ( rf_console_get_visible_byte() )
      rf_console_output_append_text_lines(dword_88E3D0, nullptr);
    else
      rf_ui_show_ok_modal(unk_88E3D4, (char *)dword_88E3D0, nullptr, 0);
LABEL_10:
    rf_string_destroy_buffer(&name_extent);
    return 0;
  }
  if ( (int)rf_string_length_from_cstr((const char **)&name_extent) > 20 )
  {
    if ( rf_console_get_visible_byte() )
      rf_console_output_append_text_lines(dword_88E344, nullptr);
    else
      rf_ui_show_ok_modal(unk_88E3D4, (char *)dword_88E344, nullptr, 0);
    goto LABEL_10;
  }
  for ( i = 0; i < (int)rf_string_length_from_cstr((const char **)&name_extent); ++i )
  {
    if ( *rf_string_byte_pointer_or_zero_sentinel(&name_extent, i) == 37 || *(&MEMORY[0x1809820] + i) == 92 )
      *rf_string_byte_pointer_or_zero_sentinel(&name_extent, i) = 95;
  }
  rf_string_assign_from_object((_DWORD *)(rf_local_fpgun_player + 8), (int)&name_extent);
  rf_string_destroy_buffer(&name_extent);
  return 1;
}

