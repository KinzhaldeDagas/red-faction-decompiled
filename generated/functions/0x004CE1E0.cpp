// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CE1E0 rf_particle_emitter_definitions_exit_cleanup
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, particle pool/list ownership, native damage admission, emitter initialization and cleanup): 
// Cdecl atexit callback registered by emitter system initialization. Signed loop i=0..count(0x867904)-1 calls raw operator delete on definition pointer table 0x867800[i], then
// assigns empty C string at original PE address 0x63BE29 to RFString name slot 0x867A60+8*i. Does not null freed pointer slots, reset count, detach live emitters, or guard repeated
// cleanup; a repeated invocation with unchanged count/pointers can delete them again. No explicit definition destructor or bitmap teardown here.
void __cdecl rf_particle_emitter_definitions_exit_cleanup()
{
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < unk_867904; ++i )
  {
    operator delete((void *)dword_867800[i]);
    rf_string_assign_from_cstr((_DWORD *)(8 * i + 8813152), (char *)byte_63BE29);
  }
}

