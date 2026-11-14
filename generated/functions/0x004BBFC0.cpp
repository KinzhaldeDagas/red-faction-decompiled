// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BBFC0 rf_object_release_owned_model_handle
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, object lifetime/free-slot/attachment/render chains, original dispatch tables and field widths and native
// signed/x87/stack/callback ABI): One required common-object pointer. If flags DWORD+124 bit0x400 is clear and model DWORD+128 nonnull, calls564280 with that handle as one cdecl
// stack argument, then cleans four bytes. Bit0x400 suppresses destruction. Does not clear model field, change ownership flags, or null-check object. EAX is object pointer on bit-set
// short circuit, otherwise incidental object/callee result; do not interpret as success. Full deletion4B73B0 invokes this after physics sphere-storage cleanup and before emitter
// destruction.
int __cdecl rf_object_release_owned_model_handle(int a1)
{
  int result; // eax

  result = a1;
  if ( (*(_DWORD *)(a1 + 124) & 0x400) == 0 )
  {
    if ( *(_DWORD *)(a1 + 128) )
      return rf_model_handle_destroy_cdecl_adapter(*(_DWORD **)(a1 + 128));
  }
  return result;
}

