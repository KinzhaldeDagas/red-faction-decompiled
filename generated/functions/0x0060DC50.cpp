// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060DC50 __ms_p5_test_fdiv
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs full BOOL0/1 Pentium divide diagnostic under
// LIVE x87 control/status/stack environment. Original binary64 constants648F78=4195835 and648F80=3145727. Copy both through stack doubles; FLD numerator,FDIV denominator,FMUL
// denominator,FSUBR original numerator; FSTP residual to binary64 local. FLD1,FCOMP residual,pop comparison operand,FNSTSW AX,TEST AH,5; odd parity of masked bits ->1,even ->0. For
// ordinary completed x87 comparison this means ordered residual>1 returns1,ordered<=1/unordered returns0. Exact native parity/status test recorded,not a guaranteed CPU-only result
// independent of precision/rounding. No x87 controlword save/load,exception masking/clearing or SEH. Normal own pushes/pops balance x87 depth but require available stack capacity; FP
// arithmetic/conversions can change status or trap. No global result/cache update,processor iteration or API call.
BOOL _ms_p5_test_fdiv()
{
  return 4195835.0 - 4195835.0 / 3145727.0 * 3145727.0 > 1.0;
}

