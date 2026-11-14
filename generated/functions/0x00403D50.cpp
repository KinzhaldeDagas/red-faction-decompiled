// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00403D50 rf_ai_global_exit_noop
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI/corpse-carry/inventory/projectile update chains, original field layouts and float constants and native
// signed/x87/stack/callback ABI): Cdecl no-argument exit hook registered by403D30. Native body is prologue, epilogue, RET only; no state writes, calls or defined return value.
void __cdecl rf_ai_global_exit_noop()
{
  ;
}

