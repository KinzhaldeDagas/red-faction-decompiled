// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F1460 rf_ui_auxiliary_record_scalar_delete
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): ECX receiver plus one DWORD stack flag slot, RET4. Always calls5F1DF0 receiver-save no-op first; native helper does not dereference or clean object. Test
// flag bit0 (fullDWORD MOV/AND1; other bits ignored), if set cdecl operator delete6060E9(self), ADD4. Return ORIGINAL receiver in EAX even when storage freed. No field reset, child
// destruction, unlink or array-cookie handling. Actual owner5F0F30 unlinks doubly-linked auxiliary record, clears its links and calls this with flag1; this wrapper does not perform
// unlinking. Existing char formal observes same bit0; stack slot remains4 bytes.
void *__thiscall rf_ui_auxiliary_record_scalar_delete(void *this, char a2)
{
  rf_saved_receiver_noop_5F1DF0();
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

