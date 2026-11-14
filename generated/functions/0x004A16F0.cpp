// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A16F0 rf_client_apply_item_create_payload45
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, replication transport admission/flush policy, item packet40/43/45 codecs, identifier mapping, traffic histories and latency timing): 
// Recovered original [4A16F0,4A1B41), cdecl(payload). No own runtime/authority/game-mode/null/payload-length guard or incoming xrefs currently. Packet45 association follows exact
// paired sender layout. Scans entire source name to NUL without length bound, remembers low16 strlen; strncpy(destination,payload,255) then forces destination[254]=0, retaining at
// most254 useful characters. Remaining-field cursor starts uint16(strlen+1), NOT truncated displayed-name length; later field advances use full32-bit int cursor. Thus long names are
// consumed according to full scanned source length modulo65536 while the spawned name is truncated.
// Then reads tag BYTE, four DWORDs A/B/C/serverUID, signed slot WORD, state BYTE,3 position and9 matrix floats. Native float loads are followed by x87 fld/fstp on locals. Arms shared
// replication timer7B25EC for8000ms BEFORE spawn even if spawn fails. Calls rf_item_instance_spawn(A,truncatedName,C,-1,&position,&matrix,B,0,1). On success stores tag into item
// BYTE+40, binds serverUID to new local identifier+44, hides/marks inactive only for state EXACTLY h(104) (every other state leaves spawn state), and if signed slot0..199 stores new
// local identifier in78BF28[slot]. Does NOT update slot count78C248. Spawn failure skips binding/hide/slot update. No duplicate-id or slot collision rejection here.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, compiled registry/dispatcher and native ABI refinement): Original PE descriptor at0x00662B64 registers opcode45 (item_create), callback0x004A16F0. Native dispatcher49FB50 indirectly calls it with(payload,source endpoint),8-byte caller cleanup,after envelope/source admission; handler receives NO payload length. Thus absence of IDA direct call/xrefs does not imply a dormant handler. Compiled registration and dispatch edge verified independently of earlier paired-layout inference; actual invocation still depends on runtime admission.
void __cdecl rf_client_apply_item_create_payload45(const unsigned __int8 *payload)
{
  int v1[3]; // [esp+14h] [ebp-15Ch] BYREF
  unsigned __int8 v2; // [esp+23h] [ebp-14Dh]
  int v3; // [esp+24h] [ebp-14Ch]
  unsigned __int8 v4; // [esp+2Bh] [ebp-145h]
  int v5; // [esp+2Ch] [ebp-144h]
  __int16 v6; // [esp+30h] [ebp-140h]
  int v7[9]; // [esp+34h] [ebp-13Ch] BYREF
  char Destination[260]; // [esp+58h] [ebp-118h] BYREF
  int v9; // [esp+160h] [ebp-10h]
  int v10; // [esp+164h] [ebp-Ch]
  int v11; // [esp+168h] [ebp-8h]
  int v12; // [esp+16Ch] [ebp-4h]

  rf_vector3_default_construct_noop(v1);
  rf_matrix3_construct((char *)v7);
  v10 = 0;
  strncpy(Destination, (const char *)payload, 0xFFu);
  Destination[254] = 0;
  v10 = (unsigned __int16)(v10 + strlen((const char *)payload) + 1);
  v4 = payload[v10];
  v5 = *(_DWORD *)&payload[++v10];
  v10 += 4;
  v3 = *(_DWORD *)&payload[v10];
  v10 += 4;
  v11 = *(_DWORD *)&payload[v10];
  v10 += 4;
  v12 = *(_DWORD *)&payload[v10];
  v10 += 4;
  v6 = *(_WORD *)&payload[v10];
  v10 += 2;
  v2 = payload[v10];
  v1[0] = *(_DWORD *)&payload[++v10];
  v10 += 4;
  v1[1] = *(_DWORD *)&payload[v10];
  v10 += 4;
  v1[2] = *(_DWORD *)&payload[v10];
  v10 += 4;
  v7[0] = *(_DWORD *)&payload[v10];
  v10 += 4;
  v7[1] = *(_DWORD *)&payload[v10];
  v10 += 4;
  v7[2] = *(_DWORD *)&payload[v10];
  v10 += 4;
  v7[3] = *(_DWORD *)&payload[v10];
  v10 += 4;
  v7[4] = *(_DWORD *)&payload[v10];
  v10 += 4;
  v7[5] = *(_DWORD *)&payload[v10];
  v10 += 4;
  v7[6] = *(_DWORD *)&payload[v10];
  v10 += 4;
  v7[7] = *(_DWORD *)&payload[v10];
  v10 += 4;
  v7[8] = *(_DWORD *)&payload[v10];
  v10 += 4;
  rf_replication_timer7B25EC_arm_8s();
  v9 = rf_item_instance_spawn(v5, Destination, v11, -1, (float *)v1, (float *)v7, v3, 0, 1);
  if ( v9 )
  {
    *(_BYTE *)(v9 + 40) = v4;
    rf_replication_bind_server_id_to_local_handle(v12, *(_DWORD *)(v9 + 44));
    if ( v2 == 104 )
      rf_object_mark_hidden_inactive(v9);
    if ( (unsigned int)v6 < 0xC8 )
      dword_78BF28[v6] = *(_DWORD *)(v9 + 44);
  }
}

