// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00403AB0 rf_entity_inventory_grant_weapon
// UNREALRED VERIFIED [combat-selected-drop-20261111]: Native grant first checks selected ownership byte. Newly-owned positive active clip replaces loaded counter from grant quantity/fullclip sentinel; reserve accounting separate. No-positive-clip branch leaves existing loaded counter alone. Dropped hidden magazine state therefore survives removal, although positiveclip reacquisition may overwrite it. Preserve stored record lifetime independently of presence.
// UNREALRED VERIFIED [combat-ammo-identity-20261111]: Exact counter semantics: alreadyowned byte=>NO counter writes or4014F0. New positiveclip and quantity-1 writes weapon-indexed fullclip only; no reserve access. Positiveclip otherquantity writes signedmin(qty,clip), overflow qty>clip?qty-clip:0, then UNGUARDED reserve[AmmoID] wrapping-add+lower-firstclamp0..activeMax. AmmoID-1 aliases AI+8 SECONDARY SELECTION even when overflow0; negativeindex is NOT universally ammo-less. Nonpositiveclip guardsAmmoID>=0 before wrapping-add+sameclamp and leavesloaded untouched. Finallysetsowned=1 and calls4014F0 forced. Do not saturate arithmetic or normalize reversed clamp bounds.
char __cdecl rf_entity_inventory_grant_weapon(int *a1, int a2, int a3)
{
  char result; // al
  int v4; // [esp+0h] [ebp-8h]
  int v5; // [esp+4h] [ebp-4h]

  result = a2 + (_BYTE)a1;
  if ( !*((_BYTE *)a1 + a2 + 396) )
  {
    v5 = dword_912024[340 * a2];
    if ( unk_912088[340 * a2] <= 0 )
    {
      if ( v5 >= 0 )
      {
        a1[v5 + 3] += a3;
        rf_integer_clamp_in_place(&a1[v5 + 3], 0, unk_912260[340 * a2]);
      }
    }
    else if ( a3 == -1 )
    {
      a1[a2 + 35] = unk_912088[340 * a2];
    }
    else
    {
      v4 = 0;
      if ( a3 > unk_912088[340 * a2] )
        v4 = a3 - unk_912088[340 * a2];
      a1[a2 + 35] = rf_int_min_signed(a3, unk_912088[340 * a2]);
      a1[v5 + 3] += v4;
      rf_integer_clamp_in_place(&a1[v5 + 3], 0, unk_912260[340 * a2]);
    }
    *((_BYTE *)a1 + a2 + 396) = 1;
    return sub_4014F0(a1, 1);
  }
  return result;
}

