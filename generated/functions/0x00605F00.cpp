// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00605F00 __ftol2_sse
// UNREALRED VERIFIED [nonworld-byte-rgb-20260903]: Converts the x87 input to an integer with truncation toward zero: the enabled fast path uses CVTTSD2SI, while the disabled path jumps to __ftol2 at 0x00605F36.
unsigned int __usercall _ftol2_sse@<eax>(double a1@<st0>)
{
  if ( unk_2021F64 )
    return (int)a1;
  else
    return _ftol2(a1);
}

