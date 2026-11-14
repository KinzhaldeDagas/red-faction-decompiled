// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043DCD0 rf_blood_decal_trace_and_submit
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, corpse factory/support/drop lifecycle, fixed-stride snapshot boundaries and existing-object restoration, record24 ownership and native decal ABI): Cdecl(strengthFloat,sourcePositionVec3,traceVectorVec3), THREE DWORD stack slots; both original corpse and projectile callers push/pop12. Saved two-argument prototype omitted trace vector, which native code reads. Global662E2C false returns with no trace/RNG. Otherwise builds world-solid sweep with source position, displacement1.5*traceVector,radius0.009999999776482582,flags0,identity/zero pose,initializeByte1. Requires positive hit count and either no hit-face room or liquid predicate false at hit point. Strength bands ordered <30,<60,<125 select size0.5,0.75,1; >=125 OR NaN selects1.2. Draws shared random float in[size*.5,size*.800000011920929], uses equalXYZ scale;
// chooses one of THREE global decal bitmap entries via rand()%3. Constructs decal parameters, uses orientation from hit normal,hit position,face room,world solid,mode4 and submits through impact-decal dispatcher. No local finite/null/normalized-vector guard or defined success return; does not itself modify health or mark object deletion.
void __cdecl rf_blood_decal_trace_and_submit(float strength, const float *position, const float *trace_vector)
{
  float *v3; // eax
  float v4; // [esp+Ch] [ebp-14Ch]
  float v5; // [esp+10h] [ebp-148h]
  float v6[3]; // [esp+14h] [ebp-144h] BYREF
  float v7[3]; // [esp+20h] [ebp-138h] BYREF
  float v8[3]; // [esp+2Ch] [ebp-12Ch] BYREF
  float scaled_result[3]; // [esp+38h] [ebp-120h] BYREF
  float copy_result[3]; // [esp+44h] [ebp-114h] BYREF
  _DWORD v11[2]; // [esp+50h] [ebp-108h] BYREF
  float v12[3]; // [esp+58h] [ebp-100h] BYREF
  _BYTE v13[16]; // [esp+64h] [ebp-F4h] BYREF
  int v14; // [esp+74h] [ebp-E4h]
  float v15[3]; // [esp+78h] [ebp-E0h] BYREF
  float v16; // [esp+84h] [ebp-D4h]
  char v17[4]; // [esp+88h] [ebp-D0h] BYREF
  float v18[3]; // [esp+8Ch] [ebp-CCh] BYREF
  float v19[9]; // [esp+98h] [ebp-C0h] BYREF
  float destination[3]; // [esp+BCh] [ebp-9Ch] BYREF
  float v21[12]; // [esp+C8h] [ebp-90h] BYREF
  float v22[3]; // [esp+F8h] [ebp-60h] BYREF
  float v23[9]; // [esp+104h] [ebp-54h] BYREF
  float v24[11]; // [esp+128h] [ebp-30h] BYREF
  float v25; // [esp+154h] [ebp-4h]

  if ( dword_662E2C )
  {
    rf_solid_collision_query_construct_clear_face_hint(v17);
    rf_vector_copy(destination, copy_result, position);
    v3 = rf_vector_multiply_scalar(trace_vector, scaled_result, 1.5);
    rf_vector_copy(v21, v8, v3);
    v21[3] = 0.0099999998;
    v21[4] = 0.0;
    rf_vector3_zero_return_destination(v18);
    rf_identity_orientation_matrix(v19);
    rf_solid_collision_result_construct_noop((int)v11);
    rf_world_collision_sweep((char *)rf_world_solid, (int)v17, (int)v11, 1);
    if ( v11[0] > 0 && (!*(_DWORD *)(v14 + 68) || !rf_liquid_room_contains_point(*(_DWORD *)(v14 + 68), (int)v12)) )
    {
      if ( strength >= 30.0 )
      {
        if ( strength >= 60.0 )
        {
          if ( strength >= 125.0 )
            v16 = 1.2;
          else
            v16 = 1.0;
        }
        else
        {
          v16 = 0.75;
        }
      }
      else
      {
        v16 = 0.5;
      }
      v5 = v16 * 0.800000011920929;
      v4 = v16 * 0.5;
      v25 = rf_random_float_range(v4, v5);
      rf_vector3_set_components_return_destination(v15, v25, v25, v25);
      rf_decal_parameter_record_construct((int)v22);
      LODWORD(v24[3]) = unk_6E6258[rand() % 3];
      LODWORD(v24[6]) = 4;
      rf_orientation_matrix_from_direction(v23, (int)v13);
      rf_vector_copy(v22, v7, v12);
      v24[4] = *(float *)(v14 + 68);
      LODWORD(v24[8]) = rf_world_solid;
      rf_vector_copy(v24, v6, v15);
      rf_impact_decal_world_submit((int)v22);
    }
  }
}

