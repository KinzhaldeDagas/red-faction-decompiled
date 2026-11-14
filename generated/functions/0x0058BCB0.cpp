// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058BCB0 rf_input_disable_scan41_modifier
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scan-state arrays, timestamps and queue control flow): Recovered no-argument function writing byte193B683=0. Suppresses scan41 contribution to modifier bit0x0800; does not clear the held scan41 byte or alter already queued keycodes. No lock or initialized guard.
void __cdecl rf_input_disable_scan41_modifier()
{
  byte_193B683 = 0;
}

