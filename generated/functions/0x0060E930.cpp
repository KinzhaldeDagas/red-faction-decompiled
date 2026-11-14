// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060E930 ?CallUnexpected@@YAXPBU_s_ESTypeList@@@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noreturn cdecl(const two-DWORD exceptionSpec* stack
// slot), argument consumed by catch funclet though absent in flattened pseudocode. EH_prolog3_catch receives EAX=own frame-handler6298F3 and stack localSize4. Before try: getptd;
// existing DWORD PTD+94h nonzero ->inconsistency. Arm state0, call noreturn unexpected (thread callback then terminate if missing/returns). Original PE fallback60E958..60E961,
// currently outside own chunk inventory, sets state-1 then terminate if unexpected unexpectedly returns. Own C++ FuncInfo65EB78 magic19930522,maxState2,unwindMap65EB54
// actionsNULL,nTry1,map65EB64 states0..0/catchHigh1,one catch-all HandlerType65EB44 attributes40/typeNULL/handler60E961. Catch funclet60E961: getptd, save ORIGINAL stack
// exceptionSpec pointer into PTD+94h, stdcall CxxThrowException(NULL,NULL) to rethrow; no normal return. Frame-handler chunk6298F3 checks cookie from registration-14h
// XOR(registration+Ch), sets EAX=FuncInfo, tail-JMP CxxFrameHandler3. No own spec membership test/destruction/reset of PTD+94h; downstream handler search owns enforcing replacement
// exception against saved spec. No locking or input validation. Preserve existing three chunks; table/fallback bytes independently verified.
void __cdecl __noreturn CallUnexpected(const _DWORD *a1)
{
  if ( _getptd()[37] )
    _inconsistency();
  unexpected();
}

