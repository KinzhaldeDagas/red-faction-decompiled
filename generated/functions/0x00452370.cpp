// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00452370 rf_input_find_scan_code_by_rf_string
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): Cdecl(RFStringPointer), one DWORD. Scans exactly256 pointer slots6619A8 in ascending index0..255,
// calls560960(raw CString slot,RFStringPointer), and returns first index for ANY nonzero AL; no match returns full EAX=-1. Comparison is whole case-insensitive CString/RFString with
// no whitespace trimming. NULL/empty CString matches only RFString extent0, so empty lookup may match an unnamed/null slot. No RFString-pointer validation, key availability filter,
// table mutation, allocation or input-state query.
int __cdecl rf_input_find_scan_code_by_rf_string(int a1)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 256; ++i )
  {
    if ( rf_cstring_equals_rf_string_case_insensitive((&off_6619A8)[i], a1) )
      return i;
  }
  return -1;
}

