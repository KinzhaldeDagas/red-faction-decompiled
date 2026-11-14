// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00435750 rf_entity_install_custom_movement2
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(required entity,opaque control pointer), no uniform bool despite savedBOOL type. Class flags1828mask4
// predicate ANYnonzero required; reject returns predicate residue withAL0. Commit entityDWORD5100=0 then5104=raw control pointer BEFORE further tests. Fall/airborne-motion predicate
// ANYnonzero AND DWORD[control]==EXACT2 plays seven-slot object-view event18 at BY-VALUE entity COMMON60,FLOAT1,FLOAT0; no control-pointer guard, sound result ignored.
// Request4344D0(this=entity,speed1), ignore result, then445740(2) descriptor to2136, context2140=control ADDRESS+16, linked-motion handle2220=-1. No allocation/copy/ownership of
// control data, prior-control cleanup, authority/death test or rollback. Committed native EAX is ORIGINAL ENTITY POINTER, not canonicalAL1; pointer lowbyte may0 after successful
// stores. Registry fallback and speed helper overrides remain native.
bool __cdecl rf_entity_install_custom_movement2(int a1, _DWORD *a2)
{
  int v2; // ecx
  bool result; // al
  float v4[3]; // [esp-10h] [ebp-1Ch] BYREF
  int v5; // [esp-4h] [ebp-10h]
  float v6; // [esp+0h] [ebp-Ch]
  float v7; // [esp+4h] [ebp-8h]
  int v8; // [esp+8h] [ebp-4h]

  v8 = v2;
  result = rf_entity_class_flags724_has_mask4(a1);
  if ( result )
  {
    *(_DWORD *)(a1 + 5100) = 0;
    *(_DWORD *)(a1 + 5104) = a2;
    if ( rf_entity_uses_fall_or_airborne_vehicle_motion(a1) && *a2 == 2 )
    {
      v7 = 0.0;
      v6 = 1.0;
      v5 = 18;
      rf_vector3_copy_return_destination(v4, (float *)(a1 + 60));
      rf_sound_event_play_for_object_view(a1, v4[0], SLODWORD(v4[1]), SLODWORD(v4[2]), v5, v6, v7);
    }
    sub_4344D0(a1, 1);
    *(_DWORD *)(a1 + 2136) = sub_445740(2u);
    *(_DWORD *)(a1 + 2140) = a2 + 4;
    *(_DWORD *)(a1 + 2220) = -1;
    return a1;
  }
  return result;
}

