// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F2670 _WinMain@16
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Application WinMain stdcall four DWORD slots, RET16; does not read the four incoming Windows arguments. Installs EH4 frame with encoded scope table65B888 and
// security cookie664BD8, initializes local result to-1, then invokes RF application_initialize_run_and_shutdown4F1D90 at try level0 and stores EAX on normal completion. Scope entry
// links filter4F26C2 and handler4F26D4: filter passes exception pointers and literal Red Faction Main to RF exception-report writer, forwarding its result; selected handler restores
// saved ESP and leaves result-1. Restores previous fs:0 frame and returns local result. Fresh PE scope table bytes prove filter/handler mapping even though pseudocode omits this
// exception path. Game entry wrapper is not CRT implementation; clear false library flag.
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  return rf_application_initialize_run_and_shutdown();
}

