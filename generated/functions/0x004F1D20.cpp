// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F1D20 rf_frontend_reset_character_theme_and_clock
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI panel switches,startup/frame/shutdown state,shared position codec boundaries and native return/argument ABI,original ECX/stack flow and PE bytes): Calls character-system cache-header reset(-1), default UI theme initialization once, then performance-clock elapsed/scaled helper(1000). Stores returned DWORD into88E448 and returns same EAX. No clock reset in this body, load-progress return, level spawn or error checks.
int rf_frontend_reset_character_theme_and_clock()
{
  int result; // eax

  rf_character_system_reset_cache_headers(-1);
  rf_ui_initialize_default_theme_once();
  result = rf_performance_clock_elapsed_scaled(1000);
  unk_88E448 = result;
  return result;
}

