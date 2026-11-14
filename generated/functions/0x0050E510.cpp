// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050E510 rf_projectile_disable_attached_emitters
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile pre/post physics,homing/expiry/render branches,two-argument cone ABI andx87unordered flow,original ECX/stack flow and PE bytes): Traverses object emitter head DWORD+616 until NULL, follows each emitter next+336 AFTER calling4CE0B0 disable (clears enabled byte+320). Does not free/unlink emitters, clear head, stop projectile voice/light or set object deletion. No NULL object/cycle guard. EAX returns object pointer if list initially empty, otherwise NULL after final next load; not an emitter count or boolean status.
int __cdecl rf_projectile_disable_attached_emitters(int a1)
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  result = a1;
  for ( i = *(_DWORD *)(a1 + 616); i; i = result )
  {
    rf_particle_emitter_disable((_BYTE *)i);
    result = *(_DWORD *)(i + 336);
  }
  return result;
}

