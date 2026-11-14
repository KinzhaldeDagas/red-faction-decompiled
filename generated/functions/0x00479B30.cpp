// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00479B30 rf_liquid_room_depth_query
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, liquid transition lifecycle, native x87 unordered comparisons, stable pointer erase, static runtime ownership and level-browser flow): 
// Cdecl(room id,depth FLOAT*out,height FLOAT*out), normalized AL Boolean. Exact id-1 immediately fails; otherwise finds first room with DWORD36==id in world pointer vector+156.
// Missing id leaves BOTH outputs untouched. On match depth output becomes0 unless room BYTE388 is ANY nonzero, then copies FLOAT392. Height output is
// binary32(maxY24-minY12-double0.00009999999747378752). Returns1 even for disabled liquid. No world/room/output NULL guard, surface rebuild or negative-id rejection beyond exact-1.
char __cdecl rf_liquid_room_depth_query(int a1, float *a2, float *a3)
{
  int v4; // [esp+0h] [ebp-Ch]
  int i; // [esp+4h] [ebp-8h]
  int v6; // [esp+8h] [ebp-4h]

  if ( a1 == -1 )
    return 0;
  v6 = 0;
  for ( i = 0; i < rf_receiver_get_first_dword((void *)(rf_world_solid + 156)); ++i )
  {
    v4 = *(_DWORD *)sub_552200((_DWORD *)(rf_world_solid + 156), i);
    if ( *(_DWORD *)(v4 + 36) == a1 )
    {
      v6 = v4;
      break;
    }
  }
  if ( !v6 )
    return 0;
  *a2 = 0.0;
  if ( *(_BYTE *)(v6 + 388) )
    *a2 = *(float *)(v6 + 392);
  *a3 = *(float *)(v6 + 24) - *(float *)(v6 + 12) - 0.00009999999747378752;
  return 1;
}

