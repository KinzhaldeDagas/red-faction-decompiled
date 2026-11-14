// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C3A50 rf_geomod_impact_chunks_initialize80
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, firing effect ring paired ownership, original GeoMod chunk initialization/motion, x87 threshold branches and native five-argument call ABI): 
// Cdecl no args. Active sentinel/head/tail814FB0/814FB4 self-linked, free sentinel815248/tail81524C self-linked; active count814FA4=0. Appends80 preallocated records stride652
// (0x28C) base8154D8 to free list using next0/prev4. Does not memset records, release prior runtime resources, reset collision payload or use heap allocation. Loads Foley definition
// index for exact Geomod Debris Hit via temporary RFString then destroys string. Clears ten voice slots814F78..814F9C, zeros position-sum81523C and speed-sum814FA0. Does NOT reset
// accumulated hit count814FA8 or sound deadline814FAC. Return EAX zero-vector receiver, not chunk count. Native XOR/JNZ self-loop tails are dead.
float *rf_geomod_impact_chunks_initialize80()
{
  char *v0; // eax
  float *result; // eax
  std::exception *v2; // [esp+4h] [ebp-20h]
  _DWORD v3[2]; // [esp+Ch] [ebp-18h] BYREF
  int i; // [esp+14h] [ebp-10h]
  int v5; // [esp+20h] [ebp-4h]

  rf_geomod_impact_chunk_active_head = &rf_geomod_impact_chunk_active_head;
  rf_geomod_impact_chunk_active_tail = &rf_geomod_impact_chunk_active_head;
  rf_geomod_impact_chunk_free_head = &rf_geomod_impact_chunk_free_head;
  unk_81524C = &rf_geomod_impact_chunk_free_head;
  rf_geomod_impact_chunk_count = 0;
  for ( i = 0; i < 80; ++i )
  {
    unk_8154DC[163 * i] = unk_81524C;
    unk_8154D8[163 * i] = (int)&rf_geomod_impact_chunk_free_head;
    *unk_81524C = &unk_8154D8[163 * i];
    unk_81524C = &unk_8154D8[163 * i];
  }
  v2 = (std::exception *)rf_string_construct_from_cstr(v3, "Geomod Debris Hit");
  v5 = 0;
  v0 = (char *)rf_string_object_c_str_or_empty(v2);
  dword_662DD0 = rf_foley_definition_find_name(v0);
  v5 = -1;
  rf_string_destroy_buffer(v3);
  for ( i = 0; i < 10; ++i )
    unk_814F78[i] = 0;
  result = rf_vector3_zero_return_destination(flt_81523C);
  unk_814FA0 = 0.0;
  return result;
}

