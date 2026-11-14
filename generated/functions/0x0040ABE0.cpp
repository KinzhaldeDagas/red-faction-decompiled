// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040ABE0 rf_ai_selected_weapon_projectile_retarget_or_delay
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Cdecl(required AI block, owner pointer at+0); AL/EAX is path-dependent delegate residue, not a uniform success result. Calls
// selected-weapon/association predicate40B6D0(block) and enters retarget branch ONLY on exact AL1. That branch resolves block+704 through projectile UID/type2 resolver50FE20; a
// nonnull projectile supplies its DWORD+48 to guarded central target writer40BA80(block,value). Missing projectile skips that writer only. Both paths then call peer
// propagation40B2D0(block), whose result survives. All other predicate bytes instead call humanoid predicate40D150(owner); any nonzero result arms embedded block+1236 deadline
// inclusive3000..6000ms, then RE-READS owner and zeros all three floats at owner+336 using5595E0. Nonhumanoid leaves deadline/vector untouched and AL0 from predicate. Armed path AL
// is the low byte of zero-helper destination, not canonical true. No route reset or direct numeric mode write occurs in this wrapper; accepted target-writer and propagation delegate
// effects remain ordered.
char __cdecl rf_ai_selected_weapon_projectile_retarget_or_delay(int *a1)
{
  char result; // al
  int v2; // [esp+0h] [ebp-4h]

  if ( sub_40B6D0(a1) == 1 )
  {
    v2 = rf_projectile_resolve_uid_type2(a1[176]);
    if ( v2 )
      sub_40BA80(a1, *(_DWORD *)(v2 + 48));
    return sub_40B2D0(a1);
  }
  else
  {
    result = rf_entity_has_humanoid_flag(*a1);
    if ( result )
    {
      rf_timestamp_arm_random_inclusive_milliseconds(a1 + 309, 3000, 6000);
      return (unsigned __int8)rf_vector3_zero_return_destination((float *)(*a1 + 336));
    }
  }
  return result;
}

