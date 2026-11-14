// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052EF90 rf_collision_spatial_tree_sweep_faces
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, collision cache/traversal,strict AABBs,face/corner ownership,signed area and reset-on-read pool peaks,original ECX/stack flow and PE bytes): Three stack arguments root,query,result; RET12. Saved ECX has no semantic use. NULL root skips traversal; nominal AL return can be local-constructor/pointer residue, not a reliable hit boolean. Compute internal segment end=query84+query96. Fixed1024-DWORD local node stack, no capacity check. Pop root, increment diagnosticD55560; expand node bounds0/12 by query radius76, test finite internal segment against expanded AABB. On overlap process node face-list24 in order through52F1B0(face,query,result). Only when a face test returns true AND query flags80&1 return AL1 immediately. Then push child32 followed by36 (36 visited first), so current-node faces precede children. No
// nearest-node sorting, child-specific AABB test before push, dedup, null-child traversal or stack overflow protection. Other exits return incidental AL; result/query fields hold the actual accumulated hits.
char __stdcall rf_collision_spatial_tree_sweep_faces(void *a1, int a2, int a3)
{
  int v3; // eax
  float *v4; // eax
  float *v5; // eax
  float v7[3]; // [esp+8h] [ebp-106Ch] BYREF
  int v8[3]; // [esp+14h] [ebp-1060h] BYREF
  float copy_result[3]; // [esp+20h] [ebp-1054h] BYREF
  int v10[3]; // [esp+2Ch] [ebp-1048h] BYREF
  int i; // [esp+38h] [ebp-103Ch]
  float *v12; // [esp+3Ch] [ebp-1038h]
  float sum_result[3]; // [esp+40h] [ebp-1034h] BYREF
  float v14[3]; // [esp+4Ch] [ebp-1028h] BYREF
  int v15; // [esp+58h] [ebp-101Ch]
  _DWORD v16[1024]; // [esp+5Ch] [ebp-1018h]
  float destination[3]; // [esp+105Ch] [ebp-18h] BYREF
  float v18[3]; // [esp+1068h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(destination);
  rf_vector3_default_construct_noop(v14);
  LOBYTE(v3) = (unsigned __int8)rf_vector3_default_construct_noop(v18);
  v15 = 0;
  if ( a1 )
  {
    rf_vector_add((const float *)(a2 + 84), sum_result, (const float *)(a2 + 96));
    LOBYTE(v3) = (_BYTE)a1;
    v16[v15++] = a1;
    while ( v15 > 0 )
    {
      v12 = (float *)v16[--v15];
      ++unk_D55560;
      v4 = rf_vector3_subtract_scalar_from_components(v12, (float *)v10, *(float *)(a2 + 76));
      rf_vector_copy(destination, copy_result, v4);
      v5 = rf_vector3_add_scalar_to_components(v12 + 3, (float *)v8, *(float *)(a2 + 76));
      rf_vector_copy(v14, v7, v5);
      LOBYTE(v3) = rf_segment_intersects_aabb(destination, v14, (float *)(a2 + 84), sum_result, v18);
      if ( (_BYTE)v3 )
      {
        for ( i = rf_receiver_get_first_dword(v12 + 6); i; i = rf_face_next_spatial_node_link(i) )
        {
          if ( rf_collision_sweep_face_test(i, a2, a3) )
          {
            v3 = *(_DWORD *)(a2 + 80) & 1;
            if ( v3 )
              return v3;
          }
        }
        if ( *((_DWORD *)v12 + 8) )
          v16[v15++] = *((_DWORD *)v12 + 8);
        LOBYTE(v3) = (_BYTE)v12;
        if ( *((_DWORD *)v12 + 9) )
        {
          v3 = *((_DWORD *)v12 + 9);
          v16[v15++] = v3;
        }
      }
    }
  }
  return v3;
}

