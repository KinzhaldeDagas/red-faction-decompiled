// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00409950 sub_409950
// UNREALRED VERIFIED [ai-goto-completion-20261028] For current numeric mode2, route-arrival dispatch calls rf_ai_route_reset(AI+0x2E8), secondary-state writer with0, then saved-state restore0x40A2A0. This is not a permanent hold in mode2/secondary1. Common pre-switch handling also masks AI+0x530 with0xBD7FFFFF, writes entity+0x8C8=1, and consumes bit0x10000000 with an optional central target write to the local-player entity. MP/splitscreen random diversion when bit0x02000000 is set occurs before these changes. These shared side effects are distinct from the mode2 saved-state correction.
// UNREALRED VERIFIED [ai-arrival-target-20261029] Non-diverted common arrival clears AI+0x530 bits0x42800000 through mask0xBD7FFFFF. If remaining bit0x10000000 is set, attempt local-player target write via0x40BA80 if pointer0x681E38 exists, then consume the bit even when no local player or target admission fails. Thus represented Goto integer1 flag0x40000000 and integer0 flag0x10000000 are consumed, while boolean0 flag8 remains. Target assignment precedes mode2 route retirement/secondary0/saved restore.
// UNREALRED INVESTIGATED [ai-arrival-scalar-20261029] Direct operand scan of defined function instructions (displacement, phrase and immediate0x8C8) found entity+0x8C8 writes here and constructor42CB80 only. No direct read/argument-offset reference was found by that scan. This is not proof of no indirect consumer; field meaning remains unresolved. Do not infer a movement-speed multiplier from this arrival write alone.
// UNREALRED VERIFIED [combat-panic-20261104]: Numeric17 arrival case calls40EAB0 directly, with no savedstate restoration. Shared prelude masks AIflags withBD7FFFFF, writes entity+8C8=1, consumes10000000 viaoptional central localplayer target assignment; MPdiversion precedes prelude. Native panic route renewal and deadline expiration are separate owners.
// UNREALRED VERIFIED [combat-native-ai-dependencies-20261111] Arrival common prelude may consume shared rand15%2 under MP/split and owner mask02000000; preserve exact draw admission before later flag/target writes. Native assumes available CRT; host availability must be explicit and must not be interpreted as renewal=false or zero draw.
void __cdecl sub_409950(int *a1)
{
  if ( (rf_multiplayer_runtime_mode || rf_splitscreen_runtime_active)
    && ((unsigned int)&unk_2000000 & a1[332]) != 0
    && rand() % 2 )
  {
    rf_ai_build_alternative_route_from_global_points(a1, 1);
  }
  else
  {
    a1[332] &= 0xBD7FFFFF;
    *(float *)(*a1 + 2248) = 1.0;
    if ( (a1[332] & 0x10000000) != 0 )
    {
      if ( dword_681E38 )
        sub_40BA80(a1, *(_DWORD *)(dword_681E38 + 44));
      a1[332] &= ~0x10000000u;
    }
    switch ( a1[160] )
    {
      case 2:
        rf_ai_route_reset((int)(a1 + 186));
        rf_ai_secondary_state_write((int)a1, 0);
        sub_40A2A0(a1);
        break;
      case 3:
        rf_ai_rebuild_route_to_retained_target(a1);
        break;
      case 4:
        sub_409C40(a1);
        break;
      case 5:
        rf_ai_secondary6_to7_and_reset_route((int)a1);
        break;
      case 6:
        sub_40A2A0(a1);
        break;
      case 7:
        rf_ai_reset_route_and_retry_target_approach(a1);
        break;
      case 10:
        rf_ai_secondary_state_write((int)a1, 0);
        break;
      case 12:
        rf_replicator_arm_milliseconds(a1 + 143, 0);
        rf_ai_probe_target_route_mode12_with_backoff(a1);
        break;
      case 16:
        rf_ai_set_secondary10_if_owner_resolves((int)a1);
        break;
      case 17:
        sub_40EAB0(*(_DWORD *)(*a1 + 44));
        break;
      default:
        return;
    }
  }
}

