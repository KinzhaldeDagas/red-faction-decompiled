// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00442A30 rf_renderer_apply_or_suspend_level_fog_and_far_clip
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Cdecl(raw LOWBYTE suspend argument), void. Require BYTE661584 EXACT1 and FLOAT6FC34C ordered>DOUBLE0; native
// FCOMP/FNSTSW/TEST AH,41h rejects negative,zero and UNORDERED (NaN), but accepts positive infinity. Rejection calls neither far-clip nor fog setter. ANY nonzero argument first sets
// far clip from FLOAT661580 (original275), then vertex fog5732E0(enable0,R0,G0,B0,startFLOAT-1,endFLOAT-1). Argument0 first sets far clip from current FLOAT6FC34C, then RE-READS that
// global as fog end and FLOAT6FC348 as start; uses RGB bytes6FC344/345/346 zero-extended into stack slots and enable1. Far-clip outgoing slot is reused as fog end; exactly six fog
// stack words cleaned after setter. No finite check, fog-start validation, distance clamp or renderer-backend gate here; delegate owns ordered start/end and far>1 acceptance. End may
// differ between calls if state changes during first delegate. Disabling does not restore previous fog/color/clip snapshot, and writes from far helper precede any fog-helper
// validation/failure.
void __cdecl rf_renderer_apply_or_suspend_level_fog_and_far_clip(char a1)
{
  if ( byte_661584 == 1 && unk_6FC34C > 0.0 )
  {
    if ( a1 )
    {
      rf_renderer_set_far_clip_distance(flt_661580);
      rf_renderer_set_vertex_fog(0, 0, 0, 0, -1.0, -1.0);
    }
    else
    {
      rf_renderer_set_far_clip_distance(unk_6FC34C);
      rf_renderer_set_vertex_fog(1, unk_6FC344, unk_6FC345, unk_6FC346, unk_6FC348, unk_6FC34C);
    }
  }
}

