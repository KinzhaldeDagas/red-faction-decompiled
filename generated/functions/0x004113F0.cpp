// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004113F0 rf_camera_allocate_player_slot
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Cdecl(player-object pointer), returns signed slot index0/1 or-1 for duplicate owner. Fixed SIGNED two-slot scan compares input to
// owner-player DWORD666AA4+12*i BEFORE finding free slot. Therefore inputNULL returns-1 when any slot is free; no separate null guard.4117A0 selects first owner DWORD0; negative
// result enters fatal diagnostic loop at camera.cpp line490 with literal Could not allocate camera! No more slots!, not a recoverable capacity return. Reserves slot owner=input
// BEFORE operator new(0x1494) and ECX Entity constructor412740; publishes constructed/null camera at slotDWORD0, sets stateDWORD2=0, then stores slot ADDRESS at player+196.
// Allocation-null branch continues camera member accesses without a guard; throws/failures do not roll back reserved owner/player publication. Constructor-unwind tail deletes raw
// allocation; setup-unwind tail destroys local setup members, neither restores slot globals. Assign camera record RFString+24 literal camera. Construct local setup, zero its first152
// bytes, set+0 to empty CString6311B3,+8=0,+72 identity,+16=0,+20 float1,+12 float4,+132 float5,+148 DWORD128; initialize record physics+136 from it. Explicitly zero
// vectors+2148,+2172,+2160,+2184,+2208. Resolve literal freelook camera definition index by431680 and store record+664; form record+660=683548+5396*index WITHOUT checking-1/bounds.
// Write record handle+44=0,type+36=0,BYTE+1824=1. Call speed transaction4344D0(ECX=record,request1), ignore result, then UNCONDITIONALLY overwrite record FLOAT+140 with float32(class
// FLOAT+92*record FLOAT+152/(class FLOAT+80*FLOAT1)); no zero/finite check or intermediate numerator/denominator float stores. Copy class vectors+108/+120 to record+5172/+5184 via
// vector-assignment hidden results. Resolve class RFString+48 through445780 movement-descriptor name lookup into record+2136; unknown name can storeNULL, loaded-name fallback/global
// selection follows delegate. Set roomNULL and cache current position via4BC210. Destroy local setup and return saved slot index. Camera terminology is proven by exact
// literals/source diagnostic, not inferred from neighboring AI code.
int __cdecl rf_camera_allocate_player_slot(int a1)
{
  char *v2; // eax
  char *v3; // eax
  char *v4; // [esp+4h] [ebp-DCh]
  int v5; // [esp+8h] [ebp-D8h]
  float v6[3]; // [esp+Ch] [ebp-D4h] BYREF
  float copy_result[3]; // [esp+18h] [ebp-C8h] BYREF
  void *v8; // [esp+24h] [ebp-BCh]
  char *v9; // [esp+28h] [ebp-B8h]
  int free_player_slot; // [esp+2Ch] [ebp-B4h]
  float *v11; // [esp+30h] [ebp-B0h]
  _DWORD v12[39]; // [esp+34h] [ebp-ACh] BYREF
  int i; // [esp+D0h] [ebp-10h]
  int v14; // [esp+DCh] [ebp-4h]

  for ( i = 0; i < 2; ++i )
  {
    if ( unk_666AA4[3 * i] == a1 )
      return -1;
  }
  free_player_slot = rf_camera_find_free_player_slot();
  if ( free_player_slot < 0 )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\camera\\camera.cpp",
      490,
      "Could not allocate camera!  No more slots!");
  unk_666AA4[3 * free_player_slot] = a1;
  v8 = operator new(0x1494u);
  v14 = 0;
  if ( v8 )
    v4 = rf_entity_construct_members((char *)v8);
  else
    v4 = nullptr;
  v9 = v4;
  v14 = -1;
  unk_666AA0[3 * free_player_slot] = (int)v4;
  unk_666AA8[3 * free_player_slot] = 0;
  v11 = (float *)unk_666AA0[3 * free_player_slot];
  *(_DWORD *)(a1 + 196) = &unk_666AA0[3 * free_player_slot];
  rf_string_assign_from_cstr((_DWORD *)v11 + 6, "camera");
  rf_object_setup152_construct_members((char *)v12);
  v14 = 1;
  memset(v12, 0, 0x98u);
  v12[0] = &unk_6311B3;
  v12[2] = 0;
  rf_identity_orientation_matrix((float *)&v12[18]);
  v12[4] = 0;
  *(float *)&v12[5] = 1.0;
  *(float *)&v12[3] = 4.0;
  *(float *)&v12[33] = 5.0;
  v12[37] = 128;
  rf_physics_state_initialize_from_setup((int)(v11 + 34), (int)v12);
  rf_vector3_zero_return_destination(v11 + 537);
  rf_vector3_zero_return_destination(v11 + 543);
  rf_vector3_zero_return_destination(v11 + 540);
  rf_vector3_zero_return_destination(v11 + 546);
  rf_vector3_zero_return_destination(v11 + 552);
  *((_DWORD *)v11 + 166) = sub_431680("freelook camera");
  *((_DWORD *)v11 + 165) = &rf_entity_info_definitions[5396 * *((_DWORD *)v11 + 166)];
  v11[11] = 0.0;
  v11[9] = 0.0;
  *((_BYTE *)v11 + 1824) = 1;
  sub_4344D0((int)v11, 1);
  v11[35] = *(float *)(*((_DWORD *)v11 + 165) + 92) * v11[38] / (*(float *)(*((_DWORD *)v11 + 165) + 80) * 1.0);
  rf_vector_copy(v11 + 1293, copy_result, (const float *)(*((_DWORD *)v11 + 165) + 108));
  rf_vector_copy(v11 + 1296, v6, (const float *)(*((_DWORD *)v11 + 165) + 120));
  v2 = (char *)rf_string_object_c_str_or_empty((const void *)(*((_DWORD *)v11 + 165) + 48));
  v3 = sub_445780(v2);
  *((_DWORD *)v11 + 534) = v3;
  rf_object_set_room_and_cache_position(v11, 0);
  v5 = free_player_slot;
  v14 = -1;
  rf_object_setup152_destroy_array_backing((int)v12);
  return v5;
}

