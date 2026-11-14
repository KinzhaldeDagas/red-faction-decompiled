// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00438DE0 rf_entity_restore_action_tables_and_apply_weapon_overrides
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(entity,signed weapon index), void. NULL or ORIGINAL index<0 returns before own table writes;40D280 any
// nonzero AL additionally requires model128 nonnull and class660 DWORD148==2, no humanoid flag test. If input equals global911C98 replace local argument with global911CC4; no upper
// bound or post-remap lower-bound validation. FIRST always restore23 fixed16-byte records from entity3364 to active2276, then45 fixed16-byte records from3732 to active2644; each
// record copies four DWORDs sequentially. Only AFTER these resets: if class660 DWORD[1896+4*index] is SIGNED>0, iterate EXACT23 records from per-weapon pointer
// DWORD[entity4452+4*index], copying all16 bytes to corresponding active2276 record ONLY when source firstDWORD!=EXACT-1. Other negative/zero firstDWORD values admit. Independently
// class DWORD[2152+4*index] SIGNED>0 gates EXACT45 records from pointer entity4708+4*index into active2644 using same sentinel. Positive class values are admission gates, NOT loop
// lengths; zero/negative values skip overlays while restored defaults remain. No pointer/nonnegative mapped-index/64-entry cap or count-vs-allocation check; override pointers re-read
// during loops and no global source snapshot/overlap protection. Does not write selected primary676, stop firing, reset clocks, mutate inventory/class definitions or normalize the
// copied DWORD fields. No status/result or rollback; first reset/overlay changes remain if later source access fails.
void __cdecl rf_entity_restore_action_tables_and_apply_weapon_overrides(int a1, int a2)
{
  _DWORD *v2; // edx
  _DWORD *v3; // eax
  _DWORD *v4; // ecx
  _DWORD *v5; // edx
  _DWORD *v6; // eax
  _DWORD *v7; // ecx
  int i; // [esp+0h] [ebp-4h]
  int j; // [esp+0h] [ebp-4h]
  int k; // [esp+0h] [ebp-4h]
  int m; // [esp+0h] [ebp-4h]

  if ( a1 && a2 >= 0 && rf_entity_admits_speech_body_actions(a1) )
  {
    if ( a2 == unk_911C98 )
      a2 = dword_911CC4;
    for ( i = 0; i < 23; ++i )
    {
      v2 = (_DWORD *)(a1 + 16 * i + 2276);
      *v2 = *(_DWORD *)(a1 + 16 * i + 3364);
      v2[1] = *(_DWORD *)(a1 + 16 * i + 3368);
      v2[2] = *(_DWORD *)(a1 + 16 * i + 3372);
      v2[3] = *(_DWORD *)(a1 + 16 * i + 3376);
    }
    for ( j = 0; j < 45; ++j )
    {
      v3 = (_DWORD *)(a1 + 16 * j + 2644);
      *v3 = *(_DWORD *)(a1 + 16 * j + 3732);
      v3[1] = *(_DWORD *)(a1 + 16 * j + 3736);
      v3[2] = *(_DWORD *)(a1 + 16 * j + 3740);
      v3[3] = *(_DWORD *)(a1 + 16 * j + 3744);
    }
    if ( *(int *)(*(_DWORD *)(a1 + 660) + 4 * a2 + 1896) > 0 )
    {
      for ( k = 0; k < 23; ++k )
      {
        if ( *(_DWORD *)(16 * k + *(_DWORD *)(a1 + 4 * a2 + 4452)) != -1 )
        {
          v4 = (_DWORD *)(16 * k + *(_DWORD *)(a1 + 4 * a2 + 4452));
          v5 = (_DWORD *)(a1 + 16 * k + 2276);
          *v5 = *v4;
          v5[1] = v4[1];
          v5[2] = v4[2];
          v5[3] = v4[3];
        }
      }
    }
    if ( *(int *)(*(_DWORD *)(a1 + 660) + 4 * a2 + 2152) > 0 )
    {
      for ( m = 0; m < 45; ++m )
      {
        if ( *(_DWORD *)(16 * m + *(_DWORD *)(a1 + 4 * a2 + 4708)) != -1 )
        {
          v6 = (_DWORD *)(16 * m + *(_DWORD *)(a1 + 4 * a2 + 4708));
          v7 = (_DWORD *)(a1 + 16 * m + 2644);
          *v7 = *v6;
          v7[1] = v6[1];
          v7[2] = v6[2];
          v7[3] = v6[3];
        }
      }
    }
  }
}

