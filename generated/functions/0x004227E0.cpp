// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004227E0 rf_entity_update_selected_weapon_firing_effect_pose
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): Cdecl(required entity), void. First422270(entity full handle+44,current primary+676) any nonzero AL required; otherwise no work. When effect
// slot+5076 is EXACT-1, create ring effect4C3220 with raw FIVE slots(handle,entity common position+60,common orientation FORWARD row+96,FLOAT10,FLOAT1), store EAX slot even if
// allocation outcomes incomplete. Native callee consumes only first three; final two raw caller slots are extra. No slot validity/creation-success check before later pose delegate.
// Local matrix spans EBP-36 through-4; EBP-12 vector passed as direction is its third/forward row, not an independent uninitialized local.438AC0 any nonzero chooses player/FPGun-data
// path: entity+5168 player pointer, model=player+52,node=player+64; only node!=-1 AND model nonzero composes world pose from player matrix+4084/position+4120, then subtracts
// FLOAT0.5*player vector+4108 from point. Missing node/model exits without fallback, leaving newly created effect slot installed. Build world-sweep query: constructor only clears
// cached-face DWORD0; query+52=entity retained point+2004, query+64 initially point then overwritten with point-entity retained point, FLOAT+76=0,DWORD+80=5. Result constructor is
// no-op.52F8D0(ECX=world6FC420,query,result,rawBYTE1), result ignored; SIGNED result DWORD0>0 stops current primary through422A40, else updates effect slot pose(point,matrix forward
// row).438AC0 zero path calls423370(entity,current primary,&point,&matrix), ignores incidental result, sets global render RGBA(0,0,255,255), draws wire
// sphere(point,FLOAT1,global187CC5C), then pose delegate. Thus debug draw/color mutation occurs on this path without own debug-mode gate. Pose helper requires standard emitter pair;
// it can leave slot unchanged, and no own teardown/retry/transaction is added. No own entity/pointer/finite guards.
void __cdecl rf_entity_update_selected_weapon_firing_effect_pose(_DWORD *a1)
{
  float *v1; // eax
  float *v2; // eax
  float v3[3]; // [esp+8h] [ebp-10Ch] BYREF
  float out_vector[3]; // [esp+14h] [ebp-100h] BYREF
  float v5[3]; // [esp+20h] [ebp-F4h] BYREF
  float copy_result[3]; // [esp+2Ch] [ebp-E8h] BYREF
  float scaled_result[3]; // [esp+38h] [ebp-DCh] BYREF
  char v8[52]; // [esp+44h] [ebp-D0h] BYREF
  float destination[3]; // [esp+78h] [ebp-9Ch] BYREF
  float v10[12]; // [esp+84h] [ebp-90h] BYREF
  _DWORD v11[10]; // [esp+B4h] [ebp-60h] BYREF
  int v12; // [esp+DCh] [ebp-38h]
  int v13; // [esp+E0h] [ebp-34h]
  float lhs[3]; // [esp+E4h] [ebp-30h] BYREF
  char v15[24]; // [esp+F0h] [ebp-24h] BYREF
  float v16[3]; // [esp+108h] [ebp-Ch] BYREF

  if ( rf_entity_weapon_firing_byte_is_set(a1[11], a1[169]) )
  {
    if ( a1[1269] == -1 )
      a1[1269] = rf_firing_effect_ring_create_four_emitters(a1[11], (float *)a1 + 15, (float *)a1 + 24);
    rf_vector3_default_construct_noop(lhs);
    rf_matrix3_construct(v15);
    if ( sub_438AC0((int)a1) )
    {
      v12 = a1[1292];
      v13 = *(_DWORD *)(v12 + 64);
      if ( v13 != -1 && *(_DWORD *)(v12 + 52) )
      {
        rf_vmesh_compose_prop_world_transform(
          *(_DWORD *)(v12 + 52),
          v13,
          (float *)(v12 + 4084),
          v12 + 4120,
          (int)v15,
          lhs);
        v1 = rf_vector_multiply_scalar((const float *)(v12 + 4108), scaled_result, 0.5);
        rf_vector_subtract_in_place(lhs, v1);
        rf_solid_collision_query_construct_clear_face_hint(v8);
        rf_solid_collision_result_construct_noop((int)v11);
        rf_vector_copy(destination, copy_result, (const float *)a1 + 501);
        rf_vector_copy(v10, v5, lhs);
        v2 = rf_vector_subtract(lhs, out_vector, (const float *)a1 + 501);
        rf_vector_copy(v10, v3, v2);
        v10[3] = 0.0;
        LODWORD(v10[4]) = 5;
        rf_world_collision_sweep((char *)rf_world_solid, (int)v8, (int)v11, 1);
        if ( v11[0] <= 0 )
          rf_firing_effect_slot_set_pose_if_standard_pair(a1[1269], lhs, v16);
        else
          rf_entity_stop_weapon_firing(a1[11], a1[169]);
      }
    }
    else
    {
      rf_entity_compute_weapon_muzzle_transform(a1, a1[169], (int)lhs, (int)v15);
      rf_render_color_set_rgba8(0, 0, 255, 255);
      rf_debug_draw_wire_sphere_backend_dispatch((int)lhs, 1.0, dword_187CC5C);
      rf_firing_effect_slot_set_pose_if_standard_pair(a1[1269], lhs, v16);
    }
  }
}

