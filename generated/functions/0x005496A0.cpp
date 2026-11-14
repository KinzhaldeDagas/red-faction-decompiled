// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005496A0 rf_solid_two_sided_polygon_create
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Cdecl sides,radius. Allocates888-byte solid,creates/adopts regular polygon atY0,clones reversed winding via solid-aware clone helper and adopts clone. Thus two coincident opposing faces,not a closed-volume prism or offset-thickness disk. Recomputes bounds,allocates460-byte room,finalizes/projects UVs/attaches all faces,rebuilds room tree,returns solid. No dimension/count/allocation validation or centering translation.
void **__cdecl rf_solid_two_sided_polygon_create(int a1, float a2)
{
  float *v3; // [esp+Ch] [ebp-34h]
  void **v4; // [esp+10h] [ebp-30h]
  void *room; // [esp+14h] [ebp-2Ch]
  void **v6; // [esp+1Ch] [ebp-24h]
  float *v7; // [esp+28h] [ebp-18h]
  int i; // [esp+28h] [ebp-18h]
  float *v9; // [esp+30h] [ebp-10h]

  v6 = (void **)operator new(0x378u);
  if ( v6 )
    v4 = rf_solid888_construct(v6);
  else
    v4 = nullptr;
  v7 = rf_geomod_regular_polygon_face_create(a1, a2, 0.0);
  rf_solid_face_adopt_link((int *)v4, (int)v7);
  v9 = rf_geomod_face_clone_reversed(v7, (int)v4);
  rf_solid_face_adopt_link((int *)v4, (int)v9);
  rf_solid_finalize_bounds((float *)v4);
  room = operator new(0x1CCu);
  if ( room )
    v3 = (float *)rf_room460_construct_register(room, v4, (const float *)v4 + 18, (const float *)v4 + 21);
  else
    v3 = nullptr;
  for ( i = rf_receiver_get_first_dword(v4 + 28); i; i = rf_solid_face_next_link(i) )
  {
    rf_geomod_face_finalize_geometry(i, nullptr, 0);
    rf_geomod_generated_uv_project(i);
    rf_geomod_room_face_attach(v3, i);
  }
  rf_room_face_spatial_tree_rebuild((int *)v3);
  return v4;
}

