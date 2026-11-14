// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B23C0 rf_client_send_use_key_pressed_packet16
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native aggregate constructors, vector/matrix/24-byte array ownership, by-value stack arguments, contact copies and packed network messages): Cdecl BYTE argument (low8 bits),one stackslot. Builds packed4-byte message:BYTEtype16 at0,WORD payloadlength1 at1,inputBYTE at3. Delegates49FEE0(global rf_local_fpgun_player,packet,4);transport helper may reselect local player in client mode,buffer data and flush previous buffer on overflow. No direct packet send/delivery guarantee,local-player validation or response wait here. XOR/JNZ repetition blocks never taken;security-cookie check after queue. No application-level meaning assigned to payload beyond original byte;return incidental queue result.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled action packet15/16/20/28/36/46/47 registry, consumed source arguments, ownership, reload ordering and
// projectile traversal): Original descriptor16 at662A08 ->4B2490 proves previously generic BYTE payload is claimed network playerID for use_key_pressed. Existing4-byte unreliable
// local transport unchanged. Receiver finds that ID, requires current generic object to resolve, dispatches use; no body source-ID comparison or own authority gate. Original PE
// registry and full receiver establish field meaning.
int __cdecl rf_client_send_use_key_pressed_packet16(char a1)
{
  char Src; // [esp+Ch] [ebp-208h] BYREF
  __int16 v3; // [esp+Dh] [ebp-207h]
  char v4; // [esp+Fh] [ebp-205h]

  Src = 16;
  v4 = a1;
  v3 = 1;
  return rf_network_queue_unreliable_player_packet(rf_local_fpgun_player, &Src, 4);
}

