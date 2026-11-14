// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F7780 rf_mission_event_create_at_position
// UNREALRED VERIFIED [event-registry-crc-20261028]: CORRECTION superseding the prior hud-world-targets comment: caller argument2 is EVENT SUBTYPE, not common-object type. Signed guards reject subtype<0 or>=90. Calls rf_object_create with fixed common type6, supplied subtype, ID-1, identity orientation, caller position and flags0x10001. Converts common pointer C to E=C-4; on success clears E+688, writes subtype E+656, appends E to event registry0x90B0E0. Returns E or0. RFL target-marker caller using subtype0x1B does not make common type0x1B.
int __cdecl rf_mission_event_create_at_position(float *source, unsigned int a2)
{
  float *v3; // eax
  const float *v4; // eax
  float *v5; // [esp+Ch] [ebp-118h]
  float *v6; // [esp+10h] [ebp-114h]
  int v7; // [esp+18h] [ebp-10Ch]
  float *v8; // [esp+1Ch] [ebp-108h]
  int v9; // [esp+20h] [ebp-104h]
  float v10[3]; // [esp+28h] [ebp-FCh] BYREF
  float v11[3]; // [esp+34h] [ebp-F0h] BYREF
  float v12[3]; // [esp+40h] [ebp-E4h] BYREF
  _BYTE v13[36]; // [esp+4Ch] [ebp-D8h] BYREF
  float copy_result[3]; // [esp+70h] [ebp-B4h] BYREF
  int v15; // [esp+7Ch] [ebp-A8h]
  void *v16[38]; // [esp+80h] [ebp-A4h] BYREF
  int v17; // [esp+120h] [ebp-4h]

  if ( a2 >= 0x5A )
    return 0;
  rf_object_setup152_construct_members((char *)v16);
  v17 = 0;
  memset(v16, 0, sizeof(v16));
  v16[0] = nullptr;
  v16[2] = nullptr;
  *(float *)&v16[5] = 1.0;
  *(float *)&v16[33] = 1.0;
  rf_vector_copy((float *)&v16[15], copy_result, source);
  v6 = rf_vector3_set_components_return_destination(v12, 0.0, 0.0, 1.0);
  v5 = rf_vector3_set_components_return_destination(v11, 0.0, 1.0, 0.0);
  v3 = rf_vector3_set_components_return_destination(v10, 1.0, 0.0, 0.0);
  v4 = (const float *)rf_matrix3_construct_from_three_rows((int)v13, v3, v5, v6);
  rf_matrix3_copy((float *)&v16[18], v4);
  v16[37] = nullptr;
  v8 = rf_object_create(6, a2, -1, (int)v16, 65537, nullptr);
  if ( v8 )
    v7 = (int)(v8 - 1);
  else
    v7 = 0;
  v15 = v7;
  if ( v7 )
  {
    *(_DWORD *)(v15 + 688) = 0;
    *(_DWORD *)(v15 + 656) = a2;
    rf_pointer_array_append_dword(unk_90B0E0, v15);
    v9 = v15;
    v17 = -1;
    rf_object_setup152_destroy_array_backing(v16);
    return v9;
  }
  else
  {
    v17 = -1;
    rf_object_setup152_destroy_array_backing(v16);
    return 0;
  }
}

