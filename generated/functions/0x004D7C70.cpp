// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D7C70 rf_physics_state_release_sphere_array_storage
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion integration, selected-row transforms, angular/tensor updates, contact velocity response and x87 gates): Cdecl physics-state P (object136). Delegates ECX=P252 to pointer-array release-storage517F40,returns that helper EAX bits. This releases24-byte sphere-record collection storage at object388;no own element cleanup,other-state reset or object free. No NULL check.
void **__cdecl rf_physics_state_release_sphere_array_storage(int a1)
{
  return rf_pointer_array_release_storage((void **)(a1 + 252));
}

