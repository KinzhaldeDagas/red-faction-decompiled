// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00491840 rf_respawn_clear_all_slot_names
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, client timeout latch and registry admission, RFString-array ownership, native lag-compensation snapshot/restore asymmetry, geometry contact limits and respawn slots): 
// Cdecl no arguments,exit callback. Iterates EXACT32 respawn slots,stride68,and assigns empty original Cstring639D06 to RFString atslot0,including unused slots beyond loaded count.
// No full-record destructor,position/orientation/flag reset,count change or raw array free. Return void.
void __cdecl rf_respawn_clear_all_slot_names()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 32; ++i )
    rf_string_assign_from_cstr(&rf_respawn_points[68 * i], (char *)byte_639D06);
}

