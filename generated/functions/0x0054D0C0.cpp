// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054D0C0 rf_solid_mark_tree_lightmaps_near_point
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Cdecl point3f,margin,solid,node;4 stack DWORDs. NULL node performs no marking. Builds expanded node bounds from min0..8,max12..20;inclusive point test gates entire subtree. If inside,traverses node face list at24 through spatial-node iterator,calling54CFF0,then child pointer32,then child36 when nonNULL. No early hit short-circuit,coordinate transform,node/descriptor flag clearing or lighting/upload. Negative margin shrinks bounds without sorting;no cycle/pointer validation. Return previously inferred int* is incidental low-byte/register residue,not node pointer/status;known direct callers ignore it. Corrected to effects-only void,pointer arguments;caller-pop16-byte
// ABI unchanged.
void __cdecl rf_solid_mark_tree_lightmaps_near_point(const float *query_point, float margin, void *solid, void *node)
{
  float *v4; // eax
  float *v5; // eax
  float v6[3]; // [esp+Ch] [ebp-58h] BYREF
  int v7[3]; // [esp+18h] [ebp-4Ch] BYREF
  float copy_result[3]; // [esp+24h] [ebp-40h] BYREF
  int v9[3]; // [esp+30h] [ebp-34h] BYREF
  void *face; // [esp+3Ch] [ebp-28h]
  float v11[3]; // [esp+40h] [ebp-24h] BYREF
  float destination[3]; // [esp+4Ch] [ebp-18h] BYREF
  char v13[12]; // [esp+58h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(destination);
  rf_vector3_default_construct_noop(v11);
  rf_vector3_default_construct_noop(v13);
  if ( node )
  {
    v4 = rf_vector3_subtract_scalar_from_components((float *)node, (float *)v9, margin);
    rf_vector_copy(destination, copy_result, v4);
    v5 = rf_vector3_add_scalar_to_components((float *)node + 3, (float *)v7, margin);
    rf_vector_copy(v11, v6, v5);
    if ( rf_aabb_contains_point_inclusive((float *)query_point, destination, v11) )
    {
      for ( face = (void *)rf_receiver_get_first_dword((char *)node + 24);
            face;
            face = (void *)rf_face_next_spatial_node_link((int)face) )
      {
        rf_solid_mark_face_lightmap_near_point(query_point, margin, solid, face);
      }
      if ( *((_DWORD *)node + 8) )
        rf_solid_mark_tree_lightmaps_near_point(query_point, margin, solid, *((void **)node + 8));
      if ( *((_DWORD *)node + 9) )
        rf_solid_mark_tree_lightmaps_near_point(query_point, margin, solid, *((void **)node + 9));
    }
  }
}

