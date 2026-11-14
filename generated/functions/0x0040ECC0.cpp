// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040ECC0 rf_ai_route_reset
// UNREALRED VERIFIED [ai-goto-event-20260826]: Resets the embedded route state. Goto calls it after initial admission failure and again after each failed mode-2 retry; it does not erase owner +0x6EC destination.
int __cdecl rf_ai_route_reset(int a1)
{
  sub_40DC00(a1);
  return 0;
}

