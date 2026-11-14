// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A9E40 rf_multiplayer_peer_update_interval_recompute
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// Cdecl(player), requires nonnull player and net+4608; no own runtime/authority guard. Gets estimate E from4A6FC0 (caller pushes player but helper does not read it).
// Budget=float(max(signed floor662C34,trunc(net requested-rate DWORD+2492 * PE double0.8999999761581421))). If game flags400 set, counts ALL players, D=max(count-1,1), forms
// single-precision global signed cap662C60/D, then exact float-min helper selects cap when cap<=budget, otherwise budget (NaN follows delegate comparisons).
// Computes single-precision intervalRatio=E/budget, multiplies that stored float by double1000, truncates via __ftol2_sse, stores signed max(result,85) into net+2496. No
// positive-budget/divide-by-zero/overflow guard, no peer exclusion by state or direct packet send. Preserves native float rounding points; does not compute using exact real
// arithmetic.
void __cdecl rf_multiplayer_peer_update_interval_recompute(int a1)
{
  _DWORD *v1; // [esp+8h] [ebp-24h]
  int v2; // [esp+10h] [ebp-1Ch]
  int v3; // [esp+10h] [ebp-1Ch]
  _DWORD *i; // [esp+14h] [ebp-18h]
  float v5; // [esp+18h] [ebp-14h]
  float v6; // [esp+1Ch] [ebp-10h]
  float v7; // [esp+20h] [ebp-Ch]
  int updated; // [esp+28h] [ebp-4h]

  if ( a1 && *(_DWORD *)(a1 + 4608) )
  {
    updated = rf_multiplayer_update_size_estimate();
    v7 = (float)rf_int_max(dword_662C34, (int)((double)*(int *)(*(_DWORD *)(a1 + 4608) + 2492) * 0.8999999761581421));
    if ( (rf_multiplayer_game_flags & 0x400) != 0 )
    {
      v2 = 0;
      for ( i = (_DWORD *)dword_87C324; i; i = v1 )
      {
        ++v2;
        if ( *i == dword_87C324 )
          v1 = nullptr;
        else
          v1 = (_DWORD *)*i;
      }
      v3 = v2 - 1;
      if ( v3 <= 0 )
        v3 = 1;
      v5 = (double)*(int *)&dword_662C60 / (double)v3;
      v7 = rf_float_minimum_two_values(v7, v5);
    }
    v6 = (double)updated / v7;
    *(_DWORD *)(*(_DWORD *)(a1 + 4608) + 2496) = rf_int_max((int)(v6 * 1000.0), 85);
  }
}

