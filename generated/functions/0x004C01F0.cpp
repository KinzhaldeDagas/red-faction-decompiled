// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C01F0 rf_intrusive_node_get_next_stdcall
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, fixed object-pool ownership and signed drain arithmetic, intrusive pair lists, allocation dispatch and native x87/register ABI): One pointer stack argument,RET4 stdcall. Reads/returns DWORD node+0, no ECX receiver requirement or mutation. No pointer validation, traversal, count update or allocation.
int __stdcall rf_intrusive_node_get_next_stdcall(int a1)
{
  return *(_DWORD *)a1;
}

