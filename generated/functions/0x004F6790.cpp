// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F6790 rf_snapshot_dequantize_s16_div32
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] Interpret argument as SIGNED16-bit value, divide by double32.0, round through float local, return x87 floating result. Event header delay quantization is signed1/32second, not unsigned milliseconds.
// UNREALRED VERIFIED [object-entity-snapshot-continuation-20261027] Unit clarification/corrected general name: signed16 value /32.0, float-rounded x87 result. Used by both event-delay restore and velocity-vector restore0x4F68E0. No seconds-only interpretation or normalization is inherent to this arithmetic.
double __cdecl rf_snapshot_dequantize_s16_div32(__int16 a1)
{
  return (float)((double)a1 / 32.0);
}

