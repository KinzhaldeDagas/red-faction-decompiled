// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004095D0 rf_ai_scan_close_unholstered_candidates
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): One required AI block. Owner humanoid predicate nonzero AND entity flags+2064 mask0x00800000 AND AI mode2/4 AND block deadline+732 elapsed
// nonzero. Rearms deadline BEFORE scan with signed DWORD table661274[global6612A4], no own index bounds. Entity list next+652: reject equal full handle+44, require candidate
// DWORD+504==2. Suppress player-associated candidate ONLY when association predicate==EXACT1 AND BYTE6663D0==EXACT1. Reject dead/inactive/holstered predicates each EXACT AL1. Fast
// distance COMMON positions rounded float32 compared against FLOAT20 via TEST AH,41/JP: ordered distance<20 OR UNORDERED admits; equality rejects. Requires4024E0(owner,candidate)
// nonzero and seven-arg collision(owner+2004,candidate+2004,1.0,3,owner,candidate,NULL)==AL0. First admitted candidate: if current mode4 reset route+744 and request mode2(-1,-1);
// then40BA80(block,candidate handle), random FLOAT30..50,40AC80(block,candidate handle,random); exits regardless of delegate acceptance. No closest-target ranking, own owner-death
// guard or separate role gate. AL/EAX incidental.
char __cdecl rf_ai_scan_close_unholstered_candidates(int *Character)
{
  int v1; // eax
  float v3; // [esp+10h] [ebp-14h]
  float v4; // [esp+14h] [ebp-10h]
  int v5; // [esp+18h] [ebp-Ch]
  int i; // [esp+20h] [ebp-4h]

  LOBYTE(v1) = rf_entity_has_humanoid_flag(*Character);
  if ( (_BYTE)v1 )
  {
    LOBYTE(v1) = (_BYTE)Character;
    if ( ((unsigned int)&unk_800000 & *(_DWORD *)(*Character + 2064)) != 0 )
    {
      LOBYTE(v1) = (_BYTE)Character;
      if ( Character[160] == 2 || Character[160] == 4 )
      {
        LOBYTE(v1) = rf_replicator_has_elapsed(Character + 183);
        if ( (_BYTE)v1 )
        {
          rf_replicator_arm_milliseconds(Character + 183, dword_661274[dword_6612A4]);
          v1 = *Character;
          v5 = *Character;
          for ( i = unk_68211C; (_UNKNOWN *)i != &unk_681E90; i = v1 )
          {
            if ( *(_DWORD *)(v5 + 44) != *(_DWORD *)(i + 44)
              && *(_DWORD *)(i + 504) == 2
              && (rf_object_is_player_associated(i) != 1 || byte_6663D0 != 1)
              && !rf_entity_is_dead(i)
              && !rf_object_has_respawn_inactive_flag(i)
              && !rf_entity_weapon_is_holstered_for_actions(i) )
            {
              v4 = rf_vector_fast_distance((const float *)(v5 + 60), (const float *)(i + 60));
              if ( (float)20.0 > (double)v4
                && sub_4024E0(v5, i)
                && !rf_segment_objects_or_world_hit_filtered_by_radius(v5 + 2004, i + 2004, 1.0, 3, v5, i, 0) )
              {
                if ( Character[160] == 4 )
                {
                  rf_ai_route_reset((int)(Character + 186));
                  rf_ai_numeric_mode_write(Character, 2, -1, -1);
                }
                sub_40BA80(Character, *(_DWORD *)(i + 44));
                v3 = rf_random_float_range(30.0, 50.0);
                LOBYTE(v1) = sub_40AC80(Character, *(_DWORD *)(i + 44), v3);
                return v1;
              }
            }
            v1 = *(_DWORD *)(i + 652);
          }
        }
      }
    }
  }
  return v1;
}

