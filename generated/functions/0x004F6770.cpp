// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F6770 rf_snapshot_quantize_float_times32
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] Multiply supplied float seconds by double32.0 then __ftol2_sse truncation toward zero; return integer. Event-state header stores only low16 bits, without saturation. This helper itself returns full integer rather than explicitly masking to16 bits.
// UNREALRED VERIFIED [object-entity-snapshot-continuation-20261027] Unit clarification/corrected general name: arithmetic multiplies any supplied float by32.0 and truncates toward zero. Event-delay packing uses seconds, while common-object velocity vector packing0x4F6840 reuses same helper per velocity component. No units enforcement or saturation in function. Earlier seconds-specific name referred to one caller only.
int __cdecl rf_snapshot_quantize_float_times32(float a1)
{
  return (int)(a1 * 32.0);
}

