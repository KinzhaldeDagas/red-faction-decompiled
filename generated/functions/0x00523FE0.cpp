// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00523FE0 rf_decal_project_unowned_and_clear_face_candidates
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, decal polygon ownership/pools,receiver registries,light-space transforms and coverage,original ECX/stack flow and PE bytes): Cdecl nine stack arguments (context,position,orientation,dimensions,bitmap,UNUSED sixth DWORD,flags,extra,scalar). Calls521AF0(context,primaryOwner0,secondaryOwner0,position,orientation,dimensions,bitmap,alpha255,flags,extra,scalar), saves returned record pointer orNULL. Then ALWAYS clear count of global candidate arrayA7063C while retaining backing, even when allocation/projection returnedNULL. Return saved pointer EAX unchanged. Sixth argument at stack+0x14 never read; no owning-face pointer forwarded, no explicit RGB white-color call. Candidate selection may have been established globally by caller; this body does not append/select a face.
float *__cdecl rf_decal_project_unowned_and_clear_face_candidates(
        int a1,
        float *a2,
        float *a3,
        float *a4,
        int a5,
        int a6,
        int a7,
        int a8,
        float a9)
{
  float *volume_and_project; // [esp+4h] [ebp-4h]

  volume_and_project = rf_world_decal_create_volume_and_project(a1, 0, 0, a2, a3, a4, a5, 255, a7, a8, a9);
  rf_pointer_array_clear_count_keep_storage(unk_A7063C);
  return volume_and_project;
}

