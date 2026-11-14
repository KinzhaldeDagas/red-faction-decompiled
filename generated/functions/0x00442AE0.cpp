// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00442AE0 rf_renderer_set_configured_fog_far_for_glare_pass
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, debris/solid ownership, glare definitions and runtime factories, native render admission and x87 unordered gates): Cdecl low-byte flag. Does nothing unless global byte0x661584 equals EXACTLY1 and configured far float0x6FC34C is ordered >0 (NaN skips). Nonzero input uses binary32-rounded far+far for renderer far clip and vertex-fog end; zero input uses configured far. Fog is always enabled with RGB bytes0x6FC344..346 and configured start0x6FC348. Calls far setter BEFORE fog setter, recomputing doubled far between calls. Does not mutate configuration globals, save/restore arbitrary prior renderer state, maintain nesting depth or provide a success result; false flag reapplies baseline configuration.
void __cdecl rf_renderer_set_configured_fog_far_for_glare_pass(char a1)
{
  float v1; // [esp+8h] [ebp-8h]
  float v2; // [esp+Ch] [ebp-4h]

  if ( byte_661584 == 1 && unk_6FC34C > 0.0 )
  {
    if ( a1 )
    {
      v2 = unk_6FC34C + unk_6FC34C;
      rf_renderer_set_far_clip_distance(v2);
      v1 = unk_6FC34C + unk_6FC34C;
      rf_renderer_set_vertex_fog(1, unk_6FC344, unk_6FC345, unk_6FC346, unk_6FC348, v1);
    }
    else
    {
      rf_renderer_set_far_clip_distance(unk_6FC34C);
      rf_renderer_set_vertex_fog(1, unk_6FC344, unk_6FC345, unk_6FC346, unk_6FC348, unk_6FC34C);
    }
  }
}

