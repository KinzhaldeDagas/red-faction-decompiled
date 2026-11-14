// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00587A50 rf_character_reserved_noop_587A50
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Entry only saves/restores frame and ECX locally, then RET; no object/global writes or callees. Called by wrapper5629C0. Exact original class role is unproven; no-op behavior verified, no meaningful return contract.
void rf_character_reserved_noop_587A50()
{
  ;
}

