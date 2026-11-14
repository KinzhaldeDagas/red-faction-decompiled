// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004541F0 rf_extras_menu_button_x_trunc_is_closed
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): No arguments, canonicalAL0/1. Truncate FLOAT buttonX6F1DB0 through605F00 then compare integer with
// current signed closed bound6F29A0; equal→AL1 else0. Not exact float position/velocity/titlebar/active-state comparison and no finite or bound validation. Fractional coordinates
// whose truncation equals the bound can report closed before exact endpoint. UpperEAX retains conversion residue exceptAL.
bool rf_extras_menu_button_x_trunc_is_closed()
{
  return (int)unk_6F1DB0 == rf_main_menu_closed_x;
}

