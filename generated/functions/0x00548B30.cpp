// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00548B30 rf_solid_triangular_prism_wedge_create
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Cdecl(heightY,widthX,depthZ) floats. Allocates888-byte solid;creates6 vertices A(0,0,0),B(width,0,0),C(0,height,0),D(0,0,depth),E(width,height,0),F(0,height,depth). Linked faces in exact order:quad A-B-E-C,quad A-C-F-D,quad B-D-F-E,triangle A-D-B,triangle C-E-F;all initial4 UV floats/corner0. Then subtracts offset(height/2,width/2,depth/2) via51C4E0: X/Y halves are SWAPPED relative to vertex coordinates,not corrected to(width/2,height/2). Recomputes bounds,allocates460-byte room,finalizes/projects generated UVs/attaches each face,rebuilds room tree,returns solid. No dimension positivity/finite/degeneracy or allocation success guard. Exact five-face topology,not an
// eight-vertex rectangular box.
_DWORD *__cdecl rf_solid_triangular_prism_wedge_create(float a1, float a2, float a3)
{
  float *v4; // [esp+14h] [ebp-78h]
  float v5; // [esp+18h] [ebp-74h]
  float v6; // [esp+1Ch] [ebp-70h]
  float v7; // [esp+20h] [ebp-6Ch]
  void **v8; // [esp+24h] [ebp-68h]
  void *room; // [esp+28h] [ebp-64h]
  void **v10; // [esp+30h] [ebp-5Ch]
  float v11[3]; // [esp+3Ch] [ebp-50h] BYREF
  float *link; // [esp+48h] [ebp-44h]
  void *solid; // [esp+4Ch] [ebp-40h]
  int v14; // [esp+50h] [ebp-3Ch]
  int v15; // [esp+54h] [ebp-38h]
  int v16; // [esp+58h] [ebp-34h]
  int v17; // [esp+5Ch] [ebp-30h]
  int v18; // [esp+60h] [ebp-2Ch]
  int v19; // [esp+64h] [ebp-28h]
  unsigned int metadata[6]; // [esp+68h] [ebp-24h] BYREF
  int v21; // [esp+88h] [ebp-4h]

  v10 = (void **)operator new(0x378u);
  v21 = 0;
  if ( v10 )
    v8 = rf_solid888_construct(v10);
  else
    v8 = nullptr;
  v21 = -1;
  solid = v8;
  rf_vector3_default_construct_noop(v11);
  rf_vector3_set_components_thiscall(v11, 0.0, 0.0, 0.0);
  v14 = (int)rf_solid_vertex_copy_append(solid, v11);
  rf_vector3_set_components_thiscall(v11, a2, 0.0, 0.0);
  v15 = (int)rf_solid_vertex_copy_append(solid, v11);
  rf_vector3_set_components_thiscall(v11, 0.0, a1, 0.0);
  v16 = (int)rf_solid_vertex_copy_append(solid, v11);
  rf_vector3_set_components_thiscall(v11, 0.0, 0.0, a3);
  v17 = (int)rf_solid_vertex_copy_append(solid, v11);
  rf_vector3_set_components_thiscall(v11, a2, a1, 0.0);
  v18 = (int)rf_solid_vertex_copy_append(solid, v11);
  rf_vector3_set_components_thiscall(v11, 0.0, a1, a3);
  v19 = (int)rf_solid_vertex_copy_append(solid, v11);
  rf_geomod_face_metadata_init(metadata);
  link = (float *)rf_solid_face_allocate_link(solid, metadata);
  rf_geomod_face_corner_append(link, v14, 0.0, 0.0, 0.0, 0.0);
  rf_geomod_face_corner_append(link, v15, 0.0, 0.0, 0.0, 0.0);
  rf_geomod_face_corner_append(link, v18, 0.0, 0.0, 0.0, 0.0);
  rf_geomod_face_corner_append(link, v16, 0.0, 0.0, 0.0, 0.0);
  link = (float *)rf_solid_face_allocate_link(solid, metadata);
  rf_geomod_face_corner_append(link, v14, 0.0, 0.0, 0.0, 0.0);
  rf_geomod_face_corner_append(link, v16, 0.0, 0.0, 0.0, 0.0);
  rf_geomod_face_corner_append(link, v19, 0.0, 0.0, 0.0, 0.0);
  rf_geomod_face_corner_append(link, v17, 0.0, 0.0, 0.0, 0.0);
  link = (float *)rf_solid_face_allocate_link(solid, metadata);
  rf_geomod_face_corner_append(link, v15, 0.0, 0.0, 0.0, 0.0);
  rf_geomod_face_corner_append(link, v17, 0.0, 0.0, 0.0, 0.0);
  rf_geomod_face_corner_append(link, v19, 0.0, 0.0, 0.0, 0.0);
  rf_geomod_face_corner_append(link, v18, 0.0, 0.0, 0.0, 0.0);
  link = (float *)rf_solid_face_allocate_link(solid, metadata);
  rf_geomod_face_corner_append(link, v14, 0.0, 0.0, 0.0, 0.0);
  rf_geomod_face_corner_append(link, v17, 0.0, 0.0, 0.0, 0.0);
  rf_geomod_face_corner_append(link, v15, 0.0, 0.0, 0.0, 0.0);
  link = (float *)rf_solid_face_allocate_link(solid, metadata);
  rf_geomod_face_corner_append(link, v16, 0.0, 0.0, 0.0, 0.0);
  rf_geomod_face_corner_append(link, v18, 0.0, 0.0, 0.0, 0.0);
  rf_geomod_face_corner_append(link, v19, 0.0, 0.0, 0.0, 0.0);
  v7 = a3 / 2.0;
  v6 = a2 / 2.0;
  v5 = a1 / 2.0;
  rf_vector3_set_components_thiscall(v11, v5, v6, v7);
  rf_solid_translate_by_subtracting_offset((float *)solid, v11);
  rf_solid_finalize_bounds((float *)solid);
  room = operator new(0x1CCu);
  v21 = 1;
  if ( room )
    v4 = (float *)rf_room460_construct_register(room, solid, (const float *)solid + 18, (const float *)solid + 21);
  else
    v4 = nullptr;
  v21 = -1;
  for ( link = (float *)rf_receiver_get_first_dword((char *)solid + 112);
        link;
        link = (float *)rf_solid_face_next_link((int)link) )
  {
    rf_geomod_face_finalize_geometry((int)link, nullptr, 0);
    rf_geomod_generated_uv_project((int)link);
    rf_geomod_room_face_attach(v4, (int)link);
  }
  rf_room_face_spatial_tree_rebuild((int *)v4);
  return solid;
}

