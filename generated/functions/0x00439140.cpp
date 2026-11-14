// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00439140 rf_entity_choose_definition_lod
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(world position pointer,signed definition index). Reject index<0 OR index>live global681E14 with
// fullEAX-1; equality==count is ADMITTED (native inclusive upper bug), no capacity75/alignment guard. Invalid branch XOR ECX,ECX/JNZ backedge cannot loop. For admitted index
// use683548+5396*index, call581710(position), store ST0 to FLOAT32 distance. Signed i=0..<definition DWORD5048 re-reads count every bound; stop ONLY when
// thresholdFLOAT[definition+5052+4*i] is ORDERED strictly>stored distance. Equality, less OR UNORDERED advances; no threshold ordering/NaN normalization. Returns first stopping index
// or signed count exhaustion; nonpositive count returns0, NaN distance can traverse entire positive count. No model selection/render, pointer/threshold-count validation or state
// writes; return is LOD index, not success.
int __cdecl rf_entity_choose_definition_lod(const float *position, int definition_index)
{
  char *v3; // [esp+0h] [ebp-Ch]
  float v4; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  if ( definition_index < 0 || definition_index > dword_681E14 )
    return -1;
  v3 = &rf_entity_info_definitions[5396 * definition_index];
  v4 = rf_renderer_lod_distance_scaled(position);
  for ( i = 0; i < *((_DWORD *)v3 + 1262) && *(float *)&v3[4 * i + 5052] <= (double)v4; ++i )
    ;
  return i;
}

