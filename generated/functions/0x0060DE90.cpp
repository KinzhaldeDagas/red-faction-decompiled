// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060DE90 __startTwoArgErrorHandling
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Internal error adapter: establish EBP frame/reserve32bytes, save incomingEAX at local-32; copy original stack DWORDs at EBP+24/+28 to locals-16/-12, then JMP
// shared60DEB0 ContinueErrorHandling WITHOUT own RET/frame teardown. No argument/pointer validation or final error policy in23-byte body. Shared continuation retains this frame;
// boundaries left intact and downstream handler is not counted as decoded here.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Completed shared-continuation review: same EBP=S-12
// borrowed frame as unary adapter; own prelude saves error type and copies original second DOUBLE at EBP+24/+28 into C record arg2 offsets+16/+20. Jump60DEB0 stores proposed result
// ST0 into record.retval, ECX name, first original DOUBLE from EBP+16/+20, invokes87except(operation,&record,&CW), reloads result and optionally originalCW,LEAVE/RET. No ordinary new
// argument block or own4/8/24-byte purge. Historical void() declaration does not describe this multi-entry frame/x87 protocol; native contract recorded rather than inventing ordinary
// args that make caller decompilation regress.
void _startTwoArgErrorHandling()
{
  JUMPOUT(0x60DEB0);
}

