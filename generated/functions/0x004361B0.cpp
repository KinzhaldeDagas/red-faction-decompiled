// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004361B0 rf_entity_try_apply_standing_shape_centers
// [UnrealRed physical spheres 2026-11-12; verified ASM] Uncrouch seeds fraction1 then sweeps real4D13C0 fromcommon3C to endpointY=commonY+GAMEPLAYclassF74+double0.10000000149. Anyhit returnsfalse before stance writes. Clear branch clears810bit400, optionalplayerbyte1770, copies ONLY XYZ from MODELclass stand40, calls4D9960. Missing sweep/support providers cannot be replaced by fabricated fraction1/clear success.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(required entity), explicit AL0/1, no own NULL/already-crouched guard. Construct no-write68-byte hit
// record and seed ONLY fractionFLOAT+24=1. Endpoint.X/Z=entity COMMON position60/68; Y=round32(entity64+GAMEPLAY-class pointer660 FLOAT3956+DOUBLE0.10000000149011612), no
// intermediate FLOAT store inside sum. Call4D13C0(start=entity60,end=endpoint,shape=entity136,inoutHit). ANY nonzero returnedAL returns0 before OWN stance/player/center stores;
// delegate query/cache/hit side effects may already exist, and no own hit-fraction/normal/material validation follows. AL0 first clears entity2064 bit0x400, then4DD720(raw full
// handle44) matching-player lookup; nonNULL result gets BYTE+177=0. Signed i0 loop dynamically re-reads physical count entity388; each i copies ONLY XYZ from MODEL-INFO entity668
// inline40 array3308 element+24 into physical24 element0 via unchecked getters. No source-count/capacity/radius reconciliation; negative physical count still reaches support
// call.4D9960(entity) result ignored, explicit AL1 follows even if support policy cannot establish a contact. No entity1972 timestamp write, direct extents/radius update,
// finite/death/authority gate, rollback or failure-state restoration.
char __cdecl rf_entity_try_apply_standing_shape_centers(int a1)
{
  int first_dword; // eax
  float *element_address_unchecked; // eax
  const float *v4; // [esp+8h] [ebp-70h]
  float v5; // [esp+Ch] [ebp-6Ch]
  float copy_result[3]; // [esp+10h] [ebp-68h] BYREF
  float v7[3]; // [esp+1Ch] [ebp-5Ch] BYREF
  char v8[24]; // [esp+28h] [ebp-50h] BYREF
  float v9; // [esp+40h] [ebp-38h]
  _DWORD *v10; // [esp+70h] [ebp-8h]
  int i; // [esp+74h] [ebp-4h]

  rf_physics_hit_record_construct_noop(v8);
  v9 = 1.0;
  v5 = *(float *)(a1 + 64) + *(float *)(*(_DWORD *)(a1 + 660) + 3956) + 0.1000000014901161;
  rf_vector3_set_components_return_destination(v7, *(float *)(a1 + 60), v5, *(float *)(a1 + 68));
  if ( rf_physics_shape_sweep_movers_and_static_world(a1 + 60, (int)v7, a1 + 136, (int)v8) )
    return 0;
  *(_DWORD *)(a1 + 2064) &= ~0x400u;
  v10 = sub_4DD720(*(_DWORD *)(a1 + 44));
  if ( v10 )
    *((_BYTE *)v10 + 177) = 0;
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword((void *)(a1 + 388));
    if ( i >= first_dword )
      break;
    v4 = (const float *)(rf_inline_array40_get_element_address((void *)(*(_DWORD *)(a1 + 668) + 3308), i) + 24);
    element_address_unchecked = (float *)rf_array24_get_element_address_unchecked((_DWORD *)(a1 + 388), i);
    rf_vector_copy(element_address_unchecked, copy_result, v4);
  }
  sub_4D9960(a1);
  return 1;
}

