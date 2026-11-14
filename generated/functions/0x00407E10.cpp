// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00407E10 rf_ai_secondary_weapon_target_admitted
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): One required AI block, explicit AL0/1. Resolve COMMON target+704; require deadline+540 elapsed any nonzero and
// visibility byte668/669 any nonzero OR flags+1328 mask0x1000. Secondary weapon index DWORD+8 is used UNCHECKED with1360-byte stride. Load range FLOAT9120CC+1360*index, fast
// COMMON-position distance roundedfloat32: ordered range<distance returns0; equality/greater OR UNORDERED admits. Then require distance NOT ordered<unrounded x87
// sum(FLOAT912208+1360*index +owner radius+384 +target radius+384); equality and unordered admit. Get rhs through435C70(owner,&rhs), IGNORE result; no-write temporary constructors do
// not clear rhs before delegate.437E80(owner)==EXACT1 copies target COMMON position but replaces target.Y with OWNER COMMON Y(+64), subtracts rhs; other AL uses true target COMMON
// position-rhs. Normalize that offset unchecked; dot against OWNER COMMON forward row+96 roundedfloat32. Ordered dot<DOUBLE0.95 returns0; unordered admits. Geometry(rhs,true target
// COMMON position,mask3,NULL) any nonzero rejects UNLESS AI mask0x1000 set; flattened aiming Y is not used by this ray. If admitted owner humanoid nonzero and mode3 and global6663E4
// deadline disarmed,401EF0(block) nonzero arms global with rand()%4000+6000ms, else rand()%3000+7000ms. Returns1 regardless of whether optional global timer branch ran. Does not
// rearm its own+540 deadline, change target, validate secondary index or commit projectile here.
char __cdecl rf_ai_secondary_weapon_target_admitted(_DWORD *a1)
{
  float *v2; // eax
  float *v3; // eax
  int v4; // eax
  int v5; // eax
  float v6[3]; // [esp+0h] [ebp-64h] BYREF
  float v7[3]; // [esp+Ch] [ebp-58h] BYREF
  float copy_result[3]; // [esp+18h] [ebp-4Ch] BYREF
  float out_vector[3]; // [esp+24h] [ebp-40h] BYREF
  float lhs[3]; // [esp+30h] [ebp-34h] BYREF
  float v11; // [esp+3Ch] [ebp-28h]
  float v12; // [esp+40h] [ebp-24h]
  float rhs[3]; // [esp+44h] [ebp-20h] BYREF
  float destination[3]; // [esp+50h] [ebp-14h] BYREF
  int v15; // [esp+5Ch] [ebp-8h]
  float v16; // [esp+60h] [ebp-4h]

  v15 = rf_object_resolve_handle(a1[176]);
  if ( !v15 )
    return 0;
  if ( !rf_replicator_has_elapsed(a1 + 135) )
    return 0;
  if ( !*((_BYTE *)a1 + 668) && !*((_BYTE *)a1 + 669) && (a1[332] & 0x1000) == 0 )
    return 0;
  v12 = *((float *)&unk_9120CC + 340 * a1[2]);
  v16 = rf_vector_fast_distance((const float *)(*a1 + 60), (const float *)(v15 + 60));
  if ( v12 < (double)v16 )
    return 0;
  if ( v16 < *((float *)&unk_912208 + 340 * a1[2]) + *(float *)(*a1 + 384) + *(float *)(v15 + 384) )
    return 0;
  rf_vector3_default_construct_noop(destination);
  rf_vector3_default_construct_noop(rhs);
  rf_entity_secondary_tag_position((unsigned int *)*a1, rhs);
  if ( sub_437E80(*a1) )
  {
    rf_vector3_copy_return_destination(lhs, (float *)(v15 + 60));
    lhs[1] = *(float *)(*a1 + 64);
    v2 = rf_vector_subtract(lhs, out_vector, rhs);
    rf_vector_copy(destination, copy_result, v2);
  }
  else
  {
    v3 = rf_vector_subtract((const float *)(v15 + 60), v7, rhs);
    rf_vector_copy(destination, v6, v3);
  }
  rf_vector_normalize_reciprocal_sqrt(destination);
  v11 = rf_vector_dot((float *)(*a1 + 96), destination);
  if ( v11 < 0.95 )
    return 0;
  if ( rf_geometry_segment_is_obstructed((int)rhs, v15 + 60, 3, 0) && (a1[332] & 0x1000) == 0 )
    return 0;
  if ( rf_entity_has_humanoid_flag(*a1) && a1[160] == 3 && !rf_replicator_is_armed(&dword_6663E4) )
  {
    if ( rf_ai_has_unholstered_mode3_peer_on_same_target(a1) )
    {
      v4 = rand();
      rf_replicator_arm_milliseconds(&dword_6663E4, v4 % 4000 + 6000);
    }
    else
    {
      v5 = rand();
      rf_replicator_arm_milliseconds(&dword_6663E4, v5 % 3000 + 7000);
    }
  }
  return 1;
}

