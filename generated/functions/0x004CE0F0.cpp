// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CE0F0 rf_particle_emitter_system_initialize
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, particle pool/list ownership, native damage admission, emitter initialization and cleanup): 
// Cdecl startup. Sets definition count 0x867904=0 and loads emitters.tbl. Self-links FREE emitter sentinel object base 0x867CD8 using next +328 at 0x867E20 and prev +332 at 0x867E24;
// self-links ACTIVE sentinel object base 0x867908 using link fields 0x867A50/0x867A54. Appends 128 emitter records at 0x867E30 with stride344 to the free tail using record links
// +328/+332. Sentinel base addresses differ from link-field addresses.
// This is list initialization, not 128 constructor calls or a payload memset. Does not detach former live emitters or free previous definitions before resetting count. Self-links
// detached particle sentinel 0x867C60 at +0/+4, registers rf_particle_emitter_definitions_exit_cleanup at 0x4CE1E0 with atexit, returns atexit status. Other particle debug
// counters/pools are initialized elsewhere.
// [UnrealRed burn initialization availability 2026-11-12; full original-byte ASM] Initializes shared emitter pool128*344 and linked lists; not a payload memset. Keep native poolNULL semantics separate from host readiness of a burn control. Shared pool lifetime/pressure across all emitter users remains required for full parity.
int rf_particle_emitter_system_initialize()
{
  int i; // [esp+0h] [ebp-4h]

  unk_867904 = 0;
  rf_particle_emitter_definitions_load_table();
  unk_867E20 = dword_867CD8;
  unk_867E24 = dword_867CD8;
  dword_867A50 = (int)dword_867908;
  unk_867A54 = dword_867908;
  for ( i = 0; i < 128; ++i )
  {
    unk_867F7C[86 * i] = unk_867E24;
    unk_867F78[86 * i] = (int)dword_867CD8;
    *(_DWORD *)(unk_867E24 + 328) = &byte_867E30[344 * i];
    unk_867E24 = &byte_867E30[344 * i];
  }
  dword_867C60 = (int)&dword_867C60;
  unk_867C64 = &dword_867C60;
  return atexit(rf_particle_emitter_definitions_exit_cleanup);
}

