// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00435900 rf_entity_vertical_sweep_contact_vectors
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(outPoint3,outNormal3,required entity,FLOAT distance), canonicalAL0/1. No-op local40-byte result
// constructor, then435960(&localHit,entity,distance). ANYnonzero delegatedAL copies FLOAT vector localHit+8 to outPoint FIRST, then localHit+20 to outNormal via vector assignment
// with LOCAL hidden result objects, returnsAL1. Zero returnsAL0 leaving BOTH caller outputs untouched. No own output/alias/finite/distance sign validation or entity/room/pose
// mutation. Ordinary identical output pointers end with second normal vector, not a snapshot pair. Query starts COMMON60 and uses entity FLOAT384 radius through delegate, not contact
// physics-center228.
char __cdecl rf_entity_vertical_sweep_contact_vectors(float *destination, float *a2, int entity, float distance)
{
  float v5[3]; // [esp+4h] [ebp-40h] BYREF
  float copy_result[3]; // [esp+10h] [ebp-34h] BYREF
  int out_hit[2]; // [esp+1Ch] [ebp-28h] BYREF
  float source[3]; // [esp+24h] [ebp-20h] BYREF
  float v9[5]; // [esp+30h] [ebp-14h] BYREF

  rf_solid_collision_result_construct_noop((int)out_hit);
  if ( !rf_entity_vertical_sweep_copy_hit(out_hit, entity, distance) )
    return 0;
  rf_vector_copy(destination, copy_result, source);
  rf_vector_copy(a2, v5, v9);
  return 1;
}

