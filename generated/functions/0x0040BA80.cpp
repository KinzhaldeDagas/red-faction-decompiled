// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040BA80 sub_40BA80
// UNREALRED VERIFIED [ai-arrival-target-20261029] Goto arrival0x409950 invokes this setter for the local player when AI+0x530 bit0x10000000 is set, BEFORE saved-mode restoration. Equal target is a strict no-op; self target clears the slot before owner predicates. Changed non-self target requires non-player-associated owner AND (runtime entity+0x810 bit0x10000 OR authored sentient flag), with mode15 bypassing that owner predicate. AI+0x530 bit0x80 separately requires target player association. This does not test friendliness, FOV, sight or damage observation; target assignment must not fabricate a seen/damage event.
// UNREALRED VERIFIED [ai-target-commit-20261029] Owner/player-only predicate failure returns without changing AI+0x2C0. An attempted candidate is therefore not evidence that the current target changed. The native return value is NOT an acceptance boolean: accepted paths return a deadline helper result, rejected paths can return owner/predicate values. Any Unreal committed/rejected/superseded result is an explicit host API contract, not a reinterpretation of EAX.
// UNREALRED VERIFIED [ai-script-target-clear-20261029] Input -1 is a guarded central target write, not unconditional teardown. Equal stored -1 returns immediately. Otherwise owner predicate434010 or mode15 is required. AI+0x530 bit0x80 rejects clearing because object resolver40CE70(-1) returns null and player-association4BCF40(null) returns0. Mode15 bypasses only the owner predicate, not bit0x80. Accepted -1 skips changed-target history/acquisition-clock/position-copy and arms AI+0x294 deadline0. Self-handle shortcut remains distinct.
// UNREALRED VERIFIED [combat-reaction-target-wait-20261111]: Changed-target central write can store a COMMON identifier including type7; its shown admission does not reject dead/inactive/type7 targets. Equal fullidentifier is a strictno-op, so host lifetime capture must not silently rebind same actor after nativeidentity retirement. Selfhandle clears before otherpredicates; ordinaryplayer-only andownerpolicy gates remainordered. Host combat-observation filtering is a separate adapter and must not stand in for the generic native setter.
char __cdecl sub_40BA80(int *a1, int a2)
{
  float v2; // eax
  float copy_result[3]; // [esp+0h] [ebp-14h] BYREF
  int v5; // [esp+Ch] [ebp-8h]
  int v6; // [esp+10h] [ebp-4h]

  LOBYTE(v2) = (_BYTE)a1;
  if ( a2 != a1[176] )
  {
    v2 = *(float *)a1;
    if ( a2 == *(_DWORD *)(*a1 + 44) )
    {
      a1[176] = -1;
    }
    else if ( rf_entity_is_nonplayer_sentient_or_runtime_enabled(*a1) || (LOBYTE(v2) = (_BYTE)a1, a1[160] == 15) )
    {
      if ( (a1[332] & 0x80) == 0
        || (v5 = rf_object_resolve_handle(a2), (LOBYTE(v2) = rf_object_is_player_associated(v5)) != 0) )
      {
        if ( a2 != a1[176] && (a1[160] == 3 || a1[160] == 7) && a2 != -1 )
          rf_pointer_array_append_unique(a1 + 131, a2);
        if ( a2 != -1 )
          a1[166] = dword_6FC428;
        a1[176] = a2;
        v6 = rf_object_resolve_handle(a2);
        if ( v6 )
        {
          rf_vector_copy((float *)a1 + 177, copy_result, (const float *)(v6 + 60));
          rf_replicator_arm_milliseconds(a1 + 180, 0);
        }
        LOBYTE(v2) = rf_replicator_arm_milliseconds(a1 + 165, 0);
      }
    }
  }
  return LOBYTE(v2);
}

