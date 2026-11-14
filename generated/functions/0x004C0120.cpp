// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C0120 rf_intrusive_slist_push_front
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, fixed object-pool ownership and signed drain arithmetic, intrusive pair lists, allocation dispatch and native x87/register ABI): Thiscall header(head0,count4), node pointer stack word,RET4. INCREMENTS count first, writes node.next0=oldHead then publishes head=node, returns header. Does not clear node payload, validate ownership/null/duplicate insertion or allocate/free storage.
_DWORD *__thiscall rf_intrusive_slist_push_front(_DWORD *this, _DWORD *a2)
{
  ++*(this + 1);
  *a2 = *this;
  *this = a2;
  return this;
}

