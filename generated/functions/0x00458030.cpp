// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00458030 rf_record272_array_append_by_value
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Private thiscall-style ECX receiver plus272 bytes BY VALUE on incoming stack; RET0110 consumes68DWORD slots. This is one opaque272-byte record, not a pointer
// or the old63-slot inferred prototype. If countDWORD0 equals capacityDWORD+4 EXACTLY, calls456050 with capacity*2 (wrapped SHL1) when capacity nonzero, else16. Count>capacity does
// NOT trigger grow. Captures old count, increments/stores count with32-bit wrap BEFORE copy; REP MOVSD copies68DWORDs from incoming stack record atEBP+8 to backing+272*oldCount.
// Returns old index fullEAX, preserving ESI/EDI. No constructor/destructor, deep copy, source pointer dereference, count/overflow/null/range check or rollback. The earlier raw-word signature was an ABI-only approximation; the appended verified aggregate-type contract supersedes its argument representation and supplies proven field offsets.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Fresh producers/row consumers prove RFFrontendRecord272: packed alignment4, char filename[260] at0, signed64 timestamp at260, FLOAT elapsed_seconds at268,
// total272 bytes.458030 receives ONE such record BY VALUE after ECX receiver and consumes272 stack bytes viaRET0110; replacing prior68-scalar-word ABI approximation with this exact
// aggregate. Core native behavior unchanged: grow only count==capacity (double nonzero capacity else16), increment count before shallow272-byte REP MOVSD, return old index.456160
// fills timestamp by sign-extending nodeDWORD+52 and elapsed float via4F35B0, row functions pass record+260 to localtime64 and derive h:m:s from+268. No inferred padding, deep
// ownership, extra fields or field initialization guarantee; filename bytes after NUL may remain stale/uninitialized but are copied by value.
int __thiscall rf_record272_array_append_by_value(void *self, struct RFFrontendRecord272 value)
{
  int v3; // [esp+8h] [ebp-10h]
  int v5; // [esp+10h] [ebp-8h]

  if ( *(_DWORD *)self == *((_DWORD *)self + 1) )
  {
    if ( *((_DWORD *)self + 1) )
      v3 = 2 * *((_DWORD *)self + 1);
    else
      v3 = 16;
    rf_record272_array_reallocate_shallow(self, v3);
  }
  v5 = (*(_DWORD *)self)++;
  qmemcpy((void *)(272 * v5 + *((_DWORD *)self + 2)), &value, 0x110u);
  return v5;
}

