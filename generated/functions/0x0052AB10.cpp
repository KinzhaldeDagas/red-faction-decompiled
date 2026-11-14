// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052AB10 rf_geomod_deleted_face_has_three_single_neighbor_edges
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): Cdecl solid,mode ALbool. GlobalBYTE rf_fixed_pool_heap_spill_enabled nonzero returns0 immediately. Otherwise walk solid face list112; select faces with actionTable[40*operand+5*mode+class]==1 and terrain eligibility517CC0. For each circular edge current vertexA,nextvertexB, scan B.incidence32: otherFace!=selected, terraineligible, tableAction!=1, and appears by pointer in A.incidence32. Count otherFace ENTRIES satisfying this (duplicates count); if exactly1, increment qualifying edgecount. Count selected faces with edgecount>2; after full scan return whether count!=0. No early true exit, actual edge-adjacency test on neighbor face, normal/winding check, classification/geometry
// change, or proof of watertight manifold. Mode and class indexes unchecked.
bool __cdecl rf_geomod_deleted_face_has_three_single_neighbor_edges(int a1, int a2)
{
  _DWORD *v3; // esi
  _DWORD *v4; // esi
  int *v5; // [esp+4h] [ebp-28h]
  int v6; // [esp+8h] [ebp-24h]
  int v7; // [esp+Ch] [ebp-20h]
  int v8; // [esp+10h] [ebp-1Ch]
  int v9; // [esp+14h] [ebp-18h]
  int k; // [esp+18h] [ebp-14h]
  int *j; // [esp+1Ch] [ebp-10h]
  int v12; // [esp+20h] [ebp-Ch]
  int v13; // [esp+24h] [ebp-8h]
  int i; // [esp+28h] [ebp-4h]

  if ( rf_fixed_pool_heap_spill_enabled[0] )
    return 0;
  v13 = 0;
  for ( i = rf_receiver_get_first_dword((void *)(a1 + 112)); i; i = rf_solid_face_next_link(i) )
  {
    v3 = &rf_geomod_boolean_action_table[40 * rf_geomod_face_operand_get((_DWORD *)(i + 40)) + 5 * a2];
    if ( v3[rf_geomod_face_boolean_class_get((_DWORD *)(i + 40))] == 1
      && rf_geomod_terrain_component_face_eligible((__int16 *)(i + 40)) )
    {
      v12 = 0;
      for ( j = *(int **)(i + 64); j; j = v5 )
      {
        v8 = *j;
        v7 = *(_DWORD *)j[5];
        v9 = 0;
        for ( k = 0; k < rf_receiver_get_first_dword((void *)(v7 + 32)); ++k )
        {
          v6 = *(_DWORD *)sub_552200((_DWORD *)(v7 + 32), k);
          if ( v6 != i && rf_geomod_terrain_component_face_eligible((__int16 *)(v6 + 40)) )
          {
            v4 = &rf_geomod_boolean_action_table[40 * rf_geomod_face_operand_get((_DWORD *)(v6 + 40)) + 5 * a2];
            if ( v4[rf_geomod_face_boolean_class_get((_DWORD *)(v6 + 40))] != 1 )
            {
              if ( rf_pointer_array_count_matches((_DWORD *)(v8 + 32), v6) )
                ++v9;
            }
          }
        }
        if ( v9 == 1 )
          ++v12;
        if ( j[5] == *(_DWORD *)(i + 64) )
          v5 = nullptr;
        else
          v5 = (int *)j[5];
      }
      if ( v12 > 2 )
        ++v13;
    }
  }
  return v13 != 0;
}

