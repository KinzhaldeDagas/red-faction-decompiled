// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00464CD0 rf_browser_prompt_manual_address
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): Noarg,initially untyped ABI preserved. Show editable OK modal(title localized88E240,empty literal636855,callback464D10,editable1). Native callback address and four stack args
// verified. No parsing,allocation,endpoint insertion,query or own active-state check;confirm callback handles it.
int rf_browser_prompt_manual_address()
{
  return rf_ui_show_ok_modal(unk_88E240, (int)&unk_636855, (int)rf_browser_accept_manual_address, 1);
}

