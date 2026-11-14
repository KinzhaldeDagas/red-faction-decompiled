// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00578490 rf_bitmap_animation_next_generation_wrapped
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitmap records/animation rates, decoded-handle tag test, tile descriptor offsets and text-parser ownership): No args. Saves and returns OLD signed32 counter663F1C,then increments it. If incremented value SIGNED>limit663F20,resets NEXT counter to1. Default PE counter1,limit178956;ordinary sequence1..178956 then1. Does not pre-clamp existing counter,guard signed overflow,validate limit,lock or inspect live entries. Consumed by animation handle formula3000*generation+slot OR40000000.
int rf_bitmap_animation_next_generation_wrapped()
{
  int v1; // [esp+0h] [ebp-4h]

  v1 = dword_663F1C++;
  if ( dword_663F1C > dword_663F20 )
    dword_663F1C = 1;
  return v1;
}

