// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00403D30 rf_ai_global_initialize_exit_hook
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI/corpse-carry/inventory/projectile update chains, original field layouts and float constants and native
// signed/x87/stack/callback ABI): No arguments. Writes DWORD6663C4=0 then registers403D50 noop using atexit. Returns atexit EAX; zero store happens even if registration fails. No
// bulk AI state, accumulated profiling ticks, pause byte or global deadline initialization here.
int rf_ai_global_initialize_exit_hook()
{
  dword_6663C4 = 0;
  return atexit(rf_ai_global_exit_noop);
}

