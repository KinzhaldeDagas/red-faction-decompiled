// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D7A00 rf_physics_state_copy_setup
// UNREALRED VERIFIED [combat-selected-drop-item-20261111]: Object physics starts atcommon+88. Copies setup+94 flags into physics+120, hence common+1A8. This is a physics-state flagword, distinct from common+7C constructor flags andEntity+810 AIflags. Selecteddrop mask400000 reads this word. Runtime support/contact writers4D9410 and4D9960 own bit400000; do not infer it from generic inventory policy.
int __cdecl rf_physics_state_copy_setup(int a1, int a2, char a3)
{
  float *v3; // eax
  int first_dword; // eax
  float *element_address_unchecked; // eax
  float v7[5]; // [esp-Ch] [ebp-68h] BYREF
  int scalar; // [esp+8h] [ebp-54h]
  float v9[3]; // [esp+10h] [ebp-4Ch] BYREF
  float v10[3]; // [esp+1Ch] [ebp-40h] BYREF
  float scaled_result[3]; // [esp+28h] [ebp-34h] BYREF
  float v12[3]; // [esp+34h] [ebp-28h] BYREF
  float v13[3]; // [esp+40h] [ebp-1Ch] BYREF
  float copy_result[3]; // [esp+4Ch] [ebp-10h] BYREF
  int i; // [esp+58h] [ebp-4h]

  *(float *)(a1 + 4) = *(float *)(a2 + 12);
  *(float *)(a1 + 8) = rf_material_friction_get(*(_DWORD *)(a2 + 16));
  *(float *)a1 = rf_material_restitution_get(*(_DWORD *)(a2 + 16));
  *(float *)(a1 + 16) = *(float *)(a2 + 20);
  rf_matrix3_copy((float *)(a1 + 20), (const float *)(a2 + 24));
  rf_vector_copy((float *)(a1 + 92), copy_result, (const float *)(a2 + 60));
  rf_vector_copy((float *)(a1 + 104), v13, (const float *)(a1 + 92));
  rf_vector_copy((float *)(a1 + 188), v12, (const float *)(a2 + 108));
  rf_vector3_zero_return_destination((float *)(a1 + 224));
  rf_matrix3_copy((float *)(a1 + 116), (const float *)(a2 + 72));
  rf_matrix3_copy((float *)(a1 + 152), (const float *)(a1 + 116));
  scalar = a2;
  v3 = rf_vector_multiply_scalar((const float *)(a2 + 120), scaled_result, *(float *)(a2 + 20));
  rf_vector_copy((float *)(a1 + 212), v10, v3);
  rf_vector_copy((float *)(a1 + 200), v9, (const float *)(a2 + 120));
  rf_vector3_zero_return_destination((float *)(a1 + 236));
  if ( !a3 )
    *(_DWORD *)(a1 + 292) = 0;
  if ( (*(_DWORD *)(a2 + 148) & 0x70) != 0 )
  {
    *(float *)(a1 + 248) = *(float *)(a2 + 132);
    for ( i = 0; ; ++i )
    {
      first_dword = rf_receiver_get_first_dword((void *)(a2 + 136));
      if ( i >= first_dword )
        break;
      element_address_unchecked = (float *)rf_array24_get_element_address_unchecked((_DWORD *)(a2 + 136), i);
      rf_record24_copy_construct_six_floats(v7, element_address_unchecked);
      rf_array24_append_record_by_value(
        (int *)(a1 + 252),
        v7[0],
        SLODWORD(v7[1]),
        SLODWORD(v7[2]),
        SLODWORD(v7[3]),
        SLODWORD(v7[4]),
        scalar);
      if ( *(float *)(rf_array24_get_element_address_unchecked((_DWORD *)(a2 + 136), i) + 16) > 0.0 )
        *(_DWORD *)(a2 + 148) |= 0x2000u;
    }
  }
  *(_DWORD *)(a1 + 288) = *(_DWORD *)(a2 + 148);
  rf_physics_state_rebuild_rotated_tensor(a1);
  *(float *)(a1 + 324) = 1.0;
  *(_DWORD *)(a1 + 348) = -1;
  *(_DWORD *)(a1 + 356) = 0;
  *(_DWORD *)(a1 + 360) = 0;
  rf_vector3_set_components_thiscall((float *)(a1 + 312), 0.0, 1.0, 0.0);
  return rf_physics_shape_recompute_radius_and_axis_bounds(a1);
}

