// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00410920 sub_410920
// UNREALRED VERIFIED [combat-steering-signature-20261112]: Cdecl second target-point pointer is PROVED by raw8B4D0C reads at4109EB/410A10 ([EBP+0xC]); entity is[EBP+8], plainRET.9 independently saved caller bodies among21 knownsites push target then entity and pop8, no contrary decoded site. Preserved existingdouble return type/name, adding only the missing argument. Target-origin selection is descriptor+20==1 OR+24==1 ->Entity7D4,otherwise currentE4. Computes/stores angular336/340 and length-caps full3-vector by class96;does not clear344 here. Only jeep/APC additionally writes normalized1800 input.
// UNREALRED VERIFIED [combat-signed-rotation-20261112]: Native no-new-steering prefix: reads class60,compares0 at4109A8..B6; only ORDERED class60<=0 returns floating0 at4109B8/BA before target pointer/origin/descriptor/dt/angle reads or angular336 writes. JP after TEST AH41 continues for orderedpositive OR unordered; do not call NaN a native disabled-turn value. This prefix does NOT zero existing angular velocity,clear targets,reset the route or cancel independent linear motion. Full positive steering then physics integration remains distinct.
// UNREALRED VERIFIED [combat-original-physics-20261112]: At410A53 the target-difference vector is normalized through411140: a rounded binary32 reciprocal1/length is formed ONCE, then each component is multiplied/stored, not three direct divisions. At410A6E the desired-right vector uses559300: ordered length>0 selects rounded reciprocal component products; zero OR unordered length writes unitX. Both helpers can differ from direct component division. With identity view, target(1,0,3),delta FLOAT32(.1),large noncapping class96, the native staged heading-rate binary32 is0x404DEB91; NaN direction reaches desired-right unitX and a zero heading against unitX while other angular/error components can remain NaN. These are native value-store facts, not host safe-normal admission.
double __cdecl sub_410920(int entity, const float *target_point)
{
  float *v3; // eax
  float *v4; // eax
  double v5; // st7
  float *v6; // eax
  float v7; // [esp+10h] [ebp-A0h]
  float v8; // [esp+14h] [ebp-9Ch]
  float v9; // [esp+18h] [ebp-98h]
  double v10; // [esp+1Ch] [ebp-94h]
  float v11[3]; // [esp+24h] [ebp-8Ch] BYREF
  int v12[3]; // [esp+30h] [ebp-80h] BYREF
  float v13[3]; // [esp+3Ch] [ebp-74h] BYREF
  float v14[3]; // [esp+48h] [ebp-68h] BYREF
  float copy_result[3]; // [esp+54h] [ebp-5Ch] BYREF
  float out_vector[3]; // [esp+60h] [ebp-50h] BYREF
  int v17; // [esp+6Ch] [ebp-44h] BYREF
  float v18; // [esp+70h] [ebp-40h]
  float v19[3]; // [esp+74h] [ebp-3Ch] BYREF
  float v20; // [esp+80h] [ebp-30h]
  float v21[3]; // [esp+84h] [ebp-2Ch] BYREF
  float destination[3]; // [esp+90h] [ebp-20h] BYREF
  int v23; // [esp+9Ch] [ebp-14h] BYREF
  float v24; // [esp+A0h] [ebp-10h]
  int v25; // [esp+ACh] [ebp-4h]

  if ( (dword_666A94 & 1) == 0 )
  {
    dword_666A94 |= 1u;
    rf_vector3_set_components_return_destination(flt_666A88, 0.0, -1.0, 0.0);
    v25 = -1;
  }
  rf_vector3_default_construct_noop(destination);
  rf_vector3_default_construct_noop(v21);
  if ( *(float *)(*(_DWORD *)(entity + 660) + 96) <= 0.0 )
    return 0.0;
  if ( *(_DWORD *)(*(_DWORD *)(entity + 2136) + 20) == 1 || *(_DWORD *)(*(_DWORD *)(entity + 2136) + 24) == 1 )
  {
    v3 = rf_vector_subtract(target_point, out_vector, (const float *)(entity + 2004));
    rf_vector_copy(destination, copy_result, v3);
  }
  else
  {
    v4 = rf_vector_subtract(target_point, v14, (const float *)(entity + 228));
    rf_vector_copy(destination, v13, v4);
  }
  *(float *)&v17 = rf_vector3_length(destination);
  if ( *(float *)&v17 == 0.0 )
    return 0.0;
  rf_vector3_divide_in_place_reciprocal(destination, *(float *)&v17);
  v21[0] = destination[2];
  v21[1] = 0.0;
  v21[2] = -destination[0];
  rf_vector_normalize(v21);
  *(float *)&v17 = rf_vector_dot(v21, (float *)(entity + 2016));
  rf_float_clamp_in_place((float *)&v17, -1.0, 1.0);
  v20 = rf_acos_float(*(float *)&v17);
  rf_vector_cross((float *)(entity + 2016), v19, v21);
  if ( v19[1] >= 0.0 )
    v5 = v20 / rf_frame_delta_seconds;
  else
    v5 = -v20 / rf_frame_delta_seconds;
  *(float *)(entity + 340) = v5;
  *(float *)&v17 = rf_vector_dot(destination, flt_666A88);
  rf_float_clamp_in_place((float *)&v17, -1.0, 1.0);
  *(float *)&v23 = rf_vector_dot((float *)(entity + 2040), flt_666A88);
  rf_float_clamp_in_place((float *)&v23, -1.0, 1.0);
  v10 = rf_acos_float(*(float *)&v17);
  v18 = v10 - rf_acos_float(*(float *)&v23);
  *(float *)(entity + 336) = v18 / rf_frame_delta_seconds;
  *(float *)&v17 = rf_vector3_length((float *)(entity + 336));
  if ( *(float *)(*(_DWORD *)(entity + 660) + 96) < (double)*(float *)&v17 )
  {
    v9 = *(float *)(*(_DWORD *)(entity + 660) + 96) / *(float *)&v17;
    rf_vector3_scale_in_place_return_self((float *)(entity + 336), v9);
  }
  v8 = fabs(v20);
  v7 = fabs(v18);
  v24 = v8 + v7;
  if ( v24 > 0.01 )
    *(float *)(entity + 1968) = *(float *)&dword_6FC428;
  if ( rf_entity_has_jeep_flag(entity) || rf_entity_class_has_contact_geomod_flag200(entity) )
  {
    v6 = rf_vector_divide((float *)(entity + 336), (float *)v12, *(float *)(*(_DWORD *)(entity + 660) + 96));
    rf_vector_copy((float *)(entity + 1800), v11, v6);
  }
  return v24;
}

