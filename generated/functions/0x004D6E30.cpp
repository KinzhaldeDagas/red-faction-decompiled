// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D6E30 rf_entity_predict_horizontal_acceleration_and_gravity
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion integration, selected-row transforms, angular/tensor updates, contact velocity response and x87 gates): Cdecl entity. Initializes local acceleration A0;flag424 bit0x01000000 skips velocity integration but still predicts position. Otherwise input1812*class92 is transformed by THREE-argument selected-row helper4457E0;only ORDERED class92<length caps vector magnitude. Adds transformed X/Z*(dt*global662E1C) to velocity324 X/Z ONLY. Caps horizontal speed after input using entity5256 when flag424 bit0x200000,otherwise class80;only ORDERED cap<speed scales X/Z. Then A=force360/scalar152;A.y-=global gravity. Computes an unused half-step velocity scratch;reloads same A and adds A*dt to actual velocity324. Final240=current228+(UPDATED velocity+extra2208)*dt-A*(0.5*dt*dt). A is acceleration here,unlike neighboring
// deltaV-correction routines. No own zero scalar/dt,negative cap,input or finite guard;force360 unchanged.
float *__cdecl rf_entity_predict_horizontal_acceleration_and_gravity(int entity)
{
  float *v1; // eax
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float scalar; // [esp+0h] [ebp-ECh]
  float *v11; // [esp+8h] [ebp-E4h]
  float v12; // [esp+Ch] [ebp-E0h]
  float v13; // [esp+10h] [ebp-DCh]
  float v14; // [esp+14h] [ebp-D8h]
  float v15[3]; // [esp+18h] [ebp-D4h] BYREF
  float out_vector[3]; // [esp+24h] [ebp-C8h] BYREF
  float v17[3]; // [esp+30h] [ebp-BCh] BYREF
  float v18[3]; // [esp+3Ch] [ebp-B0h] BYREF
  float v19[3]; // [esp+48h] [ebp-A4h] BYREF
  float v20[3]; // [esp+54h] [ebp-98h] BYREF
  float v21[3]; // [esp+60h] [ebp-8Ch] BYREF
  float v22[3]; // [esp+6Ch] [ebp-80h] BYREF
  float v23[3]; // [esp+78h] [ebp-74h] BYREF
  float scaled_result[3]; // [esp+84h] [ebp-68h] BYREF
  float v25[3]; // [esp+90h] [ebp-5Ch] BYREF
  float v26[3]; // [esp+9Ch] [ebp-50h] BYREF
  float v27[3]; // [esp+A8h] [ebp-44h] BYREF
  float copy_result[3]; // [esp+B4h] [ebp-38h] BYREF
  float v29; // [esp+C0h] [ebp-2Ch]
  float sum_result[4]; // [esp+C4h] [ebp-28h] BYREF
  float vector; // [esp+D4h] [ebp-18h] BYREF
  float v32; // [esp+D8h] [ebp-14h]
  float v33; // [esp+DCh] [ebp-10h]
  float destination[3]; // [esp+E0h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(destination);
  rf_vector3_set_components_return_destination(&vector, 0.0, 0.0, 0.0);
  if ( ((unsigned int)&unk_1000000 & *(_DWORD *)(entity + 424)) == 0 )
  {
    rf_vector_copy(destination, copy_result, (const float *)(entity + 1812));
    rf_vector3_scale_in_place_return_self(destination, *(float *)(*(_DWORD *)(entity + 660) + 92));
    v1 = rf_entity_transform_motion_vector_by_selected_rows(v27, entity, destination);
    rf_vector_copy(&vector, v26, v1);
    v29 = rf_vector3_length(&vector);
    if ( *(float *)(*(_DWORD *)(entity + 660) + 92) < (double)v29 )
    {
      v14 = *(float *)(*(_DWORD *)(entity + 660) + 92) / v29;
      rf_vector3_scale_in_place_return_self(&vector, v14);
    }
    sum_result[3] = *(float *)(entity + 324) * *(float *)(entity + 324)
                  + *(float *)(entity + 332) * *(float *)(entity + 332);
    v13 = *(float *)(entity + 432) * flt_662E1C;
    rf_vector3_scale_in_place_return_self(&vector, v13);
    *(float *)(entity + 324) = *(float *)(entity + 324) + vector;
    *(float *)(entity + 332) = *(float *)(entity + 332) + v33;
    v29 = *(float *)(entity + 324) * *(float *)(entity + 324) + *(float *)(entity + 332) * *(float *)(entity + 332);
    v29 = rf_sqrt_float(v29);
    if ( (*(_DWORD *)(entity + 424) & 0x200000) != 0 )
    {
      if ( *(float *)(entity + 5256) < (double)v29 )
      {
        v29 = *(float *)(entity + 5256) / v29;
        *(float *)(entity + 324) = *(float *)(entity + 324) * v29;
        *(float *)(entity + 332) = *(float *)(entity + 332) * v29;
      }
    }
    else if ( *(float *)(*(_DWORD *)(entity + 660) + 80) < (double)v29 )
    {
      v29 = *(float *)(*(_DWORD *)(entity + 660) + 80) / v29;
      *(float *)(entity + 324) = *(float *)(entity + 324) * v29;
      *(float *)(entity + 332) = *(float *)(entity + 332) * v29;
    }
    rf_vector_copy(&vector, v25, (const float *)(entity + 360));
    rf_vector3_divide_in_place_reciprocal(&vector, *(float *)(entity + 152));
    v32 = v32 - rf_physics_gravity_acceleration;
    v2 = rf_vector_multiply_scalar(&vector, scaled_result, *(float *)(entity + 432));
    v3 = rf_vector_multiply_scalar(v2, v23, 0.5);
    rf_vector_add((const float *)(entity + 324), sum_result, v3);
    rf_vector_copy(&vector, v22, (const float *)(entity + 360));
    rf_vector3_divide_in_place_reciprocal(&vector, *(float *)(entity + 152));
    v32 = v32 - rf_physics_gravity_acceleration;
    v4 = rf_vector_multiply_scalar(&vector, v21, *(float *)(entity + 432));
    rf_vector_accumulate((float *)(entity + 324), v4);
  }
  v12 = *(float *)(entity + 432) * 0.5 * *(float *)(entity + 432);
  v11 = rf_vector_multiply_scalar(&vector, v17, v12);
  scalar = *(float *)(entity + 432);
  v5 = rf_vector_add((const float *)(entity + 324), v20, (const float *)(entity + 2208));
  v6 = rf_vector_multiply_scalar(v5, v19, scalar);
  v7 = rf_vector_add((const float *)(entity + 228), v18, v6);
  v8 = rf_vector_subtract(v7, out_vector, v11);
  return rf_vector_copy((float *)(entity + 240), v15, v8);
}

