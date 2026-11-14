// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00459CA0 rf_main_menu_handle_multiplayer_action
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Calls490300; fullEAX0 builds46F150(title88E16C,message88E348,NULL,0), then returns helper EAX without classifying addresses or transitioning.
// Nonzero calls59B4A0 address classifier. Classifier EAX0 builds
// two-choice46F3E0(title88E2B4,message88E2B8,count2,labels[88D760,88E22C],callbacks[459DD0,459DE0],rawOption0,metadata[1,-1]). Every NONZERO classifier value, including2 and
// negatives, calls459DE0 continuation;2 merely has a separate identical branch. XOR/JNZ self-edges are impossible, not retries/spin waits. No active Internet probe/result proof
// beyond delegated classifier, callback invocation on modal path, admission-result handling, rollback or normalized result. All strings use localized globals through constant-zero
// branches.
int rf_main_menu_handle_multiplayer_action()
{
  _DWORD v1[2]; // [esp+18h] [ebp-1Ch] BYREF
  _DWORD v2[2]; // [esp+20h] [ebp-14h] BYREF
  _DWORD v3[2]; // [esp+28h] [ebp-Ch] BYREF

  if ( !rf_multiplayer_registry_update_rate_is_nonzero() )
    return rf_ui_show_ok_modal(unk_88E16C, unk_88E348, 0, 0);
  if ( rf_network_classify_local_ipv4_addresses() )
    return rf_main_menu_continue_to_multiplayer();
  v3[0] = unk_88D760;
  v3[1] = unk_88E22C;
  v1[0] = rf_main_menu_multiplayer_cancel;
  v1[1] = rf_main_menu_continue_to_multiplayer;
  v2[0] = 1;
  v2[1] = -1;
  return rf_ui_show_choice_modal(unk_88E2B4, unk_88E2B8, 2, (int)v3, (int)v1, 0, (int)v2);
}

