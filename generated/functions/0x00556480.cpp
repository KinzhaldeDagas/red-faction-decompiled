// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00556480 rf_generated_uv_set_world_scale
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid boundary topology, generated UV modes, selection transforms and independently recovered routine boundaries): Stores supplied float into global663E60 used as UV world-coordinate multiplier divided by bitmap dimensions. No positivity/finite checks.
void __stdcall rf_generated_uv_set_world_scale(float a1)
{
  flt_663E60 = a1;
}

