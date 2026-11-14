// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043B3A0 rf_entity_jeep_auxiliary_tag_world_transform
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Cdecl(entity,outPosition3f,outOrientation3x3), canonical AL0/1. Reject NULL entity, jeep predicate AL0,
// shared model681E80 NULL, or shared tag661514 EXACT-1, leaving own caller outputs untouched. Local vector/matrix default constructors write nothing; no fallback local initialization
// is supplied. Builds local tag world transform through5651D0(entity model128,tag5204,parent matrix72,parent position60,local matrix,local position). Ignores its return. If4390E0
// reports second relation resolving ANY common object, fetch unchecked relation-array2252 index1 again and resolve its DWORD4 handle through ENTITY resolver433EE0; NULL typed
// resolution returns0 after local computation. Otherwise replace ONLY local orientation with related entity matrix72, retaining position computed from original entity tag. Both
// remaining paths compose shared681E80/tag661514 against those locals into caller orientation/position through5651D0, ignore its return, then load caller positionY, add original PE
// DOUBLE0.5, round/store FLOAT32 Y, and AL1. Thus common-only related objects can pass the first predicate then fail the typed resolution; tag/model failures in composition are not
// propagated. No relation count/pointer, output pointer, tag range, finite or alias validation; globals are re-read before the second composition.
char __cdecl rf_entity_jeep_auxiliary_tag_world_transform(int entity, float *out_position, float *out_orientation)
{
  int v4; // eax
  int v5; // [esp+0h] [ebp-34h]
  float v6[9]; // [esp+4h] [ebp-30h] BYREF
  float v7[3]; // [esp+28h] [ebp-Ch] BYREF

  if ( !entity )
    return 0;
  if ( !rf_entity_has_jeep_flag(entity) )
    return 0;
  if ( !unk_681E80 || dword_661514 == -1 )
    return 0;
  rf_vector3_default_construct_noop(v7);
  rf_matrix3_construct((char *)v6);
  rf_vmesh_compose_prop_world_transform(
    *(_DWORD *)(entity + 128),
    *(_DWORD *)(entity + 5204),
    (float *)(entity + 72),
    entity + 60,
    (int)v6,
    v7);
  if ( rf_entity_jeep_second_relation_resolves_object(entity) )
  {
    v4 = sub_552200((_DWORD *)(entity + 2252), 1);
    v5 = rf_entity_resolve_handle(*(_DWORD *)(*(_DWORD *)v4 + 4));
    if ( !v5 )
      return 0;
    rf_matrix3_copy(v6, (const float *)(v5 + 72));
    rf_vmesh_compose_prop_world_transform(unk_681E80, dword_661514, v6, (int)v7, (int)out_orientation, out_position);
    out_position[1] = out_position[1] + 0.5;
  }
  else
  {
    rf_vmesh_compose_prop_world_transform(unk_681E80, dword_661514, v6, (int)v7, (int)out_orientation, out_position);
    out_position[1] = out_position[1] + 0.5;
  }
  return 1;
}

