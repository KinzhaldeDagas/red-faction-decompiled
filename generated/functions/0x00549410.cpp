// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00549410 rf_solid_cone_from_polygon_create
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Cdecl sides,radius,height. Allocates888-byte solid,creates polygon atY0,reverses its winding,adopts it. Adds apex(0,height,0). For every base corner,creates linked triangle(current vertex,PREVIOUS ring vertex at corner+24,apex),UVs all0. Subtracts(0,height/2,0),recomputes bounds,allocates460-byte room,finalizes/projects generated UV/attaches all faces and rebuilds room tree. Returns solid. No minimum side count,finite/positive dimensions,allocation/degeneracy guard or shared-cap duplication.
_DWORD *__cdecl rf_solid_cone_from_polygon_create(int a1, float a2, float a3)
{
  float *v4; // [esp+14h] [ebp-50h]
  float v5; // [esp+18h] [ebp-4Ch]
  int v6; // [esp+1Ch] [ebp-48h]
  void **v7; // [esp+20h] [ebp-44h]
  void *room; // [esp+24h] [ebp-40h]
  void **v9; // [esp+2Ch] [ebp-38h]
  float *link; // [esp+34h] [ebp-30h]
  float v11[3]; // [esp+3Ch] [ebp-28h] BYREF
  float *j; // [esp+48h] [ebp-1Ch]
  void *solid; // [esp+4Ch] [ebp-18h]
  int i; // [esp+50h] [ebp-14h]
  int v15; // [esp+54h] [ebp-10h]
  int v16; // [esp+60h] [ebp-4h]

  v9 = (void **)operator new(0x378u);
  v16 = 0;
  if ( v9 )
    v7 = rf_solid888_construct(v9);
  else
    v7 = nullptr;
  v16 = -1;
  solid = v7;
  j = rf_geomod_regular_polygon_face_create(a1, a2, 0.0);
  rf_geomod_face_reverse_winding((int)j);
  rf_solid_face_adopt_link((int *)v7, (int)j);
  rf_vector3_set_components_return_destination(v11, 0.0, a3, 0.0);
  v15 = (int)rf_solid_vertex_copy_append(solid, v11);
  for ( i = *((_DWORD *)j + 16); i; i = v6 )
  {
    link = (float *)rf_solid_face_allocate_link(solid, (const unsigned int *)j + 10);
    rf_geomod_face_corner_append(link, *(_DWORD *)i, 0.0, 0.0, 0.0, 0.0);
    rf_geomod_face_corner_append(link, **(_DWORD **)(i + 24), 0.0, 0.0, 0.0, 0.0);
    rf_geomod_face_corner_append(link, v15, 0.0, 0.0, 0.0, 0.0);
    if ( *(_DWORD *)(i + 20) == *((_DWORD *)j + 16) )
      v6 = 0;
    else
      v6 = *(_DWORD *)(i + 20);
  }
  v5 = a3 / 2.0;
  rf_vector3_set_components_thiscall(v11, 0.0, v5, 0.0);
  rf_solid_translate_by_subtracting_offset((float *)solid, v11);
  rf_solid_finalize_bounds((float *)solid);
  room = operator new(0x1CCu);
  v16 = 1;
  if ( room )
    v4 = (float *)rf_room460_construct_register(room, solid, (const float *)solid + 18, (const float *)solid + 21);
  else
    v4 = nullptr;
  v16 = -1;
  for ( j = (float *)rf_receiver_get_first_dword((char *)solid + 112); j; j = (float *)rf_solid_face_next_link((int)j) )
  {
    rf_geomod_face_finalize_geometry((int)j, nullptr, 0);
    rf_geomod_generated_uv_project((int)j);
    rf_geomod_room_face_attach(v4, (int)j);
  }
  rf_room_face_spatial_tree_rebuild((int *)v4);
  return solid;
}

