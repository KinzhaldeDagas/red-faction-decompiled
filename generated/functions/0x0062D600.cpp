// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062D600 rf_mesh_decal_free_collection_sentinel_construct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projected mesh decal pools,shadow records,x87 unordered filters and recovered no-op constructors,original ECX/stack flow and PE bytes): Cdeclnoargs. Pass fixedreceiver929140 to514C40,no-opconstructor;returnreceiverpointer inEAX. Writes no sentinel/ring bytes. No incomingxrefs observed;runtime reset5144D0 builds actual links.
char *__cdecl rf_mesh_decal_free_collection_sentinel_construct_noop()
{
  return rf_mesh_decal_collection48_construct_noop(byte_929140);
}

