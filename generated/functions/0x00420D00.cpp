// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00420D00 rf_entity_apply_landing_sound_and_motion_reset
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): Cdecl(required entity); no uniform AL/EAX success result. Stores float32 delta=entity FLOAT+476 minus FLOAT+328. Only ORDERED
// delta>DOUBLE0.25 enters sound branch immediately; otherwise calls vector length40CFA0(entity+324) and directly compares returned ST0 with DOUBLE0.5, without an extra caller float
// store; only ORDERED length>0.5 enters. Equality/NaN alone does not satisfy either gate. Sound branch chooses index: negative signed entity DWORD+4992=>0; nonnegative retained only
// if signed gameplay class(+660) DWORD[320+4*index]>0, otherwise0; no upper index bound. Entity flags+2064 mask0x1000 AND signed class DWORD+336>0 overrides index4. Calls446F60(class
// DWORD[320+4*index],0), then sound wrapper4BCDD0(entity,by-value COMMON position+60,event,1.0,0.0) without rejecting event-1. After playback,438AC0 any-nonzero writes BYTE1 to
// player-pointer(entity+5168)+176; predicate verifies player flag/nonnull pointer, not local-player identity. Audio result is ignored.  ALWAYS afterwards replaces entity vector+324
// with float32 componentwise(float32(oldVector+324 + entityVector+2208) - entityVector+472), via separate add/subtract/copy temporaries. Thus sum rounds before subtraction,
// regardless of whether sound gate passed. Then numeric entity DWORD+1312==4 delegates4355A0(entity) when flags+2064 mask0x100000 set, otherwise435500(entity,LOWBYTE0), and
// immediately returns delegated register residue. This state4 path skips later route fit/crouch handling and does NOT clear physical mask0x200000.  For every other numeric state,
// gameplay class flags DWORD+1828 mask0x02000000 triggers route_reset(entity+1416), then40FD80(position+60,FLOAT+1984,FLOAT+1988,1,&entity+1692,&entity+1696,0) with DISTINCT output
// pointers and ignored result, then40B2D0(entity+672) even on failed fit. Afterwards crouch predicate40CED0 ANY nonzero selects435500(entity,LOWBYTE1), else4355A0(entity). Ignores
// delegate result, clears entity DWORD+424 mask0x00200000 and returns EAX=entity pointer. No own null/dead/authority guard, velocity rollback or route-fit failure exit;
// sound/player-bit/vector and delegate prefix effects remain.
char __cdecl rf_entity_apply_landing_sound_and_motion_reset(int a1)
{
  float *v1; // eax
  float *v2; // eax
  float v4; // [esp+0h] [ebp-4Ch] BYREF
  int v5; // [esp+4h] [ebp-48h]
  int v6; // [esp+8h] [ebp-44h]
  int sound_by_index; // [esp+Ch] [ebp-40h]
  float v8; // [esp+10h] [ebp-3Ch]
  float v9; // [esp+14h] [ebp-38h]
  int v10; // [esp+18h] [ebp-34h]
  float copy_result[3]; // [esp+1Ch] [ebp-30h] BYREF
  float out_vector[3]; // [esp+28h] [ebp-24h] BYREF
  float sum_result[4]; // [esp+34h] [ebp-18h] BYREF
  int v14; // [esp+44h] [ebp-8h]
  float v15; // [esp+48h] [ebp-4h]

  v15 = *(float *)(a1 + 476) - *(float *)(a1 + 328);
  if ( v15 > 0.25 || rf_vector3_length((float *)(a1 + 324)) > 0.5 )
  {
    if ( *(int *)(a1 + 4992) >= 0 )
    {
      if ( *(int *)(*(_DWORD *)(a1 + 660) + 4 * *(_DWORD *)(a1 + 4992) + 320) <= 0 )
        v10 = 0;
      else
        v10 = *(_DWORD *)(a1 + 4992);
      v14 = v10;
    }
    else
    {
      v14 = 0;
    }
    if ( (*(_DWORD *)(a1 + 2064) & 0x1000) != 0 && *(int *)(*(_DWORD *)(a1 + 660) + 336) > 0 )
      v14 = 4;
    v9 = 0.0;
    v8 = 1.0;
    sound_by_index = rf_foley_get_sound_by_index(*(_DWORD *)(*(_DWORD *)(a1 + 660) + 4 * v14 + 320), 0);
    rf_vector3_copy_return_destination(&v4, (float *)(a1 + 60));
    rf_sound_event_play_for_object_view(a1, v4, v5, v6, sound_by_index, v8, v9);
    if ( sub_438AC0(a1) )
      *(_BYTE *)(*(_DWORD *)(a1 + 5168) + 176) = 1;
  }
  LODWORD(v9) = a1 + 472;
  v8 = COERCE_FLOAT(out_vector);
  v1 = rf_vector_add((const float *)(a1 + 324), sum_result, (const float *)(a1 + 2208));
  v2 = rf_vector_subtract(v1, (float *)LODWORD(v8), (const float *)LODWORD(v9));
  rf_vector_copy((float *)(a1 + 324), copy_result, v2);
  if ( *(_DWORD *)(a1 + 1312) == 4 )
  {
    if ( (*(_DWORD *)(a1 + 2064) & 0x100000) != 0 )
      return sub_4355A0(a1);
    else
      return sub_435500(a1, 0);
  }
  else
  {
    if ( ((unsigned int)&unk_2000000 & *(_DWORD *)(*(_DWORD *)(a1 + 660) + 1828)) != 0 )
    {
      rf_ai_route_reset(a1 + 1416);
      v9 = 0.0;
      LODWORD(v8) = a1 + 1696;
      sound_by_index = a1 + 1692;
      v6 = 1;
      v5 = a1;
      v5 = *(int *)(a1 + 1988);
      LODWORD(v4) = a1;
      sub_40FD80((float *)(a1 + 60), *(float *)(a1 + 1984), *(float *)&v5, 1, (int *)(a1 + 1692), (int *)(a1 + 1696), 0);
      sub_40B2D0((int *)(a1 + 672));
    }
    if ( rf_entity_is_crouched_state810(a1) )
      sub_435500(a1, 1);
    else
      sub_4355A0(a1);
    *(_DWORD *)(a1 + 424) &= ~0x200000u;
    return a1;
  }
}

