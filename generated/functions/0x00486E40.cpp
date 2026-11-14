// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00486E40 rf_waypoint_list_registry_clear_all_names
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, material/foley parse and ownership, RFString input ABI, bitmap cache, property fallback and directional sound numbering): 
// Cdecl atexit callback. Iterates EXACTLY32 storage slots, regardless runtime count0x700478; assigns empty original C string0x6392F0 to first RFString of each record
// at0x700480+i*524. Does not destroy record allocation, reset global count/byte0x70047C, clear pointcount+8 or point-index array+12, or free legacy waypoint objects. Actual RFString
// destructor callbacks elsewhere are distinct from this empty-name assignment.
void __cdecl rf_waypoint_list_registry_clear_all_names()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 32; ++i )
    rf_string_assign_from_cstr(&dword_700480[131 * i], (char *)byte_6392F0);
}

