// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00587A40 rf_character_reserved_noop_587A40
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Entry only saves/restores stack frame and ECX locally, then RET. No object/global writes, calls or meaningful return value; no known incoming reference in current database. Prior generic runtime classification does not establish a more specific class role.
void rf_character_reserved_noop_587A40()
{
  ;
}

