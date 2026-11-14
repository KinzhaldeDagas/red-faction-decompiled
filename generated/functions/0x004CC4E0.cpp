// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CC4E0 rf_particle_trace_world_contact
// UNREALRED VERIFIED [combat-particle-contact-20261104]: Portal continuation raw4CC669..4CC6D7 /4CC764..4CC7D2 advances newStart=hitPoint+(end-start)*min(1-hitFraction,0.02), recursively traces to original end with depth+1 and directly returns nested result. No fraction recomposition: returned fraction remains final recursive segment-local fraction. Referenced solids precede room liquid-face/current-BSP branches; do not replace with all-room nearest hit.
char __cdecl rf_particle_trace_world_contact(int a1, float *rhs, float *lhs, int a4, int a5)
{
  float *v6; // eax
  int first_dword; // eax
  int v8; // eax
  float *v9; // eax
  float *v10; // eax
  float v11; // [esp+8h] [ebp-E8h]
  float v12; // [esp+Ch] [ebp-E4h]
  float v13[3]; // [esp+10h] [ebp-E0h] BYREF
  float v14[3]; // [esp+1Ch] [ebp-D4h] BYREF
  float v15[3]; // [esp+28h] [ebp-C8h] BYREF
  float scaled_result[3]; // [esp+34h] [ebp-BCh] BYREF
  float v17[3]; // [esp+40h] [ebp-B0h] BYREF
  float v18[3]; // [esp+4Ch] [ebp-A4h] BYREF
  float out_vector[3]; // [esp+58h] [ebp-98h] BYREF
  float copy_result[3]; // [esp+64h] [ebp-8Ch] BYREF
  float v21[3]; // [esp+70h] [ebp-80h] BYREF
  float v22; // [esp+7Ch] [ebp-74h]
  float sum_result[3]; // [esp+80h] [ebp-70h] BYREF
  float scalar; // [esp+8Ch] [ebp-64h]
  float destination[3]; // [esp+90h] [ebp-60h] BYREF
  float vector[3]; // [esp+9Ch] [ebp-54h] BYREF
  float v27[3]; // [esp+A8h] [ebp-48h] BYREF
  float v28[3]; // [esp+B4h] [ebp-3Ch] BYREF
  int v29; // [esp+C0h] [ebp-30h] BYREF
  float v30; // [esp+C4h] [ebp-2Ch]
  float v31[3]; // [esp+C8h] [ebp-28h] BYREF
  float source[4]; // [esp+D4h] [ebp-1Ch] BYREF
  int v33; // [esp+E4h] [ebp-Ch]
  char v34; // [esp+EBh] [ebp-5h]
  int i; // [esp+ECh] [ebp-4h]

  v34 = 0;
  if ( a5 >= 5 )
    return 0;
  *(_DWORD *)(a4 + 4) = 0;
  rf_vector3_default_construct_noop(v28);
  rf_vector3_default_construct_noop(v27);
  rf_force_sample44_construct_vectors_noop((char *)destination);
  rf_vector_copy(destination, copy_result, rhs);
  v6 = rf_vector_subtract(lhs, out_vector, rhs);
  rf_vector_copy(vector, v18, v6);
  rf_segment_bounds_build(v28, v27, rhs, lhs);
  rf_solid_collision_result_construct_noop((int)&v29);
  v29 = 0;
  v30 = 1.0;
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword((void *)(*(_DWORD *)(a1 + 100) + 108));
    if ( i >= first_dword )
      break;
    v8 = sub_552200((_DWORD *)(*(_DWORD *)(a1 + 100) + 108), i);
    if ( sub_4CC9D0(*(_DWORD *)(*(_DWORD *)v8 + 60), (int)v28, (int)v27, (int)destination, (int)&v29) )
    {
      *(float *)a4 = v30;
      rf_vector_copy((float *)(a4 + 8), v17, source);
      return 1;
    }
  }
  if ( (*(_DWORD *)(a1 + 88) & 0x400) != 0 && *(_BYTE *)(*(_DWORD *)(a1 + 100) + 388) )
  {
    if ( sub_4CC890(*(_DWORD *)(a1 + 100), (int)v28, (int)v27, (int)destination, (int)&v29) )
    {
      if ( rf_particle_cross_face_portal(a1, v33) )
      {
        v12 = 1.0 - v30;
        scalar = rf_float_minimum_two_values(v12, 0.02);
        v9 = rf_vector_multiply_scalar(vector, scaled_result, scalar);
        rf_vector_add(v31, sum_result, v9);
        return rf_particle_trace_world_contact(a1, sum_result, (int)lhs, a4, a5 + 1);
      }
      else
      {
        rf_vector_copy((float *)(a4 + 8), v15, source);
        *(float *)a4 = v30;
        *(_DWORD *)(a4 + 4) = rf_face_is_liquid((_DWORD *)(v33 + 40));
        return 1;
      }
    }
    return v34;
  }
  if ( !sub_4CC9D0(*(_DWORD *)(*(_DWORD *)(a1 + 100) + 60), (int)v28, (int)v27, (int)destination, (int)&v29) )
    return v34;
  if ( rf_particle_cross_face_portal(a1, v33) )
  {
    v11 = 1.0 - v30;
    v22 = rf_float_minimum_two_values(v11, 0.02);
    v10 = rf_vector_multiply_scalar(vector, v14, v22);
    rf_vector_add(v31, v21, v10);
    return rf_particle_trace_world_contact(a1, v21, (int)lhs, a4, a5 + 1);
  }
  else
  {
    rf_vector_copy((float *)(a4 + 8), v13, source);
    *(float *)a4 = v30;
    *(_DWORD *)(a4 + 4) = 0;
    return 1;
  }
}

