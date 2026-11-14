// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D5060 rf_entity_commit_unobstructed_motion_and_bounds
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion integration, selected-row transforms, angular/tensor updates, contact velocity response and x87 gates): Cdecl entity. Copies predicted position240 to current228,then angular offset decay/clamp/wrap helper. Flags424 mask0x4000: copies2172 as axis-angle vector,inverse-rotates through current matrix252; only ORDERED length>0 divides axis by length; constructs angle=that length,computes entity2016=axisAngleMatrix*current252,repairs forward basis. Does not replace current252 on this branch. Otherwise helper4D7D70 adds2148+2160 with pitch clamp (mode0) and ONE-step wrap; stores2148,builds current252 from2148 and visual2016 from2148+2172. Both branches copy current252 to common72 and predicted288,then recompute physics rotated tensor with P=entity136. Fraction460=1; bounds400=current228-radius384
// and412=current228+radius384 componentwise (not swept bounds). Leaves velocity,other contact metadata and remaining time432 unchanged; returns final vector-copy EAX bits. No radius/finite/NULL validation.
// UNREALRED VERIFIED [combat-native-view-fov-20261112]: Ordinary view commit is not ActorForward: nonflags424mask4000 branch stores2148=EulerAdd(2148,2160,mode0), current252=4DA050(2148), view7E0=4DA050(2148+2172); special4000 branch instead derives inverse-rotated axisangle offset and rebuilds raw forward basis. Angular offset decay4D4E30 precedes both. Common48 copied from current252, not from view7E0. Preserve the distinct input/lifetime/physics phase before enabling a retained view query.
float *__cdecl rf_entity_commit_unobstructed_motion_and_bounds(int a1)
{
  float *v1; // eax
  float *v2; // eax
  const float *v3; // eax
  const float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float v8[3]; // [esp+4h] [ebp-100h] BYREF
  int v9[3]; // [esp+10h] [ebp-F4h] BYREF
  float v10[3]; // [esp+1Ch] [ebp-E8h] BYREF
  int v11[3]; // [esp+28h] [ebp-DCh] BYREF
  _BYTE v12[36]; // [esp+34h] [ebp-D0h] BYREF
  _BYTE v13[36]; // [esp+58h] [ebp-ACh] BYREF
  float v14[3]; // [esp+7Ch] [ebp-88h] BYREF
  float v15[3]; // [esp+88h] [ebp-7Ch] BYREF
  float v16[9]; // [esp+94h] [ebp-70h] BYREF
  float copy_result[3]; // [esp+B8h] [ebp-4Ch] BYREF
  float sum_result[3]; // [esp+C4h] [ebp-40h] BYREF
  int v19; // [esp+D0h] [ebp-34h] BYREF
  float v20; // [esp+D4h] [ebp-30h]
  float v21; // [esp+D8h] [ebp-2Ch]
  float v22; // [esp+DCh] [ebp-28h]
  float v23[9]; // [esp+E0h] [ebp-24h] BYREF

  rf_vector_copy((float *)(a1 + 228), copy_result, (const float *)(a1 + 240));
  rf_entity_angular_offsets_decay_clamp_and_wrap_once((float *)a1);
  if ( (*(_DWORD *)(a1 + 424) & 0x4000) != 0 )
  {
    rf_vector3_copy_return_destination((float *)&v19, (float *)(a1 + 2172));
    rf_matrix3_inverse_rotate_vector((float *)&v19, (float *)(a1 + 252));
    v22 = rf_vector3_length((float *)&v19);
    if ( v22 > 0.0 )
    {
      *(float *)&v19 = *(float *)&v19 / v22;
      v20 = v20 / v22;
      v21 = v21 / v22;
    }
    rf_matrix3_construct_from_axis_angle((int)v23, (float *)&v19, v22);
    v1 = rf_matrix3_argument_times_receiver_to_output((const float *)(a1 + 252), v16, v23);
    rf_matrix3_copy((float *)(a1 + 2016), v1);
    rf_matrix3_rebuild_basis_from_forward_in_place((char *)(a1 + 2016));
  }
  else
  {
    v2 = rf_euler_angles_add_clamp_pitch_wrap_once(v15, (float *)(a1 + 2148), (float *)(a1 + 2160), 0);
    rf_vector_copy((float *)(a1 + 2148), v14, v2);
    v3 = (const float *)rf_matrix3_build_pitch_heading_linear_horizontal_basis((int)v13, (float *)(a1 + 2148));
    rf_matrix3_copy((float *)(a1 + 252), v3);
    rf_vector_add((const float *)(a1 + 2148), sum_result, (const float *)(a1 + 2172));
    v4 = (const float *)rf_matrix3_build_pitch_heading_linear_horizontal_basis((int)v12, sum_result);
    rf_matrix3_copy((float *)(a1 + 2016), v4);
  }
  rf_matrix3_copy((float *)(a1 + 72), (const float *)(a1 + 252));
  rf_matrix3_copy((float *)(a1 + 288), (const float *)(a1 + 252));
  rf_physics_state_rebuild_rotated_tensor(a1 + 136);
  *(float *)(a1 + 460) = 1.0;
  v5 = rf_vector3_subtract_scalar_from_components((float *)(a1 + 228), (float *)v11, *(float *)(a1 + 384));
  rf_vector_copy((float *)(a1 + 400), v10, v5);
  v6 = rf_vector3_add_scalar_to_components((float *)(a1 + 228), (float *)v9, *(float *)(a1 + 384));
  return rf_vector_copy((float *)(a1 + 412), v8, v6);
}

