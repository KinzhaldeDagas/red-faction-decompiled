// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047C400 rf_object_sample_ground_light_color
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, object room/attachment ownership, shape-based ground lighting, native dispatcher table and resolver/view distinctions): Cdecl(outputRGBA,object). Writes ONLY RGB bytes64 initially; alpha untouched on fallback. Constructs temporary physics state whose only constructor payload initialization is empty sphere array; shape/hit/vector default constructors do not zero remaining storage. Sets selected record centerY=FLT_MAX, then copies full24-byte sphere record only when its centerY is ORDERED smaller than retained minimum. Ties/NaNs do not replace. If array empty or no Y<FLT_MAX, other selected-record fields remain unwritten, yet still appends that record and performs sweep. Temporary shape gets one sphere, identity matrix at P116, outer radius P248=float(abs(selectedY)+selectedRadius12), secondary flags P292=object428
// with0x1000 cleared; other physics payload is not blanket initialized. Starts at predicted position object240 with Y+.05000000074505806, ends at same original position with Y-25; builds expanded bounds. Seeds local hit fraction24=1 and liquid word56=0, then shape-sweeps moving and static solids. Only ORDERED hitFraction<1 AND nonnull face60 samples GLOBAL world-solid lightmap at returned hit point (even if hit came from mover). Sampling helper returns full RGBA including alpha255, copied as DWORD; no accepted hit retains default RGB64 and prior output alpha. Destroys temporary sphere-array member on exit; no outer object/color allocation, sphere-count/finite/radius/pointer validation or recovery from uninitialized empty selection.
void __cdecl rf_object_sample_ground_light_color(_BYTE *a1, int a2)
{
  int first_dword; // eax
  int element_address_unchecked; // eax
  float *v4; // eax
  float v5[7]; // [esp-14h] [ebp-244h] BYREF
  float v6; // [esp+8h] [ebp-228h]
  int v7; // [esp+Ch] [ebp-224h] BYREF
  float v8[3]; // [esp+10h] [ebp-220h] BYREF
  float copy_result[4]; // [esp+1Ch] [ebp-214h] BYREF
  char v10[24]; // [esp+2Ch] [ebp-204h] BYREF
  float v11; // [esp+44h] [ebp-1ECh]
  int v12; // [esp+64h] [ebp-1CCh]
  int v13; // [esp+68h] [ebp-1C8h]
  float v14; // [esp+78h] [ebp-1B8h] BYREF
  float v15; // [esp+7Ch] [ebp-1B4h]
  float v16; // [esp+84h] [ebp-1ACh]
  float v17; // [esp+90h] [ebp-1A0h]
  void *v18[29]; // [esp+94h] [ebp-19Ch] BYREF
  float v19[33]; // [esp+108h] [ebp-128h] BYREF
  float v20; // [esp+18Ch] [ebp-A4h]
  int v21[3]; // [esp+190h] [ebp-A0h] BYREF
  float v22[3]; // [esp+19Ch] [ebp-94h] BYREF
  float v23[4]; // [esp+1A8h] [ebp-88h] BYREF
  int v24; // [esp+1B8h] [ebp-78h]
  float destination; // [esp+208h] [ebp-28h] BYREF
  float v26; // [esp+20Ch] [ebp-24h]
  int i; // [esp+214h] [ebp-1Ch]
  float v28; // [esp+218h] [ebp-18h] BYREF
  float v29; // [esp+21Ch] [ebp-14h]
  int v30; // [esp+22Ch] [ebp-4h]

  rf_vector3_default_construct_noop(&destination);
  rf_vector3_default_construct_noop(&v28);
  rf_physics_hit_record_construct_noop(v10);
  rf_physics_state_construct_empty_sphere_collection((char *)v18);
  v30 = 0;
  rf_vector_prefix_construct_noop(&v14);
  *a1 = 64;
  a1[1] = 64;
  a1[2] = 64;
  v15 = 3.4028235e38;
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword((void *)(a2 + 388));
    if ( i >= first_dword )
      break;
    element_address_unchecked = rf_array24_get_element_address_unchecked((_DWORD *)(a2 + 388), i);
    if ( v15 > (double)*(float *)(element_address_unchecked + 4) )
    {
      v4 = (float *)rf_array24_get_element_address_unchecked((_DWORD *)(a2 + 388), i);
      rf_record24_copy_six_floats(&v14, v4);
    }
  }
  LODWORD(copy_result[3]) = v5;
  rf_record24_copy_construct_six_floats(v5, &v14);
  rf_array24_append_record_by_value(
    v21,
    v5[0],
    SLODWORD(v5[1]),
    SLODWORD(v5[2]),
    SLODWORD(v5[3]),
    SLODWORD(v5[4]),
    SLODWORD(v5[5]));
  v6 = fabs(v15);
  v20 = v6 + v16;
  rf_identity_orientation_matrix(v19);
  v24 = *(_DWORD *)(a2 + 428);
  v24 &= ~0x1000u;
  v17 = 1.0;
  rf_vector_copy(&destination, copy_result, (const float *)(a2 + 240));
  v26 = v26 + 0.05000000074505806;
  rf_vector_copy(&v28, v8, (const float *)(a2 + 240));
  v29 = v29 - 25.0;
  rf_segment_bounds_build(v22, v23, &destination, &v28);
  rf_vector3_subtract_scalar_in_place(v22, v20);
  rf_vector3_add_scalar_in_place(v23, v20);
  v11 = 1.0;
  v12 = 0;
  rf_physics_shape_sweep_movers_and_static_world((int)&destination, (int)&v28, (int)v18, (int)v10);
  if ( v11 < 1.0 && v13 )
    *(_DWORD *)a1 = *rf_world_face_sample_lightmap_rgb555((_DWORD *)rf_world_solid, &v7, v13, (int)v10);
  v30 = -1;
  rf_common_embedded_destroy_pointer_array(v18);
}

