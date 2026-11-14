// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00453D30 rf_extras_menu_request_glass_house_level
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): No arguments. Construct empty save RFString from PE NUL635263 directly on8-byte stack slot, then
// level RFString"glass_house.rfl" on another8-byte slot. Call4798E0 with TWO by-value RFStrings (level first/save second), caller cleans16. That helper copies level/save
// to6FC300/6FC2F8 and destroys both argument objects. Then4494C0 performs initialization notice/cache and unforced panel5 request; EAX forwards through normal SEH epilogue. No own
// load, save validation, Cstring borrowing lifetime, pending override or rollback. Two native chunks include empty-save unwind thunk623A10 and C++/cookie handler; no containing
// RFString object allocation is freed here.
int rf_extras_menu_request_glass_house_level()
{
  int v1[2]; // [esp-8h] [ebp-34h] BYREF
  int v2[5]; // [esp+0h] [ebp-2Ch] BYREF
  _DWORD *v3; // [esp+14h] [ebp-18h]
  int *v4; // [esp+18h] [ebp-14h]
  void *v5; // [esp+1Ch] [ebp-10h]
  int v6; // [esp+28h] [ebp-4h]

  v5 = v2;
  v3 = rf_string_construct_from_cstr(v2, (char *)&byte_635263);
  v2[4] = (int)v3;
  v6 = 0;
  v4 = v1;
  v2[3] = (int)rf_string_construct_from_cstr(v1, "glass_house.rfl");
  v6 = -1;
  rf_level_transition_assign_level_and_save_strings(v1[0], (char *)v1[1], v2[0], (char *)v2[1]);
  return rf_client_level_entry_initialize_and_request_panel5();
}

