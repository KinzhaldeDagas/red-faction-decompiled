// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00408DB0 rf_ai_scan_projectile_and_entity_reactions
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): One required AI block. Deadline+736 elapsed EXACT1 first rearms inclusive400..800ms, BEFORE438AC0(owner)==EXACT1
// or inactive predicate==EXACT1 rejects. No own global pause/dead/authority check. Humanoid EXACT1 enables projectile list911F74 ->911CE8, next+652. Admit weapon index projectile+664
// when grenade-index predicate5119F0(index) nonzero OR remote-charge predicate(index) nonzero. Common-position Euclidean distance roundsfloat32. Distance<=DOUBLE1 OR UNORDERED sets
// local near1 and BYPASSES angular, collision and own-projectile rejection. Ordered distance>1 requires4024E0(owner,projectile) nonzero, seven-slot
// collision(owner+2004,projectile+60,FLOAT0.5,39,owner,projectile,NULL)!=EXACT AL1, and projectile owner DWORD+48!=owner full handle+44. Tracking-byte initially0: notably
// remote-charge predicate is then called with projectile COMMON TYPE DWORD+36 (not weapon index+664); only EXACT AL1 scans block pointer array+524, signed count re-read, for raw
// entry==projectile handle+44, marking tracked1. Danger requires class pointer(projectile+660) FLOAT+520 ORDERED STRICTLY>distance-owner FLOAT+120. Equality or UNORDERED goes to far
// branch. Danger: if current AI mode3 and retained target==projectile handle, guarded target setter(projectile owner+48), break projectile scan. Otherwise untracked OR attached
// projectile+688!=-1 ->40AC80(block,near?projectile owner:projectile handle,near?3.0f:1.0f), break; tracked AND unattached skips. Far branch calls maximum attack range4098B0; ordered
// distance<returned range AND tracked EXACT1 ->guarded target projectile handle then40B2D0, break. All list ordering first-match, no closest selection. Projectile break DOES NOT
// return: follows second phase with CURRENT state after effects. Primary modes7/12 suppress second phase only. Forced-local boolean=(primary-flag20-without-secondary nonzero AND
// mode3 AND global681E38 nonnull AND retained target==global handle). Forced-local OR humanoid nonzero enables entity list68211C ->681E90,next+652: skip inactive EXACT1, require
// candidate class(+660) flags+1828 mask0x8000 via437340 nonzero and (candidate+2064 mask0x10000 OR local-player-or-related predicate nonzero OR forced-local). Threshold FLOAT36
// squared units, replaced144 only when candidate not local-related and source owner DWORD+504==0. Squared common-position distance roundsfloat32, requires ordered strict<threshold,
// equality/NaN reject. First admitted candidate calls40AC80(block,forced-local?global handle:candidate handle,FLOAT4.0) and returns regardless of delegate acceptance. No explicit
// self/dead/friendliness-match filter beyond these predicates, no geometry query in entity phase; up to one projectile reaction followed by one entity reaction can occur in a single
// call.
void __cdecl rf_ai_scan_projectile_and_entity_reactions(int *Character)
{
  bool v1; // [esp+14h] [ebp-2Ch]
  float v2; // [esp+18h] [ebp-28h]
  char v3; // [esp+1Fh] [ebp-21h]
  float v4; // [esp+20h] [ebp-20h]
  char v5; // [esp+27h] [ebp-19h]
  float v6; // [esp+28h] [ebp-18h]
  int j; // [esp+2Ch] [ebp-14h]
  char v8; // [esp+33h] [ebp-Dh]
  int i; // [esp+34h] [ebp-Ch]
  int k; // [esp+38h] [ebp-8h]

  if ( rf_replicator_has_elapsed(Character + 184) )
  {
    rf_timestamp_arm_random_inclusive_milliseconds(Character + 184, 400, 800);
    if ( !sub_438AC0(*Character) && !rf_object_has_respawn_inactive_flag(*Character) )
    {
      if ( rf_entity_has_humanoid_flag(*Character) )
      {
        for ( i = dword_911F74; (_UNKNOWN *)i != &unk_911CE8; i = *(_DWORD *)(i + 652) )
        {
          if ( sub_5119F0(*(_DWORD *)(i + 664)) || rf_weapon_has_remote_charge_flag(*(_DWORD *)(i + 664)) )
          {
            v6 = rf_vector_distance((const float *)(i + 60), (const float *)(*Character + 60));
            v5 = 0;
            if ( v6 <= 1.0 )
            {
              v5 = 1;
            }
            else if ( !sub_4024E0(*Character, i)
                   || rf_segment_objects_or_world_hit_filtered_by_radius(
                        *Character + 2004,
                        i + 60,
                        0.5,
                        39,
                        *Character,
                        i,
                        0) == 1
                   || *(_DWORD *)(i + 48) == *(_DWORD *)(*Character + 44) )
            {
              continue;
            }
            v8 = 0;
            if ( rf_weapon_has_remote_charge_flag(*(_DWORD *)(i + 36)) )
            {
              for ( j = 0; j < rf_receiver_get_first_dword(Character + 131); ++j )
              {
                if ( *(_DWORD *)sub_552200(Character + 131, j) == *(_DWORD *)(i + 44) )
                {
                  v8 = 1;
                  break;
                }
              }
            }
            if ( *(float *)(*(_DWORD *)(i + 660) + 520) <= v6 - *(float *)(*Character + 120) )
            {
              if ( v6 < rf_ai_resolve_maximum_attack_range(Character) && v8 == 1 )
              {
                sub_40BA80(Character, *(_DWORD *)(i + 44));
                sub_40B2D0(Character);
                break;
              }
            }
            else
            {
              if ( Character[160] == 3 && Character[176] == *(_DWORD *)(i + 44) )
              {
                sub_40BA80(Character, *(_DWORD *)(i + 48));
                break;
              }
              if ( !v8 || *(_DWORD *)(i + 688) != -1 )
              {
                if ( v5 == 1 )
                  sub_40AC80(Character, *(_DWORD *)(i + 48), 3.0);
                else
                  sub_40AC80(Character, *(_DWORD *)(i + 44), 1.0);
                break;
              }
            }
          }
        }
      }
      if ( Character[160] != 7 && Character[160] != 12 )
      {
        v1 = rf_ai_primary_flag20_without_secondary((int)Character)
          && Character[160] == 3
          && dword_681E38
          && Character[176] == *(_DWORD *)(dword_681E38 + 44);
        if ( v1 || rf_entity_has_humanoid_flag(*Character) )
        {
          for ( k = unk_68211C; (_UNKNOWN *)k != &unk_681E90; k = *(_DWORD *)(k + 652) )
          {
            if ( !rf_object_has_respawn_inactive_flag(k) && rf_entity_class_has_flags724_mask8000(k) )
            {
              v3 = rf_entity_matches_local_player_or_related_handle(k);
              if ( (*(_DWORD *)(k + 2064) & 0x10000) != 0 || v3 || v1 )
              {
                v4 = 36.0;
                if ( !v3 && !*(_DWORD *)(*Character + 504) )
                  v4 = 144.0;
                v2 = rf_vector_distance_squared((const float *)(k + 60), (const float *)(*Character + 60));
                if ( v4 > (double)v2 )
                {
                  if ( v1 )
                    sub_40AC80(Character, *(_DWORD *)(dword_681E38 + 44), 4.0);
                  else
                    sub_40AC80(Character, *(_DWORD *)(k + 44), 4.0);
                  return;
                }
              }
            }
          }
        }
      }
    }
  }
}

