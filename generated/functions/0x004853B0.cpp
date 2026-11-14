// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004853B0 rf_geomod_save_history_replay
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, geometry-operation phases, terrain/debris ownership, saved replay, native x87 gates and localized level-text lifecycle): 
// Cdecl noargs. Signed loop over current saved count6FCCF4, record32 base6FCD00. No-op construct runtime100, quaternion initially(0,0,0,1), then restore
// cutteru16->DWORD0,roomDWORD4,decode positionu16 at8->op8,unpack quaternion at20->matrix20,flagsu16 at2->DWORD56,normal3*s16 at14->op64,scaleFLOAT28->op60. Copies decoded position
// to local original-point vector, calls georegions_apply(originalPoint,op,0) and IGNORES its AL rejection result. This mode does not apply admission hardness scaling as mode1 does,
// but may update region ice/constraints/origin according to helper.
// Writes rebuilt op.position8 and constraints76/88 into36-byte sidecar for same index. Restored flags bit8 forces both constraints zero AFTER helper. Calls operation_begin(op), then
// repeats operation_step while returned AL equals EXACT1. Does not call admission, queue append, duplicate test or increment saved count itself. Saved flags were written flags|1, so
// ordinary replay suppresses physical debris; begin can still append network history/broadcast when exact server mode/authority1. No rollback on region rejection, no independent
// iteration timeout, and loop does not snapshot original saved count.
void rf_geomod_save_history_replay()
{
  float v0[3]; // [esp+0h] [ebp-C0h] BYREF
  float v1[3]; // [esp+Ch] [ebp-B4h] BYREF
  float v2[3]; // [esp+18h] [ebp-A8h] BYREF
  float copy_result[3]; // [esp+24h] [ebp-9Ch] BYREF
  float destination[3]; // [esp+30h] [ebp-90h] BYREF
  float v5[4]; // [esp+3Ch] [ebp-84h] BYREF
  __int16 *v6; // [esp+4Ch] [ebp-74h]
  _DWORD operation[2]; // [esp+50h] [ebp-70h] BYREF
  float source[3]; // [esp+58h] [ebp-68h] BYREF
  float v9[9]; // [esp+64h] [ebp-5Ch] BYREF
  int v10; // [esp+88h] [ebp-38h]
  float v11; // [esp+8Ch] [ebp-34h]
  float v12[3]; // [esp+90h] [ebp-30h] BYREF
  float v13[3]; // [esp+9Ch] [ebp-24h] BYREF
  float v14[5]; // [esp+A8h] [ebp-18h] BYREF
  int i; // [esp+BCh] [ebp-4h]

  for ( i = 0; i < rf_geomod_save_record_count; ++i )
  {
    v6 = &rf_geomod_save_records[16 * i];
    rf_geomod_operation_init((char *)operation);
    rf_float4_construct_zero_zero_zero_one(v5);
    rf_vector3_default_construct_noop(destination);
    operation[0] = (unsigned __int16)*v6;
    operation[1] = *((_DWORD *)v6 + 1);
    rf_geomod_saved_position_decode_u16((const float *)rf_world_solid, (const unsigned __int16 *)v6 + 4, source);
    rf_snapshot_unpack_quaternion_s16(v5, v6 + 10);
    rf_quaternion_to_matrix3_rows(v5, v9);
    v10 = (unsigned __int16)v6[1];
    rf_snapshot_unpack_normalized_vector_s16(v6 + 7, v12);
    v11 = *((float *)v6 + 7);
    rf_vector_copy(destination, copy_result, source);
    rf_geomod_georegions_apply(destination, operation, 0);
    rf_vector_copy((float *)&unk_6FDD50 + 9 * i, v2, source);
    if ( (v10 & 8) != 0 )
    {
      rf_vector3_zero_return_destination(v13);
      rf_vector3_zero_return_destination(v14);
    }
    rf_vector_copy((float *)&unk_6FDD5C + 9 * i, v1, v13);
    rf_vector_copy(&flt_6FDD68[9 * i], v0, v14);
    rf_geomod_operation_begin((int)operation);
    while ( rf_geomod_operation_step() )
      ;
  }
}

