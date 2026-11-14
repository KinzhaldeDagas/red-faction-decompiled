// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00507830 sub_507830
// UNREALRED VERIFIED [clutter-vclip-debris]: Returns signed inline particle count at VClip definition +0x34 (registry base 0x90DC80, stride 224); invalid negative or out-of-count ID returns 0. Confirmed by parser 0x506AF0 writing $particle count to +0x34 and spawn 0x506E20 consuming that field. This is not the code_explode flag (+0x30 bit 8).
int __cdecl sub_507830(int a1)
{
  if ( a1 < 0 || a1 >= unk_90B820 )
    return 0;
  else
    return unk_90DCB4[56 * a1];
}

