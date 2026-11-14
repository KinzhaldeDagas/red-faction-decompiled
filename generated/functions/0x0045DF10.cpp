// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045DF10 rf_rfstring_delete_with_scalar_or_vector_flags
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, allocation/header ownership, exception and callback stack ABI, original rule tables and UI/flag apply
// ordering): ECX RFString/address of first8-byte array element,stack flags (only masks1/2 consumed),RET4. flags&2 ->compiler EH vector destructor
// iterator(base,8,countDWORD[base-4],rf_string_destroy_buffer);then flags&1 ->operator delete(base-4);return base-4 regardless deallocation bit. Without bit2,destroy ONE RFString
// atbase;flags&1 ->operator delete(base);return base. Header count governs array extent,not live count from external container. No NULL/header/extent checks;other flag bits ignored.
// Return may be freed address,not live object/status. Native clear/reallocate consumers pass3 to destroy all header-count constructed slots and release allocation.
char *__thiscall rf_rfstring_delete_with_scalar_or_vector_flags(char *this, char a2)
{
  if ( (a2 & 2) != 0 )
  {
    `eh vector destructor iterator'(this, 8u, *((_DWORD *)this - 1), rf_string_destroy_buffer);
    if ( (a2 & 1) != 0 )
      operator delete(this - 4);
    return this - 4;
  }
  else
  {
    rf_string_destroy_buffer(this);
    if ( (a2 & 1) != 0 )
      operator delete(this);
    return this;
  }
}

