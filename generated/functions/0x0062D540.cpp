// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062D540 rf_static_construct_projectile_sentinel_register_cleanup
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weapon contact/decal control flow,ammo registry,rail trail pool,constructor layout and native argument/return ABI,original ECX/stack flow and PE bytes): Recovered previously unrecognized code62D540..62D55C, original PE bytes verified. ECX=projectile sentinel911CE8, invokes actual constructor5125B0, then registers62F510 with atexit. Returns registration EAX. No projectile ring head/self-link setup in this wrapper, model/light creation or runtime weapon initialization.
int __cdecl rf_static_construct_projectile_sentinel_register_cleanup()
{
  rf_projectile_object_construct_embedded_members(&unk_911CE8);
  return atexit(rf_static_cleanup_00911ce8);
}

