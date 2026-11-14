// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00453DB0 rf_extras_menu_request_stack_pop
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): No arguments, void. Calls4464A0 exactly once: push0/pop1/pending0 request, not immediate stack
// commit. No own depth/underflow check, animation, sound, callback loop or normalized return.
void rf_extras_menu_request_stack_pop()
{
  rf_ui_request_panel_stack_pop();
}

