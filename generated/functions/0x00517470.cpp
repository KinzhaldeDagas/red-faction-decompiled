// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00517470 rf_liquid_room_surface_rebuild
// UNREALRED VERIFIED [particle-contact-geometry-20261104] Rebuilds an enabled room's liquid surface: removes previous flag-0x04 faces, disables liquid for depth <= 0, otherwise constructs a horizontal quad at room minimum RF Y + depth across horizontal room bounds with authored material/animation and UV dimensions/rotation. Registers the quad in a temporary solid and calls immediate mode-6 0x52E9D0 against the world and selected room. Its 0x52EC40 policy attaches retained clipped faces and reversed cutter copies to that room; final liquid collision geometry is not merely the initial bounds rectangle. Both generated orientations permit particle entry or exit contact while eligibility 0x400 remains set.
char *__thiscall rf_liquid_room_surface_rebuild(int this, _DWORD *a2)
{
  char *result; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float v7; // [esp+0h] [ebp-158h]
  float v8; // [esp+0h] [ebp-158h]
  float v9; // [esp+0h] [ebp-158h]
  float v10; // [esp+0h] [ebp-158h]
  float v11; // [esp+4h] [ebp-154h]
  float v12; // [esp+4h] [ebp-154h]
  float v13; // [esp+4h] [ebp-154h]
  float v14; // [esp+4h] [ebp-154h]
  char *v15; // [esp+18h] [ebp-140h]
  _DWORD *v17; // [esp+28h] [ebp-130h]
  int v18; // [esp+30h] [ebp-128h] BYREF
  unsigned int v19; // [esp+34h] [ebp-124h]
  int v20; // [esp+38h] [ebp-120h] BYREF
  _DWORD *room_link; // [esp+3Ch] [ebp-11Ch]
  _DWORD *i; // [esp+40h] [ebp-118h]
  float v23[3]; // [esp+44h] [ebp-114h] BYREF
  float v24; // [esp+50h] [ebp-108h]
  float v25; // [esp+54h] [ebp-104h]
  float v26[3]; // [esp+58h] [ebp-100h] BYREF
  float v27[2]; // [esp+64h] [ebp-F4h] BYREF
  float v28; // [esp+6Ch] [ebp-ECh]
  float v29[3]; // [esp+70h] [ebp-E8h] BYREF
  int v30; // [esp+7Ch] [ebp-DCh] BYREF
  float v31[3]; // [esp+80h] [ebp-D8h] BYREF
  char *v32; // [esp+8Ch] [ebp-CCh]
  float v33; // [esp+90h] [ebp-C8h]
  _DWORD *v34; // [esp+94h] [ebp-C4h]
  float v35[2]; // [esp+98h] [ebp-C0h] BYREF
  float v36; // [esp+A0h] [ebp-B8h]
  int v37; // [esp+A4h] [ebp-B4h] BYREF
  float v38; // [esp+A8h] [ebp-B0h]
  float v39[3]; // [esp+ACh] [ebp-ACh] BYREF
  unsigned int v40[2]; // [esp+B8h] [ebp-A0h] BYREF
  int generated_handle_unchecked; // [esp+C0h] [ebp-98h]
  float v42[3]; // [esp+D0h] [ebp-88h] BYREF
  float v43[3]; // [esp+DCh] [ebp-7Ch] BYREF
  char v44[48]; // [esp+E8h] [ebp-70h] BYREF
  char v45[12]; // [esp+118h] [ebp-40h] BYREF
  float v46; // [esp+124h] [ebp-34h]
  float v47[9]; // [esp+128h] [ebp-30h] BYREF
  int v48; // [esp+154h] [ebp-4h]

  if ( *(_BYTE *)(this + 388) )
  {
    for ( i = (_DWORD *)rf_receiver_get_first_dword((void *)(this + 40)); i; i = room_link )
    {
      room_link = (_DWORD *)rf_face_next_room_link((int)i);
      if ( rf_face_is_liquid(i + 10) )
      {
        rf_solid_face_list_remove(a2 + 28, (int)i);
        rf_geomod_face_destroy(i);
        i = nullptr;
      }
    }
  }
  if ( *(float *)(this + 392) <= 0.0 )
    *(_BYTE *)(this + 388) = 0;
  result = (char *)this;
  if ( *(_BYTE *)(this + 388) )
  {
    if ( *(int *)(this + 408) < 0 && *(int *)(this + 432) >= 0 )
    {
      rf_bitmap_get_resolved_dimensions(*(_DWORD *)(this + 404), &v18, &v20);
      v19 = *(_DWORD *)(this + 432);
      *(_DWORD *)(this + 408) = rf_procedural_bitmap_find_or_create(v18, v20, v19, *(_DWORD *)(this + 404));
    }
    v17 = operator new(0x378u);
    v48 = 0;
    if ( v17 )
      v15 = (char *)rf_solid888_construct(v17);
    else
      v15 = nullptr;
    v48 = -1;
    v32 = v15;
    rf_vector_construct_no_unwind(v44, 0xCu, 4, rf_vector3_default_construct_noop);
    rf_vector3_copy_return_destination(v35, (float *)(this + 8));
    rf_vector3_copy_return_destination(v27, (float *)(this + 20));
    v38 = *(float *)(this + 12) + *(float *)(this + 392);
    rf_geomod_face_metadata_init(v40);
    v40[0] |= 4u;
    rf_face_metadata_set_flag_40_lowbyte(v40, 1);
    if ( *(int *)(this + 408) < 0 )
    {
      generated_handle_unchecked = *(_DWORD *)(this + 404);
      rf_bitmap_get_resolved_dimensions(*(_DWORD *)(this + 404), &v30, &v37);
    }
    else
    {
      v40[0] |= 0x400u;
      generated_handle_unchecked = rf_procedural_bitmap_get_generated_handle_unchecked(*(_DWORD *)(this + 408));
      rf_procedural_bitmap_get_dimensions_unchecked(*(_DWORD *)(this + 408), &v30, &v37);
    }
    rf_vector3_set_components_return_destination(v29, v35[0], v38, v36);
    rf_vector3_set_components_return_destination(v42, v35[0], v38, v28);
    rf_vector3_set_components_return_destination(v23, v27[0], v38, v36);
    rf_vector3_set_components_return_destination((float *)v45, v27[0], v38, v28);
    v46 = rf_vector_distance(v29, v42);
    v24 = rf_vector_distance(v29, v23);
    v25 = (double)*(int *)(this + 412) * v46 / (double)v30;
    v33 = (double)*(int *)(this + 416) * v24 / (double)v37;
    rf_vector3_set_components_return_destination(v43, 0.0, 0.0, 0.0);
    rf_vector3_set_components_return_destination(v31, v25, 0.0, 0.0);
    rf_vector3_set_components_return_destination(v39, v25, 0.0, v33);
    rf_vector3_set_components_return_destination(v26, 0.0, 0.0, v33);
    rf_matrix3_construct((char *)v47);
    rf_matrix3_set_euler_angles(v47, 0.0, 0.0, *(float *)(this + 420));
    rf_matrix3_inverse_rotate_vector(v43, v47);
    rf_matrix3_inverse_rotate_vector(v31, v47);
    rf_matrix3_inverse_rotate_vector(v26, v47);
    rf_matrix3_inverse_rotate_vector(v39, v47);
    v34 = rf_geomod_face_allocate(v40);
    v11 = v31[2];
    v7 = v31[0];
    v3 = rf_geomod_vertex_copy_allocate(v42);
    rf_geomod_face_corner_append(v34, (int)v3, v7, v11, 0.0, 0.0);
    v12 = v39[2];
    v8 = v39[0];
    v4 = rf_geomod_vertex_copy_allocate((float *)v45);
    rf_geomod_face_corner_append(v34, (int)v4, v8, v12, 0.0, 0.0);
    v13 = v26[2];
    v9 = v26[0];
    v5 = rf_geomod_vertex_copy_allocate(v23);
    rf_geomod_face_corner_append(v34, (int)v5, v9, v13, 0.0, 0.0);
    v14 = v43[2];
    v10 = v43[0];
    v6 = rf_geomod_vertex_copy_allocate(v29);
    rf_geomod_face_corner_append(v34, (int)v6, v10, v14, 0.0, 0.0);
    rf_geomod_face_finalize_geometry((int)v34, 0, 0);
    rf_solid_face_adopt_link(v32, (int)v34);
    rf_geomod_boolean_mode6_apply_immediate(a2, v32, this);
    result = v32;
    if ( v32 )
      return rf_solid_destroy(v32, 1);
  }
  return result;
}

