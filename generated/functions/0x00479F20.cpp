// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00479F20 rf_level_has_liquid_room
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, liquid transition lifecycle, native x87 unordered comparisons, stable pointer erase, static runtime ownership and level-browser flow): 
// Cdecl no arguments, normalized AL Boolean. Scans world room-pointer vector+156 and returns1 for first room whose BYTE388 equals EXACT1; other nonzero values do not qualify.
// Returns0 at end. No world NULL guard, liquid depth/height comparison or point-containment test.
char rf_level_has_liquid_room()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword((void *)(rf_world_solid + 156)); ++i )
  {
    if ( *(_BYTE *)(*(_DWORD *)sub_552200((_DWORD *)(rf_world_solid + 156), i) + 388) == 1 )
      return 1;
  }
  return 0;
}

