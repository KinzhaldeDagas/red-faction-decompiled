// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00490150 rf_multiplayer_arm_deadline_704F0C_450ms
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, multiplayer session dispatch and deadlines, reliable-peer timeout and acceptance, rename payload ordering, disabled native drawing and wrapped network-id allocation): 
// Cdecl no arguments. Calls replicator_arm_milliseconds(receiver704F0C,450),returns delegate EAX. Uses wrapped game-clock deadline,not performance-clock timeout. No immediate
// send,player mutation or elapsed check here; purpose beyond observed timer and caller is not guessed.
int rf_multiplayer_arm_deadline_704F0C_450ms()
{
  return rf_replicator_arm_milliseconds(&unk_704F0C, 450);
}

