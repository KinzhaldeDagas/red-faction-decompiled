// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00611A98 __lock
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(raw lock index), no status.
// Compute665280+index*8 without range/sign checks. If pointerNULL callmtinitlocknum(index); zero result invokesamsg_exit(17). If that fatal helper unexpectedly returns, continue
// anyway: re-read tablepointer andEnterCriticalSection. Existing nonNULL pointer bypasses init. No NULL revalidation after fatal callback, ownerrno, allocation, TryEnter policy or
// return-status check afterEnter.
void __cdecl _lock(int a1)
{
  if ( !*(&lpCriticalSection + 2 * a1) && !_mtinitlocknum(a1) )
    _amsg_exit(17);
  EnterCriticalSection(*(&lpCriticalSection + 2 * a1));
}

