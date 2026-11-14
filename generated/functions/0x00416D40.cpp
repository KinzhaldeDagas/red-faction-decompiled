// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00416D40 rf_clutter_skin108_construct_strings
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter registry grammar/default retention,108-byte skin ownership, allocator cookies, native stack aliases and original flag-table strings): Thiscall108-byte record,no stackargs. Constructs empty8-byte RFString at0 and TWELVE more at12+8*i,using EH constructor iterator stride8/count12. DOES NOT initialize DWORD8 textureCount. All13 strings owned independently;no parse,allocation for list storage,capacity clamp or record zero-fill. Normal EAXreceiver;original class identity documented through clutter skin consumers.
void __thiscall rf_clutter_skin108_construct_strings(char *this)
{
  rf_string_construct_empty(this);
  `eh vector constructor iterator'(
    this + 12,
    8u,
    12,
    (void (__thiscall *)(void *))rf_string_construct_empty,
    rf_string_destroy_buffer);
}

