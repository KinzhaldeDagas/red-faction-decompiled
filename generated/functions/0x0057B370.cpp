// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057B370 rf_vfile_construct_registered_subdirectory_rfstring
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, parser enum/CRC contracts, output formatting, root/media path construction, VPP buffer reads and lookup lifecycle): Cdecl output RFString return storage and root id. Starts temporary empty, assigns registered-root cstring pointer1897490+12*id only when id nonzero, then copy-constructs output and destroys temporary. Root0 returns empty string; data-root prefix is not included. Returns output pointer. No id/range/NULL validation.
_DWORD *__cdecl rf_vfile_construct_registered_subdirectory_rfstring(_DWORD *a1, int a2)
{
  char *v3[2]; // [esp+8h] [ebp-14h] BYREF
  int v4; // [esp+18h] [ebp-4h]

  rf_string_construct_from_cstr(v3, (char *)&byte_641544);
  v4 = 1;
  if ( a2 )
    rf_string_assign_from_cstr(v3, (char *)dword_1897490[3 * a2]);
  rf_string_copy_construct_from_object(a1, v3);
  LOBYTE(v4) = 0;
  rf_string_destroy_buffer(v3);
  return a1;
}

