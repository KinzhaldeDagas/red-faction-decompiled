// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00570F50 rf_renderer_set_context_byte84
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, renderer/window context, capture ownership across calls, gamma precision and ramp bytes): cdecl one BYTE. Copies argument to byte187CD14 (context offset84hex),returns same raw byte throughAL. No boolean normalization,device call,readiness test or other field write. Initializer stores its eighth argument here;direct xrefs inspected reveal no consumer,so semantic option name remains unproven.
unsigned __int8 __cdecl rf_renderer_set_context_byte84(unsigned __int8 value)
{
  byte_187CD14 = value;
  return value;
}

