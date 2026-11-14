// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00403CB0 rf_ai_remove_weapon_and_clear_shared_ammo
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI/corpse-carry/inventory/projectile update chains, original field layouts and float constants and native
// signed/x87/stack/callback ABI): Cdecl(AI block,weapon index). First403C20 removes ownership only for its valid0..63 IDs and may notify local player. Independently and WITHOUT
// preserving that range admission, this wrapper reads signed ammo pool index at912024+1360*weaponID. If pool index>=0 clears DWORD counters AI+12+4*poolIndex and AI+140+4*poolIndex
// (reserve and loaded counters under existing ammo schema); negative leaves both untouched. No own weapon/pool upper bound, selected-weapon reset or other ownership clearing.
// Returning EAX is raw signed pool index. Unlike403C20 alone, this operation clears the shared pool, affecting other weapons using the same index.
int __cdecl rf_ai_remove_weapon_and_clear_shared_ammo(int a1, unsigned int a2)
{
  int result; // eax

  sub_403C20(a1, a2);
  result = dword_912024[340 * a2];
  if ( result >= 0 )
  {
    *(_DWORD *)(a1 + 4 * result + 12) = 0;
    *(_DWORD *)(a1 + 4 * result + 140) = 0;
  }
  return result;
}

