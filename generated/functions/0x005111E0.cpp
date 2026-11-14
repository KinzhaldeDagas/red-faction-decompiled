// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005111E0 rf_weapon_has_positive_thrust_lifetime
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weaponflag/accessor provenance,particle descriptors,trails,ricochet/piercing andx87unorderedbranches,original ECX/stack flow and PE bytes): Cdeclsignedweaponindex,caller pops4,normalizedAL0 forinvalidindex. ValidreadsF32weapon+660 (parser optional$Thrust Lifetime,default0),returnORDERED value>0. Zero,negative andunorderedNaN reject(TESTAH41/JNZ);positiveinfinitypasses. No thruster flag,elapsedclock,currentprojectilefuel orownership check;read-only.
bool __cdecl rf_weapon_has_positive_thrust_lifetime(int a1)
{
  return a1 >= 0 && a1 < dword_911C68 && *((float *)&unk_912294 + 340 * a1) > 0.0;
}

