// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00403A80 rf_ai_release_embedded_route_and_pointer_array
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Cdecl(required AI block). Calls route reset40ECC0(block+744), then releases pointer-array storage517F40 with ECX=block+524. The
// second delegate first zeros array DWORD+0/+4, operator-deletes nonnull backing pointer+8 and then zeros+8; it does not delete pointed-to elements. Required block and embedded
// objects have no own null/type guards. Return EAX is the array object address block+524 from the final delegate, not a success predicate. No numeric mode or secondary-state writer
// is called directly.
void **__cdecl rf_ai_release_embedded_route_and_pointer_array(int a1)
{
  rf_ai_route_reset(a1 + 744);
  return rf_pointer_array_release_storage((void **)(a1 + 524));
}

