// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00402160 rf_ai_choose_weighted_target_handle
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI weighted-target/mode11/15/16/speech/stimulus chains, original dispatch/float constants and native field
// lifetime and native signed/x87/stack/callback ABI): Cdecl(required owner entity,threshold float); callers may push extra difficulty+2 but native body reads ONLY first two stack
// args. Entity list next+652 to681E90, exclude equal handle+44. Per candidate multiplier1; player-associated EXACT1 plus BYTE6663D0==EXACT1 rejects; otherwise associated EXACT1 in
// any-nonzero runtime/splitscreen gets multiplier=float32(1-signed difficulty6612A4/DOUBLE5), marked weighted-player. Reject dead EXACT1,pending-delete common
// mask2,mode1,401180(owner,candidate) AL0,inactive EXACT1. Score=float32(fastDistance(common positions)*multiplier). Threshold gate admits ordered score<threshold OR UNORDERED;
// equality rejects. Candidate flags+2000 mask0x10000, carried handle+1884==-1, alarm AL0, signed elapsed timestamp+5116>1000ms, holstered EXACT1, and402540(candidate,owner) AL0
// together suppress only when score ordered>4. Owner mask0x80 restricts candidates to player-associated any-nonzero. Owner mode11 rejects candidate when global seconds minus
// float32(latest activity436440(candidate)) ordered>DOUBLE0.2; equality/NaN continue. Owner mask0x20000 bypasses angular predicate4024E0; otherwise require nonzero AL. Clear bypass
// mask immediately after angular admission, before occlusion/final-score rejection. Then alternate geometry origin using owner mask0x40000: set copies retained point+2004 and clears
// bit, clear copies common position+60 and sets bit. Query geometry(origin,candidate+2004,mask3,NULL), any nonzero AL rejects. Final best comparison is ORDERED strictly score<best,
// unlike threshold gate; equal/NaN never win, but earlier flag side effects remain. Best starts threshold, result-1. A weighted-player that becomes best latches seen-player byte
// permanently for this call even if later nonplayer replaces it. After scan, ONLY nonzero splitscreen with no latched weighted player and retained owner target+1376!=-1 consumes
// rand()%3; remainder1/2 returns retained handle WITHOUT resolution, even over another selected best. Otherwise returns best full handle. No difficulty clamp, positive score
// requirement, extra caller-argument consumption or uniform source-player exclusion.
// UNREALRED VERIFIED [original-target-scan-continuation-20261112]: Distance dependency5598F0 subtracts raw COMMON positions with binary32 component stores then558CC0 FAST length; it is NOT Euclidean sqrt. Preserve unordered threshold admission and ordered finalbest comparison: admitted NaN can consume Entity7D0 bit20000 and flip40000 before4D0220mask3 fails/finalbest rejects. Entity next652 is read after candidate predicates/query; a valid tail append during a helper may therefore be observed.6663D0 is a distinct PE-zero byte, not the mission undercover flag; decoded direct code xrefs only read it.
int __cdecl rf_ai_choose_weighted_target_handle(const float *a1, float a2)
{
  double v2; // st7
  float v4[3]; // [esp+0h] [ebp-50h] BYREF
  float copy_result[3]; // [esp+Ch] [ebp-44h] BYREF
  float v6; // [esp+18h] [ebp-38h]
  float v7; // [esp+1Ch] [ebp-34h]
  float destination[3]; // [esp+20h] [ebp-30h] BYREF
  int v9; // [esp+2Ch] [ebp-24h]
  int v10; // [esp+30h] [ebp-20h]
  float v11; // [esp+34h] [ebp-1Ch]
  float v12; // [esp+38h] [ebp-18h]
  _BYTE v13[15]; // [esp+3Ch] [ebp-14h] BYREF
  char v14; // [esp+4Bh] [ebp-5h]
  float *i; // [esp+4Ch] [ebp-4h]

  rf_vector3_default_construct_noop(v13);
  v14 = 0;
  v10 = -1;
  v12 = a2;
  for ( i = (float *)unk_68211C; i != (float *)&unk_681E90; i = *((float **)i + 163) )
  {
    v7 = 1.0;
    v9 = 0;
    if ( *((_DWORD *)a1 + 11) == *((_DWORD *)i + 11) )
      continue;
    if ( rf_object_is_player_associated((int)i) == 1 )
    {
      if ( byte_6663D0 == 1 )
        continue;
      if ( rf_splitscreen_runtime_active | rf_multiplayer_runtime_mode )
      {
        v9 = 1;
        v7 = 1.0 - (double)dword_6612A4 / 5.0;
      }
    }
    if ( !rf_entity_is_dead((int)i) && ((_DWORD)i[31] & 2) == 0 && *((_DWORD *)i + 328) != 1 )
    {
      if ( sub_401180((int)a1, (int)i) )
      {
        if ( !rf_object_has_respawn_inactive_flag((int)i) )
        {
          v2 = rf_vector_fast_distance(a1 + 15, i + 15);
          v11 = v2 * v7;
          if ( a2 > (double)v11
            && (((_DWORD)i[500] & 0x10000) == 0
             || *((_DWORD *)i + 471) != -1
             || rf_alarm_get_shared_active()
             || rf_timestamp_signed_elapsed_milliseconds(i + 1279) <= 1000
             || !rf_entity_weapon_is_holstered_for_actions((int)i)
             || rf_ai_player_candidate_has_other_mode3_tracker((int)i, (int)a1)
             || v11 <= 4.0)
            && (((_DWORD)a1[500] & 0x80) == 0 || rf_object_is_player_associated((int)i)) )
          {
            if ( *((_DWORD *)a1 + 328) != 11
              || (v6 = rf_entity_latest_activity_timestamp(i), *(float *)&dword_6FC428 - v6 <= 0.2) )
            {
              if ( ((_DWORD)a1[500] & 0x20000) != 0 || sub_4024E0((int)a1, (int)i) )
              {
                *((_DWORD *)a1 + 500) &= ~0x20000u;
                rf_vector3_default_construct_noop(destination);
                if ( ((_DWORD)a1[500] & 0x40000) != 0 )
                {
                  rf_vector_copy(destination, copy_result, a1 + 501);
                  *((_DWORD *)a1 + 500) &= ~0x40000u;
                }
                else
                {
                  rf_vector_copy(destination, v4, a1 + 15);
                  *((_DWORD *)a1 + 500) |= 0x40000u;
                }
                if ( !rf_geometry_segment_is_obstructed((int)destination, (int)(i + 501), 3, 0) && v12 > (double)v11 )
                {
                  v12 = v11;
                  v10 = *((_DWORD *)i + 11);
                  if ( v9 )
                  {
                    if ( !v14 )
                      v14 = 1;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  if ( !rf_splitscreen_runtime_active || v14 || *((_DWORD *)a1 + 344) == -1 || !(rand() % 3) )
    return v10;
  else
    return *((_DWORD *)a1 + 344);
}

