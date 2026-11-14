// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045DA50 rf_multiplayer_setup_copy_enabled_password
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Cdecl output RFString construction storage pointer,return same pointer. Any NONZERO checkedBYTE6F2EB8 ->construct
// from edit Cstring6F3718;zero ->construct empty original PE636243. Does not write registry,clear stored password,normalize checked flag,validate strength/server admission or send
// credentials. Existing output is not assigned/destroyed here. No output-pointer or source-length guard.
_DWORD *__cdecl rf_multiplayer_setup_copy_enabled_password(_DWORD *a1)
{
  if ( byte_6F2EB8[0] )
    rf_string_construct_from_cstr(a1, (char *)byte_6F3718);
  else
    rf_string_construct_from_cstr(a1, (char *)&byte_636243);
  return a1;
}

