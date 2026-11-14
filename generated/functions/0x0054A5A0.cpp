// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054A5A0 rf_world_packet_collect_bsp_face_indices
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, complete world packet pass, room packet builder, BSP collection, draw order, buffer limits and original PE bytes): Cdecl(room,sourceBSPnode,recurseByte,unusedDWORD). Saved variadic label incorrect:no varargs walk,fourth pushed argument never read. If recurse nonzero,visits child pointers32/36 first recursively with(1,0). Appends nonnegative face WORD IDs+80 from node face list+24 to global list1482008,count143E97C;stops at5000. Then scans pending detail-part pointers145DD80[0..143E978):includes each if source node is room root+60 OR its AABB inclusively encloses part AABB offsets8..28. Sets included pending pointerNULL so first qualifying traversal owns it;appends all nonnegative detail face IDs. No dedup,sort or room bounds mutation;fourth arg ignored in recursive and external calls.
void __cdecl rf_world_packet_collect_bsp_face_indices(void *a1, void *a2, unsigned __int8 a3, int a4)
{
  float *v4; // [esp+0h] [ebp-Ch]
  int j; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]
  int k; // [esp+8h] [ebp-4h]

  if ( a3 )
  {
    if ( *((_DWORD *)a2 + 8) )
      rf_world_packet_collect_bsp_face_indices(a1, *((void **)a2 + 8), 1u, 0);
    if ( *((_DWORD *)a2 + 9) )
      rf_world_packet_collect_bsp_face_indices(a1, *((void **)a2 + 9), 1u, 0);
  }
  for ( i = rf_receiver_get_first_dword((char *)a2 + 24); i; i = rf_face_next_spatial_node_link(i) )
  {
    if ( dword_143E97C >= 5000 )
      return;
    if ( *(__int16 *)(i + 80) >= 0 )
      unk_1482008[dword_143E97C++] = *(_WORD *)(i + 80);
  }
  for ( j = 0; j < unk_143E978; ++j )
  {
    v4 = (float *)unk_145DD80[j];
    if ( v4
      && (a2 == *((void **)a1 + 15)
       || *(float *)a2 <= (double)v4[2]
       && *((float *)a2 + 1) <= (double)v4[3]
       && *((float *)a2 + 2) <= (double)v4[4]
       && *((float *)a2 + 3) >= (double)v4[5]
       && *((float *)a2 + 4) >= (double)v4[6]
       && *((float *)a2 + 5) >= (double)v4[7]) )
    {
      unk_145DD80[j] = 0;
      for ( k = rf_receiver_get_first_dword(v4 + 10); k; k = rf_face_next_room_link(k) )
      {
        if ( dword_143E97C >= 5000 )
          return;
        if ( *(__int16 *)(k + 80) >= 0 )
          unk_1482008[dword_143E97C++] = *(_WORD *)(k + 80);
      }
    }
  }
}

