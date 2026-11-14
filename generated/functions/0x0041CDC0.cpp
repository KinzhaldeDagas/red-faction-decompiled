// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041CDC0 rf_corpse_probe_support_and_adjust_contact_velocity
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, corpse factory/support/drop lifecycle, fixed-stride snapshot boundaries and existing-object restoration, record24 ownership and native decal ABI): Cdecl corpse, AL1 for insufficient support/continued motion,0 for at least two supporting probes. Array24 count<2 returns1 without probes or velocity adjustment. Otherwise rotates each record center by current physical matrix+252 and translates by position+228, traces one unit downward with public mask128 into a shared local68-byte hit record (constructor is NO-WRITE), counting successful geometry hits. At least two hits copies LAST SUCCESSFUL output record to corpse+436 and returns0; misses leave output unchanged, so not necessarily final probe or closest contact. IMPORTANT obstruction helper writes all copied fields except DWORD+56; constructor also leaves it untouched, so
// support copy propagates an unwritten local word into contact+492. With fewer hits uses EXISTING corpse contact point+436/normal+448, not local trace record: s=float(-1.100000023841858*dot(velocity+324,normal)); r=normalize(position+228-contactPoint); q=float((1-dot(normal,r))*s). Only ordered s>0 adds normal*s then r*q to velocity, each vector operation rounding/storing natively; nonpositive/NaN s skips updates. Returns1. No state clear, null/finite/zero-direction guard or allocation.
char __cdecl rf_corpse_probe_support_and_adjust_contact_velocity(int a1)
{
  int first_dword; // eax
  float *element_address_unchecked; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  double v7; // st7
  float *v8; // eax
  float *v9; // eax
  float v10[3]; // [esp+Ch] [ebp-DCh] BYREF
  float scaled_result[3]; // [esp+18h] [ebp-D0h] BYREF
  float v12[3]; // [esp+24h] [ebp-C4h] BYREF
  float out_vector[3]; // [esp+30h] [ebp-B8h] BYREF
  float v14[3]; // [esp+3Ch] [ebp-ACh] BYREF
  float sum_result[3]; // [esp+48h] [ebp-A0h] BYREF
  float copy_result[3]; // [esp+54h] [ebp-94h] BYREF
  float v17[3]; // [esp+60h] [ebp-88h] BYREF
  float v18; // [esp+6Ch] [ebp-7Ch]
  float scalar; // [esp+70h] [ebp-78h]
  float destination[3]; // [esp+74h] [ebp-74h] BYREF
  char v21[72]; // [esp+80h] [ebp-68h] BYREF
  float rhs[3]; // [esp+C8h] [ebp-20h] BYREF
  int v23; // [esp+D4h] [ebp-14h]
  int i; // [esp+D8h] [ebp-10h]
  float v25[3]; // [esp+DCh] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(destination);
  rf_vector3_default_construct_noop(v25);
  rf_vector3_set_components_return_destination(rhs, 0.0, -1.0, 0.0);
  v23 = 0;
  rf_physics_hit_record_construct_noop(v21);
  if ( rf_receiver_get_first_dword((void *)(a1 + 388)) < 2 )
    return 1;
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword((void *)(a1 + 388));
    if ( i >= first_dword )
      break;
    element_address_unchecked = (float *)rf_array24_get_element_address_unchecked((_DWORD *)(a1 + 388), i);
    v4 = rf_matrix3_rotate_vector(element_address_unchecked, v17, (float *)(a1 + 252));
    rf_vector_copy(destination, copy_result, v4);
    rf_vector_accumulate(destination, (float *)(a1 + 228));
    v5 = rf_vector_add(destination, sum_result, rhs);
    rf_vector_copy(v25, v14, v5);
    if ( rf_geometry_segment_is_obstructed((int)destination, (int)v25, 128, (int)v21) )
      ++v23;
  }
  if ( v23 >= 2 )
  {
    rf_physics_hit_record68_copy_fields(a1 + 436, (int)v21);
    return 0;
  }
  else
  {
    scalar = rf_vector_dot((float *)(a1 + 324), (float *)(a1 + 448)) * -1.100000023841858;
    v6 = rf_vector_subtract((const float *)(a1 + 228), out_vector, (const float *)(a1 + 436));
    rf_vector_copy(rhs, v12, v6);
    rf_vector_normalize(rhs);
    v7 = rf_vector_dot((float *)(a1 + 448), rhs);
    v18 = (1.0 - v7) * scalar;
    if ( scalar > 0.0 )
    {
      v8 = rf_vector_multiply_scalar((const float *)(a1 + 448), scaled_result, scalar);
      rf_vector_accumulate((float *)(a1 + 324), v8);
      v9 = rf_vector_multiply_scalar(rhs, v10, v18);
      rf_vector_accumulate((float *)(a1 + 324), v9);
    }
    return 1;
  }
}

