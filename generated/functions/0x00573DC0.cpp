// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573DC0 rf_bitmap_apply_configured_texture_quality
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fog output widths, channel-sum color filtering, backend dispatch, byte/int return distinctions and context startup): No args. Reads configured quality DWORD1897454 without modifying/clamping it. Maps value0->reduction1,label medium;value1->reduction2,label low;value2->reduction0,label high. Any other value retains default reduction0 and EMPTY label (PE bytes640E18 beginNUL),not high label. Always calls574390 global reduction setter,then formats Texture resolution set at %s! plusLF into260B local and appends with default console color. Not gated by console execute/help flags. EAX is console-output incidental result;no success/quality return defined.
int __cdecl rf_bitmap_apply_configured_texture_quality()
{
  char Buffer[260]; // [esp+4h] [ebp-110h] BYREF
  int v2; // [esp+10Ch] [ebp-8h]
  const char *v3; // [esp+110h] [ebp-4h]

  v3 = (const char *)&unk_640E18;
  v2 = 0;
  if ( dword_1897454 )
  {
    if ( dword_1897454 == 1 )
    {
      v3 = (const char *)&off_640E24;
      v2 = 2;
    }
    else if ( dword_1897454 == 2 )
    {
      v3 = "high";
      v2 = 0;
    }
  }
  else
  {
    v3 = "medium";
    v2 = 1;
  }
  rf_bitmap_set_global_reduction_mode(v2);
  sprintf(Buffer, "Texture resolution set at %s!\n", v3);
  return rf_console_output_append_text_lines(Buffer, nullptr);
}

