// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004069D0 rf_ai_mode5_select_unmarked_clutter
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): One required AI block, mode5 secondary4 subhandler. Deadline+1164 elapsed EXACT1 rearms400ms BEFORE resolving
// current COMMON target+704; any valid target skips scan after consuming/rearming timer. Missing target ->clutter list next+652 to666D18, selects FIRST entry with common flags+124
// mask0x1000 set and0x2000 clear. Distance COMMON positions roundsfloat32; TEST AH,41/JNZ admits ordered distance<=DOUBLE40 OR UNORDERED. Geometry(clutter+60,owner+60,mask3,NULL)
// must returnAL0; no nearest ranking, own death/inactive/health/room filtering. Chosen handle!=-1 ->guarded setter40BA80(block,handle), ignoring acceptance; write secondary5,
// RE-resolve chosen COMMON handle and if valid OR its common mask0x2000. Thus state/reservation effects proceed even if target setter rejected. No rollback/other reservations cleared
// or authority test.
void __cdecl rf_ai_mode5_select_unmarked_clutter(int *a1)
{
  int v1; // [esp+0h] [ebp-14h]
  int v2; // [esp+4h] [ebp-10h]
  float v3; // [esp+8h] [ebp-Ch]
  int i; // [esp+10h] [ebp-4h]

  if ( rf_replicator_has_elapsed(a1 + 291) )
  {
    rf_replicator_arm_milliseconds(a1 + 291, 400);
    if ( !rf_object_resolve_handle(a1[176]) )
    {
      v2 = -1;
      for ( i = rf_clutter_list_head; (_UNKNOWN *)i != &unk_666D18; i = *(_DWORD *)(i + 652) )
      {
        if ( (*(_DWORD *)(i + 124) & 0x1000) != 0 && (*(_DWORD *)(i + 124) & 0x2000) == 0 )
        {
          v3 = rf_vector_distance((const float *)(i + 60), (const float *)(*a1 + 60));
          if ( v3 <= 40.0 && !rf_geometry_segment_is_obstructed(i + 60, *a1 + 60, 3, 0) )
          {
            v2 = *(_DWORD *)(i + 44);
            break;
          }
        }
      }
      if ( v2 != -1 )
      {
        sub_40BA80(a1, v2);
        rf_ai_secondary_state_write((int)a1, 5);
        v1 = rf_object_resolve_handle(v2);
        if ( v1 )
          *(_DWORD *)(v1 + 124) |= 0x2000u;
      }
    }
  }
}

