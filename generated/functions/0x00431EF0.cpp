// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00431EF0 rf_weapon_decrement_clip_or_reserve_ammo
// UNREALRED VERIFIED [combat-ammo-identity-20261111]: Qualification: validweapon0..63 uses POSITIVE activeclip predicate. Positiveclip decrements THAT weapon loaded; otherwise UNGUARDED reserve[weapon.AmmoID]. Decrement is wrapping32bit then signed<0 floor0 (INT_MIN wrapsINT_MAX). UnknownAmmoID-1 aliases selectedsecondary Entity2A8 in noclip branch; this is not same as safe4391D0 query.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity node pose/physics, VFX rendering, secondary ammunition and attachment/detach native chains and native
// signed/x87/stack/callback ABI): Cdecl(entity pointer,signed weapon index), void. Literal signed0<=weapon<64 gate; invalid exits before entity access. Calls511240
// positive-active-clip predicate; EXACT AL1 decrements entity DWORD[812+4*weapon], every other byte decrements entity DWORD[684+4*weapon.AmmoID]. No NULL entity guard and no AmmoID
// lower/upper bound in reserve branch: AmmoID-1 aliases entity+680 selected secondary. Each branch loads value, subtracts1 with wrapping32 arithmetic, STORES wrapped result, then
// re-reads stored value and floors to0 ONLY if signed negative; INT_MIN wraps toINT_MAX and is retained. This is not a saturating mathematical decrement and does not always consume
// loaded ammo. No ammo-availability/ownership/death/authority gate, reserve-to-clip transfer or status result. Repeated AmmoID/entity reads and store-before-floor order are native;
// raw invalid IDs are not given safe4391D0 fallback.
void __cdecl rf_weapon_decrement_clip_or_reserve_ammo(int a1, unsigned int a2)
{
  if ( a2 < 0x40 )
  {
    if ( rf_weapon_has_positive_clip_size(a2) )
    {
      if ( (int)--*(_DWORD *)(a1 + 4 * a2 + 812) < 0 )
        *(_DWORD *)(a1 + 4 * a2 + 812) = 0;
    }
    else if ( (int)--*(_DWORD *)(a1 + 4 * dword_912024[340 * a2] + 684) < 0 )
    {
      *(_DWORD *)(a1 + 4 * dword_912024[340 * a2] + 684) = 0;
    }
  }
}

