// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054A7B0 rf_world_packet_build_bvh_node
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, complete world packet pass, room packet builder, BSP collection, draw order, buffer limits and original PE bytes): Cdecl(room,packetContext,cursorPointer,depth,sourceBSPnode,outputNodePointer). Publishes current cursor as node pointer,advances44,rejects cursor>=arenaEnd1482000 with-1. Initializes stamp0,child28/32,NULL face list40/count36;copies source AABB0/12 into node4/16. If depth<global663F30 and source has children32/36,recurses on both,then collects only current source faces/detail parts with54A5A0(recurse0);otherwise collects subtree(recurse1). Second packetContext threaded recursively but not otherwise read here. Clears global collect count before collection,sorts via54A4C0 WITHOUT dedup,copies WORD indices after44-byte node and stores count/pointer. Returns0 success,-1 allocation/child failure. Cursor/output
// pointers remain advanced/published on failure;no rollback,tree cycle or capacity for collector beyond its5000 cap.
int __cdecl rf_world_packet_build_bvh_node(void *a1, int a2, _DWORD *a3, int a4, float *source, int a6)
{
  float v7[3]; // [esp+0h] [ebp-18h] BYREF
  float copy_result[3]; // [esp+Ch] [ebp-Ch] BYREF

  *(_DWORD *)a6 = *a3;
  *a3 += 44;
  if ( *a3 >= unk_1482000 )
    return -1;
  **(_DWORD **)a6 = 0;
  *(_DWORD *)(*(_DWORD *)a6 + 36) = 0;
  *(_DWORD *)(*(_DWORD *)a6 + 40) = 0;
  *(_DWORD *)(*(_DWORD *)a6 + 28) = 0;
  *(_DWORD *)(*(_DWORD *)a6 + 32) = 0;
  rf_vector_copy((float *)(*(_DWORD *)a6 + 4), copy_result, source);
  rf_vector_copy((float *)(*(_DWORD *)a6 + 16), v7, source + 3);
  if ( a4 < (int)flt_663F30 && (*((_DWORD *)source + 8) || *((_DWORD *)source + 9)) )
  {
    if ( *((_DWORD *)source + 8)
      && rf_world_packet_build_bvh_node((int)a1, a2, a3, a4 + 1, *((_DWORD *)source + 8), *(_DWORD *)a6 + 28) )
    {
      return -1;
    }
    if ( *((_DWORD *)source + 9)
      && rf_world_packet_build_bvh_node((int)a1, a2, a3, a4 + 1, *((_DWORD *)source + 9), *(_DWORD *)a6 + 32) )
    {
      return -1;
    }
    dword_143E97C = 0;
    rf_world_packet_collect_bsp_face_indices(a1, source, 0, 1);
    rf_world_packet_sort_collected_face_indices();
    if ( !dword_143E97C )
      return 0;
    *(_DWORD *)(*(_DWORD *)a6 + 36) = dword_143E97C;
    *(_DWORD *)(*(_DWORD *)a6 + 40) = *a3;
    *a3 += 2 * dword_143E97C;
    if ( *a3 >= unk_1482000 )
      return -1;
  }
  else
  {
    dword_143E97C = 0;
    rf_world_packet_collect_bsp_face_indices(a1, source, 1u, 1);
    rf_world_packet_sort_collected_face_indices();
    *(_DWORD *)(*(_DWORD *)a6 + 36) = dword_143E97C;
    *(_DWORD *)(*(_DWORD *)a6 + 40) = *a3;
    *a3 += 2 * dword_143E97C;
    if ( *a3 >= unk_1482000 )
      return -1;
  }
  memcpy(*(void **)(*(_DWORD *)a6 + 40), unk_1482008, 2 * dword_143E97C);
  return 0;
}

