// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00448420 rf_object_relocate_reset_pose_and_reactivate
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): Cdecl(object,position3,orientation3x3), three DWORD arguments; NULL object is a no-op. Calls4BC330(object,position), sets
// cached roomNULL through4BC210, then refreshes room/audio through4BC240. A zero cached-room getter result marks original object pending-delete via4BCFD0 but DOES NOT abort. Copies
// LIVE common position+60 into predicted position+240, then vector+108, using vector-copy receiver plus hidden-result temporaries. Recomputes low bound+400 from current physics
// position+228 minus radius+384, then high bound+412 from a RE-READ position/radius plus that scalar; no positivity/finite guard here, overriding the initial setter's
// nonpositive-radius bound rule. Copies supplied orientation into+72, then+252, then+288 using sequential3-row copy delegates; arbitrary input/object overlap is not snapshotted or
// protected. If DWORD+32!=-999, replaces it with the previous global object-counter value from4B8640, which decrements that counter. Resolves LIVE original UID+44 as entity; only
// nonnull resolution AND original object's current pending-delete bit2 CLEAR invokes420870(resolvedEntity), tests438010(resolvedEntity) for ANY nonzero AL to optionally shape-snap
// ORIGINAL object downward, then unconditionally calls437410(resolvedEntity). Delegate return codes are ignored. Finally ALWAYS clears original object's current flag0x800 at+124,
// including pending-delete/nonentity paths, without undoing pending-delete; any snap/activation delegate side effects are retained. NULL orientation/position are not separately
// guarded, no normalization/rollback, and this function returns void.
void __cdecl rf_object_relocate_reset_pose_and_reactivate(void *a1, float *a2, float *a3)
{
  float *v3; // eax
  float *v4; // eax
  float v5[3]; // [esp+4h] [ebp-4Ch] BYREF
  int v6[3]; // [esp+10h] [ebp-40h] BYREF
  float v7[3]; // [esp+1Ch] [ebp-34h] BYREF
  int v8[3]; // [esp+28h] [ebp-28h] BYREF
  float v9[3]; // [esp+34h] [ebp-1Ch] BYREF
  float copy_result[3]; // [esp+40h] [ebp-10h] BYREF
  int v11; // [esp+4Ch] [ebp-4h]

  if ( a1 )
  {
    rf_object_publish_position_and_bounds((int)a1, a2);
    rf_object_set_room_and_cache_position((float *)a1, 0);
    rf_object_refresh_room_cache_and_audio(a1);
    if ( !rf_receiver_get_first_dword(a1) )
      rf_object_mark_for_deferred_delete((int)a1);
    rf_vector_copy((float *)a1 + 60, copy_result, (const float *)a1 + 15);
    rf_vector_copy((float *)a1 + 27, v9, (const float *)a1 + 15);
    v3 = rf_vector3_subtract_scalar_from_components((float *)a1 + 57, (float *)v8, *((float *)a1 + 96));
    rf_vector_copy((float *)a1 + 100, v7, v3);
    v4 = rf_vector3_add_scalar_to_components((float *)a1 + 57, (float *)v6, *((float *)a1 + 96));
    rf_vector_copy((float *)a1 + 103, v5, v4);
    rf_matrix3_copy((float *)a1 + 18, a3);
    rf_matrix3_copy((float *)a1 + 63, a3);
    rf_matrix3_copy((float *)a1 + 72, a3);
    if ( *((_DWORD *)a1 + 8) != -999 )
      *((_DWORD *)a1 + 8) = rf_object_counter_take_and_decrement();
    v11 = rf_entity_resolve_handle(*((_DWORD *)a1 + 11));
    if ( v11 && (*((_DWORD *)a1 + 31) & 2) == 0 )
    {
      sub_420870(v11);
      if ( sub_438010(v11) )
        rf_object_snap_down_using_physics_shape_sweep((int)a1);
      sub_437410(v11);
    }
    *((_DWORD *)a1 + 31) &= ~0x800u;
  }
}

