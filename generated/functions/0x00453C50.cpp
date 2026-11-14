// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00453C50 rf_extras_menu_select_next
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): No arguments. Wrapped32 increment shared selection6F1DAC FIRST; read focus-list6F1F24 firstDWORD
// count via486DE0. Only signed incremented index>=count stores0; negative wrapped indices can remain negative and no modulo/count-positive guard is applied. Always
// play568050(event40,group0,FLOAT0,FLOAT1), returning sound-helperEAX rather than selected index. No focus-byte updates, disabled-control filtering, list dereference or active/input
// admission.
int rf_extras_menu_select_next()
{
  ++dword_6F1DAC;
  if ( dword_6F1DAC >= rf_receiver_get_first_dword(&unk_6F1F24) )
    dword_6F1DAC = 0;
  return rf_gamesound_play_event(40, 0, 0.0, 1.0);
}

