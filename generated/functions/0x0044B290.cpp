// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044B290 rf_hud_message_queue_expire_one_and_activate_head
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments, void/incidental EAX. If SIGNED activeIndexDWORD6616C8>=0, query55F040(deadline6EE6D8); ANYnonzero AL means
// elapsed. On elapsed: count6EE6D4-- with raw32-bit wrap, head6EE6D0=(signed32_wrap(oldHead+1))%8 using native signed-remainder sequence (negative dividend yields negative
// remainder), setactive=-1, then55F020 disarm deadline. No count>0/active<8/head bounds guard before expiry mutations; at most ONE expiry processed per invocation.  After that block,
// reread active. If signedactive>=0 return. If active<0 and signedcount<=0 return; active<0 plus signedcount>0 storesactive=CURRENT rawhead, then arm55EF80(deadline,delay). Delay
// comes from DWORD[6EE7E4+272*active], i.e. selected record+260; if CURRENT signedcount>1 use signedmin(200,storedDuration) via40D680, else full rawduration. No positive-duration
// clamp: signednegative duration can be armed, inherited wrapped-clock policy applies. Units are milliseconds on shared game-clock deadline663E90; no frame-seconds conversion. Does
// not clear expired record text/color/duration or copy records. Dynamic fields are reread around helpers; no snapshot normalization, bulk drain, new-message enqueue, draw/sound
// operation, success result or rollback.
void rf_hud_message_queue_expire_one_and_activate_head()
{
  int v0; // eax

  if ( dword_6616C8 >= 0 && rf_replicator_has_elapsed(unk_6EE6D8) )
  {
    --dword_6EE6D4;
    unk_6EE6D0 = (unk_6EE6D0 + 1) % 8;
    dword_6616C8 = -1;
    rf_replicator_reset(unk_6EE6D8);
  }
  if ( dword_6616C8 < 0 && dword_6EE6D4 > 0 )
  {
    dword_6616C8 = unk_6EE6D0;
    if ( dword_6EE6D4 <= 1 )
    {
      rf_replicator_arm_milliseconds(unk_6EE6D8, unk_6EE7E4[68 * dword_6616C8]);
    }
    else
    {
      v0 = rf_int_min_signed(200, unk_6EE7E4[68 * dword_6616C8]);
      rf_replicator_arm_milliseconds(unk_6EE6D8, v0);
    }
  }
}

