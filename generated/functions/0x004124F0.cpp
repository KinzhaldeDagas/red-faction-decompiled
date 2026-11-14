// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004124F0 rf_entity_destroy_members
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Native void thiscall ECX entity, no stack args/plainRET; saved old integer signature corrected. Normal cleanup order: destroy
// pointer-array backing storage at entity+5144, +2264, +2252; destroy embedded AI members via4125E0(entity+672); then common embedded members via412580(entity). No scalar operator
// delete or entity-pool unlink in this body. Staged MSVC SEH state3->2->1->0->-1 and original unwind map657E38 preserve reverse cleanup of remaining members if an earlier destructor
// unwinds; attached tails6222A0/A8/B6/C4 implement common/AI/2252/2264 cleanup. Returned register bits incidental, no success boolean or game-death effects.
void __thiscall rf_entity_destroy_members(void *self)
{
  rf_pointer_array_destroy_backing_storage((void **)self + 1286);
  rf_pointer_array_destroy_backing_storage((void **)self + 566);
  rf_pointer_array_destroy_backing_storage((void **)self + 563);
  rf_ai_destroy_members((int)self + 672);
  rf_common_object_destroy_embedded_members((int)self);
}

