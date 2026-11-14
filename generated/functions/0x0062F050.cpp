// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062F050 rf_static_cleanup_0070046c
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native complete 6-instruction/15-byte body independently matched to original PE. No consumed arguments, plain RET. Set ECX to FIXED global receiver0070046C,
// call0047A3F0(rf_pointer_array_destroy_backing_storage) once, then return without further EAX assignment. Exact static receiver, not an incoming object or pointer loaded FROM that
// address. Registered with atexit by original PUSH at0x0062C1DF. Wrapper adds no NULL/ready/count guard, allocation, outer-object delete, count/header reset or unwind frame; cleanup
// ownership remains the verified callee contract. Returned EAX is delegate residue, not a promised success status. Delegate conditionally operator-deletes ONLY backing pointer at
// receiver+8. It does not destroy pointees or reset pointer/count/capacity, so repeated destruction is not made safe.
void __cdecl rf_static_cleanup_0070046c()
{
  rf_pointer_array_destroy_backing_storage((void **)rf_material_bitmap_prefix_registry);
}

