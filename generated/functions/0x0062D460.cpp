// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062D460 rf_static_construct_vclip_definitions64_register_cleanup
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, VClip initialization/preloads,byte occupancy and physical array sizes,trigger suppression/member cleanup and constructor ABI,original ECX/stack flow and PE bytes): Recovered original code62D460..62D48D. Calls EH vector constructor6065FA(base90DC80,stride224,count64,constructor5079B0,destructor507A30), then registers62F4B0 with atexit and returns registration EAX. Fixed physical64 array, not loaded-count loop or table parsing/resource initialization.
int __cdecl rf_static_construct_vclip_definitions64_register_cleanup()
{
  `eh vector constructor iterator'(
    byte_90DC80,
    0xE0u,
    64,
    (void (__thiscall *)(void *))rf_vclip_definition224_construct_members,
    (void (__thiscall *)(void *))rf_vclip_definition224_destroy_members);
  return atexit(rf_static_destroy_array_0090dc80);
}

