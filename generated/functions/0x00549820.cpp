// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00549820 rf_solid_latitude_ring_sphere_create
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Cdecl signed longitude sides,radius,signed ringCount. Allocates888-byte solid and pole vertices(0,2*radius,0),(0,0,0). For i=1..ringCount computes float theta=float2pi/(2*ringCount+2)*i+float3pi/2 using literals6.283185482025146/4.71238899230957;Y=sin(theta)*radius+radius,ringRadius=sqrt(radius^2-(radius-Y)^2). Creates/adopts standalone polygon rings and stores pointers in dynamic array. Adjacent rings are connected by quads(current lower,next lower,next upper,current upper) advancing NEXT corner+20 in each ring. First ring fans triangles(current,PREVIOUS corner+24,bottom pole);last ring fans(current,NEXT corner+20,top pole). Removes/destroys temporary polygon faces
// with flag0,retaining reused vertices for side faces. Subtracts(0,radius,0),recomputes bounds,creates460-byte room,finalizes/projects UVs/attaches final faces,rebuilds room tree,destroys ring-pointer array,returns solid. No sqrt-domain clamp,ring/side-count/overflow/allocation validation. ringCount<=0 still dereferences unchecked ring indices0 andcount-1 after empty construction;not a supported empty result.
_DWORD *__cdecl rf_solid_latitude_ring_sphere_create(int a1, float a2, int a3)
{
  int first_dword; // eax
  int v4; // eax
  int v5; // eax
  float *v7; // [esp+14h] [ebp-C0h]
  int v8; // [esp+18h] [ebp-BCh]
  int v9; // [esp+1Ch] [ebp-B8h]
  int v10; // [esp+20h] [ebp-B4h]
  int v11; // [esp+24h] [ebp-B0h]
  float v12; // [esp+28h] [ebp-ACh]
  float v13; // [esp+30h] [ebp-A4h]
  void **v14; // [esp+34h] [ebp-A0h]
  void *v15; // [esp+38h] [ebp-9Ch]
  void *room; // [esp+3Ch] [ebp-98h]
  void **v17; // [esp+44h] [ebp-90h]
  float *v18; // [esp+4Ch] [ebp-88h]
  float *v19; // [esp+50h] [ebp-84h]
  float *link; // [esp+54h] [ebp-80h]
  int j; // [esp+58h] [ebp-7Ch]
  int v22; // [esp+5Ch] [ebp-78h]
  float v23; // [esp+60h] [ebp-74h]
  float v24; // [esp+64h] [ebp-70h]
  float v25; // [esp+68h] [ebp-6Ch]
  float *v26; // [esp+6Ch] [ebp-68h]
  float v27; // [esp+70h] [ebp-64h]
  float v28[3]; // [esp+78h] [ebp-5Ch] BYREF
  void *v29[3]; // [esp+84h] [ebp-50h] BYREF
  int v30; // [esp+90h] [ebp-44h]
  int v31; // [esp+94h] [ebp-40h]
  _DWORD *m; // [esp+98h] [ebp-3Ch]
  void *solid; // [esp+9Ch] [ebp-38h]
  int k; // [esp+A0h] [ebp-34h]
  int i; // [esp+A4h] [ebp-30h]
  int v36; // [esp+A8h] [ebp-2Ch]
  unsigned int metadata[6]; // [esp+ACh] [ebp-28h] BYREF
  int v38; // [esp+C4h] [ebp-10h]
  int v39; // [esp+D0h] [ebp-4h]

  v17 = (void **)operator new(0x378u);
  v39 = 0;
  if ( v17 )
    v14 = rf_solid888_construct(v17);
  else
    v14 = nullptr;
  v39 = -1;
  solid = v14;
  v13 = a2 + a2;
  rf_vector3_set_components_return_destination(v28, 0.0, v13, 0.0);
  v36 = (int)rf_solid_vertex_copy_append(solid, v28);
  rf_vector3_set_components_thiscall(v28, 0.0, 0.0, 0.0);
  v30 = (int)rf_solid_vertex_copy_append(solid, v28);
  rf_dword_array_construct_capacity(v29, 0);
  v39 = 1;
  rf_geomod_face_metadata_init(metadata);
  for ( i = 1; i <= a3; ++i )
  {
    v23 = 6.283185482025146 / (double)(2 * a3 + 2) * (double)i + 4.71238899230957;
    v27 = rf_sin_float(v23) * a2 + a2;
    v24 = a2 - v27;
    v12 = a2 * a2 - v24 * v24;
    v25 = rf_sqrt_float(v12);
    v26 = rf_geomod_regular_polygon_face_create(a1, v25, v27);
    rf_solid_face_adopt_link((int *)solid, (int)v26);
    rf_pointer_array_append_dword(v29, (int)v26);
  }
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword(v29);
    if ( i >= first_dword - 1 )
      break;
    v31 = *(_DWORD *)sub_552200(v29, i);
    v38 = *(_DWORD *)sub_552200(v29, i + 1);
    v22 = *(_DWORD *)(v38 + 64);
    for ( j = *(_DWORD *)(v31 + 64); j; j = v11 )
    {
      link = (float *)rf_solid_face_allocate_link(solid, metadata);
      rf_geomod_face_corner_append(link, *(_DWORD *)j, 0.0, 0.0, 0.0, 0.0);
      rf_geomod_face_corner_append(link, **(_DWORD **)(j + 20), 0.0, 0.0, 0.0, 0.0);
      rf_geomod_face_corner_append(link, **(_DWORD **)(v22 + 20), 0.0, 0.0, 0.0, 0.0);
      rf_geomod_face_corner_append(link, *(_DWORD *)v22, 0.0, 0.0, 0.0, 0.0);
      if ( *(_DWORD *)(v22 + 20) == *(_DWORD *)(v38 + 64) )
        v10 = 0;
      else
        v10 = *(_DWORD *)(v22 + 20);
      v22 = v10;
      if ( *(_DWORD *)(j + 20) == *(_DWORD *)(v31 + 64) )
        v11 = 0;
      else
        v11 = *(_DWORD *)(j + 20);
    }
  }
  v31 = *(_DWORD *)sub_552200(v29, 0);
  for ( k = *(_DWORD *)(v31 + 64); k; k = v9 )
  {
    v19 = (float *)rf_solid_face_allocate_link(solid, metadata);
    rf_geomod_face_corner_append(v19, *(_DWORD *)k, 0.0, 0.0, 0.0, 0.0);
    rf_geomod_face_corner_append(v19, **(_DWORD **)(k + 24), 0.0, 0.0, 0.0, 0.0);
    rf_geomod_face_corner_append(v19, v30, 0.0, 0.0, 0.0, 0.0);
    if ( *(_DWORD *)(k + 20) == *(_DWORD *)(v31 + 64) )
      v9 = 0;
    else
      v9 = *(_DWORD *)(k + 20);
  }
  v4 = rf_receiver_get_first_dword(v29);
  v38 = *(_DWORD *)sub_552200(v29, v4 - 1);
  for ( k = *(_DWORD *)(v38 + 64); k; k = v8 )
  {
    v18 = (float *)rf_solid_face_allocate_link(solid, metadata);
    rf_geomod_face_corner_append(v18, *(_DWORD *)k, 0.0, 0.0, 0.0, 0.0);
    rf_geomod_face_corner_append(v18, **(_DWORD **)(k + 20), 0.0, 0.0, 0.0, 0.0);
    rf_geomod_face_corner_append(v18, v36, 0.0, 0.0, 0.0, 0.0);
    if ( *(_DWORD *)(k + 20) == *(_DWORD *)(v38 + 64) )
      v8 = 0;
    else
      v8 = *(_DWORD *)(k + 20);
  }
  for ( i = 0; ; ++i )
  {
    v5 = rf_receiver_get_first_dword(v29);
    if ( i >= v5 )
      break;
    m = *(_DWORD **)sub_552200(v29, i);
    rf_solid_face_remove_destroy((int *)solid, m, 0);
  }
  rf_vector3_set_components_thiscall(v28, 0.0, a2, 0.0);
  rf_solid_translate_by_subtracting_offset((float *)solid, v28);
  rf_solid_finalize_bounds((float *)solid);
  room = operator new(0x1CCu);
  LOBYTE(v39) = 2;
  if ( room )
    v7 = (float *)rf_room460_construct_register(room, solid, (const float *)solid + 18, (const float *)solid + 21);
  else
    v7 = nullptr;
  LOBYTE(v39) = 1;
  for ( m = (_DWORD *)rf_receiver_get_first_dword((char *)solid + 112); m; m = (_DWORD *)rf_solid_face_next_link((int)m) )
  {
    rf_geomod_face_finalize_geometry((int)m, nullptr, 0);
    rf_geomod_generated_uv_project((int)m);
    rf_geomod_room_face_attach(v7, (int)m);
  }
  rf_room_face_spatial_tree_rebuild((int *)v7);
  v15 = solid;
  v39 = -1;
  rf_pointer_array_destroy_backing_storage(v29);
  return v15;
}

