// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062D620 rf_mesh_decal_polygons150_static_construct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projected mesh decal pools,shadow records,x87 unordered filters and recovered no-op constructors,original ECX/stack flow and PE bytes): Cdeclnoargs. Constructor iterator applies514C60 to150records at9291A0 withstride36. Verified callbackchain writes no recordbytes;doesnot establish vertex/free rings. No incomingxrefs observed;static initializer shape alone is not evidence of execution.
void __cdecl rf_mesh_decal_polygons150_static_construct_noop()
{
  rf_vector_construct_no_unwind(byte_9291A0, 0x24u, 150, rf_mesh_decal_polygon36_construct_noop);
}

