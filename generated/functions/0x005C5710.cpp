// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C5710 rf_renderer_backend102_lod_distance_scaled
// UNREALRED VERIFIED [character-pipeline-20261029]: One logical stack argument position3f,returns x87 FLOAT. Calls rf_vector_distance(position,global camera point0x18CD4A8),multiplies0x18CD3C4,divides0x18CD3BC,rounds through float local. Actual assembly uses distance return in st0; inferred additional st0 input is misleading. No denominator-zero,pointer or finite-value check. This is scaled Euclidean distance,not view-space Z.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Native cdecl ONE stack argument const float[3] world position, caller cleans4, plainRET; NO incoming ST0
// parameter. Calls559890(position,global camera point18CD4A8), consumes its Euclidean-distance ST0 RETURN, then FMUL DWORD18CD3C4 followed by FDIV DWORD18CD3BC, no intermediate float
// stores between these two operations. FSTP DWORD local at5C5731 then FLD sameDWORD5C5734 returns FLOAT32-rounded scaled distance throughST0 despite saved double return spelling.
// Corrected false usercall(double incomingST0,int) signature to one-pointer cdecl; decompiler void result is also false:581710 forwards returnedST0 unchanged to439140, which stores
// it. No own backend-selector test, source/global mutation, denominator-zero/pointer/finite checks, clamp, threshold selection, view-space-Z substitute or success EAX. Native
// zero/negative/NaN/infinite global factors retain their arithmetic/control-environment behavior. Existing correct distance/rounding commentary preserved.
double __cdecl rf_renderer_backend102_lod_distance_scaled(const float *position)
{
  return (float)(rf_vector_distance(position, unk_18CD4A8) * unk_18CD3C4 / unk_18CD3BC);
}

