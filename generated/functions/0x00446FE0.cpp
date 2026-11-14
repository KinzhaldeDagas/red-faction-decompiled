// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00446FE0 rf_foley_get_material_or_invalid
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): Cdecl(groupIndex), one DWORD. Signed groupIndex<0 or groupIndex>=LIVE DWORD6EDC30 returns full EAX=-1. Otherwise returns the
// raw material DWORD at6E6E50+44*groupIndex with native32-bit address arithmetic. No count/list validation, allocation, mutation or fallback material conversion; a stored -1 is
// indistinguishable from an invalid index.
int __cdecl rf_foley_get_material_or_invalid(int a1)
{
  if ( a1 >= 0 && a1 < unk_6EDC30 )
    return unk_6E6E50[11 * a1];
  else
    return -1;
}

