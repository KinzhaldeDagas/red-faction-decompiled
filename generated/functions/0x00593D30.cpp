// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00593D30 rf_window_register_message_observer_unchecked
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tokenizer ownership/quote rules, native hook contracts, observer registration, startup signaling and thread-exit/calling-convention paths): Cdecl observer code pointer (currently stored as int parameter). Appends DWORD to array1BC2010 at global count1BC2144, increments count and returns OLD count/index in EAX. Message procedure594370 invokes each as cdecl(Msg,wParam,lParam) and ignores return. No NULL check, bounds check, duplicate detection, allocation, removal or critical-section acquisition. Does not invoke observer immediately or restrict to activation messages.
int __cdecl rf_window_register_message_observer_unchecked(int a1)
{
  int result; // eax

  result = unk_1BC2144;
  unk_1BC2010[unk_1BC2144++] = a1;
  return result;
}

