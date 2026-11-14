// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00401350 rf_ai_publish_deferred_route_context
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI firing/acquisition/probe/route-point and vector arithmetic chains, independent native review and exact
// float/stack/dataflow behavior and native signed/x87/stack/callback ABI): Cdecl(signed entity HANDLE,opaque DWORD,source point). Only signed handle>-1 admits (all negative handles
// rejected, not only-1). Resolves ENTITY then stores arithmetic resolverResult+672 to global6663D4 WITHOUT null guard; unresolved nonnegative handle therefore publishes raw0x2A0,
// notNULL. Writes opaque DWORD to6663C0 and copies all three source floats into6663E8, in that order. No validation of output context, role/pause gate or fallback. Overwrites single
// global pending entry rather than appending queue. Consumer401300 compares supplied AI pointer to6663D4 under runtime/splitscreen and invokes401260 before clearing pending. Source
// point has no null guard on admitted path.
void __cdecl rf_ai_publish_deferred_route_context(int a1, int a2, float *source)
{
  float copy_result[3]; // [esp+0h] [ebp-10h] BYREF
  int v4; // [esp+Ch] [ebp-4h]

  if ( a1 > -1 )
  {
    v4 = rf_entity_resolve_handle(a1);
    dword_6663D4 = v4 + 672;
    dword_6663C0 = a2;
    rf_vector_copy(flt_6663E8, copy_result, source);
  }
}

