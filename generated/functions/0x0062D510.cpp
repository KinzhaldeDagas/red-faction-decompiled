// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062D510 rf_static_construct_weapon_records64_register_cleanup
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weapon contact/decal control flow,ammo registry,rail trail pool,constructor layout and native argument/return ABI,original ECX/stack flow and PE bytes): Recovered previously unrecognized code62D510..62D53D, original PE bytes verified. Calls EH vector constructor6065FA(base912000,stride1360,count64,constructor512270,destructor512440), then registers62F4F0 with atexit. Returns atexit EAX. Fixed physical64 records independent of runtime parsed weapon count; does not parse/load records or initialize numeric fields itself.
int __cdecl rf_static_construct_weapon_records64_register_cleanup()
{
  `eh vector constructor iterator'(
    rf_weapon_records,
    0x550u,
    64,
    (void (__thiscall *)(void *))rf_weapon_record1360_construct,
    (void (__thiscall *)(void *))rf_weapon_record1360_destroy_members);
  return atexit(rf_static_destroy_array_00912000);
}

