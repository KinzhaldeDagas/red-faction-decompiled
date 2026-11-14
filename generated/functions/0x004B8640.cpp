// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B8640 rf_object_counter_take_and_decrement
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, object lifetime/free-slot/attachment/render chains, original dispatch tables and field widths and native
// signed/x87/stack/callback ABI): No arguments. Loads DWORD662DC4, saves its previous 32-bit value, subtracts1 with native wrapping arithmetic, stores the new value, and returns the
// previous value in EAX. No lower bound, sentinel check or synchronization. Cleanup4B7D80 seeds this counter with0x7FFFFFFF. Name describes observed behavior without assigning an
// unproven identifier domain.
int rf_object_counter_take_and_decrement()
{
  return dword_662DC4--;
}

