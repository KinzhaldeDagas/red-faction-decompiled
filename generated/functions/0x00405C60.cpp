// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00405C60 sub_405C60
// UNREALRED VERIFIED [combat-native-view-fov-20261112]: Additional mutable840 owner: when linked event resolves type46, facing-dot>=0.95 and requested bodyaction44 has finished, writes float-1 to entity840 at405DBD BEFORE event activation, mode2 and secondary0 writes. Unported action/event consumers prevent claiming static authored FOV is complete lifetime840 parity.
void __cdecl sub_405C60(int *a1)
{
  float *v1; // eax
  float scaled_result[3]; // [esp+Ch] [ebp-3Ch] BYREF
  int v3; // [esp+18h] [ebp-30h]
  float vector[3]; // [esp+1Ch] [ebp-2Ch] BYREF
  float out_vector[3]; // [esp+28h] [ebp-20h] BYREF
  float lhs[3]; // [esp+34h] [ebp-14h] BYREF
  int *v7; // [esp+40h] [ebp-8h]
  float v8; // [esp+44h] [ebp-4h]

  v3 = rf_mission_event_find_by_uid(a1[307]);
  if ( v3 )
  {
    if ( *(_DWORD *)(v3 + 656) == 46 )
    {
      v7 = (int *)v3;
      rf_vector3_copy_return_destination(vector, (float *)(v3 + 100));
      v1 = rf_vector_multiply_scalar(vector, scaled_result, 1000.0);
      rf_vector_add((const float *)(v3 + 64), lhs, v1);
      lhs[1] = *(float *)(*a1 + 2008);
      sub_410920(*a1, lhs);
      rf_vector_subtract(lhs, out_vector, (const float *)(*a1 + 60));
      rf_vector_normalize_reciprocal_sqrt(out_vector);
      v8 = rf_vector_dot((float *)(*a1 + 96), out_vector);
      if ( v8 >= 0.949999988079071 )
      {
        if ( (a1[332] & 0x200000) == 0 )
        {
          rf_entity_request_body_action(*a1, 0x2Cu, 1.0, 0, 1);
          a1[332] |= 0x200000u;
        }
        if ( !rf_entity_body_action_is_active(*a1, 0x2Cu) )
        {
          *(float *)(*a1 + 2112) = -1.0;
          rf_mission_event_activate(v7, -1, -1, 1);
          rf_ai_numeric_mode_write(a1, 2, -1, -1);
          rf_ai_secondary_state_write((int)a1, 0);
        }
      }
    }
  }
  else
  {
    rf_ai_numeric_mode_write(a1, 2, -1, -1);
    rf_ai_secondary_state_write((int)a1, 0);
  }
}

