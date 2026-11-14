// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00490B20 rf_lag_compensation_trace_with_temporary_poses
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, client timeout latch and registry admission, RFString-array ownership, native lag-compensation snapshot/restore asymmetry, geometry contact limits and respawn slots): 
// Cdecl(ignore/source object pointer,projectile pointer),returns final snapshot-loop count EAX on normal exit. For each slot754158+424*i up to dynamic signed count754150,resolves
// stored entity handle0. Valid entity saves bounds400/412 toslot320/332,matrices156/192 to76/112,positions228/240 to148/160,MATRIX288 to172,vectors324/336/348/360/372
// to244/256/268/280/292,flags424/428 to344/348,FLOAT432 to352,68-byte contact436 to356. Then installs sampled slot8 position intoentity228 andslot20 matrix intoentity252. Rebuilds
// bounds400..420 as sampled position +/- RAW entity radiusFLOAT120,WITHOUT positive-radius or finite guard. Does not publish common position60/orientation72 here.
// IMPORTANT asymmetry verified in native instructions: save copies entity+288 into slot+172; restore instead copies slot+208 into entity+252. Slot208 is NOT filled by this body's
// save phase; embedded constructor's matrices are no-ops,so do not invent a valid saved matrix or symmetric restoration. Matrix288 has no direct restore in this body. Other listed
// saved fields restored to matching destinations,using fresh handle resolution in same slot order. Stored model handle4 not checked/restored. Repeated handles not deduplicated. Only
// normal-flow restoration; no SEH/transaction guard around tracing and callbacks.
// Trace loop initializes previous objectNULL and geometry-contact count0. EACH iteration rereads projectile common position60 and direction96,forms endpoint=start+direction*2000.0
// with materialized float vector operations. Resets contact handleDWORD16=-1,statusDWORD20=0. Calls
// weapon_trace_character_clutter_contacts(start,end,arg0,previousObject,contact,info172,flag(info616&0x400),info1356),info=projectile660. Miss stops. Handle>=0 resolves
// previousObject and invokes piercing visitor4905B0(contact,projectile); false stops. Negative handle increments GEOMETRY counter and invokes490A00; false stops. Continues only
// geometry counter<12; object contacts do NOT increment that cap,so this is not a12-total-contact bound. Previous object preserved across geometry path. Callback mutations/damage
// outside enumerated saved fields are not rolled back. Invalid entity handles skipped both phases; count not reset after trace.
int __cdecl rf_lag_compensation_trace_with_temporary_poses(int a1, float *a2)
{
  float *v2; // eax
  float *v3; // eax
  int result; // eax
  float v5[3]; // [esp+Ch] [ebp-15Ch] BYREF
  float v6[3]; // [esp+18h] [ebp-150h] BYREF
  float v7[3]; // [esp+24h] [ebp-144h] BYREF
  float v8[3]; // [esp+30h] [ebp-138h] BYREF
  float v9[3]; // [esp+3Ch] [ebp-12Ch] BYREF
  float v10[3]; // [esp+48h] [ebp-120h] BYREF
  float v11[3]; // [esp+54h] [ebp-114h] BYREF
  float v12[3]; // [esp+60h] [ebp-108h] BYREF
  float v13[3]; // [esp+6Ch] [ebp-FCh] BYREF
  float v14[3]; // [esp+78h] [ebp-F0h] BYREF
  float sum_result[3]; // [esp+84h] [ebp-E4h] BYREF
  float scaled_result[3]; // [esp+90h] [ebp-D8h] BYREF
  float v17[3]; // [esp+9Ch] [ebp-CCh] BYREF
  float v18[3]; // [esp+A8h] [ebp-C0h] BYREF
  float v19[3]; // [esp+B4h] [ebp-B4h] BYREF
  float v20[3]; // [esp+C0h] [ebp-A8h] BYREF
  float v21[3]; // [esp+CCh] [ebp-9Ch] BYREF
  float v22[3]; // [esp+D8h] [ebp-90h] BYREF
  float v23[3]; // [esp+E4h] [ebp-84h] BYREF
  float v24[3]; // [esp+F0h] [ebp-78h] BYREF
  float v25[3]; // [esp+FCh] [ebp-6Ch] BYREF
  float v26[3]; // [esp+108h] [ebp-60h] BYREF
  float copy_result[3]; // [esp+114h] [ebp-54h] BYREF
  int v28; // [esp+120h] [ebp-48h]
  char v29; // [esp+127h] [ebp-41h]
  int v30; // [esp+128h] [ebp-40h]
  int v31; // [esp+12Ch] [ebp-3Ch]
  int v32; // [esp+130h] [ebp-38h]
  float destination[3]; // [esp+134h] [ebp-34h] BYREF
  int i; // [esp+140h] [ebp-28h]
  float v35[3]; // [esp+144h] [ebp-24h] BYREF
  int v36[4]; // [esp+150h] [ebp-18h] BYREF
  int v37; // [esp+160h] [ebp-8h]
  int v38; // [esp+164h] [ebp-4h]

  for ( i = 0; i < unk_754150; ++i )
  {
    v30 = rf_entity_resolve_handle(unk_754158[106 * i]);
    if ( v30 )
    {
      rf_vector_copy((float *)&unk_754298 + 106 * i, copy_result, (const float *)(v30 + 400));
      rf_vector_copy((float *)&unk_7542A4 + 106 * i, v26, (const float *)(v30 + 412));
      rf_matrix3_copy((float *)&unk_7541A4 + 106 * i, (const float *)(v30 + 156));
      rf_matrix3_copy((float *)&unk_7541C8 + 106 * i, (const float *)(v30 + 192));
      rf_vector_copy((float *)&unk_7541EC + 106 * i, v25, (const float *)(v30 + 228));
      rf_vector_copy((float *)&unk_7541F8 + 106 * i, v24, (const float *)(v30 + 240));
      rf_matrix3_copy((float *)&unk_754204 + 106 * i, (const float *)(v30 + 288));
      rf_vector_copy((float *)&unk_75424C + 106 * i, v23, (const float *)(v30 + 324));
      rf_vector_copy((float *)&unk_754258 + 106 * i, v22, (const float *)(v30 + 336));
      rf_vector_copy((float *)&unk_754264 + 106 * i, v21, (const float *)(v30 + 348));
      rf_vector_copy((float *)&unk_754270 + 106 * i, v20, (const float *)(v30 + 360));
      rf_vector_copy((float *)&unk_75427C + 106 * i, v19, (const float *)(v30 + 372));
      unk_7542B0[106 * i] = *(_DWORD *)(v30 + 424);
      unk_7542B4[106 * i] = *(_DWORD *)(v30 + 428);
      *((float *)&unk_7542B8 + 106 * i) = *(float *)(v30 + 432);
      rf_physics_hit_record68_copy_fields(&flt_7542BC[106 * i], (float *)(v30 + 436));
      rf_vector_copy((float *)(v30 + 228), v18, (const float *)&unk_754160 + 106 * i);
      rf_matrix3_copy((float *)(v30 + 252), (const float *)&unk_75416C + 106 * i);
      *(float *)(v30 + 400) = *(float *)(v30 + 228) - *(float *)(v30 + 120);
      *(float *)(v30 + 404) = *(float *)(v30 + 232) - *(float *)(v30 + 120);
      *(float *)(v30 + 408) = *(float *)(v30 + 236) - *(float *)(v30 + 120);
      *(float *)(v30 + 412) = *(float *)(v30 + 228) + *(float *)(v30 + 120);
      *(float *)(v30 + 416) = *(float *)(v30 + 232) + *(float *)(v30 + 120);
      *(float *)(v30 + 420) = *(float *)(v30 + 236) + *(float *)(v30 + 120);
    }
  }
  v31 = 0;
  rf_vector_prefix_construct_noop(v36);
  rf_vector3_default_construct_noop(destination);
  rf_vector3_default_construct_noop(v35);
  v32 = 0;
  do
  {
    rf_vector_copy(destination, v17, a2 + 15);
    v2 = rf_vector_multiply_scalar(a2 + 24, scaled_result, 2000.0);
    v3 = rf_vector_add(destination, sum_result, v2);
    rf_vector_copy(v35, v14, v3);
    v38 = 0;
    v37 = -1;
    v29 = (*(_DWORD *)(*((_DWORD *)a2 + 165) + 616) & 0x400) != 0;
    if ( !rf_weapon_trace_character_clutter_contacts(
            (int)destination,
            (int)v35,
            a1,
            v31,
            (int)v36,
            *(float *)(*((_DWORD *)a2 + 165) + 172),
            v29,
            *(float *)(*((_DWORD *)a2 + 165) + 1356)) )
      break;
    if ( v37 < 0 )
    {
      ++v32;
      if ( !rf_projectile_contact_continue_if_not_done((float *)v36, (int)a2) )
        break;
    }
    else
    {
      v31 = rf_object_resolve_handle(v37);
      if ( !sub_4905B0((int)v36, a2) )
        break;
    }
  }
  while ( v32 < 12 );
  for ( i = 0; ; ++i )
  {
    result = i;
    if ( i >= unk_754150 )
      break;
    v28 = rf_entity_resolve_handle(unk_754158[106 * i]);
    if ( v28 )
    {
      rf_vector_copy((float *)(v28 + 400), v13, (const float *)&unk_754298 + 106 * i);
      rf_vector_copy((float *)(v28 + 412), v12, (const float *)&unk_7542A4 + 106 * i);
      rf_matrix3_copy((float *)(v28 + 156), (const float *)&unk_7541A4 + 106 * i);
      rf_matrix3_copy((float *)(v28 + 192), (const float *)&unk_7541C8 + 106 * i);
      rf_vector_copy((float *)(v28 + 228), v11, (const float *)&unk_7541EC + 106 * i);
      rf_vector_copy((float *)(v28 + 240), v10, (const float *)&unk_7541F8 + 106 * i);
      rf_matrix3_copy((float *)(v28 + 252), (const float *)&unk_754228 + 106 * i);
      rf_vector_copy((float *)(v28 + 324), v9, (const float *)&unk_75424C + 106 * i);
      rf_vector_copy((float *)(v28 + 336), v8, (const float *)&unk_754258 + 106 * i);
      rf_vector_copy((float *)(v28 + 348), v7, (const float *)&unk_754264 + 106 * i);
      rf_vector_copy((float *)(v28 + 360), v6, (const float *)&unk_754270 + 106 * i);
      rf_vector_copy((float *)(v28 + 372), v5, (const float *)&unk_75427C + 106 * i);
      *(_DWORD *)(v28 + 424) = unk_7542B0[106 * i];
      *(_DWORD *)(v28 + 428) = unk_7542B4[106 * i];
      *(float *)(v28 + 432) = *((float *)&unk_7542B8 + 106 * i);
      rf_physics_hit_record68_copy_fields((float *)(v28 + 436), &flt_7542BC[106 * i]);
    }
  }
  return result;
}

