// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D7200 rf_entity_predict_traction_drag_and_gravity
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion integration, selected-row transforms, angular/tensor updates, contact velocity response and x87 gates): Cdecl entity. Initializes local D0;flag424 bit0x01000000 skips velocity update but still predicts position. If material4992!=-1,subtracts current row252*dot(velocity,row252)*traction*0.5*dt from velocity. Only ORDERED current rowY268>0.8500000238418579 enters traction-drive path: D starts(0,0,input1820),rotated by current252. If velocity exactly nonzero,normalizes it unchecked;when dot(unitV,D)<=0 ORDERED ONLY,multiplies velocity by1-(2-dot)*dt. Then scales D byclass92*traction*rowY ONLY on nonzero-velocity path;exactzero leaves rotated unscaled input. Other slope values including NaN multiply velocity by1-3*dt. Next flags124 bit0x80000 subtracts velocity*(2*float140/scalar152) from D regardless
// material;otherwise valid material subtracts velocity*(float140/scalar152);no material and no bit skips drag. D.y-=gravity;D+=force360/scalar152;D*=dt;velocity+=D. Final240=current228+(UPDATED velocity+extra2208)*dt-D*(0.5*dt*dt). D is delta velocity here,not acceleration;no clamp of damping factors or finite/zero denominators,force not cleared here.
float *__cdecl rf_entity_predict_traction_drag_and_gravity(int a1)
{
  float *v1; // eax
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float v10; // [esp+0h] [ebp-C0h]
  float scalar; // [esp+8h] [ebp-B8h]
  float *scalara; // [esp+8h] [ebp-B8h]
  float v13; // [esp+Ch] [ebp-B4h]
  float v14; // [esp+10h] [ebp-B0h]
  float v15; // [esp+14h] [ebp-ACh]
  float v16; // [esp+18h] [ebp-A8h]
  float v17; // [esp+1Ch] [ebp-A4h]
  float v18; // [esp+20h] [ebp-A0h]
  float copy_result[3]; // [esp+24h] [ebp-9Ch] BYREF
  float out_vector[3]; // [esp+30h] [ebp-90h] BYREF
  float v21[3]; // [esp+3Ch] [ebp-84h] BYREF
  float v22[3]; // [esp+48h] [ebp-78h] BYREF
  float v23[3]; // [esp+54h] [ebp-6Ch] BYREF
  float sum_result[3]; // [esp+60h] [ebp-60h] BYREF
  int v25[3]; // [esp+6Ch] [ebp-54h] BYREF
  int v26[3]; // [esp+78h] [ebp-48h] BYREF
  int v27[3]; // [esp+84h] [ebp-3Ch] BYREF
  _BYTE v28[12]; // [esp+90h] [ebp-30h] BYREF
  float v29; // [esp+9Ch] [ebp-24h]
  float scaled_result[3]; // [esp+A0h] [ebp-20h] BYREF
  float v31; // [esp+ACh] [ebp-14h]
  float v32; // [esp+B0h] [ebp-10h]
  float vector; // [esp+B4h] [ebp-Ch] BYREF
  float v34; // [esp+B8h] [ebp-8h]
  float v35; // [esp+BCh] [ebp-4h]

  rf_vector3_set_components_return_destination(&vector, 0.0, 0.0, 0.0);
  if ( ((unsigned int)&unk_1000000 & *(_DWORD *)(a1 + 424)) == 0 )
  {
    if ( *(_DWORD *)(a1 + 4992) != -1 )
    {
      scalar = rf_vector_dot((float *)(a1 + 324), (float *)(a1 + 252));
      rf_vector_multiply_scalar((const float *)(a1 + 252), scaled_result, scalar);
      v32 = rf_material_traction_get(*(_DWORD *)(a1 + 4992));
      v18 = v32 * 0.5 * *(float *)(a1 + 432);
      rf_vector3_scale_in_place_return_self(scaled_result, v18);
      rf_vector_subtract_in_place((float *)(a1 + 324), scaled_result);
      if ( *(float *)(a1 + 268) <= 0.8500000238418579 )
      {
        v16 = 1.0 - *(float *)(a1 + 432) * 3.0;
        rf_vector3_scale_in_place_return_self((float *)(a1 + 324), v16);
      }
      else
      {
        v31 = *(float *)(*(_DWORD *)(a1 + 660) + 92) * v32 * *(float *)(a1 + 268);
        v35 = *(float *)(a1 + 1820);
        rf_vector_rotate_by_matrix3(&vector, (float *)(a1 + 252));
        if ( !rf_vector3_is_exact_zero((float *)(a1 + 324)) )
        {
          v1 = (float *)rf_vector3_normalized_copy_unchecked((float *)(a1 + 324), (int)v28);
          v29 = rf_vector_dot(v1, &vector);
          if ( v29 <= 0.0 )
          {
            v17 = 1.0 - (2.0 - v29) * *(float *)(a1 + 432);
            rf_vector3_scale_in_place_return_self((float *)(a1 + 324), v17);
          }
          rf_vector3_scale_in_place_return_self(&vector, v31);
        }
      }
    }
    if ( (*(_DWORD *)(a1 + 124) & 0x80000) != 0 )
    {
      v15 = 2.0 * *(float *)(a1 + 140) / *(float *)(a1 + 152);
      v2 = rf_vector_scale((float *)v27, v15, (float *)(a1 + 324));
      rf_vector_subtract_in_place(&vector, v2);
    }
    else if ( *(_DWORD *)(a1 + 4992) != -1 )
    {
      v14 = 1.0 * *(float *)(a1 + 140) / *(float *)(a1 + 152);
      v3 = rf_vector_scale((float *)v26, v14, (float *)(a1 + 324));
      rf_vector_subtract_in_place(&vector, v3);
    }
    v34 = v34 - rf_physics_gravity_acceleration;
    v4 = rf_vector_divide((float *)(a1 + 360), (float *)v25, *(float *)(a1 + 152));
    rf_vector_accumulate(&vector, v4);
    rf_vector3_scale_in_place_return_self(&vector, *(float *)(a1 + 432));
    rf_vector_accumulate((float *)(a1 + 324), &vector);
  }
  v13 = *(float *)(a1 + 432) * 0.5 * *(float *)(a1 + 432);
  scalara = rf_vector_multiply_scalar(&vector, v21, v13);
  v10 = *(float *)(a1 + 432);
  v5 = rf_vector_add((const float *)(a1 + 324), sum_result, (const float *)(a1 + 2208));
  v6 = rf_vector_multiply_scalar(v5, v23, v10);
  v7 = rf_vector_add((const float *)(a1 + 228), v22, v6);
  v8 = rf_vector_subtract(v7, out_vector, scalara);
  return rf_vector_copy((float *)(a1 + 240), copy_result, v8);
}

