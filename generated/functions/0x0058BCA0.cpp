// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058BCA0 rf_input_enable_scan41_modifier
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scan-state arrays, timestamps and queue control flow): Recovered no-argument function writing byte193B683=1. Allows held scan41 to contribute event/modifier bit0x0800. No lock, initialized guard or state/FIFO reset.
void __cdecl rf_input_enable_scan41_modifier()
{
  byte_193B683 = 1;
}

