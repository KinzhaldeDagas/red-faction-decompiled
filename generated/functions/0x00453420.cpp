// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00453420 rf_credits_panel_close_clear_byte6EFEB2
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): Native no-argument void callback: clears ONLY BYTE6EFEB2 to0. Does not clear
// fade-in/fade-out/exit/scroll/text/budget, free bitmap, stop music, adjust mouse or issue transition. Incoming EAX preserved; extra close-dispatch payload/option slots are ignored.
void rf_credits_panel_close_clear_byte6EFEB2()
{
  unk_6EFEB2 = 0;
}

