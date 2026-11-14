// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062A990 rf_static_init_frontend_record_array6F26AC
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments, plainRET. Push DWORD0 and call456100 with ECX=fixed global006F26AC; ignore constructor EAX. 456100 forwards the raw zero slot to456120 with
// this receiver, returns original receiver EAX and RET4; deeper initializer field stores are not asserted here. Fixed global is an RF frontend list: fresh native UI slider/edit/list
// consumer contexts and matching47A3F0 atexit cleanup prove ownership. After normal constructor return, call CRT atexit6060D2 with exact callback62ECD0, pop4, return full raw atexit
// EAX. Callback is REGISTERED, not executed by this body. No once guard, own allocation/element traversal/prerelease, registration-result test or rollback: initialization remains if
// registration fails; repeated invocation attempts repeated registration. No locale lookup, locale object, language/ctype manipulation or floating operation. This fixed RF-container
// initialization/cleanup-registration wrapper is RF application code; false library flag cleared while all other flags preserved.
int rf_static_init_frontend_record_array6F26AC()
{
  rf_record272_array_construct(dword_6F26AC, 0);
  return atexit(rf_static_cleanup_006f26ac);
}

