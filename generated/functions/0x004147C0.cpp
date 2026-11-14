// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004147C0 rf_clutter_contact_response_code
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter runtime teardown/render admission, DWORD-category glass callback, cached model binding and signed-counter clock-hand geometry): ECX clutter/common object,no stackargs,plainRET. Only ORDERED reciprocal468==0 returns2 immediately;nonzero OR unordered resolves otherUID484. Unresolvedother returns2;otherwise calls413BB0(self,other),maps callback nonzero to2 andzero to1. Current callback ALWAYSreturnsAL0,so resolved-other path returns1 EVEN when callback changed self float52 to0 for flag0x200 entity. No generic impulse/damage application orNULLself guard;return code2 does not imply callback mutation andcode1 does not imply untouchedself.
int __thiscall rf_clutter_contact_response_code(int this)
{
  int v3; // [esp+4h] [ebp-4h]

  if ( *(float *)(this + 468) == 0.0 )
    return 2;
  v3 = rf_object_resolve_handle(*(_DWORD *)(this + 484));
  if ( !v3 )
    return 2;
  if ( rf_callback_zero_float52_for_flag200_entity(this, v3) )
    return 2;
  return 1;
}

