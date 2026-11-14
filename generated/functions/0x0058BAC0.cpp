// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058BAC0 rf_input_get_modifier_keycode_bits
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scan-state arrays, timestamps and queue control flow): Recovered no-argument helper. Uninitialized returns0. Under lock returns OR of Shift42/54=>0x1000, Alt56/184=>0x2000, Ctrl29/157=>0x4000, and scan41=>0x0800 only when modifier-enable193B683 is set. Returns modifier bits only, no base scan code or FIFO access.
int __cdecl rf_input_get_modifier_keycode_bits()
{
  int v1; // [esp+0h] [ebp-4h]

  v1 = 0;
  if ( !byte_193B680 )
    return 0;
  EnterCriticalSection(&unk_193B668);
  if ( byte_193B58A || byte_193B596 )
    v1 = 4096;
  if ( byte_193B598 || byte_193B618 )
    v1 |= 0x2000u;
  if ( byte_193B57D || byte_193B5FD )
    v1 |= 0x4000u;
  if ( byte_193B589 )
  {
    if ( byte_193B683 )
      v1 |= 0x800u;
  }
  LeaveCriticalSection(&unk_193B668);
  return v1;
}

