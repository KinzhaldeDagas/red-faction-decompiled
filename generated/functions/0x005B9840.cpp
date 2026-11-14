// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B9840 rf_mesh_get_hierarchy_node_transform
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, tagged model bounds, scene transform propagation, by-value matrix ABI, named spheres and cyclic/action dispatch): ECX mesh collection plus index,outPosition,outMatrix, RET12. If count72==0 returns byte0. Follows first mesh record76->LOD pointer140->offset4 hierarchy; validates index0..hierarchy count20-1. Copies position at node100*index+84, converts quaternion at+68 to matrix, returns1. Failed index leaves outputs untouched. No aggregate mesh selection or animated pose.
// UNREALRED VERIFIED [combat-selected-drop-resource-20261111]: Static node pose copies local position at node+84 and converts raw quaternion at+68 to a matrix. It does NOT compose parent+96. The first-mesh LOD0 hierarchy uses 100-byte records matching decoded LodPropRaw(Name68,quat4,pos3,parent). Do not substitute animated-parent composition or the held-render model-axis bridge.
char __thiscall rf_mesh_get_hierarchy_node_transform(_DWORD *this, int a2, float *destination, float *a4)
{
  float copy_result[3]; // [esp+4h] [ebp-10h] BYREF
  int v6; // [esp+10h] [ebp-4h]

  if ( !*(this + 18) )
    return 0;
  v6 = *(_DWORD *)(*(_DWORD *)(*(this + 19) + 140) + 4);
  if ( a2 < 0 || a2 >= *(_DWORD *)(v6 + 20) )
    return 0;
  rf_vector_copy(destination, copy_result, (const float *)(*(_DWORD *)(v6 + 16) + 100 * a2 + 84));
  rf_quaternion_to_matrix3_rows((float *)(*(_DWORD *)(v6 + 16) + 100 * a2 + 68), a4);
  return 1;
}

