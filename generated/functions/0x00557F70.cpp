// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00557F70 rf_geomod_vertex_copy_allocate
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): Allocates44-byte vertex; writes scratch DWORD28=0, initializes incident-face DWORD array32 with capacity0, copies input XYZ0..11, and sets DWORD24=0xFFFFFFFF (decompiler NaN is bit-pattern artifact). Fields12/16/20 are not initialized here. Input need only supply XYZ; no copy of its incidence/metadata. Raw allocationNULL is dereferenced unconditionally.
float *__cdecl rf_geomod_vertex_copy_allocate(float *source)
{
  float copy_result[3]; // [esp+0h] [ebp-10h] BYREF
  float *destination; // [esp+Ch] [ebp-4h]

  destination = (float *)rf_geomod_vertex_pool_allocate_raw(rf_geomod_vertex_pool_descriptor);
  destination[7] = 0.0;
  rf_dword_array_initialize_capacity((_DWORD *)destination + 8, 0);
  rf_vector_copy(destination, copy_result, source);
  destination[6] = NAN;
  return destination;
}

