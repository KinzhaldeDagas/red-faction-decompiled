// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B21B0 rf_network_control_cancel_pending_state
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native buffered-motion insertion/sampling, asymmetric WORD time differences, temporary physics snapshot/restore and native list guards): Noargs;if global7B4DB8 inactive,no changes. Otherwise setsDWORD7B2624=0,7B2854=1,7B2620=-100. Does not send packet,close socket,free state or validate prior state;no defined application-level return value.
void rf_network_control_cancel_pending_state()
{
  if ( dword_7B4DB8 )
  {
    dword_7B2624 = 0;
    unk_7B2854 = 1;
    unk_7B2620 = -100;
  }
}

