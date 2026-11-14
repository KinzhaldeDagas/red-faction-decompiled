// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004918A0 rf_respawn_append_record68
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, client timeout latch and registry admission, RFString-array ownership, native lag-compensation snapshot/restore asymmetry, geometry contact limits and respawn slots): 
// Cdecl(name Cstring,raw byte tag,position3f*,matrix3*,raw flags byteA/B/C),returns0 success,-1 if signed count>=32. No lower-count or inputNULL/finite validation. Uses68-byte slot
// atbase+68*count; assigns RFString0,copies tagBYTE8,position12,matrix24,three raw bytes60/61/62,FLOAT64=-1. Does not normalize booleans or clear padding9..11/byte63. Increments
// count after writes; no raw allocation,deduplication,team filtering or spawn selection. Negative corrupted count can address before array because only upper bound checked.
int __cdecl rf_respawn_append_record68(char *Source, char a2, float *source, float *a4, char a5, char a6, char a7)
{
  float copy_result[3]; // [esp+0h] [ebp-10h] BYREF
  char *v9; // [esp+Ch] [ebp-4h]

  if ( rf_respawn_point_count >= 32 )
    return -1;
  v9 = &rf_respawn_points[68 * rf_respawn_point_count];
  rf_string_assign_from_cstr(v9, Source);
  v9[8] = a2;
  rf_vector_copy((float *)v9 + 3, copy_result, source);
  rf_matrix3_copy((float *)v9 + 6, a4);
  v9[60] = a5;
  v9[61] = a6;
  v9[62] = a7;
  *((float *)v9 + 16) = -1.0;
  ++rf_respawn_point_count;
  return 0;
}

