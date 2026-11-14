// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00518590 rf_nav_node_to_point_clearance_sweep
// UNREALRED VERIFIED [combat-panic-20261104]: Mandatory start clearance: zero enablegate→true, otherwise world52F8D0 sphere sweep start=nodeWORKINGpos,delta=bodyStart-nodeWORKINGpos,radius=requestRadius,flags69(0x45),zero offset,identity matrix. Accept hitcount==0. Querydirection matters for native front-plane tests; a body-to-node point ray reverses and weakens the original query.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Cdecl world/enable pointer,node,startPoint3f,radius float,UNUSED height float:5 stack DWORDs,20-byte caller cleanup. worldNULL immediately true. Otherwise builds collision request with sweep START=node.working12,delta=startPoint-node.working,radius supplied,flags69(45h);zero offset and identity matrix. Calls world collision sweep(mode1),returns hitCountDWORD0==0. Direction is node-to-point,not reverse ray;radius sweep not height capsule. Fifth height is pushed by518320/518770 but never read in body. No own result filtering,point/radius/finite validation or path mutation. Corrected old4-argument signature;earlier combat clearance note retained.
bool __cdecl rf_nav_node_to_point_clearance_sweep(
        void *world,
        void *node,
        const float *start_point,
        float radius,
        float unused_height)
{
  float *v6; // eax
  float v7[3]; // [esp+0h] [ebp-BCh] BYREF
  float out_vector[3]; // [esp+Ch] [ebp-B0h] BYREF
  float copy_result[3]; // [esp+18h] [ebp-A4h] BYREF
  _DWORD v10[10]; // [esp+24h] [ebp-98h] BYREF
  char v11[4]; // [esp+4Ch] [ebp-70h] BYREF
  float v12[3]; // [esp+50h] [ebp-6Ch] BYREF
  float v13[9]; // [esp+5Ch] [ebp-60h] BYREF
  float destination[3]; // [esp+80h] [ebp-3Ch] BYREF
  float v15[12]; // [esp+8Ch] [ebp-30h] BYREF

  if ( !world )
    return 1;
  rf_solid_collision_query_construct_clear_face_hint(v11);
  rf_vector_copy(destination, copy_result, (const float *)node + 3);
  v6 = rf_vector_subtract(start_point, out_vector, (const float *)node + 3);
  rf_vector_copy(v15, v7, v6);
  v15[3] = radius;
  LODWORD(v15[4]) = 69;
  rf_vector3_zero_return_destination(v12);
  rf_identity_orientation_matrix(v13);
  rf_solid_collision_result_construct_noop((int)v10);
  rf_world_collision_sweep((char *)world, (int)v11, (int)v10, 1);
  return v10[0] == 0;
}

