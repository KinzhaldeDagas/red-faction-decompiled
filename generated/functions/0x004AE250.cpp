// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AE250 rf_console_request_split_match_test_level
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, packet14/27 registry bindings, rate-width/clamp policy, native string ABI and pregame17/18 wire layout): Noarg
// console callback. Only argument-present1809818 nonzero: construct two owned8-byte RFStrings, second from verified empty NUL63B454 and first exact mk_circuits3.rfl; pass their16
// bytes byvalue to level_transition_assign_level_and_save_strings (callee owns strings), caller ADD ESP16. Then invoke4AE4F0 pending split/panel5 helper. No argument parsing,
// mode/authority gate, file-existence or panel-admission check. SEH cleans temporary string on construction failure; level assignment precedes panel request and is not rolled back if
// request refused.
void rf_console_request_split_match_test_level()
{
  int v0[2]; // [esp-10h] [ebp-34h] BYREF
  int v1[5]; // [esp-8h] [ebp-2Ch] BYREF
  _DWORD *v2; // [esp+Ch] [ebp-18h]
  int *v3; // [esp+10h] [ebp-14h]
  void *v4; // [esp+14h] [ebp-10h]
  int v5; // [esp+20h] [ebp-4h]

  if ( dword_1809818 )
  {
    v4 = v1;
    v2 = rf_string_construct_from_cstr(v1, (char *)&byte_63B454);
    v1[4] = (int)v2;
    v5 = 0;
    v3 = v0;
    v1[3] = (int)rf_string_construct_from_cstr(v0, "mk_circuits3.rfl");
    v5 = -1;
    rf_level_transition_assign_level_and_save_strings(v0[0], (char *)v0[1], v1[0], (char *)v1[1]);
    rf_splitscreen_set_pending_and_request_panel5();
  }
}

