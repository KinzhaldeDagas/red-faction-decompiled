// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045DFF0 rf_two_rfstring_assign_from_object
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, allocation/header ownership, exception and callback stack ABI, original rule tables and UI/flag apply
// ordering): Thiscall destination pairECX,one source pointer stack,RET4. Assign existing RFString destination0 from source0,then destination8 from source8,return destination. Not
// construction/memcpy,does not destroy source or assign any metadata/int field. Two calls occur in order without pair-level rollback if second throws;each RFString delegate owns its
// assignment/self-alias behavior. Used by inline16-byte array append and reallocation.
_DWORD *__thiscall rf_two_rfstring_assign_from_object(_DWORD *this, int a2)
{
  rf_string_assign_from_object(this, a2);
  rf_string_assign_from_object(this + 2, a2 + 8);
  return this;
}

