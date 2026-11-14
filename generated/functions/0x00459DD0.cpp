// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00459DD0 rf_main_menu_multiplayer_cancel
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No consumed arguments. Only saves/restores EBP then plain RET. No state writes, calls, stack-argument cleanup or result normalization. Existing
// multiplayer-cancel callback role retained without inventing cancellation side effects.
void rf_main_menu_multiplayer_cancel()
{
  ;
}

