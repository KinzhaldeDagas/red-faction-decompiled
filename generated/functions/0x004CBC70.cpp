// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CBC70 rf_particle_move_and_resolve_contact
// UNREALRED VERIFIED [combat-particle-liquid-handoff-20261104]: Liquid hit clears particle eligibilitybit0x400 permanently at4CBDD3..4CBDE1. Per-frame response/contactbit0x8000 is set only in response branch4CBED9; collide_and_die without explode instead writesage=life and returns before that bit, leaving retirement to next update. Response includes tangential secondary trace; generic hit=true is not complete parity. Liquid tracing depends on room/portal ownership4CC4E0/4CC810 and retained face containment, not solely roomAABB/waterheight.
// UNREALRED VERIFIED [combat-particle-contact-20261104]: Response branch keeps hard-contact position at old origin until tangent retrace; liquid branch first moves to entry point. Initial normal n and speed s=-dot(v,n) define correction c=n*s and tangent v+c. Retrace can replace result normal; on miss position becomes tangent endpoint and prior normal survives. Bounce b=nibble/16 is replaced by b/r only for strict 0<r<1, r=-(s*b)/(dot(resultNormal,static(0,-9.8,0))*dt). Add (1+b)*c - squared-stick*tangent. Fragment velocity uses original decoded bounce, not adjusted b. collide_and_die writes age=life after fragments/response; without explode it bypasses response/contactbit entirely. Pool update still applies later forces/color; unlink is next age gate.
void __cdecl rf_particle_move_and_resolve_contact(int a1, float a2)
{
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  int v6; // ecx
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  double v12; // st7
  int v13; // [esp+0h] [ebp-174h] BYREF
  int v14; // [esp+4h] [ebp-170h]
  int v15; // [esp+8h] [ebp-16Ch]
  float scalar; // [esp+Ch] [ebp-168h]
  float v17; // [esp+10h] [ebp-164h]
  float v18; // [esp+14h] [ebp-160h]
  int v19; // [esp+18h] [ebp-15Ch]
  float v20[5]; // [esp+1Ch] [ebp-158h] BYREF
  float v21[3]; // [esp+30h] [ebp-144h] BYREF
  float v22[3]; // [esp+3Ch] [ebp-138h] BYREF
  int v23[3]; // [esp+48h] [ebp-12Ch] BYREF
  float v24[3]; // [esp+54h] [ebp-120h] BYREF
  float v25[3]; // [esp+60h] [ebp-114h] BYREF
  float v26[3]; // [esp+6Ch] [ebp-108h] BYREF
  float v27[3]; // [esp+78h] [ebp-FCh] BYREF
  float v28[3]; // [esp+84h] [ebp-F0h] BYREF
  float scaled_result[3]; // [esp+90h] [ebp-E4h] BYREF
  float copy_result[3]; // [esp+9Ch] [ebp-D8h] BYREF
  int v31[3]; // [esp+A8h] [ebp-CCh] BYREF
  float v32[3]; // [esp+B4h] [ebp-C0h] BYREF
  float v33; // [esp+C0h] [ebp-B4h] BYREF
  int v34; // [esp+C4h] [ebp-B0h] BYREF
  int v35[3]; // [esp+C8h] [ebp-ACh] BYREF
  float out_vector[3]; // [esp+D4h] [ebp-A0h] BYREF
  int i; // [esp+E0h] [ebp-94h]
  char *v38; // [esp+E4h] [ebp-90h]
  float v39; // [esp+E8h] [ebp-8Ch]
  float source[3]; // [esp+ECh] [ebp-88h] BYREF
  int v41; // [esp+F8h] [ebp-7Ch]
  bool v42; // [esp+FFh] [ebp-75h]
  float sum_result[3]; // [esp+100h] [ebp-74h] BYREF
  int v44; // [esp+10Ch] [ebp-68h]
  float v45; // [esp+110h] [ebp-64h]
  float v46; // [esp+114h] [ebp-60h]
  float v47[3]; // [esp+118h] [ebp-5Ch] BYREF
  float v48; // [esp+124h] [ebp-50h]
  float v49; // [esp+128h] [ebp-4Ch]
  char v50; // [esp+12Fh] [ebp-45h]
  float rhs[3]; // [esp+130h] [ebp-44h] BYREF
  float v52[3]; // [esp+13Ch] [ebp-38h] BYREF
  float v53; // [esp+148h] [ebp-2Ch] BYREF
  int v54; // [esp+14Ch] [ebp-28h] BYREF
  float vector[3]; // [esp+150h] [ebp-24h] BYREF
  float lhs[3]; // [esp+15Ch] [ebp-18h] BYREF
  float destination[3]; // [esp+168h] [ebp-Ch] BYREF

  rf_geomod_intersection24_construct_noop((char *)&v53);
  rf_vector3_default_construct_noop(destination);
  rf_vector3_default_construct_noop(v52);
  if ( unk_8377D8 )
  {
    rf_vector_multiply_scalar((const float *)(a1 + 24), rhs, a2);
    rf_vector_add((const float *)(a1 + 12), lhs, rhs);
    if ( rf_particle_trace_world_contact(a1, (float *)(a1 + 12), (int)lhs, (int)&v53, 0) )
    {
      v50 = 0;
      if ( (*(_DWORD *)(a1 + 88) & 0x20) != 0 )
      {
        v2 = rf_vector_subtract(lhs, out_vector, (const float *)(a1 + 12));
        v3 = rf_vector_scale((float *)v35, v53, v2);
        rf_vector_add((const float *)(a1 + 12), sum_result, v3);
        v44 = rf_object_resolve_handle(*(_DWORD *)(a1 + 8));
        if ( v44 )
          v19 = *(_DWORD *)(v44 + 32);
        else
          v19 = -1;
        v34 = v19;
        v33 = *(float *)(a1 + 52) - *(float *)(a1 + 36);
        (*(void (__cdecl **)(float *, int, float *, float *, int *, int *))(a1 + 96))(
          sum_result,
          a1 + 24,
          vector,
          &v33,
          &v54,
          &v34);
      }
      if ( v54 )
      {
        *(_DWORD *)(a1 + 88) &= ~0x400u;
        if ( *(float *)(a1 + 56) >= 0.800000011920929 )
          v41 = unk_90B824;
        else
          v41 = unk_90B830;
        v4 = rf_vector_subtract(lhs, v32, (const float *)(a1 + 12));
        v5 = rf_vector_scale((float *)v31, v53, v4);
        rf_vector_add((const float *)(a1 + 12), source, v5);
        v6 = *(_DWORD *)(a1 + 88) & 0x1000;
        v42 = v6 != 0;
        LODWORD(scalar) = v6 != 0;
        v15 = 0;
        v14 = -1;
        v13 = v6;
        rf_vclip_spawn_runtime_effect(v41, *(_DWORD *)(a1 + 100), 0, (int)source, *(float *)(a1 + 56), -1, 0, v6 != 0);
        rf_vector_copy((float *)(a1 + 12), copy_result, source);
        v50 = 1;
      }
      if ( (*(_DWORD *)(a1 + 88) & 0x800) == 0 || (*(_DWORD *)(a1 + 88) & 0x80) != 0 )
      {
        *(_DWORD *)(a1 + 88) |= 0x8000u;
        v49 = -rf_vector_dot((float *)(a1 + 24), vector);
        v7 = rf_vector_multiply_scalar(vector, scaled_result, v49);
        rf_vector_copy(destination, v28, v7);
        rf_vector_add((const float *)(a1 + 24), v47, destination);
        v8 = rf_vector_multiply_scalar(v47, v27, a2);
        v9 = rf_vector_add((const float *)(a1 + 12), v26, v8);
        rf_vector_copy(lhs, v25, v9);
        if ( !rf_particle_trace_world_contact(a1, (float *)(a1 + 12), (int)lhs, (int)&v53, 0) )
          rf_vector_copy((float *)(a1 + 12), v24, lhs);
        v45 = rf_vector_dot(vector, flt_8377F4);
        v46 = rf_particle_decode_bounciness(a1);
        v48 = -(v49 * v46) / (v45 * a2);
        if ( v48 > 0.0 && v48 < 1.0 )
          v46 = v46 / v48;
        v18 = v46 + 1.0;
        v10 = rf_vector_scale((float *)v23, v18, destination);
        rf_vector_copy(v52, v22, v10);
        if ( (int)((unsigned int)&unk_F00000 & *(_DWORD *)(a1 + 88)) > 0 )
        {
          scalar = rf_particle_decode_stickiness(a1);
          v11 = rf_vector_multiply_scalar(v47, v21, scalar);
          rf_vector_subtract_in_place(v52, v11);
        }
        rf_vector_accumulate((float *)(a1 + 24), v52);
        if ( (*(_DWORD *)(a1 + 88) & 0x80) != 0 )
        {
          if ( *(float *)(a1 + 56) <= 0.1000000014901161 )
          {
            *(_DWORD *)(a1 + 88) &= ~0x80u;
          }
          else if ( v49 > 1.0 )
          {
            *(float *)(a1 + 56) = *(float *)(a1 + 56) * 0.75;
            v38 = (char *)&unk_866600 + 252 * *(char *)(a1 + 80);
            v39 = rf_random_float_range(1.5, 3.5);
            for ( i = 0; *((_DWORD *)v38 + 62) < *((_DWORD *)v38 + 1) && v39 > (double)i; ++i )
            {
              scalar = 0.5;
              rf_vector3_copy_return_destination((float *)&v13, vector);
              rf_random_unit_vector_in_cone(v52, *(float *)&v13, *(float *)&v14, *(float *)&v15, scalar);
              v12 = rf_particle_decode_bounciness(a1);
              v17 = v12 * v49;
              rf_vector3_scale_in_place_return_self(v52, v17);
              scalar = 0.75;
              rf_vector3_copy_return_destination((float *)&v13, v52);
              rf_particle_spawn_collision_fragment(a1, v13, v14, v15, scalar);
            }
          }
        }
        if ( (*(_DWORD *)(a1 + 88) & 0x800) != 0 )
          *(float *)(a1 + 36) = *(float *)(a1 + 52);
      }
      else
      {
        *(float *)(a1 + 36) = *(float *)(a1 + 52);
      }
    }
    else
    {
      rf_vector_copy((float *)(a1 + 12), v20, lhs);
    }
  }
  else
  {
    *(_DWORD *)(a1 + 88) &= ~0x10u;
  }
}

