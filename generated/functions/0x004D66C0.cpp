// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D66C0 rf_entity_predict_axis_angle_from_angular_state
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion integration, selected-row transforms, angular/tensor updates, contact velocity response and x87 gates): Cdecl entity. Physics flag424 bit0x01000000 skips input/torque integration but STILL predicts rotation from saved angular state. Otherwise selected entities (local/related predicate,entity1312==4/3,or1312==2 AND1364==1) update angular348 about current row264. Input=1804;for local jeep multiply by abs(dot(velocity324,current row276))/2 only for ORDERED speed in[0.5,2),zero if ordered<0.5,otherwise leave input (NaN leaves it). Gain=1-exp(float(dt/float((class96/class100)/log(0.05))));desired=class96*input/entity172. Adds row264*(desired-dot(row264,348))*gain;sets2184X=1800*class100*dt only on selected path. Unless integration skipped,adds torque372*dt to348 and clears372. Always copies348
// to336,inverse-rotates336 by matrix192,forms axis=336*dt then inverse-rotates by current252;only ordered length>0 normalizes axis. Predicted288=axisAngle(axis,length)*current252,then repairs forward basis. No dt/coefficient/172 denominator,finite or pointer guard;current252/common72/tensor unchanged.
int __cdecl rf_entity_predict_axis_angle_from_angular_state(int a1)
{
  float *v1; // eax
  float *v2; // eax
  float *v3; // eax
  float scalar; // [esp+4h] [ebp-C0h]
  float v6; // [esp+8h] [ebp-BCh]
  float v7; // [esp+14h] [ebp-B0h]
  float v8[9]; // [esp+18h] [ebp-ACh] BYREF
  float v9[3]; // [esp+3Ch] [ebp-88h] BYREF
  float v10[3]; // [esp+48h] [ebp-7Ch] BYREF
  float copy_result[3]; // [esp+54h] [ebp-70h] BYREF
  float v12[3]; // [esp+60h] [ebp-64h] BYREF
  float v13; // [esp+6Ch] [ebp-58h]
  float scaled_result[3]; // [esp+70h] [ebp-54h] BYREF
  float v15; // [esp+7Ch] [ebp-48h]
  float v16; // [esp+80h] [ebp-44h]
  float v17; // [esp+84h] [ebp-40h]
  float v18; // [esp+88h] [ebp-3Ch]
  float v19; // [esp+8Ch] [ebp-38h]
  float v20[9]; // [esp+90h] [ebp-34h] BYREF
  float destination; // [esp+B4h] [ebp-10h] BYREF
  float v22; // [esp+B8h] [ebp-Ch]
  float v23; // [esp+BCh] [ebp-8h]
  float v24; // [esp+C0h] [ebp-4h]

  rf_vector3_default_construct_noop(&destination);
  if ( ((unsigned int)&unk_1000000 & *(_DWORD *)(a1 + 424)) == 0 )
  {
    if ( rf_entity_matches_local_player_or_related_handle(a1)
      || *(_DWORD *)(a1 + 1312) == 4
      || *(_DWORD *)(a1 + 1312) == 3
      || *(_DWORD *)(a1 + 1312) == 2 && *(_DWORD *)(a1 + 1364) == 1 )
    {
      v15 = *(float *)(a1 + 1804);
      if ( rf_entity_has_jeep_flag(a1) && rf_entity_matches_local_player_or_related_handle(a1) )
      {
        v13 = rf_vector_dot((float *)(a1 + 324), (float *)(a1 + 276));
        v7 = fabs(v13);
        v13 = v7;
        if ( v7 >= 0.5 )
        {
          if ( v13 < 2.0 )
            v15 = v13 / 2.0 * v15;
        }
        else
        {
          v15 = 0.0;
        }
      }
      v16 = *(float *)(*(_DWORD *)(a1 + 660) + 96) / *(float *)(*(_DWORD *)(a1 + 660) + 100);
      v18 = v16 / log(0.05);
      v6 = *(float *)(a1 + 432) / v18;
      v16 = 1.0 - rf_exp_float(v6);
      v17 = *(float *)(*(_DWORD *)(a1 + 660) + 96) * v15 / *(float *)(a1 + 172);
      v19 = rf_vector_dot((float *)(a1 + 264), (float *)(a1 + 348));
      scalar = (v17 - v19) * v16;
      rf_vector_multiply_scalar((const float *)(a1 + 264), scaled_result, scalar);
      rf_vector_accumulate((float *)(a1 + 348), scaled_result);
      *(float *)(a1 + 2184) = *(float *)(a1 + 1800) * *(float *)(*(_DWORD *)(a1 + 660) + 100) * *(float *)(a1 + 432);
    }
    v1 = rf_vector_multiply_scalar((const float *)(a1 + 372), v12, *(float *)(a1 + 432));
    rf_vector_accumulate((float *)(a1 + 348), v1);
    rf_vector3_zero_return_destination((float *)(a1 + 372));
  }
  rf_vector_copy((float *)(a1 + 336), copy_result, (const float *)(a1 + 348));
  rf_matrix3_inverse_rotate_vector((float *)(a1 + 336), (float *)(a1 + 192));
  v2 = rf_vector_multiply_scalar((const float *)(a1 + 336), v10, *(float *)(a1 + 432));
  rf_vector_copy(&destination, v9, v2);
  rf_matrix3_inverse_rotate_vector(&destination, (float *)(a1 + 252));
  v24 = rf_vector3_length(&destination);
  if ( v24 > 0.0 )
  {
    destination = destination / v24;
    v22 = v22 / v24;
    v23 = v23 / v24;
  }
  rf_matrix3_construct_from_axis_angle((int)v20, &destination, v24);
  v3 = rf_matrix3_argument_times_receiver_to_output((const float *)(a1 + 252), v8, v20);
  rf_matrix3_copy((float *)(a1 + 288), v3);
  return rf_matrix3_rebuild_basis_from_forward_in_place((char *)(a1 + 288));
}

