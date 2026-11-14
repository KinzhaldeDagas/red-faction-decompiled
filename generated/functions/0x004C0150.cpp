// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C0150 rf_intrusive_slist_remove_with_previous
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, fixed object-pool ownership and signed drain arithmetic, intrusive pair lists, allocation dispatch and native x87/register ABI): Thiscall header plus target,previous pointers,RET8. Decrements count BEFORE validation (there is none), writes previous.next=target.next, clears target.next0, returns target. Does not check previous actually links target, handle head specially, free payload or clamp underflow.
_DWORD *__thiscall rf_intrusive_slist_remove_with_previous(_DWORD *this, _DWORD *a2, _DWORD *a3)
{
  --*(this + 1);
  *a3 = *a2;
  *a2 = 0;
  return a2;
}

