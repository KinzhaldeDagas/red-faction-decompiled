// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00459BB0 rf_main_menu_queue_level_load
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl source C string. Establishes C++ exception frame; constructs8-byte RFString directly in outgoing stack area from635D28, then second outgoing8-byte
// RFString from supplied Source. Calls4798E0 consuming the two by-value string slots, caller removes16 bytes, then4494C0 client level entry/panel5 helper, forwards final EAX while
// restoring fs:0. First string is protected by state0 while constructing second: unwind tail623A90 destroys first through55F6D0. State disables before4798E0 call; no normal
// caller-side string destructor after that call. No source null/range/RFL existence check or admission gate on helper return. By-value RFString ABI, not four independent pointer
// arguments from pseudocode.
int __cdecl rf_main_menu_queue_level_load(char *Source)
{
  int v2[2]; // [esp-8h] [ebp-34h] BYREF
  int v3[5]; // [esp+0h] [ebp-2Ch] BYREF
  _DWORD *v4; // [esp+14h] [ebp-18h]
  int *v5; // [esp+18h] [ebp-14h]
  void *v6; // [esp+1Ch] [ebp-10h]
  int v7; // [esp+28h] [ebp-4h]

  v6 = v3;
  v4 = rf_string_construct_from_cstr(v3, (char *)&byte_635D28);
  v3[4] = (int)v4;
  v7 = 0;
  v5 = v2;
  v3[3] = (int)rf_string_construct_from_cstr(v2, Source);
  v7 = -1;
  rf_level_transition_assign_level_and_save_strings(v2[0], (char *)v2[1], v3[0], (char *)v3[1]);
  return rf_client_level_entry_initialize_and_request_panel5();
}

