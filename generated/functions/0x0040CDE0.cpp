// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040CDE0 rf_ai_resume_updates
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI/corpse-carry/inventory/projectile update chains, original field layouts and float constants and native
// signed/x87/stack/callback ABI): No arguments. Single state effect BYTE6663D1=0. No traversal, timer adjustment, weapon restart, velocity restoration or independent return value.
void rf_ai_resume_updates()
{
  byte_6663D1 = 0;
}

