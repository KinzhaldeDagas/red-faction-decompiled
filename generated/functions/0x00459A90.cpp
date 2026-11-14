// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00459A90 rf_main_menu_show_new_game_dialog
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Builds three local arrays: labels from localized88D760,88E174,88E178; callbacks[NULL,459C30,459B80]; metadata DWORDs[1,31,34]. Constant-zero
// branches always take localized globals, not embedded English strings. Calls46F3E0(title88D4E0,message88E130,count3,labels,callbacks,rawOption2,metadata), cleanup28, forwards EAX.
// No callback invocation, multiplayer teardown, music stop or close transition on reachable path. Native JMP459B5F->459B77 skips trailing459B61 teardown/stop/clear/close sequence
// entirely; preserve as unreachable body, not a modal-cancel handler.
int rf_main_menu_show_new_game_dialog()
{
  _DWORD v1[3]; // [esp+14h] [ebp-24h] BYREF
  _DWORD v2[3]; // [esp+20h] [ebp-18h] BYREF
  _DWORD v3[3]; // [esp+2Ch] [ebp-Ch] BYREF

  v3[0] = unk_88D760;
  v3[1] = unk_88E174;
  v3[2] = unk_88E178;
  v1[0] = 0;
  v1[1] = rf_main_menu_start_campaign;
  v1[2] = rf_main_menu_start_training;
  v2[0] = 1;
  v2[1] = 31;
  v2[2] = 34;
  return rf_ui_show_choice_modal(unk_88D4E0, unk_88E130, 3, (int)v3, (int)v1, 2, (int)v2);
}

