// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00419A00 rf_glare_initialize_list_load_definitions_register_shutdown
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, debris/solid ownership, glare definitions and runtime factories, native render admission and x87 unordered gates): Sets intrusive glare sentinel next/prev at0x680DA0/0x680DA4 to sentinel object0x680AE8, loads definitions0x419690, then registers name-clearing shutdown0x419A30 with atexit and returns its result. Does not reset definition count, destroy old runtime records or guard repeated initialization; count loading appends while old runtime links are lost.
int rf_glare_initialize_list_load_definitions_register_shutdown()
{
  unk_680DA0 = &unk_680AE8;
  unk_680DA4 = &unk_680AE8;
  rf_glare_definitions_load_effects_table();
  return atexit(rf_glare_definition_names_clear_shutdown);
}

