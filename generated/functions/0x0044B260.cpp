// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044B260 rf_hud_message_queue_reset_metadata_and_deadline
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments. In order set headDWORD6EE6D0=0,countDWORD6EE6D4=0,activeIndexDWORD6616C8=-1, then55F020(this=deadline6EE6D8)
// disarms stored milliseconds deadline to-1. Return deadline RECEIVER pointer6EE6D8 from delegate, not count/success. Does not clear any of eight272-byte message records at6EE6E0,
// free/allocate strings, alter default color6EE6A8, stop sound or dispatch queued messages. No pause/runtime gate or rollback.
_DWORD *rf_hud_message_queue_reset_metadata_and_deadline()
{
  unk_6EE6D0 = 0;
  unk_6EE6D4 = 0;
  dword_6616C8 = -1;
  return rf_replicator_reset(unk_6EE6D8);
}

