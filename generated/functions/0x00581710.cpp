// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581710 rf_renderer_lod_distance_scaled
// UNREALRED VERIFIED [character-pipeline-20261029]: One logical stack argument world position; returns x87 float. Backend selector0x187CC9C==102 delegates0x5C5710,else returns0. Existing inferred live st0 input is a decompiler artifact; backend computes Euclidean distance from position. Does not select LOD itself or modify thresholds.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Native cdecl ONE stack argument const float[3] world-position pointer, plainRET; no ECX receiver or incoming
// ST0 argument. Read global backend selector187CC9C; EXACT DWORD102 calls5C5710(position) with one pushed pointer then caller cleanup4, forwards returnedST0 unchanged. EVERY other
// selector value, including negative/other nonzero, executes FLDZ and returns0 throughST0 without reading/dereferencing the position argument. No additional float rounding/store,
// backend fallback search, pointer/finite check, threshold selection or result Boolean. EAX is selector/delegate incidental bits. Corrected saved integer argument to constfloat*
// while preserving existing one-argument cdecl/floating return; backend actual signature is independently corrected to one-pointer cdecl. Existing correct selector/distance
// commentary preserved.
double __cdecl rf_renderer_lod_distance_scaled(const float *position)
{
  if ( dword_187CC9C == 102 )
    return rf_renderer_backend102_lod_distance_scaled(position);
  else
    return 0.0;
}

