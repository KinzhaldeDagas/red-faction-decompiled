// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004013E0 rf_ai_current_weapon_priority_slot
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): One AI block. Primary index DWORD+4<0 invokes4013A0(block), then re-reads selected index without validating
// repair success. Reads owner signed DWORD+5244; negative returns-1. Nonnegative indexes record84-byte stride at75768C, obtains row DWORD, then scans exactly8 DWORD
// entries661018+32*row in ascending order comparing selected index. Returns first matching slot0..7, or-2 if no match. No owner/record/row upper bound, no explicit rejection of
// still-negative selected index, no ammo/ownership filtering in this body. Helper call may change primary index; this is not a pure lookup on negative-primary path.
int __cdecl rf_ai_current_weapon_priority_slot(int *a1)
{
  int v2; // [esp+4h] [ebp-Ch]
  int i; // [esp+8h] [ebp-8h]

  if ( a1[1] < 0 )
    sub_4013A0(a1);
  v2 = *(_DWORD *)(*a1 + 5244);
  if ( v2 < 0 )
    return -1;
  for ( i = 0; i < 8; ++i )
  {
    if ( dword_661018[8 * unk_75768C[21 * v2] + i] == a1[1] )
      return i;
  }
  return -2;
}

