// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046F8C0 rf_ui_copy_modal_edit_text
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Cdecl(destination,capacityDWORD),return strlen(destination). Native source is INLINE buffer address6F8E00 (PUSH immediate),NOT pointer loaded from
// MEMORY[6F8E00] despite decompiler notation. strncpy(dest,inlineBuffer,capacity-1),then dest[capacity-1]=NUL,then full destination scan to compute returned length. Positive capacity
// retains at mostcapacity-1;capacity0/negative not rejected,so count converts huge and terminator can precede destination. No dest/source validation,sanitization,modal
// acceptance/running-state check,owned allocation or source clear. Password-confirm passes256;does not itself send or validate credentials.
unsigned int __cdecl rf_ui_copy_modal_edit_text(char *Destination, int a2)
{
  strncpy(Destination, MEMORY[0x6F8E00], a2 - 1);
  Destination[a2 - 1] = 0;
  return strlen(Destination);
}

