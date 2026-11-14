// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051EB40 rf_intrusive_list_reset_head_tail
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): False Concurrency work-stealing SDK symbol. This function only clears TWO DWORDs at receiver0/4 and returns receiver. In spatial nodes this is face-list head/tail24/28. No synchronization, scheduling, allocation, or traversal; does not unlink existing elements/reciprocal owners.
_DWORD *__thiscall rf_intrusive_list_reset_head_tail(_DWORD *this)
{
  *this = 0;
  *(this + 1) = 0;
  return this;
}

