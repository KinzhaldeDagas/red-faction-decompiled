// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D5390 rf_physics_body_resolve_world_contact
// Applies normal restitution and tangential friction impulses; ordinary impacts decay restitution by 0.8 and deactivate sufficiently settled bodies.
// UNREALRED VERIFIED [respawn-surrounding]: The ordinary entity world-contact branch passes the negative inward normal velocity to rf_fall_damage_apply_from_contact_speed before resolving restitution/friction response.
void __cdecl rf_physics_body_resolve_world_contact(int a1)
{
  float *v1; // eax
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // ecx
  float *v8; // ecx
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  double v12; // st7
  float *v13; // eax
  float *v14; // eax
  float *v15; // eax
  float v16[2]; // [esp-4h] [ebp-1A8h] BYREF
  float v17; // [esp+4h] [ebp-1A0h]
  float scalar; // [esp+8h] [ebp-19Ch]
  float v19; // [esp+Ch] [ebp-198h]
  float v20; // [esp+10h] [ebp-194h]
  float v21; // [esp+14h] [ebp-190h]
  float v22[3]; // [esp+18h] [ebp-18Ch] BYREF
  float v23[3]; // [esp+24h] [ebp-180h] BYREF
  float v24[3]; // [esp+30h] [ebp-174h] BYREF
  float v25[3]; // [esp+3Ch] [ebp-168h] BYREF
  float v26[3]; // [esp+48h] [ebp-15Ch] BYREF
  float v27[3]; // [esp+54h] [ebp-150h] BYREF
  float v28[3]; // [esp+60h] [ebp-144h] BYREF
  int v29[3]; // [esp+6Ch] [ebp-138h] BYREF
  int v30[3]; // [esp+78h] [ebp-12Ch] BYREF
  float sum_result[3]; // [esp+84h] [ebp-120h] BYREF
  float v32[3]; // [esp+90h] [ebp-114h] BYREF
  float v33[3]; // [esp+9Ch] [ebp-108h] BYREF
  int v34[3]; // [esp+A8h] [ebp-FCh] BYREF
  float v35[3]; // [esp+B4h] [ebp-F0h] BYREF
  float v36[4]; // [esp+C0h] [ebp-E4h] BYREF
  float v37[3]; // [esp+D0h] [ebp-D4h] BYREF
  float v38[3]; // [esp+DCh] [ebp-C8h] BYREF
  float copy_result[3]; // [esp+E8h] [ebp-BCh] BYREF
  float v40[3]; // [esp+F4h] [ebp-B0h] BYREF
  float scaled_result[3]; // [esp+100h] [ebp-A4h] BYREF
  float v42; // [esp+10Ch] [ebp-98h]
  int v43; // [esp+110h] [ebp-94h]
  float destination[3]; // [esp+114h] [ebp-90h] BYREF
  float out_vector[3]; // [esp+120h] [ebp-84h] BYREF
  float v46; // [esp+12Ch] [ebp-78h]
  float v47[3]; // [esp+130h] [ebp-74h] BYREF
  float v48; // [esp+13Ch] [ebp-68h]
  float rhs[3]; // [esp+140h] [ebp-64h] BYREF
  float v50; // [esp+14Ch] [ebp-58h]
  float v51[3]; // [esp+150h] [ebp-54h] BYREF
  float lhs[3]; // [esp+15Ch] [ebp-48h] BYREF
  float v53; // [esp+168h] [ebp-3Ch]
  float v54; // [esp+16Ch] [ebp-38h]
  float source[3]; // [esp+170h] [ebp-34h] BYREF
  float v56; // [esp+17Ch] [ebp-28h]
  float v57[3]; // [esp+180h] [ebp-24h] BYREF
  float v58; // [esp+18Ch] [ebp-18h]
  float v59; // [esp+190h] [ebp-14h]
  float v60; // [esp+194h] [ebp-10h]
  _BYTE v61[12]; // [esp+198h] [ebp-Ch] BYREF

  if ( *(_DWORD *)(a1 + 492) )
  {
    *(_DWORD *)(a1 + 428) &= ~0x1000u;
    *(_DWORD *)(a1 + 492) = 0;
  }
  else if ( (*(_DWORD *)(a1 + 424) & 0x200) == 0 )
  {
    rf_vector3_default_construct_noop(destination);
    rf_vector3_default_construct_noop(v61);
    rf_vector3_set_components_return_destination(v51, 0.0, 0.0, 0.0);
    rf_vector3_set_components_return_destination(v57, 0.0, 0.0, 0.0);
    rf_vector3_default_construct_noop(v47);
    rf_vector3_default_construct_noop(rhs);
    rf_vector_subtract((const float *)(a1 + 436), out_vector, (const float *)(a1 + 228));
    rf_physics_state_point_velocity_from_rotated_tensor((int)lhs, a1 + 136, (int)out_vector);
    v58 = rf_vector_dot((float *)(a1 + 448), lhs);
    if ( v58 <= 0.0 )
    {
      v1 = rf_vector_multiply_scalar((const float *)(a1 + 448), scaled_result, v58);
      rf_vector_subtract(lhs, source, v1);
      v48 = rf_vector_dot(unk_87BF54, (float *)(a1 + 448));
      v60 = (rf_material_friction_get(*(_DWORD *)(a1 + 464)) + *(float *)(a1 + 144)) / 2.0;
      v50 = rf_material_restitution_get(*(_DWORD *)(a1 + 464)) * *(float *)(a1 + 136);
      if ( (*(_DWORD *)(a1 + 424) & 0x4000) != 0 && !*(_DWORD *)(a1 + 36) )
      {
        v43 = a1;
        if ( *(_DWORD *)(a1 + 4992) == -1 )
        {
          scalar = -v58;
          rf_fall_damage_apply_from_contact_speed(v43, scalar);
        }
        v50 = *(float *)(a1 + 136);
      }
      if ( (*(_DWORD *)(a1 + 424) & 0x4000) != 0
        || (*(float *)(a1 + 136) = *(float *)(a1 + 136) * 0.800000011920929, *(float *)(a1 + 136) >= 0.05000000074505806)
        && (rf_vector_length_squared((float *)(a1 + 324)) >= 0.25 || rf_vector_length_squared((float *)(a1 + 336)) >= 0.5) )
      {
        v46 = -(v50 + 1.0) * v58;
        v2 = rf_vector_cross(out_vector, v40, (float *)(a1 + 448));
        rf_vector_copy(destination, copy_result, v2);
        rf_matrix3_inverse_rotate_vector(destination, (float *)(a1 + 192));
        v3 = rf_vector_cross(destination, v38, out_vector);
        rf_vector_copy(v47, v37, v3);
        v54 = rf_vector_dot((float *)(a1 + 448), v47);
        v54 = 1.0 / *(float *)(a1 + 152) + v54;
        v53 = v46 / v54;
        if ( (*(_DWORD *)(a1 + 424) & 0x100) != 0 )
        {
          scalar = 0.89999998;
          rf_vector3_copy_return_destination(v16, (float *)(a1 + 448));
          rf_random_unit_vector_in_cone(v51, v16[0], v16[1], v17, scalar);
          rf_vector3_scale_in_place_return_self(v51, v53);
        }
        else
        {
          v4 = rf_vector_multiply_scalar((const float *)(a1 + 448), v36, v53);
          rf_vector_copy(v51, v35, v4);
        }
        v56 = v60 * *(float *)(a1 + 152) * -v48;
        LODWORD(scalar) = a1 + 448;
        v17 = rf_vector_dot((float *)(a1 + 448), (float *)(a1 + 324));
        v5 = rf_vector_scale((float *)v34, v17, (float *)LODWORD(scalar));
        v6 = rf_vector_subtract((const float *)(a1 + 324), v33, v5);
        rf_vector_copy(rhs, v32, v6);
        v59 = rf_vector3_length(rhs);
        if ( v59 <= 0.0 || (*(_DWORD *)(a1 + 424) & 0x4000) != 0 )
        {
          scalar = *(float *)&v7;
          v11 = rf_vector_divide(v51, (float *)v29, *(float *)(a1 + 152));
          rf_vector_accumulate((float *)(a1 + 324), v11);
        }
        else
        {
          v21 = v59 * *(float *)(a1 + 152);
          v56 = rf_float_minimum_two_values(v56, v21);
          v20 = v56 / -v59;
          rf_vector3_scale_in_place_return_self(rhs, v20);
          scalar = *(float *)&v8;
          scalar = *(float *)(a1 + 152);
          v17 = COERCE_FLOAT(v30);
          v9 = rf_vector_add(v51, sum_result, rhs);
          v10 = rf_vector_divide(v9, (float *)LODWORD(v17), scalar);
          rf_vector_accumulate((float *)(a1 + 324), v10);
        }
        v59 = rf_vector3_length(source);
        if ( v59 <= 0.0 || (*(_DWORD *)(a1 + 424) & 0x4000) != 0 )
        {
          v15 = rf_vector_cross(out_vector, v24, v51);
          rf_vector_copy(v57, v23, v15);
        }
        else
        {
          v42 = v59 * *(float *)(a1 + 152);
          rf_vector_copy(rhs, v28, source);
          v12 = rf_float_minimum_two_values(v56, v42);
          v19 = v12 / -v59;
          rf_vector3_scale_in_place_return_self(rhs, v19);
          v13 = rf_vector_add(v51, v27, rhs);
          v14 = rf_vector_cross(out_vector, v26, v13);
          rf_vector_copy(v57, v25, v14);
        }
        rf_vector_accumulate((float *)(a1 + 348), v57);
        rf_vector_copy((float *)(a1 + 336), v22, (const float *)(a1 + 348));
        rf_matrix3_inverse_rotate_vector((float *)(a1 + 336), (float *)(a1 + 192));
      }
      else
      {
        rf_physics_state_deactivate(a1 + 136);
      }
    }
  }
}

