// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0042B710 rf_driller_contact_geomod_update
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity node pose/physics, VFX rendering, secondary ammunition and attachment/detach native chains and native
// signed/x87/stack/callback ABI): Cdecl(required entity), output procedure with incidental EAX/AL, no uniform success result. Initializes contact-hit count0, collected-point count0
// and FOUR local12-byte point slots via no-op constructors. Signed attachment loop starts0 while i<first DWORD at entity sound/variant pointer(+668)+468, re-reading count each
// iteration; no independent limit4. Calls420020(entity,i,outAttachmentPoint,outCorrectedPoint,outMatrix) FIVE slots. Only FULL EAX EXACT-1 skips attachment; other values proceed.
// Uses returned matrix row2/forward. Initial endpoint=FLOAT32 componentwise(correctedPoint+FLOAT32(forward*FLOAT3.5)). Builds world sweep query: start+52=correctedPoint,
// displacement+64=FLOAT32(endpoint-correctedPoint), radius FLOAT+76=0.4000000059604645, DWORD+80=0, aux vector+4 zero and orientation+16 identity; query constructor only clears its
// face hint. Calls52F8D0(ECX worldSolid,query,result,1), ignores return; only signed result DWORD+0>0 admits contact. Recomputes contact
// point=FLOAT32(correctedPoint+FLOAT32(FLOAT32(forward*result FLOAT+4)*FLOAT3.5)), preserving TWO separately rounded scalar products.  For each admitted hit increments local hit
// count and ORs entity DWORD+2068 mask0x40 BEFORE later gates; this function never clears that bit. Signed owner DWORD+5232>=25: if cached voice DWORD+5072==-1 plays positional
// event39(contactPoint,1,shared17F10B0,0) and saves FULL EAX including-1. Then calls44B4B0(global DWORD88D438,0,0,NULL) and RETURNS ENTIRE function. Native XOR EAX,EAX/JZ always
// chooses global message pointer; embedded literal maintenance-string branch is unreachable. Existing any-not-1 voice is retained without playing/position validation. Limit check
// occurs only after a hit and uses signed comparison; it counts nonzero GeoMod admissions, not confirmed terrain cuts.  Below limit: calls510670(primary weapon entity+676,captured
// current room DWORD[entity],entity COMMON position+60,&collisionResult+8,&collisionResult+20,-1), ignoring result. If cached voice+5072==-1 plays event38 at contact point and saves
// playback result; existing cached value suppresses new playback. Tests embedded deadline entity+5068 is-armed ANY nonzero. Disarmed path arms750ms and IMMEDIATELY RETURNS ENTIRE
// function before later attachments/aggregation. Armed path calls elapsed and appends contact point ONLY on EXACT AL1; other nonzero bytes do not append. Append increments collected
// count and copies into local point[count] WITHOUT a4-slot bounds check. Armed but not-exactly-elapsed contacts still retain hit marker/impact/sound prefix effects.  After full
// attachment loop, local hit count0 disarms5068 and, if cached voice5072!=-1, stops it then stores-1, regardless of playback state. Nonzero hit count preserves voice/deadline unless
// collection path below resets it. If collected count<=0 signed, exits without GeoMod. Positive count FIRST disarms5068, then zeros accumulator, adds collected vectors in order with
// float32 per-component accumulation, divides using411140 reciprocal helper with float32-converted signed count (reciprocal roundsFLOAT32 then component multiplication), and adds
// exact DOUBLE0.7799999713897705 to Y with float32 store. Radius argument=FLOAT32(signed count*DOUBLE10). Resolves cutter bit_driller_double.v3d ONLY when count==2; every other
// positive count uses bit_driller_single.v3d. No cutter-1 guard. Calls484E60(radius,entity full handle,current room DWORD[entity],&average,entity vector+96,cutter,LOWBYTE0x3E) once.
// ANY nonzero returned AL increments owner DWORD+5232 by wrapped32 one; zero preserves count but earlier deadline reset/effects remain. GeoMod delegate can return nonzero without
// queueing terrain at its global saved-record cap, so this counter is admission-based. No own room/world/model/finite/authority/pointer validation or local contact-buffer clamp;
// invalid/oversized native inputs retain literal partial writes/overflow behavior.
void __cdecl rf_driller_contact_geomod_update(int *entity)
{
  int first_dword; // eax
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // [esp+14h] [ebp-1C8h]
  float scalar; // [esp+18h] [ebp-1C4h]
  float *v12; // [esp+1Ch] [ebp-1C0h]
  float v13[3]; // [esp+24h] [ebp-1B8h] BYREF
  float v14[3]; // [esp+30h] [ebp-1ACh] BYREF
  float v15[3]; // [esp+3Ch] [ebp-1A0h] BYREF
  float v16[3]; // [esp+48h] [ebp-194h] BYREF
  float v17[3]; // [esp+54h] [ebp-188h] BYREF
  float v18[3]; // [esp+60h] [ebp-17Ch] BYREF
  float out_vector[3]; // [esp+6Ch] [ebp-170h] BYREF
  float v20[3]; // [esp+78h] [ebp-164h] BYREF
  float copy_result[3]; // [esp+84h] [ebp-158h] BYREF
  float sum_result[3]; // [esp+90h] [ebp-14Ch] BYREF
  float scaled_result[3]; // [esp+9Ch] [ebp-140h] BYREF
  float v24; // [esp+A8h] [ebp-134h]
  int v25; // [esp+ACh] [ebp-130h]
  int v26; // [esp+B0h] [ebp-12Ch] BYREF
  float v27; // [esp+B4h] [ebp-128h]
  _DWORD v28[2]; // [esp+BCh] [ebp-120h] BYREF
  char v29; // [esp+C4h] [ebp-118h] BYREF
  _BYTE v30[20]; // [esp+D0h] [ebp-10Ch] BYREF
  char v31[4]; // [esp+E4h] [ebp-F8h] BYREF
  float v32[3]; // [esp+E8h] [ebp-F4h] BYREF
  float v33[9]; // [esp+F4h] [ebp-E8h] BYREF
  float destination[3]; // [esp+118h] [ebp-C4h] BYREF
  float v35[13]; // [esp+124h] [ebp-B8h] BYREF
  float out_orientation[6]; // [esp+158h] [ebp-84h] BYREF
  float vector[3]; // [esp+170h] [ebp-6Ch] BYREF
  int v38; // [esp+17Ch] [ebp-60h]
  _DWORD v39[12]; // [esp+180h] [ebp-5Ch] BYREF
  int v40; // [esp+1B0h] [ebp-2Ch]
  float out_attachment_position[3]; // [esp+1B4h] [ebp-28h] BYREF
  int attachment_index; // [esp+1C0h] [ebp-1Ch]
  float rhs[3]; // [esp+1C4h] [ebp-18h] BYREF
  float lhs[3]; // [esp+1D0h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(out_attachment_position);
  rf_vector3_default_construct_noop(rhs);
  rf_vector3_default_construct_noop(lhs);
  rf_matrix3_construct((char *)out_orientation);
  v40 = 0;
  rf_vector_construct_no_unwind((char *)v39, 0xCu, 4, rf_vector3_default_construct_noop);
  v38 = 0;
  for ( attachment_index = 0; ; ++attachment_index )
  {
    first_dword = rf_receiver_get_first_dword((void *)(entity[167] + 468));
    if ( attachment_index >= first_dword )
      break;
    if ( rf_entity_copy_weapon_attachment_transforms(
           (const unsigned int *)entity,
           attachment_index,
           out_attachment_position,
           rhs,
           out_orientation) != -1 )
    {
      v2 = rf_vector_multiply_scalar(vector, scaled_result, 3.5);
      v3 = rf_vector_add(rhs, sum_result, v2);
      rf_vector_copy(lhs, copy_result, v3);
      rf_solid_collision_query_construct_clear_face_hint(v31);
      rf_solid_collision_result_construct_noop((int)v28);
      rf_vector_copy(destination, v20, rhs);
      v4 = rf_vector_subtract(lhs, out_vector, rhs);
      rf_vector_copy(v35, v18, v4);
      v35[3] = 0.40000001;
      v35[4] = 0.0;
      rf_vector3_zero_return_destination(v32);
      rf_identity_orientation_matrix(v33);
      rf_world_collision_sweep((char *)rf_world_solid, (int)v31, (int)v28, 1);
      if ( v28[0] > 0 )
      {
        v5 = rf_vector_multiply_scalar(vector, v17, *(float *)&v28[1]);
        v6 = rf_vector_multiply_scalar(v5, v16, 3.5);
        v7 = rf_vector_add(rhs, v15, v6);
        rf_vector_copy(lhs, v14, v7);
        ++v40;
        entity[517] |= 0x40u;
        if ( entity[1308] >= 25 )
        {
          if ( entity[1268] == -1 )
            entity[1268] = rf_gamesound_play_positional_event(39, lhs, 1.0, (int)&unk_17F10B0, 0);
          rf_hud_message_enqueue_expand_tokens_and_rearm_head((const char *)unk_88D438[0], 0, 0, nullptr);
          return;
        }
        v8 = rf_receiver_get_first_dword(entity);
        rf_weapon_spawn_impact_vclips(entity[169], v8, (int)(entity + 15), (char)&v29, (int)v30, -1);
        if ( entity[1268] == -1 )
          entity[1268] = rf_gamesound_play_positional_event(38, lhs, 1.0, (int)&unk_17F10B0, 0);
        if ( !rf_replicator_is_armed(entity + 1267) )
        {
          rf_replicator_arm_milliseconds(entity + 1267, 750);
          return;
        }
        if ( rf_replicator_has_elapsed(entity + 1267) )
        {
          v12 = (float *)&v39[3 * v38++];
          rf_vector_copy(v12, v13, lhs);
        }
      }
    }
  }
  if ( !v40 )
  {
    rf_replicator_reset(entity + 1267);
    if ( entity[1268] != -1 )
    {
      rf_gamesound_stop_voice_handle(entity[1268]);
      entity[1268] = -1;
    }
  }
  if ( v38 > 0 )
  {
    rf_replicator_reset(entity + 1267);
    rf_vector3_default_construct_noop(&v26);
    rf_vector3_zero_return_destination((float *)&v26);
    for ( attachment_index = 0; attachment_index < v38; ++attachment_index )
      rf_vector_accumulate((float *)&v26, (float *)&v39[3 * attachment_index]);
    scalar = (float)v38;
    rf_vector3_divide_in_place_reciprocal((float *)&v26, scalar);
    v27 = v27 + 0.7799999713897705;
    v24 = (double)v38 * 10.0;
    v25 = 0;
    v25 = v38 == 2
        ? rf_geomod_cutter_registry_find_name("bit_driller_double.v3d")
        : rf_geomod_cutter_registry_find_name("bit_driller_single.v3d");
    v10 = v25;
    v9 = rf_receiver_get_first_dword(entity);
    if ( rf_geomod_operation_admit(v24, entity[11], v9, (int)&v26, (int)(entity + 24), v10, 62) )
      ++entity[1308];
  }
}

