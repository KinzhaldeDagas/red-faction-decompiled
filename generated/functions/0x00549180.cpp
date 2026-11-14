// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00549180 rf_solid_segmented_cylinder_create
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Cdecl sides,radius,height,verticalSubdivisions. Allocates888-byte solid;creates regular polygon atY0 and adopts it. Creates second face sharing its vertex pointers,all UV0,reverses winding,adopts it as stationary cap. step=height/(verticalSubdivisions+1);for j<verticalSubdivisions+1 repeatedly extrudes ORIGINAL face via51CED0 by negative current face normal*step. Each extrusion replaces moving-cap corner vertices and bridges old/new edge rings;does not clone entire solid per segment. Subtracts offset(0,height/2,0),recomputes bounds,allocates460-byte room,finalizes/projects UV/attaches all faces,rebuilds room tree,returns solid. No
// side-count/radius/height/subdivision/allocation validation;subdiv=-1 divides byzero before zero-iteration loop;negative subdivisions can suppress extrusion. Winding and extrusion direction are as implemented,not assumed from polygon handedness.
_DWORD *__cdecl rf_solid_segmented_cylinder_create(int a1, float a2, float a3, int a4)
{
  float *v4; // eax
  float scalar; // [esp+Ch] [ebp-90h]
  int *v7; // [esp+14h] [ebp-88h]
  float v8; // [esp+18h] [ebp-84h]
  int *v9; // [esp+20h] [ebp-7Ch]
  void **v10; // [esp+24h] [ebp-78h]
  void *room; // [esp+28h] [ebp-74h]
  char v12[12]; // [esp+30h] [ebp-6Ch] BYREF
  void *v13; // [esp+3Ch] [ebp-60h]
  void **v14; // [esp+40h] [ebp-5Ch]
  float scaled_result[3]; // [esp+44h] [ebp-58h] BYREF
  float *v16; // [esp+50h] [ebp-4Ch]
  float v17; // [esp+54h] [ebp-48h]
  char v18[12]; // [esp+58h] [ebp-44h] BYREF
  float *k; // [esp+64h] [ebp-38h]
  void *solid; // [esp+68h] [ebp-34h]
  int *i; // [esp+6Ch] [ebp-30h]
  int j; // [esp+70h] [ebp-2Ch]
  float *v23; // [esp+74h] [ebp-28h]
  _DWORD v24[6]; // [esp+78h] [ebp-24h] BYREF
  int v25; // [esp+98h] [ebp-4h]

  v13 = operator new(0x378u);
  v25 = 0;
  if ( v13 )
    v10 = rf_solid888_construct((void **)v13);
  else
    v10 = nullptr;
  v14 = v10;
  v25 = -1;
  solid = v10;
  k = rf_geomod_regular_polygon_face_create(a1, a2, 0.0);
  rf_solid_face_adopt_link((int *)v10, (int)k);
  rf_geomod_face_metadata_init(v24);
  v23 = (float *)rf_geomod_face_allocate(v24);
  for ( i = *((int **)k + 16); i; i = v9 )
  {
    rf_geomod_face_corner_append(v23, *i, 0.0, 0.0, 0.0, 0.0);
    if ( i[5] == *((_DWORD *)k + 16) )
      v9 = nullptr;
    else
      v9 = (int *)i[5];
  }
  rf_geomod_face_reverse_winding((int)v23);
  rf_solid_face_adopt_link((int *)solid, (int)v23);
  v17 = a3 / (double)(a4 + 1);
  for ( j = 0; j < a4 + 1; ++j )
  {
    scalar = v17;
    v4 = rf_vector_negate(k, (float *)v12);
    rf_vector_multiply_scalar(v4, scaled_result, scalar);
    rf_solid_extrude_one_face_by_vector(solid, (int)k, scaled_result);
  }
  v8 = a3 / 2.0;
  rf_vector3_set_components_return_destination((float *)v18, 0.0, v8, 0.0);
  rf_solid_translate_by_subtracting_offset((float *)solid, (float *)v18);
  rf_solid_finalize_bounds((float *)solid);
  room = operator new(0x1CCu);
  v25 = 1;
  if ( room )
    v7 = (int *)rf_room460_construct_register(room, solid, (const float *)solid + 18, (const float *)solid + 21);
  else
    v7 = nullptr;
  v25 = -1;
  v16 = (float *)v7;
  for ( k = (float *)rf_receiver_get_first_dword((char *)solid + 112); k; k = (float *)rf_solid_face_next_link((int)k) )
  {
    rf_geomod_face_finalize_geometry((int)k, nullptr, 0);
    rf_geomod_generated_uv_project((int)k);
    rf_geomod_room_face_attach(v16, (int)k);
  }
  rf_room_face_spatial_tree_rebuild((int *)v16);
  return solid;
}

