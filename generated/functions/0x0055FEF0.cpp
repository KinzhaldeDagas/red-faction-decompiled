// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055FEF0 rf_string_logical_not_is_empty
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): Directly returns rf_string_is_empty result, not negation of that result. Empty predicate true when stored extent<=0 OR buffer[0]==NUL; positive extent dereferences buffer without null guard. Does not calculate strlen, free or modify string.
unsigned __int8 __thiscall rf_string_logical_not_is_empty(const void *this)
{
  return rf_string_is_empty((int *)this);
}

