// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062D650 rf_mesh_decal_vertices500_static_construct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projected mesh decal pools,shadow records,x87 unordered filters and recovered no-op constructors,original ECX/stack flow and PE bytes): Cdeclnoargs. Constructor iterator applies491340 to500records at92A6B8,stride28;callbackcalls no-op vector3default. Initializes NO vertexpayload orlinks;runtime5144D0 doeslinks. No incomingxrefs observed;doesnotestablish startupreachability.
void __cdecl rf_mesh_decal_vertices500_static_construct_noop()
{
  rf_vector_construct_no_unwind(byte_92A6B8, 0x1Cu, 500, rf_vector_prefix_construct_noop);
}

