// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00489820 rf_mover_publish_pending_positions
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL volume/decal layouts, cumulative corner room queries, mover list and auxiliary-node ownership, linked physics flags and native debug draw arguments): 
// Cdecl mover pointer. Only if DWORD792 has either bit0x8 or0x80000000 set: publishes mover position using its predicted vector240, then resolves each handle in arrays716 and704,
// publishing valid child predicted vector240. Publish delegate copies input to common published60,current228,predicted240 and derives bounds; wrapper performs no coordinate
// transform. Invalid handles skipped, duplicate handles not deduplicated. Finally clears BOTH trigger bits0x8 and0x80000000 from mover792 preserving others, even when some child
// handles failed. No list mutation/flag clearing on children. Without either bit no writes or publication; EAX incidental on skip and final flags on executed path.
int __cdecl rf_mover_publish_pending_positions(int a1)
{
  int result; // eax
  int *v2; // eax
  int *v3; // eax
  int v4; // [esp+0h] [ebp-Ch]
  int i; // [esp+4h] [ebp-8h]
  int j; // [esp+4h] [ebp-8h]
  int v7; // [esp+8h] [ebp-4h]

  result = a1;
  if ( (*(_DWORD *)(a1 + 792) & 0x80000008) != 0 )
  {
    rf_object_publish_position_and_bounds(a1, (float *)(a1 + 240));
    for ( i = 0; i < rf_receiver_get_first_dword((void *)(a1 + 716)); ++i )
    {
      v2 = (int *)sub_552200((_DWORD *)(a1 + 716), i);
      v7 = rf_object_resolve_handle(*v2);
      if ( v7 )
        rf_object_publish_position_and_bounds(v7, (float *)(v7 + 240));
    }
    for ( j = 0; j < rf_receiver_get_first_dword((void *)(a1 + 704)); ++j )
    {
      v3 = (int *)sub_552200((_DWORD *)(a1 + 704), j);
      v4 = rf_object_resolve_handle(*v3);
      if ( v4 )
        rf_object_publish_position_and_bounds(v4, (float *)(v4 + 240));
    }
    *(_DWORD *)(a1 + 792) &= ~8u;
    result = *(_DWORD *)(a1 + 792) & 0x7FFFFFFF;
    *(_DWORD *)(a1 + 792) = result;
  }
  return result;
}

