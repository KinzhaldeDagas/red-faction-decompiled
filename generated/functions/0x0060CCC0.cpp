// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060CCC0 _fmod
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Ten-byte standard fmod boundary: MOV EDX descriptor664D90 (original bytes length4 plus fmod and handler pointers), TAIL JMP verified616A7B ctrandisp2. TWO
// caller stackDOUBLE64 inputs, floating result ST0; descriptor is implicit EDX input to runtime. No modulo computation, NULL pointer, own frame or stack cleanup. Table/runtime own
// special-value/error/CW behavior.
double __cdecl fmod(double X, double Y)
{
  return _ctrandisp2(&unk_664D90, X, Y);
}

