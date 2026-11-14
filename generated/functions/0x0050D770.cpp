// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050D770 rf_weapon_recompute_lifetime_velocity_product
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile pre/post physics,homing/expiry/render branches,two-argument cone ABI andx87unordered flow,original ECX/stack flow and PE bytes): Loops signed i=0..<global weapon count911C68, stride1360 at912000; writes record F32+204=F32(runtime lifetime+176 * runtime velocity+192). Does not use authored SP source fields180/200 directly, fixed64 cap, validation or allocation. Native EAX is incidental loop residue (count for positive count, uninitialized if loop skipped), not reliable success.
int rf_weapon_recompute_lifetime_velocity_product()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < dword_911C68; ++i )
  {
    *((float *)&unk_9120CC + 340 * i) = *((float *)&unk_9120B0 + 340 * i) * *((float *)&unk_9120C0 + 340 * i);
    result = i + 1;
  }
  return result;
}

