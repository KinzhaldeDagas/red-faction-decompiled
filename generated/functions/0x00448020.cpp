// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00448020 rf_ui_reload_last_requested_level
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments. Constructs an empty-save RFString directly in an8-byte stack argument, then copy-constructs RFString6FC31C into a
// second8-byte stack argument. Calls4798E0 with the resulting16-byte by-value level/save pair; that helper assigns level6FC300/save6FC2F8 and destroys both argument strings. Then
// requests panel5/force0 through446100 and forwards that EAX. C++ unwind destroys the already-constructed empty-save argument if construction of the level copy throws; ownership is
// transferred before the4798E0 call. No file existence check, multiplayer teardown, world load or cache clear in this body.
int rf_ui_reload_last_requested_level()
{
  int v0; // eax
  int v2[2]; // [esp-8h] [ebp-34h] BYREF
  int v3[5]; // [esp+0h] [ebp-2Ch] BYREF
  _DWORD *v4; // [esp+14h] [ebp-18h]
  int *v5; // [esp+18h] [ebp-14h]
  void *v6; // [esp+1Ch] [ebp-10h]
  int v7; // [esp+28h] [ebp-4h]

  v6 = v3;
  v4 = rf_string_construct_from_cstr(v3, (char *)&byte_633CA7);
  v3[4] = (int)v4;
  v7 = 0;
  v5 = v2;
  rf_string_copy_construct_from_object(v2, (char **)unk_6FC31C);
  v3[3] = v0;
  v7 = -1;
  rf_level_transition_assign_level_and_save_strings(v2[0], (char *)v2[1], v3[0], (char *)v3[1]);
  return rf_ui_request_panel_immediate(5, 0);
}

