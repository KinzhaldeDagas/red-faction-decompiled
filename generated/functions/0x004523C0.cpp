// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004523C0 rf_input_find_mouse_binding_name_by_rf_string
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): Cdecl(RFStringPointer), one DWORD. Scans five DWORD pointers at6EFE80 in ascending order.
// Dereferences EACH pointer once to obtain raw CString pointer, then560960(CString,RFStringPointer); first ANY nonzero AL returns index0..4, no match full EAX=-1. Outer pointer is
// not NULL-guarded; delegate handles optional inner CString/empty RFString semantics only. Whole case-insensitive comparison, no trimming, current-button query, mutation or
// allocation. Does not read direct strings from6EFE80 or validate runtime initialization of that pointer-to-pointer table.
int __cdecl rf_input_find_mouse_binding_name_by_rf_string(int a1)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 5; ++i )
  {
    if ( rf_cstring_equals_rf_string_case_insensitive(*(char **)dword_6EFE80[i], a1) )
      return i;
  }
  return -1;
}

