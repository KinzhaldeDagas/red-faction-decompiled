// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062D5E0 rf_mesh_decal_collections50_static_construct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projected mesh decal pools,shadow records,x87 unordered filters and recovered no-op constructors,original ECX/stack flow and PE bytes): Cdecl noargs. Calls generic vector-constructor iterator onbase9287E0,stride48,count50,callback514C40. Callbackchain is entirely no-op;no recordbytes initialized or free/active rings built. Exact body span24bytes throughRET verified against PE. No incomingxrefs observed;does not prove startup registration/reachability.
void __cdecl rf_mesh_decal_collections50_static_construct_noop()
{
  rf_vector_construct_no_unwind(
    (char *)unk_9287E0,
    0x30u,
    50,
    (void *(__thiscall *)(void *))rf_mesh_decal_collection48_construct_noop);
}

