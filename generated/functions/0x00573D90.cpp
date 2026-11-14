// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573D90 rf_renderer_context_construct_noop_color_members
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fog output widths, channel-sum color filtering, backend dispatch, byte/int return distinctions and context startup): ECX renderer-context pointer,no stack args,returns receiver. Calls verified RGBA no-op constructor at receiver+84 (0x54) and receiver+97 (0x61),then returns receiver. Static wrapper62E200 supplies global context187CC90,so members are current packed color187CCE4 and fogRGB187CCF1. Both callees write NO bytes;entire context storage remains unchanged by this constructor. Does not initialize dimensions,backend,flags or other context fields;generic570A00 later zeroes/initializes144B context. Corrected old integer receiver/result declaration to pointer.
void *__thiscall rf_renderer_context_construct_noop_color_members(void *self)
{
  rf_rgba8_default_construct_noop((char *)self + 84);
  rf_rgba8_default_construct_noop((char *)self + 97);
  return self;
}

