// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00514B80 rf_mesh_decal_query176_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projected mesh decal pools,shadow records,x87 unordered filters and recovered no-op constructors,original ECX/stack flow and PE bytes): Thiscallquery176,returnreceiver,no stackargs. Invoke six16-byte no-op plane-prefix defaults0..95,then4E2AE0 request80 constructor at+96. Thus planes remain untouched;payload initializes owner96=0,texture100=-1,radius104=+0,start108/end120 fromglobal17F10B0,basis132=identity,flags168=2. SelectorDWORD172 remains untouched. Does not initialize whole176-byte record or allocate pools.
char *__thiscall rf_mesh_decal_query176_construct(char *this)
{
  rf_vector_construct_no_unwind(this, 0x10u, 6, rf_vector_prefix_construct_noop);
  rf_mesh_decal_request80_construct(this + 96);
  return this;
}

