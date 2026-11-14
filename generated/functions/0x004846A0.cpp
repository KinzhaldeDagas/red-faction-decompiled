// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004846A0 rf_geomod_operation_runtime_level_init
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, geometry-operation phases, terrain/debris ownership, saved replay, native x87 gates and localized level-text lifecycle): 
// Cdecl noargs. Loads blastmark02.tga with(-1,1), stores handle0x6FCCE4 without success check; sets operation phase0x66282C=-1. Self-links active debris sentinel0x6FDD18 and free
// sentinel0x6FF4D0. Appends32 fixed work records at0x6FEF50,stride44, to free tail; sets each solid pointer+8=0 and links+0/+4 only. Does not memset positions, axis, aspect or
// extent, free formerly owned solids, call per-record constructors, or reset subdivision static guards. Finally clears saved-admission/history count0x6FCCF4=0. Does not reset
// detached-bounds count, execution queue, network-history count or bitmap handles elsewhere. Returns pointer to last free record incidentally.
int *rf_geomod_operation_runtime_level_init()
{
  int *result; // eax
  int i; // [esp+0h] [ebp-4h]

  unk_6FCCE4 = rf_bitmap_load_with_optional_mipmap_generation("blastmark02.tga", (void *)0xFFFFFFFF, 1);
  rf_geomod_operation_phase = -1;
  rf_geomod_debris_work_active_head = &rf_geomod_debris_work_active_head;
  rf_geomod_debris_work_active_tail = &rf_geomod_debris_work_active_head;
  result = nullptr;
  rf_geomod_debris_work_free_head = &rf_geomod_debris_work_free_head;
  rf_geomod_debris_work_free_tail = &rf_geomod_debris_work_free_head;
  for ( i = 0; i < 32; ++i )
  {
    unk_6FEF58[11 * i] = 0;
    unk_6FEF54[11 * i] = rf_geomod_debris_work_free_tail;
    rf_geomod_debris_work_records[11 * i] = (int)&rf_geomod_debris_work_free_head;
    *rf_geomod_debris_work_free_tail = &rf_geomod_debris_work_records[11 * i];
    result = &rf_geomod_debris_work_records[11 * i];
    rf_geomod_debris_work_free_tail = result;
  }
  rf_geomod_save_record_count = 0;
  return result;
}

