// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048F740 rf_multiplayer_clear_string_704EC0
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, multiplayer session dispatch and deadlines, reliable-peer timeout and acceptance, rename payload ordering, disabled native drawing and wrapped network-id allocation): 
// Cdecl no arguments. Assigns empty Cstring at6393A2 (original byte00) to global RFString704EC0,returns assignment result. No network packet,player-list operation or session-flag
// update. Exact user-visible role of this string is not assigned solely from adjacent functions.
_DWORD *rf_multiplayer_clear_string_704EC0()
{
  return rf_string_assign_from_cstr(unk_704EC0, (char *)&byte_6393A2);
}

