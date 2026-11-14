// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00547F20 rf_solid_gridded_box_create
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Cdecl sizeX,sizeY,sizeZ floats,subdivX,subdivY,subdivZ signed ints;returns888-byte solid. Computes float steps sizeX/(subdivX+1),sizeY/(subdivY+1),sizeZ/(subdivZ+1) without divisor/range/overflow guards. Allocates two outer dynamic arrays of row pointers. For zIndex0..subdivZ+1 inclusive,allocates two12-byte row arrays and appends vertices for xIndex0..subdivX+1 at(x*stepX,0,z*stepZ) and(x*stepX,stepY,z*stepZ). Builds oppositely wound bottom/top quad grids for z0..subdivZ andx0..subdivX;top faces are selected via solid+216 array. Adds front/back strips for each X interval and left/right strips for each Z interval. Uses19FF0 ECX solid receiver plus stack metadata. For
// each iteration0..subdivY-1,calls selected-boundary split/bridge helper,then raises EVERY vertex still referenced by upper row arrays bystepY. Clears selected-face count,deletes both row-array objects for each Z row. Centers through51BF40,which subtracts ARITHMETIC MEAN OF ALL STORED VERTEX POSITIONS,not AABB center;recomputes bounds. Allocates460-byte room with solid and bounds72/84,projects generated UVs for all faces,attaches faces,rebuilds room tree,destroys outer array storage,returns solid. No final separate per-face geometry loop here;construction/split/centering helpers perform their own updates. No NULL allocation gate,subdivision/dimension validation or transactional cleanup. Negative counts can skip needed construction yet later indexing still executes;subdiv=-1 divides byzero. Earlier repeatable box summary retained.
_DWORD *__cdecl rf_solid_gridded_box_create(float a1, float a2, float a3, int a4, int a5, int a6)
{
  int *v6; // eax
  int *v7; // eax
  int *v8; // eax
  int *v9; // eax
  int *v10; // eax
  int *v11; // eax
  int *v12; // eax
  int *v13; // eax
  _DWORD **v14; // eax
  int *v15; // eax
  _DWORD **v16; // eax
  int *v17; // eax
  _DWORD **v18; // eax
  int *v19; // eax
  _DWORD **v20; // eax
  int *v21; // eax
  _DWORD **v22; // eax
  int *v23; // eax
  _DWORD **v24; // eax
  int *v25; // eax
  _DWORD **v26; // eax
  int *v27; // eax
  _DWORD **v28; // eax
  int *v29; // eax
  _DWORD **v30; // eax
  int *v31; // eax
  _DWORD **v32; // eax
  int *v33; // eax
  _DWORD **v34; // eax
  int *v35; // eax
  _DWORD **v36; // eax
  int *v37; // eax
  _DWORD **v38; // eax
  int *v39; // eax
  _DWORD **v40; // eax
  int *v41; // eax
  _DWORD **v42; // eax
  int *v43; // eax
  _DWORD **v44; // eax
  int *v45; // eax
  int first_dword; // eax
  void **v47; // eax
  _DWORD **v48; // eax
  int v49; // eax
  int v50; // eax
  int v52; // [esp-4h] [ebp-11Ch]
  int v53; // [esp-4h] [ebp-11Ch]
  int v54; // [esp-4h] [ebp-11Ch]
  int v55; // [esp-4h] [ebp-11Ch]
  int v56; // [esp-4h] [ebp-11Ch]
  int v57; // [esp-4h] [ebp-11Ch]
  int v58; // [esp-4h] [ebp-11Ch]
  int v59; // [esp-4h] [ebp-11Ch]
  int *v60; // [esp+14h] [ebp-104h]
  _DWORD *v61; // [esp+20h] [ebp-F8h]
  _DWORD *v62; // [esp+24h] [ebp-F4h]
  void **v63; // [esp+34h] [ebp-E4h]
  void *v64; // [esp+38h] [ebp-E0h]
  void *room; // [esp+3Ch] [ebp-DCh]
  void **v66; // [esp+48h] [ebp-D0h]
  void **v67; // [esp+50h] [ebp-C8h]
  void *v68; // [esp+54h] [ebp-C4h]
  void *v69; // [esp+5Ch] [ebp-BCh]
  void **v70; // [esp+64h] [ebp-B4h]
  int k; // [esp+70h] [ebp-A8h]
  float *v72; // [esp+74h] [ebp-A4h]
  float *v73; // [esp+78h] [ebp-A0h]
  float *v74; // [esp+7Ch] [ebp-9Ch]
  float *v75; // [esp+80h] [ebp-98h]
  float *v76; // [esp+84h] [ebp-94h]
  float *link; // [esp+88h] [ebp-90h]
  _DWORD *v78; // [esp+8Ch] [ebp-8Ch]
  _DWORD *v79; // [esp+90h] [ebp-88h]
  _DWORD *v80; // [esp+94h] [ebp-84h]
  _DWORD *v81; // [esp+98h] [ebp-80h]
  float v82[3]; // [esp+9Ch] [ebp-7Ch] BYREF
  float *v83; // [esp+A8h] [ebp-70h]
  float v84; // [esp+ACh] [ebp-6Ch]
  _DWORD *v85; // [esp+B0h] [ebp-68h]
  _DWORD *v86; // [esp+B4h] [ebp-64h]
  float v87; // [esp+B8h] [ebp-60h]
  int j; // [esp+BCh] [ebp-5Ch]
  int m; // [esp+C0h] [ebp-58h]
  float *v90; // [esp+C4h] [ebp-54h]
  float v91; // [esp+C8h] [ebp-50h]
  float v92; // [esp+CCh] [ebp-4Ch]
  void *v93[3]; // [esp+D0h] [ebp-48h] BYREF
  void *v94[3]; // [esp+DCh] [ebp-3Ch] BYREF
  void *solid; // [esp+E8h] [ebp-30h]
  int i; // [esp+ECh] [ebp-2Ch]
  unsigned int metadata[6]; // [esp+F0h] [ebp-28h] BYREF
  float v98; // [esp+108h] [ebp-10h]
  int v99; // [esp+114h] [ebp-4h]

  v70 = (void **)operator new(0x378u);
  v99 = 0;
  if ( v70 )
    v63 = rf_solid888_construct(v70);
  else
    v63 = nullptr;
  v99 = -1;
  solid = v63;
  v98 = a1 / (double)(a4 + 1);
  v91 = a2 / (double)(a5 + 1);
  v92 = a3 / (double)(a6 + 1);
  rf_dword_array_construct_capacity(v93, 0);
  v99 = 1;
  rf_dword_array_construct_capacity(v94, 0);
  LOBYTE(v99) = 2;
  for ( i = 0; i <= a6 + 1; ++i )
  {
    v69 = operator new(0xCu);
    LOBYTE(v99) = 3;
    if ( v69 )
      v62 = rf_dword_array_construct_zero_capacity_51e910(v69);
    else
      v62 = nullptr;
    LOBYTE(v99) = 2;
    v85 = v62;
    v68 = operator new(0xCu);
    LOBYTE(v99) = 4;
    if ( v68 )
      v61 = rf_dword_array_construct_zero_capacity_51e910(v68);
    else
      v61 = nullptr;
    LOBYTE(v99) = 2;
    v86 = v61;
    v87 = (double)i * v92;
    for ( j = 0; j <= a4 + 1; ++j )
    {
      v84 = (double)j * v98;
      rf_vector3_set_components_return_destination(v82, v84, 0.0, v87);
      v83 = rf_solid_vertex_copy_append(solid, v82);
      rf_pointer_array_append_dword(v85, (int)v83);
      rf_vector3_set_components_thiscall(v82, v84, v91, v87);
      v83 = rf_solid_vertex_copy_append(solid, v82);
      rf_pointer_array_append_dword(v86, (int)v83);
    }
    rf_pointer_array_append_dword(v93, (int)v85);
    rf_pointer_array_append_dword(v94, (int)v86);
  }
  rf_geomod_face_metadata_init(metadata);
  for ( i = 0; i <= a6; ++i )
  {
    v79 = *(_DWORD **)sub_552200(v93, i);
    v78 = *(_DWORD **)sub_552200(v93, i + 1);
    v80 = *(_DWORD **)sub_552200(v94, i);
    v81 = *(_DWORD **)sub_552200(v94, i + 1);
    for ( j = 0; j <= a4; ++j )
    {
      link = (float *)rf_solid_face_allocate_link(solid, metadata);
      v6 = (int *)sub_552200(v79, j);
      rf_geomod_face_corner_append(link, *v6, 0.0, 0.0, 0.0, 0.0);
      v7 = (int *)sub_552200(v78, j);
      rf_geomod_face_corner_append(link, *v7, 0.0, 0.0, 0.0, 0.0);
      v8 = (int *)sub_552200(v78, j + 1);
      rf_geomod_face_corner_append(link, *v8, 0.0, 0.0, 0.0, 0.0);
      v9 = (int *)sub_552200(v79, j + 1);
      rf_geomod_face_corner_append(link, *v9, 0.0, 0.0, 0.0, 0.0);
      rf_geomod_face_finalize_geometry((int)link, nullptr, 0);
      v76 = (float *)rf_solid_face_allocate_link(solid, metadata);
      v10 = (int *)sub_552200(v80, j);
      rf_geomod_face_corner_append(v76, *v10, 0.0, 0.0, 0.0, 0.0);
      v11 = (int *)sub_552200(v80, j + 1);
      rf_geomod_face_corner_append(v76, *v11, 0.0, 0.0, 0.0, 0.0);
      v12 = (int *)sub_552200(v81, j + 1);
      rf_geomod_face_corner_append(v76, *v12, 0.0, 0.0, 0.0, 0.0);
      v13 = (int *)sub_552200(v81, j);
      rf_geomod_face_corner_append(v76, *v13, 0.0, 0.0, 0.0, 0.0);
      rf_geomod_face_finalize_geometry((int)v76, nullptr, 0);
      rf_pointer_array_append_dword((_DWORD *)solid + 54, (int)v76);
    }
  }
  for ( i = 0; i <= a4; ++i )
  {
    v74 = (float *)rf_solid_face_allocate_link(solid, metadata);
    v52 = i;
    v14 = (_DWORD **)sub_552200(v93, 0);
    v15 = (int *)sub_552200(*v14, v52);
    rf_geomod_face_corner_append(v74, *v15, 0.0, 0.0, 0.0, 0.0);
    v53 = i + 1;
    v16 = (_DWORD **)sub_552200(v93, 0);
    v17 = (int *)sub_552200(*v16, v53);
    rf_geomod_face_corner_append(v74, *v17, 0.0, 0.0, 0.0, 0.0);
    v54 = i + 1;
    v18 = (_DWORD **)sub_552200(v94, 0);
    v19 = (int *)sub_552200(*v18, v54);
    rf_geomod_face_corner_append(v74, *v19, 0.0, 0.0, 0.0, 0.0);
    v55 = i;
    v20 = (_DWORD **)sub_552200(v94, 0);
    v21 = (int *)sub_552200(*v20, v55);
    rf_geomod_face_corner_append(v74, *v21, 0.0, 0.0, 0.0, 0.0);
    v75 = (float *)rf_solid_face_allocate_link(solid, metadata);
    v56 = i;
    v22 = (_DWORD **)sub_552200(v93, a6 + 1);
    v23 = (int *)sub_552200(*v22, v56);
    rf_geomod_face_corner_append(v75, *v23, 0.0, 0.0, 0.0, 0.0);
    v57 = i;
    v24 = (_DWORD **)sub_552200(v94, a6 + 1);
    v25 = (int *)sub_552200(*v24, v57);
    rf_geomod_face_corner_append(v75, *v25, 0.0, 0.0, 0.0, 0.0);
    v58 = i + 1;
    v26 = (_DWORD **)sub_552200(v94, a6 + 1);
    v27 = (int *)sub_552200(*v26, v58);
    rf_geomod_face_corner_append(v75, *v27, 0.0, 0.0, 0.0, 0.0);
    v59 = i + 1;
    v28 = (_DWORD **)sub_552200(v93, a6 + 1);
    v29 = (int *)sub_552200(*v28, v59);
    rf_geomod_face_corner_append(v75, *v29, 0.0, 0.0, 0.0, 0.0);
  }
  for ( i = 0; i <= a6; ++i )
  {
    v73 = (float *)rf_solid_face_allocate_link(solid, metadata);
    v30 = (_DWORD **)sub_552200(v93, i);
    v31 = (int *)sub_552200(*v30, 0);
    rf_geomod_face_corner_append(v73, *v31, 0.0, 0.0, 0.0, 0.0);
    v32 = (_DWORD **)sub_552200(v94, i);
    v33 = (int *)sub_552200(*v32, 0);
    rf_geomod_face_corner_append(v73, *v33, 0.0, 0.0, 0.0, 0.0);
    v34 = (_DWORD **)sub_552200(v94, i + 1);
    v35 = (int *)sub_552200(*v34, 0);
    rf_geomod_face_corner_append(v73, *v35, 0.0, 0.0, 0.0, 0.0);
    v36 = (_DWORD **)sub_552200(v93, i + 1);
    v37 = (int *)sub_552200(*v36, 0);
    rf_geomod_face_corner_append(v73, *v37, 0.0, 0.0, 0.0, 0.0);
    v72 = (float *)rf_solid_face_allocate_link(solid, metadata);
    v38 = (_DWORD **)sub_552200(v93, i);
    v39 = (int *)sub_552200(*v38, a4 + 1);
    rf_geomod_face_corner_append(v72, *v39, 0.0, 0.0, 0.0, 0.0);
    v40 = (_DWORD **)sub_552200(v93, i + 1);
    v41 = (int *)sub_552200(*v40, a4 + 1);
    rf_geomod_face_corner_append(v72, *v41, 0.0, 0.0, 0.0, 0.0);
    v42 = (_DWORD **)sub_552200(v94, i + 1);
    v43 = (int *)sub_552200(*v42, a4 + 1);
    rf_geomod_face_corner_append(v72, *v43, 0.0, 0.0, 0.0, 0.0);
    v44 = (_DWORD **)sub_552200(v94, i);
    v45 = (int *)sub_552200(*v44, a4 + 1);
    rf_geomod_face_corner_append(v72, *v45, 0.0, 0.0, 0.0, 0.0);
  }
  for ( i = 0; i < a5; ++i )
  {
    rf_solid_split_selected_boundary_vertices_and_bridge(solid);
    for ( j = 0; ; ++j )
    {
      first_dword = rf_receiver_get_first_dword(v94);
      if ( j >= first_dword )
        break;
      for ( k = 0; ; ++k )
      {
        v47 = (void **)sub_552200(v94, j);
        if ( k >= rf_receiver_get_first_dword(*v47) )
          break;
        v48 = (_DWORD **)sub_552200(v94, j);
        v49 = sub_552200(*v48, k);
        *(float *)(*(_DWORD *)v49 + 4) = *(float *)(*(_DWORD *)v49 + 4) + v91;
      }
    }
  }
  rf_solid_clear_selected_face_count(solid);
  for ( i = 0; ; ++i )
  {
    v50 = rf_receiver_get_first_dword(v93);
    if ( i >= v50 )
      break;
    v67 = *(void ***)sub_552200(v93, i);
    if ( v67 )
      rf_pointer_array_scalar_deleting_destructor(v67, 1);
    v66 = *(void ***)sub_552200(v94, i);
    if ( v66 )
      rf_pointer_array_scalar_deleting_destructor(v66, 1);
  }
  rf_solid_center_on_vertex_mean((char *)solid);
  rf_solid_finalize_bounds((float *)solid);
  room = operator new(0x1CCu);
  LOBYTE(v99) = 5;
  if ( room )
    v60 = (int *)rf_room460_construct_register(room, solid, (const float *)solid + 18, (const float *)solid + 21);
  else
    v60 = nullptr;
  LOBYTE(v99) = 2;
  v90 = (float *)v60;
  for ( m = rf_receiver_get_first_dword((char *)solid + 112); m; m = rf_solid_face_next_link(m) )
  {
    rf_geomod_generated_uv_project(m);
    rf_geomod_room_face_attach(v90, m);
  }
  rf_room_face_spatial_tree_rebuild((int *)v90);
  v64 = solid;
  LOBYTE(v99) = 1;
  rf_pointer_array_destroy_backing_storage(v94);
  v99 = -1;
  rf_pointer_array_destroy_backing_storage(v93);
  return v64;
}

