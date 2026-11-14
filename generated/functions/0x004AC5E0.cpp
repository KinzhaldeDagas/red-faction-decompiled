// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AC5E0 rf_client_apply_pregame_remote_charge_payload19
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native packet19 registry/codec, x87 quantization, powerup linked nodes, entity state masks and action
// arbitration): Recovered contiguous native body4AC5E0..4ACB63 (last RET4ACB62); original descriptor19 at662A2C points here. Cdecl payload pointer; dispatcher also supplies unused
// source word, no payload length. No runtime/authority guard. Read count unsignedBYTE then exactly count records of71 bytes, fully consuming record before allocation. DWORD packet
// projectileID0,parentID4,ownerID8; float12; positionXYZ16, forwardXYZ28; parent-local positionXYZ40, parent-local forwardXYZ52; flagsDWORD64; velocity bytes68..70. Map ownerID via
// server-to-local handle delegate, build two orientations from supplied forward vectors without own normalization/finite checks. Decode signed X/Y bytes /double127 then round each
// float. If x+y compares ORDERED EQUAL0 set z=1 (including nonzero x==-y); otherwise sqrt(float(1-x*x-y*y)), no clamp. ThirdBYTE80 negates z,low7 magnitude scales vector. Create
// projectile(global remote-charge ID911C78,mappedOwner,position,orientation,0,packetProjectileID); failure skips postwrites but continues next record. On success, if wire parent!=-1
// map it (even if mapping gives-1), write parent handle+688 and copy local pose+692/+704. Always write float668, copy current world pose into fields228/252, overwrite common
// flags424, copy velocity324. Only when parent!=-1 resolve mapped parent object and if nonNULL call attach delegate AFTER all those writes. Does not reject unknown owner/parent,
// revalidate packet IDs or arm replication timer. Apparent success/failure return is absent; callback result unused.
void __cdecl rf_client_apply_pregame_remote_charge_payload19(const unsigned __int8 *payload)
{
  float v1; // [esp+0h] [ebp-F0h]
  float v2; // [esp+8h] [ebp-E8h]
  float v3[3]; // [esp+14h] [ebp-DCh] BYREF
  float v4[3]; // [esp+20h] [ebp-D0h] BYREF
  float copy_result[3]; // [esp+2Ch] [ebp-C4h] BYREF
  int v6; // [esp+38h] [ebp-B8h]
  int v7; // [esp+3Ch] [ebp-B4h]
  unsigned __int8 v8; // [esp+42h] [ebp-AEh]
  signed __int8 v9; // [esp+43h] [ebp-ADh]
  int runtime; // [esp+44h] [ebp-ACh]
  int v11; // [esp+48h] [ebp-A8h]
  _DWORD v12[3]; // [esp+4Ch] [ebp-A4h] BYREF
  float source[3]; // [esp+58h] [ebp-98h] BYREF
  int v14; // [esp+64h] [ebp-8Ch]
  float v15; // [esp+68h] [ebp-88h]
  int v16; // [esp+6Ch] [ebp-84h]
  float v17[3]; // [esp+70h] [ebp-80h] BYREF
  float v18[9]; // [esp+7Ch] [ebp-74h] BYREF
  float v19[3]; // [esp+A0h] [ebp-50h] BYREF
  int v20; // [esp+ACh] [ebp-44h]
  int v21; // [esp+B0h] [ebp-40h]
  float v22; // [esp+B4h] [ebp-3Ch] BYREF
  float v23; // [esp+B8h] [ebp-38h]
  float v24; // [esp+BCh] [ebp-34h]
  int i; // [esp+C0h] [ebp-30h]
  int v26; // [esp+C4h] [ebp-2Ch]
  unsigned __int8 v27; // [esp+CBh] [ebp-25h]
  float v28[9]; // [esp+CCh] [ebp-24h] BYREF

  v20 = 0;
  rf_vector3_default_construct_noop(source);
  rf_vector3_default_construct_noop(v17);
  rf_vector3_default_construct_noop(v12);
  rf_vector3_default_construct_noop(v19);
  rf_vector3_default_construct_noop(&v22);
  rf_matrix3_construct((char *)v28);
  rf_matrix3_construct((char *)v18);
  v27 = payload[v20++];
  for ( i = 0; i < v27; ++i )
  {
    v16 = *(_DWORD *)&payload[v20];
    v20 += 4;
    v21 = *(_DWORD *)&payload[v20];
    v20 += 4;
    v14 = *(_DWORD *)&payload[v20];
    v20 += 4;
    v15 = *(float *)&payload[v20];
    v20 += 4;
    v11 = rf_replication_server_id_to_local_handle(v14);
    v12[0] = *(_DWORD *)&payload[v20];
    v20 += 4;
    v12[1] = *(_DWORD *)&payload[v20];
    v20 += 4;
    v12[2] = *(_DWORD *)&payload[v20];
    v20 += 4;
    v19[0] = *(float *)&payload[v20];
    v20 += 4;
    v19[1] = *(float *)&payload[v20];
    v20 += 4;
    v19[2] = *(float *)&payload[v20];
    v20 += 4;
    rf_orientation_matrix_from_normalized_direction(v18, v19);
    source[0] = *(float *)&payload[v20];
    v20 += 4;
    source[1] = *(float *)&payload[v20];
    v20 += 4;
    source[2] = *(float *)&payload[v20];
    v20 += 4;
    v17[0] = *(float *)&payload[v20];
    v20 += 4;
    v17[1] = *(float *)&payload[v20];
    v20 += 4;
    v17[2] = *(float *)&payload[v20];
    v20 += 4;
    rf_orientation_matrix_from_normalized_direction(v28, v17);
    v26 = *(_DWORD *)&payload[v20];
    v20 += 4;
    v9 = payload[v20++];
    v22 = (double)v9 / 127.0;
    v9 = payload[v20++];
    v23 = (double)v9 / 127.0;
    if ( v22 + v23 == 0.0 )
    {
      v24 = 1.0;
    }
    else
    {
      v2 = 1.0 - (v22 * v22 + v23 * v23);
      v24 = rf_sqrt_float(v2);
    }
    v8 = payload[v20++];
    if ( (v8 & 0x80) != 0 )
      v24 = v24 * -1.0;
    v1 = (float)(v8 & 0x7F);
    rf_vector3_scale_in_place_return_self(&v22, v1);
    runtime = rf_projectile_create_runtime(dword_911C78, v11, (int)v12, (int)v18, 0, v16);
    if ( runtime )
    {
      v7 = -1;
      if ( v21 != -1 )
      {
        v7 = rf_replication_server_id_to_local_handle(v21);
        *(_DWORD *)(runtime + 688) = v7;
        rf_vector_copy((float *)(runtime + 692), copy_result, source);
        rf_matrix3_copy((float *)(runtime + 704), v28);
      }
      *(float *)(runtime + 668) = v15;
      rf_vector_copy((float *)(runtime + 228), v4, (const float *)(runtime + 60));
      rf_matrix3_copy((float *)(runtime + 252), (const float *)(runtime + 72));
      *(_DWORD *)(runtime + 424) = v26;
      rf_vector_copy((float *)(runtime + 324), v3, &v22);
      if ( v21 != -1 )
      {
        v6 = rf_object_resolve_handle(v7);
        if ( v6 )
          rf_object_attach_store_parent_and_pose(runtime, v6);
      }
    }
  }
}

