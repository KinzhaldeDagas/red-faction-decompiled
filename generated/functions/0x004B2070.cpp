// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B2070 rf_network_control_send_fixed10_when_active
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native buffered-motion insertion/sampling, asymmetric WORD time differences, temporary physics snapshot/restore and native list guards): Noargs;globalDWORD7B4DB8==0 returns without changes. Active:storesBYTE7B4BBF=10,sends UDP channel packet(data7B4BB8,length10,arg0,endpoint7B2638,channel2),setsDWORD7B2640=1,stores scaled performance clock(1) into7B284C,setsDWORD7B4998=0. Does not check/send result,wait for reply or initialize other packet bytes here. Static header/global meanings not inferred beyond native fields;no allocations or own validation.
void rf_network_control_send_fixed10_when_active()
{
  if ( dword_7B4DB8 )
  {
    unk_7B4BBF = 10;
    rf_network_send_udp_channel_packet(&unk_7B4BB8, 0xAu, 0, (int)&dword_7B2638, 2);
    unk_7B2640 = 1;
    unk_7B284C = rf_performance_clock_elapsed_scaled(1);
    unk_7B4998 = 0;
  }
}

