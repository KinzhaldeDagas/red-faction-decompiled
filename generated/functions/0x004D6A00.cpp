// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D6A00 rf_entity_predict_velocity_with_exponential_control
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion integration, selected-row transforms, angular/tensor updates, contact velocity response and x87 gates): Cdecl entity. Initializes deltaV0;flag424 bit0x01000000 skips velocity update but still predicts position. Otherwise tau=2240/class92;current descriptor run1 or apc5 uses traction(material4992) divisor as well,and multiplayer substitutes global87BF44 for class92. Gain=1-exp(float(dt/float(tau/log(0.05)))). Transforms local input1812 through selected-row helper4457E0 with its THREE arguments. Grounded predicate438010: d=dot(normal448,global87BF48);ordered d==0 uses transformed input directly;otherwise tangent=input-N*dot(N,input),q=tangent/d,h=dot(q,global87BF48),and uses original input when h<0 OR unordered,else tangent*(1-h*h). Non-grounded uses transformed input. Only ordered length>1 normalizes
// selected direction;scale by2240. deltaV=(desired-velocity324)*gain + (force360/scalar152)*dt,then velocity+=deltaV. Final prediction240=current228+(UPDATED velocity324+extra2208)*dt-deltaV*(0.5*dt*dt). The correction uses deltaV,not acceleration;do not simplify to conventional constant-acceleration formula. Several intermediates roundedF32. No dt/tau/material/scalar/normal/finite guards;does not clear force360 here.
float *__cdecl rf_entity_predict_velocity_with_exponential_control(int entity)
{
  float *v1; // eax
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  float v15; // [esp+0h] [ebp-188h]
  float v16; // [esp+4h] [ebp-184h]
  float scalar; // [esp+8h] [ebp-180h]
  float scalara; // [esp+8h] [ebp-180h]
  float *scalarb; // [esp+8h] [ebp-180h]
  float v20; // [esp+Ch] [ebp-17Ch]
  float v21; // [esp+10h] [ebp-178h]
  double v22; // [esp+1Ch] [ebp-16Ch]
  double v23; // [esp+24h] [ebp-164h]
  float v24[3]; // [esp+2Ch] [ebp-15Ch] BYREF
  float v25[3]; // [esp+38h] [ebp-150h] BYREF
  float v26[3]; // [esp+44h] [ebp-144h] BYREF
  float v27[3]; // [esp+50h] [ebp-138h] BYREF
  float v28[3]; // [esp+5Ch] [ebp-12Ch] BYREF
  float sum_result[3]; // [esp+68h] [ebp-120h] BYREF
  float v30[3]; // [esp+74h] [ebp-114h] BYREF
  int v31[3]; // [esp+80h] [ebp-108h] BYREF
  float v32[3]; // [esp+8Ch] [ebp-FCh] BYREF
  float v33[3]; // [esp+98h] [ebp-F0h] BYREF
  float v34[3]; // [esp+A4h] [ebp-E4h] BYREF
  float v35[3]; // [esp+B0h] [ebp-D8h] BYREF
  float v36[3]; // [esp+BCh] [ebp-CCh] BYREF
  float v37[3]; // [esp+C8h] [ebp-C0h] BYREF
  float scaled_result[3]; // [esp+D4h] [ebp-B4h] BYREF
  float v39[3]; // [esp+E0h] [ebp-A8h] BYREF
  int v40[3]; // [esp+ECh] [ebp-9Ch] BYREF
  float v41[3]; // [esp+F8h] [ebp-90h] BYREF
  float out_vector[3]; // [esp+104h] [ebp-84h] BYREF
  int v43[3]; // [esp+110h] [ebp-78h] BYREF
  float v44[3]; // [esp+11Ch] [ebp-6Ch] BYREF
  float v45[3]; // [esp+128h] [ebp-60h] BYREF
  float v46[3]; // [esp+134h] [ebp-54h] BYREF
  float copy_result[3]; // [esp+140h] [ebp-48h] BYREF
  float v48; // [esp+14Ch] [ebp-3Ch]
  float v49; // [esp+150h] [ebp-38h]
  float v50; // [esp+154h] [ebp-34h]
  float v51; // [esp+158h] [ebp-30h]
  float v52; // [esp+15Ch] [ebp-2Ch]
  float destination[3]; // [esp+160h] [ebp-28h] BYREF
  float vector[3]; // [esp+16Ch] [ebp-1Ch] BYREF
  float v55; // [esp+178h] [ebp-10h]
  float lhs[3]; // [esp+17Ch] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(vector);
  rf_vector3_default_construct_noop(lhs);
  rf_vector3_set_components_return_destination(destination, 0.0, 0.0, 0.0);
  if ( ((unsigned int)&unk_1000000 & *(_DWORD *)(entity + 424)) == 0 )
  {
    if ( sub_438010(entity) )
    {
      if ( rf_multiplayer_runtime_mode )
      {
        v23 = *(float *)(entity + 2240) / unk_87BF44;
        v51 = v23 / rf_material_traction_get(*(_DWORD *)(entity + 4992));
      }
      else
      {
        v22 = *(float *)(entity + 2240) / *(float *)(*(_DWORD *)(entity + 660) + 92);
        v51 = v22 / rf_material_traction_get(*(_DWORD *)(entity + 4992));
      }
    }
    else
    {
      v51 = *(float *)(entity + 2240) / *(float *)(*(_DWORD *)(entity + 660) + 92);
    }
    v55 = v51 / log(0.05);
    v21 = *(float *)(entity + 432) / v55;
    v51 = 1.0 - rf_exp_float(v21);
    rf_vector_copy(lhs, copy_result, (const float *)(entity + 1812));
    v1 = rf_entity_transform_motion_vector_by_selected_rows(v46, entity, lhs);
    rf_vector_copy(lhs, v45, v1);
    if ( sub_438010(entity) )
    {
      v50 = rf_vector_dot((float *)(entity + 448), &flt_87BF48);
      if ( v50 == 0.0 )
      {
        rf_vector_copy(destination, v44, lhs);
      }
      else
      {
        v16 = rf_vector_dot((float *)(entity + 448), lhs);
        v2 = rf_vector_scale((float *)v43, v16, (float *)(entity + 448));
        v3 = rf_vector_subtract(lhs, out_vector, v2);
        rf_vector_copy(vector, v41, v3);
        v4 = rf_vector_divide(vector, (float *)v40, v50);
        rf_vector_copy(destination, v39, v4);
        v49 = rf_vector_dot(destination, &flt_87BF48);
        if ( v49 < 0.0 )
        {
          rf_vector_copy(destination, v36, lhs);
        }
        else
        {
          v48 = 1.0 - v49 * v49;
          v5 = rf_vector_multiply_scalar(vector, scaled_result, v48);
          rf_vector_copy(destination, v37, v5);
        }
      }
    }
    else
    {
      rf_vector_copy(destination, v35, lhs);
    }
    v52 = rf_vector3_length(destination);
    if ( v52 > 1.0 )
      rf_vector3_divide_in_place_reciprocal(destination, v52);
    rf_vector3_scale_in_place_return_self(destination, *(float *)(entity + 2240));
    scalar = v51;
    v6 = rf_vector_subtract(destination, v34, (const float *)(entity + 324));
    v7 = rf_vector_multiply_scalar(v6, v33, scalar);
    rf_vector_copy(destination, v32, v7);
    scalara = *(float *)(entity + 432);
    v8 = rf_vector_divide((float *)(entity + 360), (float *)v31, *(float *)(entity + 152));
    v9 = rf_vector_multiply_scalar(v8, v30, scalara);
    rf_vector_accumulate(destination, v9);
    rf_vector_accumulate((float *)(entity + 324), destination);
  }
  v20 = *(float *)(entity + 432) * 0.5 * *(float *)(entity + 432);
  scalarb = rf_vector_multiply_scalar(destination, v26, v20);
  v15 = *(float *)(entity + 432);
  v10 = rf_vector_add((const float *)(entity + 324), sum_result, (const float *)(entity + 2208));
  v11 = rf_vector_multiply_scalar(v10, v28, v15);
  v12 = rf_vector_add((const float *)(entity + 228), v27, v11);
  v13 = rf_vector_subtract(v12, v25, scalarb);
  return rf_vector_copy((float *)(entity + 240), v24, v13);
}

