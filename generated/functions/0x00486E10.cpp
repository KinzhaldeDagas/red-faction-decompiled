// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00486E10 rf_waypoint_list_registry_process_initialize
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, material/foley parse and ownership, RFString input ABI, bitmap cache, property fallback and directional sound numbering): 
// Cdecl noargs, separate waypoint-list subsystem adjacent to material functions. Writes DWORD count0x700478=0 and BYTE0x70047C=0, registers waypoint-list name cleanup486E40 with
// atexit, returns EAX0 regardless atexit status. Does not clear/destroy32 records at0x700480, their point counts or arrays. Existing loader486EA0 identifies0x20C-byte named
// waypoint-list records and count. Not a material-system counter reset.
int rf_waypoint_list_registry_process_initialize()
{
  unk_700478 = 0;
  unk_70047C = 0;
  atexit(rf_waypoint_list_registry_clear_all_names);
  return 0;
}

