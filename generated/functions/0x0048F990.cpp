// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048F990 rf_multiplayer_receive_display_name_payload
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, multiplayer session dispatch and deadlines, reliable-peer timeout and acceptance, rename payload ordering, disabled native drawing and wrapped network-id allocation): 
// Cdecl payload pointer(no packet size parameter); no incoming xrefs currently recorded. Reads network idBYTE0,then scans incoming NUL-terminated name at+1 with UNBOUNDED strlen
// BEFORE bounded copy. strncpy(local256,name,255) followed by explicit local[254]=0,so at most254 visible characters retained. Computes16-bit parse cursor from original strlen but
// does not return consumed count.
// Finds player by id. Existing player whose name differs CASE-INSENSITIVELY: unbounded-copies old name to local260,unbounded sprintf local256 '%s is now known as %s',enqueues style5
// with empty trailing RFString,then assigns truncated new name. Case-only change leaves stored spelling unchanged. No sender ownership/id validation or length/finite packet admission
// here.
// INDEPENDENT of player lookup/name-change success,mode1 authority EXACT1 rebroadcasts opcode13 with supplied id and TRUNCATED name,total len+5,payload len+2. Thus unknown id and
// unchanged names still broadcast. No own dispatch-table attachment is inferred from missing xrefs. Return AL incidental/last helper,not normalized Boolean. Notification uses
// two8-byte by-value strings plus style,consumed by delegate; unwind protects temporary trailing string.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, compiled registry/dispatcher and native ABI refinement): Original PE descriptor at0x006629E4 registers opcode13 (name_change), callback0x0048F990. Native dispatcher49FB50 indirectly calls it with(payload,source endpoint),8-byte caller cleanup,after envelope/source admission; handler receives NO payload length. Thus absence of IDA direct call/xrefs does not imply a dormant handler. Compiled registration and dispatch edge verified independently of earlier paired-layout inference; actual invocation still depends on runtime admission.
char __cdecl rf_multiplayer_receive_display_name_payload(int a1)
{
  _DWORD *v1; // eax
  int v3[2]; // [esp-14h] [ebp-590h] BYREF
  int v4; // [esp-Ch] [ebp-588h]
  int v5[6]; // [esp-8h] [ebp-584h] BYREF
  char *p_Destination; // [esp+10h] [ebp-56Ch]
  _DWORD *v7; // [esp+14h] [ebp-568h]
  _DWORD *v8; // [esp+18h] [ebp-564h]
  _DWORD *v9; // [esp+1Ch] [ebp-560h]
  char v10; // [esp+23h] [ebp-559h]
  char *v11; // [esp+24h] [ebp-558h]
  char *v12; // [esp+28h] [ebp-554h]
  const char *v13; // [esp+2Ch] [ebp-550h]
  unsigned int v14; // [esp+30h] [ebp-54Ch]
  int v15; // [esp+38h] [ebp-544h]
  unsigned int v16; // [esp+3Ch] [ebp-540h]
  int *v17; // [esp+40h] [ebp-53Ch]
  void *v18; // [esp+44h] [ebp-538h]
  __int16 v19; // [esp+48h] [ebp-534h]
  unsigned __int16 v20; // [esp+4Ch] [ebp-530h]
  char v21; // [esp+53h] [ebp-529h]
  unsigned __int16 v22; // [esp+54h] [ebp-528h]
  unsigned __int8 Src; // [esp+58h] [ebp-524h] BYREF
  __int16 v24; // [esp+59h] [ebp-523h]
  char v25; // [esp+5Bh] [ebp-521h]
  int v26; // [esp+5Ch] [ebp-520h] BYREF
  char Buffer[256]; // [esp+258h] [ebp-324h] BYREF
  char v28[260]; // [esp+358h] [ebp-224h] BYREF
  __int16 v29; // [esp+45Ch] [ebp-120h]
  char Destination; // [esp+460h] [ebp-11Ch] BYREF
  _BYTE v31[255]; // [esp+461h] [ebp-11Bh] BYREF
  char v32; // [esp+567h] [ebp-15h]
  _DWORD *v33; // [esp+568h] [ebp-14h]
  int v34; // [esp+56Ch] [ebp-10h]
  int v35; // [esp+578h] [ebp-4h]

  v34 = 0;
  v32 = *(_BYTE *)a1;
  v34 = 1;
  v15 = a1 + 2;
  v16 = a1 + 1 + strlen((const char *)(a1 + 1)) + 1;
  v14 = v16 - (a1 + 2);
  v29 = v16 - (a1 + 2);
  strncpy(&Destination, (const char *)(a1 + 1), 0xFFu);
  v31[253] = 0;
  v34 = (unsigned __int16)(v34 + v29 + 1);
  v1 = rf_player_find_by_network_id(v32);
  v33 = v1;
  if ( v1 )
  {
    LOBYTE(v1) = rf_rf_string_not_equals_cstring_case_insensitive((int)(v33 + 2), &Destination);
    if ( (_BYTE)v1 )
    {
      v13 = rf_string_object_c_str_or_empty(v33 + 2);
      v12 = v28;
      v11 = v28;
      do
      {
        v10 = *v13;
        *v12 = v10;
        ++v13;
        ++v12;
      }
      while ( v10 );
      sprintf(Buffer, "%s is now known as %s", v28, &Destination);
      v18 = v5;
      v9 = rf_string_construct_from_cstr(v5, (char *)&byte_6393A3);
      v8 = v9;
      v35 = 0;
      v4 = 5;
      v17 = v3;
      v7 = rf_string_construct_from_cstr(v3, Buffer);
      v35 = -1;
      rf_multiplayer_notification_enqueue(v3[0], v3[1], v4, v5[0]);
      LOBYTE(v1) = (unsigned __int8)rf_string_assign_from_cstr(v33 + 2, &Destination);
    }
  }
  if ( rf_multiplayer_runtime_mode == 1 )
  {
    LOBYTE(v1) = rf_multiplayer_server_authority;
    if ( rf_multiplayer_server_authority == 1 )
    {
      Src = 13;
      v21 = v32;
      v25 = v32;
      v22 = 4;
      p_Destination = &Destination;
      v5[5] = (int)v31;
      p_Destination += strlen(p_Destination);
      v5[3] = ++p_Destination - v31;
      v20 = (_WORD)p_Destination - (unsigned __int16)v31;
      memcpy(&v26, &Destination, v20);
      v22 += v20;
      *(&Src + v22++) = 0;
      v19 = v22 - 3;
      v24 = v22 - 3;
      LOBYTE(v1) = rf_server_broadcast_packet(&Src, v22, 0);
    }
  }
  return (char)v1;
}

